#!/usr/bin/env python3
"""Peer side of the network layer host test. Run it through run.sh, which starts it
inside a private network namespace (unshare -rn): nothing here reaches a real network.

It creates tap0 (192.168.77.1/24), starts dnsmasq (DHCP + DNS) and test servers,
then runs the test program in DHCP and in static mode and answers its READY / LISTEN
lines (ping, connect to its server). Exit status 0 when every check passed.
"""
import http.server
import os
import re
import socket
import socketserver
import struct
import subprocess
import sys
import tempfile
import threading
import time

HOST_IP = '192.168.77.1'


def sh(*cmd):
    subprocess.run(cmd, check=True)


# ---------------------------------------------------------------- servers

class TcpEcho(socketserver.BaseRequestHandler):
    def handle(self):
        while True:
            data = self.request.recv(65536)
            if not data:
                return
            self.request.sendall(data)


class UdpEcho(socketserver.BaseRequestHandler):
    def handle(self):
        data, sock = self.request
        sock.sendto(data, self.client_address)


class Http(http.server.BaseHTTPRequestHandler):
    protocol_version = 'HTTP/1.1'

    def log_message(self, *args):
        pass

    def send_body(self, status, body, ctype='text/plain'):
        self.send_response(status)
        self.send_header('Content-Type', ctype)
        self.send_header('Content-Length', str(len(body)))
        self.send_header('Connection', 'close')
        self.end_headers()
        self.wfile.write(body)

    def do_GET(self):
        if self.path == '/hello':
            self.send_body(200, b'Hello from the host')
        elif self.path == '/chunked':
            self.send_response(200)
            self.send_header('Transfer-Encoding', 'chunked')
            self.send_header('Connection', 'close')
            self.end_headers()
            for part in (b'chunk one|', b'chunk two|', b'end'):
                self.wfile.write(b'%x;ext=1\r\n%s\r\n' % (len(part), part))
            self.wfile.write(b'0\r\nX-Trailer: yes\r\n\r\n')
        elif self.path == '/big':
            self.send_body(200, bytes(i % 251 for i in range(100000)), 'application/octet-stream')
        elif self.path == '/close-delimited':
            self.wfile.write(b'HTTP/1.1 200 OK\r\nConnection: close\r\n\r\nuntil the connection closes')
            self.close_connection = True
        elif self.path == '/malformed':
            self.wfile.write(b'NOT-HTTP garbage\r\n\r\n')
            self.close_connection = True
        else:
            self.send_body(404, b'not found')

    def do_POST(self):
        length = int(self.headers.get('Content-Length', '0'))
        body = self.rfile.read(length)
        ok = self.path == '/echo' and self.headers.get('X-Test') == '1' and \
            self.headers.get('Content-Type') == 'application/json'
        self.send_body(200 if ok else 400, body if ok else b'bad request')


class ThreadingTCP(socketserver.ThreadingMixIn, socketserver.TCPServer):
    allow_reuse_address = True
    daemon_threads = True


NTP_UNIX_OFFSET = 2208988800


def ntp_timestamp(t):
    seconds = int(t) + NTP_UNIX_OFFSET
    return struct.pack('!II', seconds & 0xFFFFFFFF, int((t % 1) * 2**32))


class Sntp(socketserver.BaseRequestHandler):
    """SNTP server; the address it is bound to selects its behaviour:
    .1 correct, .2 kiss-of-death, .3 only invalid answers (wrong nonce, unsynchronised)."""
    def handle(self):
        data, sock = self.request
        if len(data) < 48 or (data[0] & 7) != 3:
            return
        nonce = data[40:48]
        host = self.server.server_address[0]
        now = time.time()

        def reply(li, stratum, origin):
            head = bytes([(li << 6) | (4 << 3) | 4, stratum, 6, 0xEC]) + bytes(8) + b'TEST'
            return head + bytes(8) + origin + ntp_timestamp(now) + ntp_timestamp(time.time())

        if host.endswith('.1'):
            sock.sendto(reply(0, 2, nonce), self.client_address)
        elif host.endswith('.2'):
            sock.sendto(reply(3, 0, nonce)[:12] + b'RATE' + reply(3, 0, nonce)[16:], self.client_address)
        else:
            sock.sendto(reply(0, 2, bytes(8)), self.client_address)     # does not echo our nonce
            sock.sendto(reply(3, 2, nonce), self.client_address)        # unsynchronised


