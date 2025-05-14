/****************************************************************************
**
** Copyright (C) ${COPYRIGHT_YEAR} MikroElektronika d.o.o.
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
 * @file  mikroSDK_version.h
 * @brief mikroSDK Version support.
 */

#ifndef _mikroSDK_VERSION_H_
#define _mikroSDK_VERSION_H_

#ifdef __cplusplus
extern "C"{
#endif

/**
  * @brief mikroSDK_MAJOR_VERSION
  * @note changes in major version indicate that there could be features
  * of mikroSDK not compatible with previous version
  */
#define mikroSDK_MAJOR_VERSION 2

/**
  * @brief mikroSDK_MINOR_VERSION
  * @note changes in minor version indicate that there have been
  * significant improvements and/or features added
  */
#define mikroSDK_MINOR_VERSION 14

/**
  * @brief mikroSDK_PATCH_VERSION
  * @note changes in patch version indicate smaller updates,
  * bug fixes and improvements
  */
#define mikroSDK_PATCH_VERSION 4

/**
  * @brief mikroSDK_GET_VERSION
  * @note get version of mikroSDK
  */
#define mikroSDK_GET_VERSION ((mikroSDK_MAJOR_VERSION)*10000 + (mikroSDK_MINOR_VERSION)*100 + (mikroSDK_PATCH_VERSION))

#ifdef __cplusplus
}
#endif

#endif // _mikroSDK_VERSION_H_
// ------------------------------------------------------------------------- END
