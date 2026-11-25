#!/usr/bin/env python3
"""Peer side of the network layer host test. Run it through run.sh, which starts it
inside a private network namespace (unshare -rn): nothing here reaches a real network.

It creates tap0 (192.168.77.1/24), starts dnsmasq (DHCP + DNS) and test servers,
then runs the test program in DHCP and in static mode and answers its READY / LISTEN
lines (ping, connect to its server). Exit status 0 when every check passed.
"""
import http.server
import os
import socket
import socketserver
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


def serve(server):
    threading.Thread(target=server.serve_forever, daemon=True).start()
    return server


# ---------------------------------------------------------------- test run

def run_test(binary, mode, failures):
    print(f'--- test_net {mode}', flush=True)
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

    tmp = tempfile.mkdtemp(prefix='net-host-test-')
    dnsmasq = subprocess.Popen([
        'dnsmasq', '--no-daemon', '--conf-file=/dev/null', '--interface=tap0', '--bind-interfaces',
        '--listen-address=' + HOST_IP, '--no-resolv', '--no-hosts', '--user=root', '--group=root',
        '--dhcp-range=192.168.77.50,192.168.77.60,255.255.255.0,1h',
        '--dhcp-option=3,' + HOST_IP, '--dhcp-option=6,' + HOST_IP,
        '--address=/test.mikroe.local/' + HOST_IP, '--address=/missing.mikroe.local/',
        '--dhcp-leasefile=' + os.path.join(tmp, 'leases'), '--pid-file=' + os.path.join(tmp, 'pid'),
        '--log-facility=' + os.path.join(tmp, 'dnsmasq.log')])

    serve(ThreadingTCP((HOST_IP, 7007), TcpEcho))
    serve(socketserver.ThreadingUDPServer((HOST_IP, 7008), UdpEcho))
    serve(ThreadingTCP((HOST_IP, 8000), Http))
    time.sleep(0.5)

    failures = []
    try:
        run_test(binary, 'dhcp', failures)
        run_test(binary, 'static', failures)
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