class MqttState:
    """Shared broker state; `events` is what the harness checks after the client test."""
    def __init__(self):
        self.lock = threading.Lock()
        self.clients = []
        self.events = []

    def event(self, *e):
        with self.lock:
            self.events.append(e)


MQTT = MqttState()


def mqtt_length(n):
    out = bytearray()
    while True:
        digit, n = n % 128, n // 128
        out.append(digit | (0x80 if n else 0))
        if not n:
            return bytes(out)


def mqtt_string(data):
    return struct.pack('!H', len(data)) + data


def topic_matches(filt, topic):
    f, t = filt.split('/'), topic.split('/')
    for i, part in enumerate(f):
        if part == '#':
            return True
        if i >= len(t) or (part != '+' and part != t[i]):
            return False
    return len(f) == len(t)


class MqttClient:
    def __init__(self, sock, cid):
        self.sock, self.cid, self.subs, self.lock, self.next_id = sock, cid, {}, threading.Lock(), 1

    def send(self, first, body=b''):
        with self.lock:
            self.sock.sendall(bytes([first]) + mqtt_length(len(body)) + body)

    def deliver(self, topic, payload, qos, pid=None):
        body = mqtt_string(topic.encode())
        if qos:
            if pid is None:
                pid, self.next_id = self.next_id, self.next_id % 0xFFFF + 1
            body += struct.pack('!H', pid)
        self.send(0x30 | (qos << 1), body + payload)


def mqtt_route(topic, payload, qos):
    with MQTT.lock:
        targets = [(c, max(q for f, q in c.subs.items() if topic_matches(f, topic)))
                   for c in MQTT.clients if any(topic_matches(f, topic) for f in c.subs)]
    for client, sub_qos in targets:
        try:
            client.deliver(topic, payload, min(qos, sub_qos))
        except OSError:
            pass


