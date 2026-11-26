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
 * @file cc.h
 * @brief lwIP architecture port for mikroSDK (GCC: ARM, PIC32, host tests).
 * @details Included by lwip/arch.h. Diagnostics are off, assertions and random
 * numbers go to the network layer (middleware/net, src/net_lwip.c), so nothing
 * here needs printf, stdlib's rand() or an RTOS.
 */

#ifndef LWIP_ARCH_CC_H
#define LWIP_ARCH_CC_H

#include <stdint.h>

/* Byte order: ARM Cortex-M and PIC32 (MIPS) as used by mikroSDK are little-endian. */
#if defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define BYTE_ORDER BIG_ENDIAN
#else
#define BYTE_ORDER LITTLE_ENDIAN
#endif

/* No console: diagnostics are dropped. */
#define LWIP_PLATFORM_DIAG(x) do { } while (0)

/* Assertions are passed to the network layer, which calls the application's
 * hook (net_config_t.assert_hook) if one is set. */
void net_port_assert(const char *message, const char *file, int line);
#define LWIP_PLATFORM_ASSERT(x) net_port_assert((x), __FILE__, __LINE__)

/* Random numbers (TCP initial sequence numbers, DNS transaction IDs and ports,
 * DHCP transaction IDs). The network layer uses net_config_t.random if the
 * application provides one (e.g. a hardware RNG), otherwise a seeded PRNG. */
uint32_t net_port_rand(void);
#define LWIP_RAND() (net_port_rand())

#endif /* LWIP_ARCH_CC_H */
