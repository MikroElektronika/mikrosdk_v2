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
 * @file systime.h
 * @brief Millisecond time since start, without interrupts or timers.
 * @details Uses the core's cycle counter: DWT CYCCNT on Cortex-M3 and newer
 * (core clock), CP0 Count on PIC32 (half the core clock), mcycle on RISC-V.
 * Every call adds up the cycles since the previous one, so the time is exact
 * as long as systime_ms() is called at least once per counter period (2^32
 * cycles: about 25 s at 168 MHz, 43 s on a 200 MHz PIC32MZ). The network
 * layer calls it all the time; elsewhere, call it in the main loop.
 *
 * Not available on cores without a cycle counter (Cortex-M0/M0+/M23).
 *
 * @code
 * uint32_t start = systime_ms();
 * while ( systime_ms() - start < 500 ) { ... }   // correct across the wrap
 * @endcode
 */

#ifndef _SYSTIME_H_
#define _SYSTIME_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>

/*!
 * @brief Start the time base. Optional: the first systime_ms() call does it.
 */
void systime_init( void );

/*!
 * @brief Milliseconds since the first call (systime_init() or systime_ms()).
 * @return Time in ms; wraps after about 49.7 days, compare with subtraction.
 */
uint32_t systime_ms( void );

#ifdef __cplusplus
}
#endif

#endif // _SYSTIME_H_
// ------------------------------------------------------------------------- END