class MqttBroker(socketserver.BaseRequestHandler):
    """Small MQTT 3.1.1 broker (QoS 0/1, no retained messages, no sessions) with test behaviour:
    username 'bad' gets CONNACK 5, client id 'silent' never gets a CONNACK, 'noping' gets no PINGRESP;
    filter 'forbidden/...' is refused (0x80); publishing to 'cmd/big' sends the client a 2000-byte QoS 1
    message (id 0x1234) and then a small one, 'cmd/garbage' a 5-byte remaining length, 'cmd/close' closes;
    a QoS 1 'cmd/wrongack' gets a PUBACK with another packet id."""
    def handle(self):
        s = self.request

        def read(n):
            buf = b''
            while len(buf) < n:
                chunk = s.recv(n - len(buf))
                if not chunk:
                    raise EOFError
                buf += chunk
            return buf

        def packet():
            first, length, mult = read(1)[0], 0, 1
            for _ in range(4):
                b = read(1)[0]
                length += (b & 0x7F) * mult
                mult *= 128
                if not b & 0x80:
                    return first, read(length)
            raise ValueError('remaining length over 4 bytes')

        def string(body, pos):
            n = struct.unpack_from('!H', body, pos)[0]
            return body[pos + 2:pos + 2 + n], pos + 2 + n

        client, clean, will = None, False, None
        try:
            first, body = packet()
            proto, pos = string(body, 0)
            level, flags, keepalive = body[pos], body[pos + 1], struct.unpack_from('!H', body, pos + 2)[0]
            cid, pos = string(body, pos + 4)
            cid = cid.decode()
            user = password = None
            if flags & 0x04:
                wt, pos = string(body, pos)
                wm, pos = string(body, pos)
                will = (wt.decode(), wm, (flags >> 3) & 3, bool(flags & 0x20))
            if flags & 0x80:
                user, pos = string(body, pos)
            if flags & 0x40:
                password, pos = string(body, pos)
            MQTT.event('connect', cid, first, proto, level, flags, keepalive, user, password, will, pos == len(body))
            if user == b'bad':
                s.sendall(b'\x20\x02\x00\x05')
                return
            if cid == 'silent':
                while s.recv(64):
                    pass
                return
            client = MqttClient(s, cid)
            client.send(0x20, b'\x00\x00')
            with MQTT.lock:
                MQTT.clients.append(client)
            while True:
                first, body = packet()
                kind = first >> 4
                if kind == 3:
                    qos = (first >> 1) & 3
                    topic, pos = string(body, 0)
                    topic = topic.decode()
                    if qos:
                        pid = body[pos:pos + 2]
                        pos += 2
                        if topic == 'cmd/wrongack':     # acknowledges another id, never this one
                            pid = struct.pack('!H', (struct.unpack('!H', pid)[0] + 1) & 0xFFFF)
                        client.send(0x40, pid)
                    payload = body[pos:]
                    MQTT.event('publish', cid, topic, qos, bool(first & 1), len(payload))
                    if topic == 'cmd/big':
                        client.deliver('echo/big', b'B' * 2000, 1, 0x1234)
                        client.deliver('echo/small', b'after big', 0)
                    elif topic == 'cmd/garbage':
                        s.sendall(b'\x30\xFF\xFF\xFF\xFF\x7F')
                    elif topic == 'cmd/close':
                        clean = True
                        return
                    else:
                        mqtt_route(topic, payload, qos)
                elif kind == 4:
                    MQTT.event('puback', cid, struct.unpack('!H', body)[0])
                elif kind == 8 and (first & 0x0F) == 2:
                    pid, pos, codes = body[:2], 2, b''
                    while pos < len(body):
                        filt, pos = string(body, pos)
                        qos = body[pos]
                        pos += 1
                        if filt.startswith(b'forbidden/'):
                            codes += b'\x80'
                        else:
                            client.subs[filt.decode()] = min(qos, 1)
                            codes += bytes([min(qos, 1)])
                    client.send(0x90, pid + codes)
                elif kind == 10 and (first & 0x0F) == 2:
                    pid, pos = body[:2], 2
                    while pos < len(body):
                        filt, pos = string(body, pos)
                        client.subs.pop(filt.decode(), None)
                    client.send(0xB0, pid)
                elif kind == 12:
                    MQTT.event('ping', cid)
                    if cid != 'noping':
                        client.send(0xD0)
                elif kind == 14:
                    clean = True
                    return
                else:
                    MQTT.event('unexpected', cid, first)
                    return
        except (EOFError, OSError, ValueError, IndexError, struct.error) as e:
            MQTT.event('error', client.cid if client else None, repr(e))
        finally:
            if client:
                with MQTT.lock:
                    MQTT.clients.remove(client)
                MQTT.event('closed', client.cid, clean)
                if will and not clean:
                    mqtt_route(will[0], will[1], will[2])


