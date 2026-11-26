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
 * @file net_sntp.h
 * @brief SNTP client (RFC 4330) on the mikroSDK network API: wall-clock time.
 * @details net_sntp_sync() asks a time server once; afterwards net_sntp_now()
 * gives the current UTC time from the last answer plus net_now_ms(). Sync again
 * at least once a day (the local millisecond counter drifts, and wraps after
 * 49 days). Replies are checked: only from the server asked, only answering
 * this request (random nonce), no "kiss-of-death" or unsynchronised servers.
 *
 * @code
 * if ( NET_OK == net_sntp_sync( "pool.ntp.org", 3000 ) )
 * {
 *     uint32_t seconds;               // since 1970-01-01 00:00:00 UTC
 *     uint16_t ms;
 *     net_sntp_now( &seconds, &ms );
 * }
 * @endcode
 */

#ifndef _NET_SNTP_H
#define _NET_SNTP_H

#ifdef __cplusplus
extern "C"{
#endif

#include "net_api.h"

/*! SNTP server port. */
#define NET_SNTP_PORT 123

/*!
 * @brief Ask @p server (host name or dotted IPv4 address) for the time.
 * @return NET_OK (the clock is set), NET_TIMEOUT (no valid answer),
 * NET_REFUSED (the server sent "kiss-of-death": ask another or later),
 * NET_NOT_FOUND, NET_NOT_READY, NET_NO_MEMORY.
 */
net_err_t net_sntp_sync( const char *server, uint32_t timeout_ms );

/*! @brief true after a successful net_sntp_sync(). */
bool net_sntp_synced( void );

/*!
 * @brief Current UTC time: seconds since 1970-01-01 and the milliseconds in
 * that second (either pointer may be NULL).
 * @return NET_OK, or NET_NOT_READY before the first sync.
 */
net_err_t net_sntp_now( uint32_t *unix_seconds, uint16_t *milliseconds );

#ifdef __cplusplus
}
#endif

#endif // _NET_SNTP_H
// ------------------------------------------------------------------------- END
