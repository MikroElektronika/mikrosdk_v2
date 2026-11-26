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
 * @file net_http.h
 * @brief Minimal HTTP/1.1 client on the mikroSDK network API (plain HTTP, no TLS).
 * @details One request per connection ("Connection: close"). Any method, extra
 * header lines and a request body; the response status and body are returned,
 * with "Content-Length", chunked and close-delimited bodies supported. Built
 * only on net_api.h, so it works with any stack behind it.
 */

#ifndef _NET_HTTP_H
#define _NET_HTTP_H

#ifdef __cplusplus
extern "C"{
#endif

#include "net_api.h"

/*! Largest status line plus response header block accepted, in bytes. */
#ifndef NET_HTTP_HEADER_MAX
#define NET_HTTP_HEADER_MAX 1024
#endif

/*! @brief HTTP request. Only host is mandatory. */
typedef struct
{
    const char *method;          /*!< "GET" (default if NULL), "POST", "PUT", ... */
    const char *host;            /*!< Host name or dotted IPv4 address. */
    uint16_t port;               /*!< Server port, 0 = 80. */
    const char *path;            /*!< Path and query, e.g. "/api?id=1"; NULL = "/". */
    const char *headers;         /*!< Extra header lines, each ending in "\r\n", or NULL. */
    const char *content_type;    /*!< Content-Type of the body, or NULL. */
    const void *body;            /*!< Request body, or NULL. */
    uint32_t body_len;           /*!< Request body length in bytes. */
} net_http_request_t;

/*! @brief HTTP response. Set body and body_size before the request. */
typedef struct
{
    uint16_t status;             /*!< HTTP status, e.g. 200. */
    char *body;                  /*!< Buffer for the body (may be NULL to discard it). */
    uint32_t body_size;          /*!< Size of the body buffer. */
    uint32_t body_len;           /*!< Body bytes stored in the buffer. */
    bool truncated;              /*!< true if the body did not fit into the buffer. */
} net_http_response_t;

/*!
 * @brief Send one request and read the response.
 * @details If body_size allows, a '\0' is kept after the body (not counted in
 * body_len), also when the request fails, so a text body can be used as a string.
 * @return NET_OK when a complete response was received (check status), or
 * NET_NOT_FOUND, NET_TIMEOUT, NET_REFUSED, NET_RESET, NET_NO_MEMORY,
 * NET_INVALID, NET_ERROR (malformed response).
 */
net_err_t net_http_request( const net_http_request_t *req, net_http_response_t *resp, uint32_t timeout_ms );

#ifdef __cplusplus
}
#endif

#endif // _NET_HTTP_H
// ------------------------------------------------------------------------- END