def mqtt_checks():
    """What the broker saw of test_mqtt() in test_net.c (the main client has just disconnected)."""
    deadline = time.time() + 3
    while True:
        with MQTT.lock:
            ev = list(MQTT.events)
        if any(e[0] == 'closed' and e[1].startswith('mikrosdk-') for e in ev) or time.time() > deadline:
            break
        time.sleep(0.05)
    connects = [e for e in ev if e[0] == 'connect']
    main = next((e for e in connects if e[7] == b'user'), None)
    yield 'mqtt-connect-packet', bool(main) and main[2:5] == (0x10, b'MQTT', 4) and main[10], repr(main)
    if not main:
        return
    cid = main[1]
    yield 'mqtt-generated-client-id', re.fullmatch(r'mikrosdk-[0-9a-f]{8}', cid) is not None, cid
    yield 'mqtt-connect-fields', main[5] == 0xC2 and main[6] == 2 and main[8] == b'secret', repr(main)
    crash = next((e for e in connects if e[1] == 'crash'), None)
    yield 'mqtt-will-fields', bool(crash) and crash[9] == ('status/crash', b'offline', 1, True) and \
        crash[5] == 0x2E, repr(crash)
    yield 'mqtt-ping-sent', ('ping', cid) in ev, 'no PINGREQ from the client'
    yield 'mqtt-big-message-acked', ('puback', cid, 0x1234) in ev, 'dropped QoS 1 message not acknowledged'
    yield 'mqtt-retain-flag', ('publish', cid, 'echo/retained', 0, True, 1) in ev, 'retain flag not set'
    yield 'mqtt-clean-disconnect', ('closed', cid, True) in ev, 'no DISCONNECT'
    yield 'mqtt-nothing-unexpected', not any(e[0] == 'unexpected' for e in ev), repr(ev)


# ---------------------------------------------------------------- mDNS

MDNS_GROUP, MDNS_PORT = '224.0.0.251', 5353
T_A, T_PTR, T_TXT, T_SRV, T_ANY = 1, 12, 16, 33, 255


def dns_name(name):
    return b''.join(bytes([len(p)]) + p.encode() for p in name.split('.') if p) + b'\0'


def dns_read_name(data, pos, depth=0):
    labels = []
    while True:
        n = data[pos]
        if n & 0xC0 == 0xC0:
            if depth > 10:
                raise ValueError('compression loop')
            ptr = struct.unpack_from('!H', data, pos)[0] & 0x3FFF
            labels.append(dns_read_name(data, ptr, depth + 1)[0])
            return '.'.join(l for l in labels if l), pos + 2
        pos += 1
        if n == 0:
            return '.'.join(labels), pos
        labels.append(data[pos:pos + n].decode('utf-8', 'replace'))
        pos += n


def dns_parse(data):
    """(id, flags, questions [(name, type)], records [(name, type, value)]) with every section's records."""
    qid, flags, qd, an, ns, ar = struct.unpack_from('!6H', data, 0)
    pos, questions, records = 12, [], []
    for _ in range(qd):
        name, pos = dns_read_name(data, pos)
        qtype, _cls = struct.unpack_from('!HH', data, pos)
        pos += 4
        questions.append((name.lower(), qtype))
    for _ in range(an + ns + ar):
        name, pos = dns_read_name(data, pos)
        rtype, _cls, _ttl, rlen = struct.unpack_from('!HHIH', data, pos)
        pos += 10
        rd = data[pos:pos + rlen]
        if rtype == T_A:
            value = socket.inet_ntoa(rd)
        elif rtype == T_PTR:
            value = dns_read_name(data, pos)[0]
        elif rtype == T_SRV:
            value = struct.unpack_from('!HHH', rd) + (dns_read_name(data, pos + 6)[0],)
        elif rtype == T_TXT:
            value, i = [], 0
            while i < len(rd):
                value.append(rd[i + 1:i + 1 + rd[i]].decode())
                i += 1 + rd[i]
        else:
            value = rd
        records.append((name.lower(), rtype, value))
        pos += rlen
    return qid, flags, questions, records


class MdnsPeer:
    """Listens on 224.0.0.251:5353 (tap0): records what the stack announces, and answers probes
    for 'taken.local' as the device that already owns that name."""
    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind(('', MDNS_PORT))
        self.sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP,
                             socket.inet_aton(MDNS_GROUP) + socket.inet_aton(HOST_IP))
        self.sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_IF, socket.inet_aton(HOST_IP))
        self.lock, self.announced, self.probes = threading.Lock(), [], []
        threading.Thread(target=self.run, daemon=True).start()

    def run(self):
        while True:
            data, src = self.sock.recvfrom(2048)
            if src[0] == HOST_IP:
                continue                                    # our own queries, looped back
            try:
                _qid, flags, questions, records = dns_parse(data)
            except (ValueError, IndexError, struct.error, UnicodeDecodeError):
                continue
            with self.lock:
                if flags & 0x8000:
                    self.announced.extend(records)
                else:
                    self.probes.extend(questions)
            if not flags & 0x8000 and any(n == 'taken.local' for n, _t in questions):
                answer = dns_name('taken.local') + struct.pack('!HHIH', T_A, 0x8001, 120, 4) + \
                    socket.inet_aton(HOST_IP)
                self.sock.sendto(struct.pack('!6H', 0, 0x8400, 0, 1, 0, 0) + answer, (MDNS_GROUP, MDNS_PORT))

    def clear(self):
        with self.lock:
            self.announced, self.probes = [], []


