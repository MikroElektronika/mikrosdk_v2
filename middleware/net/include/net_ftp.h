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
 * @file net_ftp.h
 * @brief FTP client (RFC 959, passive mode, binary transfers), built on net_api.h.
 * @details One control connection per net_ftp_t and at most one transfer at a
 * time (one more socket while it runs). Every call waits for the server's
 * answer up to the timeout given to net_ftp_connect(); the last reply is in
 * net_ftp_t.status and net_ftp_t.reply.
 *
 * Plain FTP sends the password and the data unencrypted: use it only on
 * networks you trust. Arguments (names, paths) must not contain CR or LF
 * (NET_INVALID), so they cannot add commands. The data connection always goes
 * to the control connection's server: the address in the PASV reply is ignored
 * (as curl does), only its port is used.
 *
 * @code
 * static net_ftp_t ftp;
 * net_ftp_connect( &ftp, "ftp.example.com", 21, 10000 );
 * net_ftp_login( &ftp, "user", "password" );
 * net_ftp_open( &ftp, "readme.txt", NET_FTP_READ );
 * while ( ( n = net_ftp_read( &ftp, buf, sizeof( buf ) ) ) > 0 ) { ... }
 * net_ftp_close( &ftp );
 * net_ftp_quit( &ftp );
 * @endcode
 */

#ifndef _NET_FTP_H
#define _NET_FTP_H

#ifdef __cplusplus
extern "C"{
#endif

#include "net_api.h"

#define NET_FTP_PORT 21

#ifndef NET_FTP_REPLY_MAX
#define NET_FTP_REPLY_MAX 128           /*!< Reply text kept (first line, truncated). */
#endif

/*! @brief What net_ftp_open() starts. */
typedef enum
{
    NET_FTP_READ = 0,                   /*!< Download a file (RETR). */
    NET_FTP_WRITE,                      /*!< Upload a file, replacing it (STOR). */
    NET_FTP_APPEND,                     /*!< Upload, appending to the file (APPE). */
    NET_FTP_LIST,                       /*!< Directory listing, server's format (LIST); path may be NULL. */
    NET_FTP_NAMES                       /*!< Names only, one per line (NLST); path may be NULL. */
} net_ftp_mode_t;

/*! @brief Client state. Read `status` and `reply`; the other fields are private. */
typedef struct
{
    net_socket_t ctrl;
    net_socket_t data;
    bool connected;
    bool transfer;                      /* a transfer is open */
    bool data_done;                     /* the server closed the data connection */
    bool replied;                       /* the transfer's final reply came already */
    bool reading;                       /* download or listing (not an upload) */
    net_ip4_t server;
    uint32_t timeout_ms;
    uint16_t status;                    /*!< Last reply code, e.g. 226 (not "code": an empty macro in mikroSDK). */
    char reply[ NET_FTP_REPLY_MAX ];    /*!< Its first line, '\0'-terminated. */
} net_ftp_t;

/*!
 * @brief Connect to an FTP server and read its greeting.
 * @param port 0 = 21. @param timeout_ms Used for this and every later call.
 * @return NET_OK, NET_REFUSED (server not ready: status 4xx/5xx, or TCP refused),
 * NET_NOT_FOUND, NET_TIMEOUT, NET_ERROR (malformed reply), NET_INVALID.
 */
net_err_t net_ftp_connect( net_ftp_t *ftp, const char *host, uint16_t port, uint32_t timeout_ms );

/*!
 * @brief Log in and switch to binary transfers (TYPE I).
 * @param password May be NULL when the server does not ask for one.
 * @return NET_OK, NET_REFUSED (login failed, see status), NET_INVALID, ...
 */
net_err_t net_ftp_login( net_ftp_t *ftp, const char *user, const char *password );

/*!
 * @brief Start a transfer (passive mode). Then net_ftp_read() or net_ftp_write(),
 * and net_ftp_close().
 * @return NET_OK, NET_REFUSED (the server refused, e.g. 550 no such file: see
 * status), NET_INVALID (a transfer is already open, bad path), NET_NO_MEMORY (no
 * socket), connection errors.
 */
net_err_t net_ftp_open( net_ftp_t *ftp, const char *path, net_ftp_mode_t mode );

/*!
 * @brief Read from a download or listing.
 * @return Bytes read, 0 at the end, or a negative net_err_t.
 */
int32_t net_ftp_read( net_ftp_t *ftp, void *buf, uint32_t size );

/*! @brief Write to an upload. @return Bytes written (all of len) or a negative net_err_t. */
int32_t net_ftp_write( net_ftp_t *ftp, const void *data, uint32_t len );

/*!
 * @brief End the transfer and read the server's result.
 * @return NET_OK when the transfer completed (226/250) or a download was stopped
 * early on purpose (426/451 after net_ftp_close() before the end); NET_ERROR when
 * the server reports a failed transfer; connection errors.
 */
net_err_t net_ftp_close( net_ftp_t *ftp );

/*! @brief Change the directory (CWD). @return NET_OK or NET_REFUSED (see status). */
net_err_t net_ftp_cwd( net_ftp_t *ftp, const char *path );

/*! @brief Current directory (PWD), '\0'-terminated, truncated to size. */
net_err_t net_ftp_pwd( net_ftp_t *ftp, char *buf, uint32_t size );

/*! @brief Create a directory (MKD). */
net_err_t net_ftp_mkdir( net_ftp_t *ftp, const char *path );

/*! @brief Remove a directory (RMD). */
net_err_t net_ftp_rmdir( net_ftp_t *ftp, const char *path );

/*! @brief Delete a file (DELE). */
net_err_t net_ftp_delete( net_ftp_t *ftp, const char *path );

/*! @brief Rename or move a file (RNFR, RNTO). */
net_err_t net_ftp_rename( net_ftp_t *ftp, const char *from, const char *to );

/*! @brief Size of a file in bytes (SIZE, RFC 3659). @return NET_OK, NET_REFUSED. */
net_err_t net_ftp_size( net_ftp_t *ftp, const char *path, uint32_t *size );

/*! @brief Say goodbye (QUIT) and close everything; also ends an open transfer. */
void net_ftp_quit( net_ftp_t *ftp );

#ifdef __cplusplus
}
#endif

#endif // _NET_FTP_H
// ------------------------------------------------------------------------- END
