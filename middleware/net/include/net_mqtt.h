/****************************************************************************
**
** Copyright ( C ) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** This file is part of the mikroSDK package
**
** Commercial License Usage
**
** Licensees holding valid commercial NECTO compilers AI licenses may use this
** file in accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The MikroElektronika Company.
** For licensing terms and conditions see
** https://www.mikroe.com/legal/software-license-agreement.
** For further information use the contact form at
** https://www.mikroe.com/contact.
**
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used for
** non-commercial projects under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
** OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

/*!
 * @file net_mqtt.h
 * @brief MQTT 3.1.1 client on the mikroSDK network API (plain TCP, QoS 0 and 1).
 * @details One connection per net_mqtt_t, polled: call net_mqtt_poll() from the
 * main loop after net_poll(); it delivers received messages to the callback,
 * acknowledges QoS 1 messages and keeps the connection alive (PINGREQ). The
 * connect, publish (QoS 1), subscribe and unsubscribe calls wait for the
 * broker's answer up to their timeout, delivering messages meanwhile.
 *
 * Received packets must fit into the buffer given to net_mqtt_connect();
 * larger messages are dropped (and still acknowledged) and counted in
 * net_mqtt_t.dropped. QoS 2 is not supported: subscriptions are capped at
 * QoS 1. The callback must not call net_mqtt_* functions that wait (QoS 1
 * publish, subscribe, unsubscribe); a QoS 0 publish is fine.
 *
 * @code
 * static void on_message( void *ctx, const char *topic, const uint8_t *payload, uint32_t len ) { ... }
 * static uint8_t mqtt_buffer[ 512 ];
 * static net_mqtt_t mqtt;
 *
 * net_mqtt_cfg_t cfg;
 * net_mqtt_cfg_setup( &cfg );
 * cfg.host = "broker.local";
 * if ( NET_OK == net_mqtt_connect( &mqtt, &cfg, mqtt_buffer, sizeof( mqtt_buffer ), on_message, NULL, 5000 ) )
 * {
 *     net_mqtt_subscribe( &mqtt, "board/led", 1, 3000 );
 *     net_mqtt_publish( &mqtt, "board/temp", "23.5", 4, 0, false, 0 );
 * }
 * for ( ; ; ) { net_poll(); net_mqtt_poll( &mqtt ); }
 * @endcode
 */

#ifndef _NET_MQTT_H
#define _NET_MQTT_H

#ifdef __cplusplus
extern "C"{
#endif

#include "net_api.h"

/*! @brief Received message: topic ('\0'-terminated) and payload, valid during the call. */
typedef void ( *net_mqtt_on_message_t )( void *ctx, const char *topic, const uint8_t *payload, uint32_t len );

/*! @brief Connection settings, see net_mqtt_cfg_setup(). */
typedef struct
{
    const char *host;               /*!< Broker name or dotted IPv4 address (mandatory). */
    uint16_t port;                  /*!< Default 1883. */
    const char *client_id;          /*!< NULL: "mikrosdk-" + a random number. */
    const char *username;           /*!< NULL for none. */
    const char *password;           /*!< NULL for none (needs a username). */
    uint16_t keepalive_s;           /*!< Seconds, default 60; 0 disables keep-alive. */
    bool clean_session;             /*!< Default true. */
    const char *will_topic;         /*!< Last will, NULL for none. */
    const void *will_message;
    uint16_t will_len;
    uint8_t will_qos;               /*!< 0 or 1. */
    bool will_retain;
} net_mqtt_cfg_t;

/*! @brief Client state. Fields are private; read only `dropped` and `connack_code`. */
typedef struct
{
    net_socket_t sock;
    bool connected;
    uint8_t *buf;
    uint32_t size;
    net_mqtt_on_message_t on_message;
    void *ctx;
    uint16_t keepalive_s;
    uint32_t last_tx;
    uint32_t ping_sent;
    bool ping_pending;
    uint16_t next_id;
    /* receiving */
    uint8_t rx_state;
    uint8_t rx_type;
    uint8_t rx_len_bytes;
    uint32_t rx_len;
    uint32_t rx_got;
    uint32_t rx_multiplier;
    /* last acknowledgement seen, for the waiting calls */
    uint8_t ack_type;
    uint16_t ack_id;
    uint8_t ack_code;
    bool ack_seen;
    uint32_t dropped;               /*!< Messages too large for the buffer. */
    uint8_t connack_code;           /*!< Broker's CONNACK return code after a refused connect. */
} net_mqtt_t;

/*! @brief Defaults: port 1883, random client id, keep-alive 60 s, clean session. */
void net_mqtt_cfg_setup( net_mqtt_cfg_t *cfg );

/*!
 * @brief Connect to the broker (TCP, CONNECT, wait for CONNACK).
 * @param buffer Holds one received packet (topic + payload); at least 64 bytes.
 * @return NET_OK, NET_REFUSED (the broker refused: see connack_code), NET_TIMEOUT,
 * NET_INVALID, or the resolve / connect error.
 */
net_err_t net_mqtt_connect( net_mqtt_t *mqtt, const net_mqtt_cfg_t *cfg, uint8_t *buffer, uint32_t size,
                            net_mqtt_on_message_t on_message, void *ctx, uint32_t timeout_ms );

/*!
 * @brief Publish a message; QoS 1 waits for the broker's PUBACK.
 * @return NET_OK, NET_TIMEOUT (QoS 1 not acknowledged), NET_INVALID (topic with
 * wildcards, QoS > 1), NET_CLOSED / NET_RESET (connection lost).
 */
net_err_t net_mqtt_publish( net_mqtt_t *mqtt, const char *topic, const void *payload, uint32_t len, uint8_t qos,
                            bool retain, uint32_t timeout_ms );

/*!
 * @brief Subscribe to a topic filter (wildcards allowed) with QoS 0 or 1.
 * @return NET_OK, NET_REFUSED (the broker refused it), NET_TIMEOUT, NET_INVALID, NET_CLOSED.
 */
net_err_t net_mqtt_subscribe( net_mqtt_t *mqtt, const char *filter, uint8_t qos, uint32_t timeout_ms );

/*! @brief Unsubscribe from a topic filter. @return NET_OK, NET_TIMEOUT, NET_CLOSED. */
net_err_t net_mqtt_unsubscribe( net_mqtt_t *mqtt, const char *filter, uint32_t timeout_ms );

/*!
 * @brief Receive and handle what the broker sent, keep the connection alive.
 * Call it often, after net_poll().
 * @return NET_OK while connected, else why the connection ended (NET_CLOSED,
 * NET_RESET, NET_TIMEOUT for an unanswered ping, NET_ERROR for a protocol error).
 */
net_err_t net_mqtt_poll( net_mqtt_t *mqtt );

/*! @brief true while connected. */
bool net_mqtt_connected( const net_mqtt_t *mqtt );

/*! @brief Send DISCONNECT (no will is published) and close. */
void net_mqtt_disconnect( net_mqtt_t *mqtt );

#ifdef __cplusplus
}
#endif

#endif // _NET_MQTT_H
// ------------------------------------------------------------------------- END