def mdns_query(name, qtype, dest=MDNS_GROUP, timeout=1.5, flags=0):
    """Legacy unicast query (source port != 5353): the responder answers to this socket."""
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as q:
        q.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_IF, socket.inet_aton(HOST_IP))
        q.bind((HOST_IP, 0))
        q.settimeout(timeout)
        qid = int(time.time() * 1000) & 0xFFFF
        q.sendto(struct.pack('!6H', qid, flags, 1, 0, 0, 0) + dns_name(name) + struct.pack('!HH', qtype, 1),
                 (dest, MDNS_PORT))
        deadline = time.time() + timeout
        while time.time() < deadline:
            try:
                data, _src = q.recvfrom(2048)
            except socket.timeout:
                break
            rid, flags, _q, records = dns_parse(data)
            if rid == qid and flags & 0x8000:
                return records
    return None


def mdns_checks(stack_ip, host, peer):
    fqdn = host + '.local'
    with peer.lock:
        announced = list(peer.announced)
        probes = list(peer.probes)
    yield 'mdns-probed', (fqdn, T_ANY) in probes, repr(probes[:6])
    yield 'mdns-announced', (fqdn, T_A, stack_ip) in announced, repr(announced[:6])
    r = mdns_query(fqdn, T_A)
    yield 'mdns-a-multicast', r is not None and (fqdn, T_A, stack_ip) in r, repr(r)
    r = mdns_query(fqdn.upper(), T_A, dest=stack_ip)
    yield 'mdns-a-unicast-any-case', r is not None and (fqdn, T_A, stack_ip) in r, repr(r)
    r = mdns_query('_services._dns-sd._udp.local', T_PTR)
    types = sorted(v for n, t, v in r or [] if t == T_PTR)
    yield 'mdns-service-types', types == ['_http._tcp.local', '_mqtt._tcp.local'], repr(r)
    r = mdns_query('_http._tcp.local', T_PTR)
    inst = 'mikrosdk web._http._tcp.local'
    yield 'mdns-ptr', r is not None and ('_http._tcp.local', T_PTR, inst) in r, repr(r)
    r = mdns_query(inst, T_SRV)
    yield 'mdns-srv', r is not None and (inst, T_SRV, (0, 0, 80, fqdn)) in r, repr(r)
    r = mdns_query(inst, T_TXT)
    yield 'mdns-txt', r is not None and (inst, T_TXT, ['path=/', 'board=test']) in r, repr(r)
    r = mdns_query('mikrosdk mqtt._mqtt._tcp.local', T_TXT)
    yield 'mdns-txt-empty', r is not None and any(t == T_TXT and v in ([], ['']) for _n, t, v in r), repr(r)
    r = mdns_query('other-board.local', T_A, timeout=1)
    yield 'mdns-other-name-silent', r is None, repr(r)
    t0 = time.time()
    r = mdns_query(fqdn, T_A, timeout=2, flags=0x0200)       # truncated: answered after 400-500 ms
    took = time.time() - t0
    yield 'mdns-truncated-query', r is not None and (fqdn, T_A, stack_ip) in r and 0.35 < took < 1.5, \
        f'{r!r} after {took:.2f} s'


def mdns_gone_checks(host):
    r = mdns_query('_http._tcp.local', T_PTR, timeout=1)
    yield 'mdns-removed-service-silent', r is None or not any(t == T_PTR for _n, t, _v in r), repr(r)
    r = mdns_query('_mqtt._tcp.local', T_PTR)
    yield 'mdns-other-service-kept', r is not None and \
        ('_mqtt._tcp.local', T_PTR, 'mikrosdk mqtt._mqtt._tcp.local') in r, repr(r)
    r = mdns_query(host + '.local', T_A)
    yield 'mdns-host-kept', r is not None and any(t == T_A for _n, t, _v in r), repr(r)


def serve(server):
    threading.Thread(target=server.serve_forever, daemon=True).start()
    return server


# ---------------------------------------------------------------- HTTP server checks

def raw_request(ip, port, data, pause_after=None, then=b'', timeout=8):
    """Send raw bytes, optionally wait for a reply part before sending `then`; return all bytes received."""
    with socket.create_connection((ip, port), timeout=timeout) as c:
        c.sendall(data)
        got = b''
        if pause_after is not None:
            while pause_after not in got:
                chunk = c.recv(4096)
                if not chunk:
                    return got
                got += chunk
            c.sendall(then)
        while True:
            try:
                chunk = c.recv(65536)
            except ConnectionResetError:
                return got + b'<RESET>'
            if not chunk:
                return got
            got += chunk


def parse_response(raw):
    head, _, body = raw.partition(b'\r\n\r\n')
    lines = head.decode('latin-1').split('\r\n')
    status = int(lines[0].split()[1]) if lines and lines[0].startswith('HTTP/1.1 ') else 0
    headers = {k.lower(): v.strip() for k, _, v in (l.partition(':') for l in lines[1:])}
    return status, headers, body


def http_server_checks(ip, port):
    def req(method, path, body=b'', headers=''):
        h = f'{method} {path} HTTP/1.1\r\nHost: board\r\n{headers}'
        if body:
            h += f'Content-Length: {len(body)}\r\n'
        return (h + '\r\n').encode() + body

    def check(name, raw, status, body=None, extra=None):
        st, hd, bd = parse_response(raw)
        ok = st == status and (body is None or bd == body) and \
            hd.get('connection') == 'close' and hd.get('content-length') == str(len(bd))
        if ok and extra:
            ok = extra(hd, bd)
        return name, ok, f'got {st} {bd[:80]!r} headers {hd}'

    payload = bytes(range(256)) + b'{"k":"v"}' * 5
    big = bytes((i % 251) for i in range(30000))
    yield check('get-index', raw_request(ip, port, req('GET', '/')), 200, b'index page',
                lambda h, b: h.get('content-type') == 'text/html')
    yield check('query-params', raw_request(ip, port, req('GET', '/api?name=Hello+World%21&x=42')), 200,
                b'name=Hello World!;x=42')
    yield check('post-echo', raw_request(ip, port, req('POST', '/echo', payload)), 200, payload)
    yield check('body-too-large-413', raw_request(ip, port, req('POST', '/echo', b'x' * 2000)), 413)
    yield check('unknown-path-404', raw_request(ip, port, req('GET', '/nope')), 404)
    yield check('wrong-method-405', raw_request(ip, port, req('DELETE', '/')), 405)
    yield check('any-method-route', raw_request(ip, port, req('PUT', '/any')), 200, b'PUT')
    yield check('streamed-30k', raw_request(ip, port, req('GET', '/big')), 200, big,
                lambda h, b: h.get('x-pieces') == '30')
    yield check('no-response-500', raw_request(ip, port, req('GET', '/forgot')), 500)
    yield check('garbage-400', raw_request(ip, port, b'GARBAGE\r\n\r\n'), 400)
    yield check('lowercase-method-400', raw_request(ip, port, b'get / HTTP/1.1\r\n\r\n'), 400)
    yield check('header-too-large-431',
                raw_request(ip, port, req('GET', '/', headers='X-Fill: ' + 'a' * 600 + '\r\n')), 431)
    yield check('chunked-body-501',
                raw_request(ip, port, req('POST', '/echo', headers='Transfer-Encoding: chunked\r\n') + b'5\r\nhello\r\n0\r\n\r\n'), 501)
    body = b'z' * 200
    head = f'POST /echo HTTP/1.1\r\nHost: board\r\nExpect: 100-continue\r\nContent-Length: {len(body)}\r\n\r\n'.encode()
    raw = raw_request(ip, port, head, pause_after=b'100 Continue\r\n\r\n', then=body)
    interim, _, rest = raw.partition(b'HTTP/1.1 100 Continue\r\n\r\n')
    yield check('expect-100-continue', rest, 200, body) if interim == b'' else ('expect-100-continue', False, repr(raw[:80]))
    t0 = time.time()
    raw = raw_request(ip, port, b'GET / HTTP/1.1\r\nHost: ')      # stalls in the header
    took = time.time() - t0
    name, ok, detail = check('stalled-client-408', raw, 408)
    yield name, ok and 2.5 < took < 6, f'{detail} after {took:.1f} s'
    yield check('serves-after-timeout', raw_request(ip, port, req('GET', '/')), 200, b'index page')


# ---------------------------------------------------------------- test run

def run_test(binary, mode, failures, mdns_peer):
    print(f'--- test_net {mode}', flush=True)
    with MQTT.lock:
        MQTT.events.clear()
    mdns_peer.clear()
    proc = subprocess.Popen([binary, mode], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    stack_ip = None
    deadline = time.time() + 180
    for line in proc.stdout:
        line = line.rstrip('\n')
        print('   ' + line, flush=True)
        if line.startswith('FAIL'):
            failures.append(f'{mode}: {line}')
        if line.startswith('READY '):
            stack_ip = line.split()[1]
            ping = subprocess.run(['ping', '-c', '3', '-i', '0.2', '-W', '2', stack_ip], capture_output=True, text=True)
            ok = ping.returncode == 0
            print(f'   {"OK" if ok else "FAIL"} harness-ping {stack_ip}', flush=True)
            if not ok:
                failures.append(f'{mode}: ping {stack_ip} failed: {ping.stdout[-200:]}')
            proc.stdin.write('GO\n')
            proc.stdin.flush()
        elif line.startswith('HTTPSERVER '):
            port = int(line.split()[1])
            for name, ok, detail in http_server_checks(stack_ip, port):
                print(f'   {"OK" if ok else "FAIL"} harness-{name}{"" if ok else ": " + detail}', flush=True)
                if not ok:
                    failures.append(f'{mode}: http server {name}: {detail}')
            proc.stdin.write('GO\n')
            proc.stdin.flush()
        elif line == 'MDNSMARK':
            mdns_peer.clear()
            proc.stdin.write('GO\n')
            proc.stdin.flush()
        elif line.startswith('MDNSAGAIN '):
            fqdn = line.split()[1] + '.local'
            with mdns_peer.lock:
                ok = (fqdn, T_ANY) in mdns_peer.probes and (fqdn, T_A, stack_ip) in mdns_peer.announced
            print(f'   {"OK" if ok else "FAIL"} harness-mdns-after-link-change', flush=True)
            if not ok:
                failures.append(f'{mode}: mdns not probed/announced again after the link change')
            proc.stdin.write('GO\n')
            proc.stdin.flush()
        elif line.startswith('MDNS ') or line.startswith('MDNSGONE '):
            host = line.split()[1]
            checks = mdns_checks(stack_ip, host, mdns_peer) if line.startswith('MDNS ') else mdns_gone_checks(host)
            for name, ok, detail in checks:
                print(f'   {"OK" if ok else "FAIL"} harness-{name}{"" if ok else ": " + detail}', flush=True)
                if not ok:
                    failures.append(f'{mode}: {name}: {detail}')
            proc.stdin.write('GO\n')
            proc.stdin.flush()
        elif line == 'MQTTCHECK':
            for name, ok, detail in mqtt_checks():
                print(f'   {"OK" if ok else "FAIL"} harness-{name}{"" if ok else ": " + detail}', flush=True)
                if not ok:
                    failures.append(f'{mode}: {name}: {detail}')
            proc.stdin.write('GO\n')
            proc.stdin.flush()
        elif line.startswith('LISTEN '):
            port = int(line.split()[1])
            reply = b''
            try:
                with socket.create_connection((stack_ip, port), timeout=5) as c:
                    c.sendall(b'hello server')
                    while len(reply) < 12:
                        chunk = c.recv(64)
                        if not chunk:
                            break
                        reply += chunk
            except OSError as e:
                reply = repr(e).encode()
            ok = reply == b'HELLO SERVER'
            print(f'   {"OK" if ok else "FAIL"} harness-client {reply!r}', flush=True)
            if not ok:
                failures.append(f'{mode}: server reply {reply!r}')
            proc.stdin.write('GO\n')
            proc.stdin.flush()
        if time.time() > deadline:
            proc.kill()
            failures.append(f'{mode}: timed out')
            break
    rc = proc.wait(timeout=30)
    if rc != 0:
        failures.append(f'{mode}: exit status {rc}')


def main():
    if len(sys.argv) != 2:
        sys.exit('usage: harness.py <test_net binary>  (run through run.sh)')
    binary = os.path.abspath(sys.argv[1])
    if os.getuid() != 0:
        sys.exit('run inside a network namespace: unshare -rn ' + ' '.join(sys.argv))

    sh('ip', 'link', 'set', 'lo', 'up')
    sh('ip', 'tuntap', 'add', 'dev', 'tap0', 'mode', 'tap')
    sh('ip', 'link', 'set', 'tap0', 'up')
    sh('ip', 'addr', 'add', HOST_IP + '/24', 'dev', 'tap0')
    for extra in ('192.168.77.2', '192.168.77.3'):         # misbehaving SNTP servers
        sh('ip', 'addr', 'add', extra + '/24', 'dev', 'tap0')

    tmp = tempfile.mkdtemp(prefix='net-host-test-')
    dnsmasq = subprocess.Popen([
        'dnsmasq', '--no-daemon', '--conf-file=/dev/null', '--interface=tap0', '--bind-interfaces',
        '--listen-address=' + HOST_IP, '--no-resolv', '--no-hosts', '--user=root', '--group=root',
        '--dhcp-range=192.168.77.50,192.168.77.60,255.255.255.0,1h',
        '--dhcp-option=3,' + HOST_IP, '--dhcp-option=6,' + HOST_IP,
        '--address=/test.mikroe.local/' + HOST_IP, '--address=/missing.mikroe.local/',
        '--address=/ntp.mikroe.local/' + HOST_IP, '--address=/broker.mikroe.local/' + HOST_IP,
        '--dhcp-leasefile=' + os.path.join(tmp, 'leases'), '--pid-file=' + os.path.join(tmp, 'pid'),
        '--log-facility=' + os.path.join(tmp, 'dnsmasq.log')])

    serve(ThreadingTCP((HOST_IP, 7007), TcpEcho))
    serve(socketserver.ThreadingUDPServer((HOST_IP, 7008), UdpEcho))
    for ip in (HOST_IP, '192.168.77.2', '192.168.77.3'):
        serve(socketserver.ThreadingUDPServer((ip, 123), Sntp))
    serve(ThreadingTCP((HOST_IP, 8000), Http))
    serve(ThreadingTCP((HOST_IP, 1883), MqttBroker))
    mdns_peer = MdnsPeer()
    time.sleep(0.5)

    failures = []
    try:
        run_test(binary, 'dhcp', failures, mdns_peer)
        run_test(binary, 'static', failures, mdns_peer)
    finally:
        dnsmasq.terminate()

    print('=' * 60)
    if failures:
        print(f'FAILED ({len(failures)}):')
        for f in failures:
            print('  ' + f)
        sys.exit(1)
    print('ALL PASSED')


if __name__ == '__main__':
    main()
