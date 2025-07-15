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
 * @file  ft800_const.h
 * @brief FT800 Display Controller Constants.
 */

/*!
 * @addtogroup middlewaregroup Middleware
 * @{
 */

/*!
 * @addtogroup ft800 FT800 Display Controller Driver
 * @{
 */

/*!
 * @addtogroup ft800_constants FT800 Display Controller Registers
 * @brief FT800 Display Controller Constants List
 * @{
 */

#ifndef FT800_CONST_H
#define FT800_CONST_H

/**
 * @brief FT800 RX Data Buffer Size.
 * @details Macro for defining SPI Read buffer size for FT800 series controllers.
 */
#define FT800_RX_DATA_BUFF                                     ( 5 )

/**
 * @brief FT800 TX Data Buffer Size.
 * @details Macro for defining SPI write buffer size for FT800 series controllers.
 */
#define FT800_TX_DATA_BUFF                                     ( 3 )

/**
 * @brief FT800 RAM G Header.
 * @details Macro to define RAM G header size for FT800 series controllers.
 */
#define FT800_RAM_G_HEADER                                     ( 3 )

/**
 * @brief FT800 Gesture Event Zoom Out.
 * @details Represents a pinch-out gesture event, typically used for zooming out
 * for FT800 series controllers.
 */
#define FT800_EVENT_GEST_ZOOM_OUT                              ( 0x49UL )

/**
 * @brief FT800 Gesture Event Zoom In.
 * @details Represents a pinch-in gesture event, typically used for zooming in
 * for FT800 series controllers.
 */
#define FT800_EVENT_GEST_ZOOM_IN                               ( 0x48UL )

/**
 * @brief FT800 Gesture Event Swipe Down.
 * @details Represents a downward swipe gesture on the touch screen for FT800
 * series controllers
 */
#define FT800_EVENT_GEST_DOWN                                  ( 0x18UL )

/**
 * @brief FT800 Gesture Event Swipe Up.
 * @details Represents an upward swipe gesture on the touch screen for FT800
 * series controllers
 */
#define FT800_EVENT_GEST_UP                                    ( 0x10UL )

/**
 * @brief FT800 Gesture Event Swipe Right.
 * @details Represents a rightward swipe gesture on the touch screen for FT800
 * series controllers
 */
#define FT800_EVENT_GEST_RIGHT                                 ( 0x14UL )

/**
 * @brief FT800 Gesture Event Swipe Left.
 * @details Represents a leftward swipe gesture on the touch screen for FT800
 * series controllers
 */
#define FT800_EVENT_GEST_LEFT                                  ( 0x1CUL )

/**
 * @brief FT800 Command Offset.
 * @details The amount by which FT800_RAM-DL is increased with each command sent
 * for FT800 series controllers.
 */
#define FT800_COMMAND_OFFSET                                   ( 4 )

/**
 * @brief FT800 SPI Receive Data Length 5 Bytes.
 * @details Defines reading 5 bytes of data via SPI communication for FT800
 * series controllers.
 */
#define FT800_SPI_RECEIVE_DATA_LENGTH_5                        ( 5 )

/**
 * @brief FT800 SPI Receive Data Length 3 Bytes.
 * @details Defines reading 3 bytes of data via SPI communication for FT800
 * series controllers.
 */
#define FT800_SPI_RECEIVE_DATA_LENGTH_3                        ( 3 )

/**
 * @brief FT800 SPI Receive Data Length 2 Bytes.
 * @details Defines reading 2 bytes of data via SPI communication for FT800
 * series controllers.
 */
#define FT800_SPI_RECEIVE_DATA_LENGTH_2                        ( 2 )

/**
 * @brief FT800 SPI Send Data Length 7 Bytes.
 * @details Defines sending 7 bytes of data via SPI communication for FT800
 * series controllers.
 */
#define FT800_SPI_SEND_DATA_LENGTH_7                           ( 7 )

/**
 * @brief FT800 SPI Send Data Length 5 Bytes.
 * @details Defines sending 5 bytes of data via SPI communication for FT800
 * series controllers.
 */
#define FT800_SPI_SEND_DATA_LENGTH_5                           ( 5 )

/**
 * @brief FT800 SPI Send Data Length 4 Bytes.
 * @details Defines sending 4 bytes of data via SPI communication for FT800
 * series controllers.
 */
#define FT800_SPI_SEND_DATA_LENGTH_4                           ( 4 )

/**
 * @brief FT800 SPI Send Data Length 3 Bytes.
 * @details Defines sending 3 bytes of data via SPI communication for FT800
 * series controllers.
 */
#define FT800_SPI_SEND_DATA_LENGTH_3                           ( 3 )

/**
 * @brief FT800 Char Height Value 31.
 * @details Height of one character of the in-built font 31 for FT800 series
 * controllers.
 */
#define FT800_CHAR_HEIGHT_31                                   ( 36 )

/**
 * @brief FT800 Char Height Value 30.
 * @details Height of one character of the in-built font 30 for FT800 series
 * controllers.
 */
#define FT800_CHAR_HEIGHT_30                                   ( 30 )

/**
 * @brief FT800 Char Height Value 29.
 * @details Height of one character of the in-built font 29 for FT800 series
 * controllers.
 */
#define FT800_CHAR_HEIGHT_29                                   ( 25 )

/**
 * @brief FT800 Char Height Value 28.
 * @details Height of one character of the in-built font 28 for FT800 series
 * controllers.
 */
#define FT800_CHAR_HEIGHT_28                                   ( 21 )

/**
 * @brief FT800 Char Height Value 27.
 * @details Height of one character of the in-built font 27 for FT800 series
 * controllers.
 */
#define FT800_CHAR_HEIGHT_27                                   ( 16 )

/**
 * @brief FT800 Char Height Value 26.
 * @details Height of one character of the in-built font 26 for FT800 series
 * controllers.
 */
#define FT800_CHAR_HEIGHT_26                                   ( 13 )

/**
 * @brief FT800 Text Scaled Y position.
 * @details Scaled text position value along the Y axis for FT800 series
 * controllers.
 */
#define FT800_TEXT_SCALE_Y                                     ( 2 )

/**
 * @brief FT800 Text Scaled X position.
 * @details Scaled text position value along the X axis for FT800 series
 * controllers.
 */
#define FT800_TEXT_SCALE_X                                     ( 2 )

/**
 * @brief FT800 Letter Width Value 31.
 * @details Width of one character of the in-built font 31 for FT800 series
 * controllers.
 */
#define FT800_LETTER_WIDTH_31                                  ( 24 )

/**
 * @brief FT800 Letter Width Value 30.
 * @details Width of one character of the in-built font 30 for FT800 series
* controllers.
 */
#define FT800_LETTER_WIDTH_30                                  ( 17 )

/**
 * @brief FT800 Letter Width Value 29.
 * @details Width of one character of the in-built font 29 for FT800 series
 * controllers.
 */
#define FT800_LETTER_WIDTH_29                                  ( 14 )

/**
 * @brief FT800 Letter Width Value 28.
 * @details Width of one character of the in-built font 28 for FT800 series
 * controllers.
 */
#define FT800_LETTER_WIDTH_28                                  ( 12 )

/**
 * @brief FT800 Letter Width Value 27.
 * @details Width of one character of the in-built font 27 for FT800 series
 * controllers.
 */
#define FT800_LETTER_WIDTH_27                                  ( 10 )

/**
 * @brief FT800 Letter Width Value 26.
 * @details Width of one character of the in-built font 26 for FT800 series
 * controllers.
 */
#define FT800_LETTER_WIDTH_26                                  ( 8 )

/**
 * @brief FT800 Text Height Middle 31.
 * @details Middle of height of the in-built font 31 for FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_MIDDLE_31                            ( 18 )

/**
 * @brief FT800 Text Height Middle 30.
 * @details Middle of height of the in-built font 30 for FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_MIDDLE_30                            ( 15 )

/**
 * @brief FT800 Text Height Middle 29.
 * @details Middle of height of the in-built font 29 for FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_MIDDLE_29                            ( 12 )

/**
 * @brief FT800 Text Height Middle 28.
 * @details Middle of height of the in-built font 28 for FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_MIDDLE_28                            ( 10 )

/**
 * @brief FT800 Text Height Middle 27.
 * @details Middle of height of the in-built font 27 for FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_MIDDLE_27                            ( 8 )

/**
 * @brief FT800 Text Height Middle 26.
 * @details Middle of height of the in-built font 26 for FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_MIDDLE_26                            ( 6 )

/**
 * @brief FT800 Font Size 31.
 * @details Value 31 of in-built font for FT800 series controllers.
 */
#define FT800_TEXT_FONT_SIZE_31                                ( 31 )

/**
 * @brief FT800 Font Size 30.
 * @details Value 30 of in-built font for FT800 series controllers.
 */
#define FT800_TEXT_FONT_SIZE_30                                ( 30 )

/**
 * @brief FT800 Font Size 29.
 * @details Value 29 of in-built font for FT800 series controllers.
 */
#define FT800_TEXT_FONT_SIZE_29                                ( 29 )

/**
 * @brief FT800 Font Size 28.
 * @details Value 28 of in-built font for FT800 series controllers.
 */
#define FT800_TEXT_FONT_SIZE_28                                ( 28 )

/**
 * @brief FT800 Font Size 27.
 * @details Value 27 of in-built font for FT800 series controllers.
 */
#define FT800_TEXT_FONT_SIZE_27                                ( 27 )

/**
 * @brief FT800 Font Size 26.
 * @details Value 26 of in-built font for FT800 series controllers.
 */
#define FT800_TEXT_FONT_SIZE_26                                ( 26 )

/**
 * @brief FT800 Text Size 80.
 * @details Value of 80 of font size received from NECTO Designer for FT800
 * series controllers.
 */
#define FT800_TEXT_SIZE_80                                     ( 17 )

/**
 * @brief FT800 Text Size 64.
 * @details Value of 64 of font size received from NECTO Designer for FT800
 * series controllers.
 */
#define FT800_TEXT_SIZE_64                                     ( 13 )

/**
 * @brief FT800 Text Size 48.
 * @details Value of 48 of font size received from NECTO Designer for FT800
 * series controllers.
 */
#define FT800_TEXT_SIZE_48                                     ( 10 )

/**
 * @brief FT800 Text Size 32.
 * @details Value of 32 of font size received from NECTO Designer for FT800
 * series controllers.
 */
#define FT800_TEXT_SIZE_32                                     ( 7 )

/**
 * @brief FT800 Text Size 16.
 * @details Value of 16 of font size received from NECTO Designer for FT800
 * series controllers.
 */
#define FT800_TEXT_SIZE_16                                     ( 3 )

/**
 * @brief FT800 Text Height Scale 16.
 * @details Scales the position of vertical text relative to its height for
 * FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_SCALE_16                             ( 0.32 )

/**
 * @brief FT800 Text Height Scale 32.
 * @details Scales the position of vertical text relative to its height for
 * FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_SCALE_32                             ( 0.33 )

/**
 * @brief FT800 Text Height Scale 48.
 * @details Scales the position of vertical text relative to its height for
 * FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_SCALE_48                             ( 0.34 )

/**
 * @brief FT800 Text Height Scale 64.
 * @details Scales the position of vertical text relative to its height for
 * FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_SCALE_64                             ( 1.5 )

/**
 * @brief FT800 Text Height Scale 80.
 * @details Scales the position of vertical text relative to its height for
 * FT800 series controllers.
 */
#define FT800_TEXT_HEIGHT_SCALE_80                             ( 1.3 )

/**
 * @brief FT800 Rectangle Gradient Offset X.
 * @details Offset of the end edge of the gradient rectangle along the X axis.
 */
#define FT800_RECTANGLE_GRADIENT_OFFSET_X                      ( 1 )

/**
 * @brief FT800 Rectangle Gradient Offset Y.
 * @details Offset of the end edge of the gradient rectangle along the Y axis.
 */
#define FT800_RECTANGLE_GRADIENT_OFFSET_Y                      ( 1 )

/**
 * @brief FT800 Rectangle Gradient Width Scale.
 * @details Gradient rectangle width scaling parameter for FT800 series
 * controllers.
 */
#define FT800_RECTANGLE_GRADIENT_WIDTH_SCALE                   ( 2 )

/**
 * @brief FT800 Rectangle Gradient Height Scale.
 * @details Gradient rectangle height scaling parameter for FT800 series
 * controllers.
 */
#define FT800_RECTANGLE_GRADIENT_HEIGHT_SCALE                  ( 2 )

/**
 * @brief FT800 Rectangle Edges Theta Scale.
 * @details Scales the value of the corner angle of the rectangle edges for
 * FT800 series controllers.
 */
#define FT800_RECTANGLE_EDGES_THETA_SCALE                      ( 3.14159 / 2.0 )

/**
 * @brief FT800 Rectangle Edges Height Scale.
 * @details Scales the height of the rectangle edges for FT800 series controllers.
 */
#define FT800_RECTANGLE_EDGES_HEIGHT_SCALE                     ( 2 )

/**
 * @brief FT800 Rectangle Edges Width Scale.
 * @details Scales the width of the rectangle edges for FT800 series controllers.
 */
#define FT800_RECTANGLE_EDGES_WIDTH_SCALE                      ( 2 )

/**
 * @brief FT800 Rectangle Edges Radius Scale
 * @details Scales the radius of the corner edge of a rectangle for FT800 series
 * controllers.
 */
#define FT800_RECTANGLE_EDGES_RADIUS_SCALE                     ( 2 )

/**
 * @brief FT800 Rectangle Edges Segment.
 * @details The number of segments that make up the corners of the edges of a
 * rectangle for FT800 series controllers.
 */
#define FT800_RECTANGLE_EDGES_SEGMENT                          ( 10 )

/**
 * @brief FT800 Ellipse Gradient Interpolation Offset
 * @details Gradient ellipse color interpolation offset value for FT800 series
 * controllers.
 */
#define FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET                   ( 1 )

/**
 * @brief FT800 Ellipse Gradient Interpolation Offset Y
 * @details Gradient ellipse color interpolation offset value along the Y axis
 * for FT800 series controllers.
 */
#define FT800_ELLIPSE_GRADIENT_INTPOL_OFFSET_Y                 ( 0.5 )

/**
 * @brief FT800 Ellipse Gradient Normalization Value.
 * @details Parameter for transforming the coordinates of the gradient ellipse
 * so that they are in the range 0-1 for FT800 series controllers.
 */
#define FT800_ELLIPSE_GRADIENT_NORMAL_VALUE                    ( 1.0 )

/**
 * @brief FT800 Ellipse Gradient Segment.
 * @details Number of segments from which the gradient ellipse is drawn for
 * FT800 series controllers.
 */
#define FT800_ELLIPSE_GRADIENT_SEGMENTS                        ( 100 )

/**
 * @brief FT800 Ellipse Gradient Height Scale.
 * @details Gradient ellipse height scaling parameter for FT800 series controllers.
 */
#define FT800_ELLIPSE_GRADIENT_HEIGHT_SCALE                    ( 2.0 )

/**
 * @brief FT800 Ellipse Gradient Width Scale.
 * @details Gradient ellipse width scaling parameter for FT800 series controllers.
 */
#define FT800_ELLIPSE_GRADIENT_WIDTH_SCALE                     ( 2.0 )

/**
 * @brief FT800 Ellipse Edges Theta Scale
 * @details Scales the value of the angle at which the edges of the ellipse are
 * drawn for FT800 series controllers.
 */
#define FT800_ELLIPSE_EDGES_THETA_SCALE                        ( 2.0 * 3.14159 )

/**
 * @brief FT800 Ellipse Edges Segment.
 * @details The number of segments from which the edges of the ellipse are drawn
 * for FT800 series controllers.
 */
#define FT800_ELLIPSE_EDGES_SEGMENTS                           ( 100 )

/**
 * @brief FT800 Ellipse Edges Height Scale.
 * @details Edges ellipse height scaling parameter for FT800 series controllers.
 */
#define FT800_ELLIPSE_EDGES_HEIGHT_SCALE                       ( 2.0 )

/**
 * @brief FT800 Ellipse Edges Width Scale.
 * @details Edges ellipse width scaling parameter for FT800 series controllers.
 */
#define FT800_ELLIPSE_EDGES_WIDTH_SCALE                        ( 2.0 )

/**
 * @brief FT800 Circle Gradient Offset X.
 * @details Gradient circle offset along the X axis for FT800 series controllers.
 */
#define FT800_CIRCLE_GRADIENT_OFFSET_X                         ( 1 )

/**
 * @brief FT800 Circle Gradient Offset Y.
 * @details Gradient circle offset along the Y axis for FT800 series controllers.
 */
#define FT800_CIRCLE_GRADIENT_OFFSET_Y                         ( 1 )

/**
 * @brief FT800 Circle Gradient Normalization Value
 * @details Parameter for transforming the coordinates of the gradient circle so
 * that they are in the range 0-1 for FT800 series controllers.
 */
#define FT800_CIRCLE_GRADIENT_NORMAL_VALUE                     ( 1.0 )

/**
 * @brief FT800 Circle Gradient Radius Scale
 * @details Gradient circle diameter scaling parameter for FT800 series
 * controllers.
 */
#define FT800_CIRCLE_GRADIENT_RADIUS_SCALE                     ( 2.0 )

/**
 * @brief FT800 Circle Gradient Width Scale.
 * @details Gradient circle width scaling parameter for FT800 series controllers.
 */
#define FT800_CIRCLE_GRADIENT_WIDTH_SCALE                      ( 2.0 )

/**
 * @brief FT800 Circle Edges Segments.
 * @details The number of segments from which the edges of the circle are drawn
 * for FT800 series controllers.
 */
#define FT800_CIRCLE_EDGES_SEGMENTS                            ( 100 )

/**
 * @brief FT800 Circle Edges Theta Scale
 * @details Scales the value of the angle at which the edges of the circle are
 * drawn for FT800 series controllers.
 */
#define FT800_CIRCLE_EDGES_THETA_SCALE                         ( 2.0 * 3.14159 )

/**
 * @brief FT800_Circle Edges Width Scale
 * @details Edges circle width scaling parameter for FT800 series controllers.
 */
#define FT800_CIRCLE_EDGES_WIDTH_SCALE                         ( 2.0 )

/**
 * @brief FT800 RGB Blue Scale Value.
 * @details Parameter for scaling blue values ​​when converting from RGB 565 format
 * for FT800 series controllers.
 */
#define FT800_RGB_BLUE_SCALE                                   ( 255.0 / 31.0 )

/**
 * @brief FT800 RGB Green Scale Value.
 * @details Parameter for scaling green values ​​when converting from RGB 565 format
 * for FT800 series controllers.
 */
#define FT800_RGB_GREEN_SCALE                                  ( 255.0 / 63.0 )

/**
 * @brief FT800 RGB Red Scale Value.
 * @details Parameter for scaling red values ​​when converting from RGB 565 format
 * for FT800 series controllers.
 */
#define FT800_RGB_RED_SCALE                                    ( 255.0 / 31.0 )


/**
 * @brief FT800 Bitmap Layout Format Index.
 * @details Index used to configure the bitmap pixel format in the layout
 * descriptor of an image for FT800 series controllers.
 */
#define FT800_IMAGE_BITMAP_LAYOUT_FORMAT                       ( 7 )

/**
 * @brief FT800 Image Padding Size.
 * @details Number of bytes used to align image data rows in memory for FT800
 * series controllers.
 */
#define FT800_IMAGE_PADDING_SIZE                               ( 4 )

/**
 * @brief FT800 Image Padding Alignment.
 * @details Memory alignment value in bytes for image padding calculations for
 * FT800 series controllers.
 */
#define FT800_IMAGE_PADDING_ALIGNMENT                           ( 4 )

/**
 * @brief FT800 Image Size Constant.
 * @details Internal constant used for image array size calculation for FT800
 * series controllers.
 */
#define FT800_IMAGE_SIZE_CONST_2                               ( 6 )

/**
 * @brief FT800 Image Size Constant.
 * @details Internal constant used for image array size calculation for FT800
 * series controllers.
 */
#define FT800_IMAGE_SIZE_CONST_1                               ( 2 )

/**
 * @brief FT800 Ellipse Width Scale Factor.
 * @details Used to calculate the effective width of the ellipse shape for
 * FT800 series controllers.
 */
#define FT800_ELLIPSE_WIDTH_SCALE                              ( 2.0 )

/**
 * @brief FT800 Ellipse Height Scale Factor.
 * @details Used to calculate the effective height of the ellipse shape for
 * FT800 series controllers.
 */
#define FT800_ELLIPSE_HEIGHT_SCALE                             ( 2.0 )

/**
 * @brief FT800 Radio Button Right Height Scale.
 * @details Determines the height for the right-side position of Radio Button
 * circle for FT800 series controllers.
 */
#define FT800_RADIO_BUTTON_HEIGHT_SCALE_R                      ( 2.0 )

/**
 * @brief FT800 Radio Button Left Height Scale.
 * @details Determines the height for the left-side position of Radio Button
 * circle for FT800 series controllers.
 */
#define FT800_RADIO_BUTTON_HEIGHT_SCALE_L                      ( 2.0 )

/**
 * @brief FT800 Radio Button Center Scale Right.
 * @details Determines the center radius of the right side position of Radio
 * button for FT800 series controllers.
 */
#define FT800_RADIO_BUTTON_CENTER_SCALE_R                      ( 0.8 )

/**
 * @brief FT800 Radio Button Pen Offset Scale.
 * @details Used to offset the pen width when drawing radio button outline for
 * FT800 series controllers.
 */
#define FT800_RADIO_BUTTON_PEN_OFFSET_SCALE                    ( 2 )

/**
 * @brief FT800 Radio Button Center Scale Left.
 * @details Determines the center radius of the left side position of Radio
 * button for FT800 series controllers.
 */
#define FT800_RADIO_BUTTON_CENTER_SCALE_L                      ( 2.0 )

/**
 * @brief FT800 Check Box Corner Radius Scale.
 * @details Defines how rounded the check box corners appear for FT800 series
 * controllers.
 */
#define FT800_CHECK_BOX_CORNER_RADIUS_SCALE                    ( 2 )

/**
 * @brief FT800 Check Box Pen Offset Scale.
 * @details Used to offset the pen when rendering the Check box for FT800 series
 * controllers.
 */
#define FT800_CHECK_BOX_PEN_OFFSET_SCALE                       ( 2 )

/**
 * @brief FT800 Check Mark Scale Factor.
 * @details Used to scale the size of the third segment of the check mark symbol.
 */
#define FT800_CHECK_BOX_SIGN_SCALE_3                           ( 2.0 / 3.0 )

/**
 * @brief FT800 Check Mark Scale Factor.
 * @details Used to scale the size of the second segment of the check mark symbol.
 */
#define FT800_CHECK_BOX_SIGN_SCALE_2                           ( 1.0 / 3.0 )

/**
 * @brief FT800 Check Mark Scale Factor.
 * @details Base size factor used for defining the check mark proportions and resolution.
 */
#define FT800_CHECK_BOX_SIGN_SCALE_1                           ( 10.0 )

/**
 * @brief FT800 Progress Bar Number Y Offset.
 * @details Offset for vertical placement of numerical text in the progress bar
 * for FT800 series controllers.
 */
#define FT800_PROGRESS_BAR_NUMBER_Y_OFFSET                     ( 13 )

/**
 * @brief FT800 Progress Bar Number X Offset.
 * @details Offset for vertical placement of numerical text in the progress bar
 * for FT800 series controllers.
 */
#define FT800_PROGRESS_BAR_NUMBER_X_OFFSET                     ( 15 )

/**
 * @brief FT800 Progress Bar Number X Position Scale.
 * @details Defines the proportional X offset for placing the progress value
 * on the progress bar for FT800 series controllers.
 */
#define FT800_PROGRESS_BAR_NUMBER_X_POSITION_SCALE_1           ( 5.0 / 479.0 )

/**
 * @brief FT800 Progress Bar Number X Position Scale.
 * @details Static offset used as a fallback or normalization constant
 * in the progress bar for FT800 series controllers.
 */
#define FT800_PROGRESS_BAR_NUMBER_X_POSITION_SCALE_2           ( 1 )

/**
 * @brief FT800 Progress Bar Number Height Scale.
 * @details Multiplier for text height within Progress bar for FT800 series
 * controllers.
 */
#define FT800_PROGRESS_BAR_NUMBER_HEIGHT_SCALE                 ( 2 )

/**
 * @brief FT800 Progress Bar Number Width Scale.
 * @details Multiplier for text width within Progress bar for FT800 series
 * controllers.
 */
#define FT800_PROGRESS_BAR_NUMBER_WIDTH_SCALE                  ( 5 )

/**
 * @brief FT800 Progress Bar Percentage Scale.
 * @details Used to divide value to percentage representation for FT800 series
 * controllers.
 */
#define FT800_PROGRESS_BAR_PERCENTAGE_SCALE                    ( 100 )

/**
 * @brief FT800 Progress Bar Right Offset.
 * @details Horizontal offset for rendering text on the right side for FT800
 * series controllers.
 */
#define FT800_PROGRESS_BAR_OFFSET_X_RIGHT                      ( 52 )

/**
 * @brief FT800 Progress Bar Left Offset.
 * @details Horizontal offset for rendering text on the left side for FT800
 * series controllers.
 */
#define FT800_PROGRESS_BAR_OFFSET_X_LEFT                       ( 26 )

/**
 * @brief FT800 Box Corner Radius Scale.
 * @details Used to scale the corner radius of Box shapes for FT800 series
 * controllers.
 */
#define FT800_BOX_RADIUS_SCALE                                 ( 2 )

/**
 * @brief FT800 Circle Radius Scale.
 * @details Scaling factor for rendering circle radius for FT800 series
 * controllers.
 */
#define FT800_CIRCLE_RADIUS_SCALE                              ( 2 )

/**
 * @brief FT800 Button Corner Radius Scale.
 * @details Determines the rounding applied to button corners for FT800 series
 * controllers.
 */
#define FT800_BUTTON_RADIUS_SCALE                              ( 2 )

/**
 * @brief FT800 Alignment Address
 * @details A parameter that aligns the address to 4 bytes for FT800 series
 * controllers.
 */
#define FT800_ALIGNMENT_ADDRESS                                 ( 0x03UL )

/**
 * @brief FT800 Touch Activation Value
 * @details Parameter to activate the Touch Engine for FT800 series controllers.
 */
#define FT800_TOUCH_ACTIVATION_VALUE                           ( 0x03UL )

/**
 * @brief FT800 Calibrate Text Font.
 * @details Font size of the text displayed on the screen during the calibration
 * routine for FT800 series controllers.
 */
#define FT800_CALIBRATE_TEXT_FONT                              ( 27 )

/**
 * @brief FT800 Calibrate Text Y.
 * @details Position on Y axle of the text displayed on the screen during the
 * calibration routine for FT800 series controllers.
 */
#define FT800_CALIBRATE_TEXT_Y                                 ( 120 )

/**
 * @brief FT800 Calibrate Text X.
 * @details Position on X axle of the text displayed on the screen during the
 * calibration routine for FT800 series controllers.
 */
#define FT800_CALIBRATE_TEXT_X                                 ( 80 )

/**
 * @brief FT800 RAM DL Offset 4 Bytes.
 * @details Takes the display list value for 4 bytes for FT800 series controllers.
 */
#define FT800_RAM_DL_OFFSET_4                                  ( 4 )

/**
 * @brief FT800 RAM DL Offset 8 Bytes.
 * @details Takes the display list value for 4 bytes for FT800 series controllers.
 */
#define FT800_RAM_DL_OFFSET_8                                  ( 8 )

/**
 * @brief FT800 Pixel Clock Divisor Value.
 * @details Determines the division factor for the main clock to generate the
 * pixel clock for FT800 series controllers.
 */
#define FT800_PCLK_VALUE                                       ( 0x05UL )

/**
 * @brief FT800 PWM Duty Cycle Default Value.
 * @details Sets the default duty cycle for the PWM output for backlight control
 * for FT800 series controllers.
 */
#define FT800_PWM_DUTY_VALUE                                   ( 0x80UL )

/**
 * @brief FT800 PWM Frequency Default Value.
 * @details Frequency value in Hz for the PWM output for backlight control for
 * FT800 series controllers.
 */
#define FT800_PWM_HZ_VALUE                                     ( 0x00FAUL )

/**
 * @brief FT800 GPIO Value.
 * @details Default output value for FT800 general-purpose IO pins after
 * initialization for FT800 series controllers.
 */
#define FT800_GPIO_VALUE                                       ( 0x80UL )

/**
 * @brief FT800 GPIO Direction Value.
 * @details Default direction configuration for FT800 GPIO pins after
 * initialization for FT800 series controllers.
 */
#define FT800_GPIO_DIR_VALUE                                   ( 0x80UL )

/**
 * @brief FT800 Display List SWAP Mode.
 * @details Value indicating a full SWAP of the display list for FT800 series
 * controllers.
 */
#define FT800_DLSWAP_VALUE                                     ( 2 )

/**
 * @brief FT800 Clear Buffer Mask.
 * @details Used to specify which buffers ( Color, Stencil, TAG ) should be
 * cleared for FT800 series controllers.
 */
#define FT800_CLR_BUFF_MASK                                    ( 1 )

/**
 * @brief FT800 RGB Initialization Value.
 * @details Default RGB color value used during screen clearing or color fill
 * for FT800 series controllers.
 */
#define FT800_RGB_INIT_VALUE                                   ( 255 )

/**
 * @brief FT800 Clock Spread Control.
 * @details Value to enable or disable spread spectrum clocking for FT800 series
 * controllers.
 */
#define FT800_CSPREAD_VALUE                                    ( 0 )

/**
 * @brief FT800 Vertical Screen Resolution.
 * @details Height of the active display area in pixels for FT800 series
 * controllers.
 */
#define FT800_VSIZE_VALUE                                      ( 272 )

/**
 * @brief FT800 Horizontal Screen Resolution.
 * @details Width of the active display area in pixels for FT800 series
 * controllers.
 */
#define FT800_HSIZE_VALUE                                      ( 480 )

/**
 * @brief FT800 PCLK Polarity.
 * @details Pixel clock polarity for FT800 series controllers.
 */
#define FT800_PCLK_POL_VALUE                                   ( 1 )

/**
 * @brief FT800 Vertical Sync Pulse End.
 * @details Number of lines where the vertical sync pulse ends for FT800 series
 * controllers.
 */
#define FT800_VSYNC1_VALUE                                     ( 10 )

/**
 * @brief FT800 Vertical Sync Pulse Start.
 * @details Number of lines where the vertical sync pulse starts for FT800 series
 * controllers.
 */
#define FT800_VSYNC0_VALUE                                     ( 0 )

/**
 * @brief FT800 Vertical Offset.
 * @details Number of lines after VSYNC0 to the start of active video for FT800
 * series controllers.
 */
#define FT800_VOFFSET_VALUE                                    ( 12 )

/**
 * @brief FT800 Vertical Cycle.
 * @details Total number of lines per screen for FT800 series controllers.
 */
#define FT800_VCYCLE_VALUE                                     ( 292 )

/**
 * @brief FT800 Horizontal Sync Pulse End.
 * @details Pixel clock position where HSYNC pulse ends for FT800 series
 * controllers.
 */
#define FT800_HSYNC1_VALUE                                     ( 41 )

/**
 * @brief FT800 Horizontal Sync Pulse Start.
 * @details Pixel clock position where HSYNC pulse begins for FT800 series
 * controllers.
 */
#define FT800_HSYNC0_VALUE                                     ( 0 )

/**
 * @brief FT800 Horizontal Offset.
 * @details Pixel clock offset to the start of active video for FT800 series
 * controllers.
 */
#define FT800_HOFFSET_VALUE                                    ( 43 )

/**
 * @brief FT800 Horizontal Cycle.
 * @details Total pixel clocks per line for FT800 series controllers.
 */
#define FT800_HCYCLE_VALUE                                     ( 548 )

/**
 * @brief FT800 Default Value For PCLK Register.
 * @details Used to disable the pixel clock during initial power-on configuration
 * for FT800 series controllers.
 */
#define FT800_PCLK_INIT_VALUE                                  ( 0x00UL )

/**
 * @brief FT800 Default Value For GPIO Register.
 * @details Sets all GPIO outputs to logic low on initialization for FT800 series
 * controllers.
 */
#define FT800_GPIO_INIT_VALUE                                  ( 0x00UL )

/**
 * @brief FT800 Point Size Scale Factor.
 * @details Used to convert size values to FT800 internal point format multiplying
 * by 16 for FT800 series controllers.
 */
#define FT800_POINT_SIZE_SCALE                                 ( 16 )

/**
 * @brief FT800 SPI Initialization Speed.
 * @details Set maximum SPI clock speed for FT800 series controllers.
 */
#define FT800_SPI_INIT_SPEED                                   ( 18000000 )

/**
 * @brief FT800 Normal SPI Operating Speed.
 * @details Default SPI clock frequency after initialization for FT800 series
 * controllers.
 */
#define FT800_SPI_SPEED                                        ( 4500000 )

/**
 * @brief FT800 Coordinate Value Mask.
 * @details Used to extract 16-bit valid coordinate data for FT800 series
 * controllers.
 */
#define FT800_READ_COORD_MASK                                  ( 0xFFFFUL )

/**
 * @brief FT800 Command Value Mask.
 * @details Used to extract the lower 16 bits from a command or address value
 * for FT800 series controllers.
 */
#define FT800_COMMAND_MASK                                     ( 0xFFFFUL )

/**
 * @brief FT800 LSB Mask.
 * @details Mask to extract 1 least significant bit for FT800 series controllers.
 */
#define FT800_SELECT_LSB_BITS_1                                ( 0x01UL )

/**
 * @brief FT800 LSB Mask.
 * @details Mask to extract 2 least significant bits for FT800 series controllers.
 */
#define FT800_SELECT_LSB_BITS_2                                ( 0x03UL )

/**
 * @brief FT800 LSB Mask.
 * @details Mask to extract 3 least significant bits for FT800 series controllers.
 */
#define FT800_SELECT_LSB_BITS_3                                ( 0x07UL )

/**
 * @brief FT800 LSB Mask.
 * @details Mask to extract 4 least significant bits for FT800 series controllers.
 */
#define FT800_SELECT_LSB_BITS_4                                ( 0x0FUL )

/**
 * @brief FT800 LSB Mask.
 * @details Mask to extract 5 least significant bits for FT800 series controllers.
 */
#define FT800_SELECT_LSB_BITS_5                                ( 0x1FUL )

/**
 * @brief FT800 LSB Mask.
 * @details Mask to extract 6 least significant bits for FT800 series controllers.
 */
#define FT800_SELECT_LSB_BITS_6                                ( 0x3FUL )

/**
 * @brief FT800 LSB Mask.
 * @details Mask to extract 7 least significant bits for FT800 series controllers.
 */
#define FT800_SELECT_LSB_BITS_7                                ( 0x7FUL )

/**
 * @brief FT800 Byte Mask.
 * @details Mask to extract full 8-bit values for FT800 series controllers.
 */
#define FT800_SELECT_BYTE                                      ( 0xFFUL )

/**
 * @brief FT800 Command Label Prefix.
 * @details Indicates the next SPI byte is a command instruction for FT800 series
 * controllers.
 */
#define FT800_SENT_COMMAND_LABEL                               ( 0x40UL )

/**
 * @brief FT800 Data Label Prefix.
 * @details Indicates the next SPI byte is data to be sent for FT800 series
 * controllers.
 */
#define FT800_SENT_DATA_LABEL                                  ( 0x80UL )

/**
 * @brief FT800 Receive Data Label.
 * @details Label used by FT800 to prefix received data bytes for FT800 series
 * controllers.
 */
#define FT800_RECEIVE_DATA_LABEL                               ( 0x3FUL )

/**
 * @brief FT800 Command Parameter Offset.
 * @details Bit shift offset for 2-byte command parameters for FT800 series
 * controllers.
 */
#define FT800_OFFSET_COMMAND_PARAM_BYTES_2                     ( 16 )

/**
 * @brief FT800 Offset Access First Received Byte.
 * @details Bit shift for accessing 1-byte response data for FT800 series
 * controllers.
 */
#define FT800_OFFSET_RECEIVED_DATA_BYTES_1                     ( 8 )

/**
 * @brief FT800 Offset Access Second Received Byte.
 * @details Bit shift for accessing 2-byte response data for FT800 series
 * controllers.
 */
#define FT800_OFFSET_RECEIVED_DATA_BYTES_2                     ( 16 )

/**
 * @brief FT800 Offset Access Second Received Byte.
 * @details Bit shift for accessing 3-byte response data for FT800 series
 * controllers.
 */
#define FT800_OFFSET_RECEIVED_DATA_BYTES_3                     ( 24 )

/**
 * @brief FT800 Offset Access Second Received Byte.
 * @details Bit shift for accessing 4-byte response data for FT800 series
 * controllers.
 */
#define FT800_OFFSET_RECEIVED_DATA_BYTES_4                    ( 32 )

/**
 * @brief FT800 Green Color Bit Offset.
 * @details Used when extracting green from RGB565 color value for FT800 series
 * controllers.
 */
#define FT800_OFFSET_RGB_COLOR_GREEN                           ( 5 )

/**
 * @brief FT800 Red Color Bit Offset.
 * @details Used when extracting red from RGB565 color value for FT800 series
 * controllers.
 */
#define FT800_OFFSET_RGB_COLOR_RED                             ( 11 )

/**
 * @brief FT800 Offset Read Coordinate Bytes 2.
 * @details Shifting the read coordinates by 2 bytes for FT800 series controllers.
 */
#define FT800_OFFSET_READ_COORD_BYTES_2                        ( 16 )

/**
 * @brief FT800 Offset Received Address Bytes 1.
 * @details Shifting the received address for 1 byte for FT800 series controllers.
 */
#define FT800_OFFSET_RECEIVED_ADDRESS_BYTES_1                  ( 8 )

/**
 * @brief FT800 Offset Received Address Bytes 2.
 * @details Shifting the received address by 2 bytes for FT800 series controllers.
 */
#define FT800_OFFSET_RECEIVED_ADDRESS_BYTES_2                  ( 16 )

/**
 * @brief FT800 Offset Received Address Bytes 3.
 * @details Shifting the received address by 3 bytes for FT800 series controllers.
 */
#define FT800_OFFSET_RECEIVED_ADDRESS_BYTES_3                  ( 24 )

/**
 * @brief FT800 Offset Received Address Bytes 4.
 * @details Shifting the received address by 4 bytes for FT800 series controllers.
 */
#define FT800_OFFSET_RECEIVED_ADDRESS_BYTES_4                  ( 32 )

/**
 * @brief FT800 Offset Sent Address Bytes 1.
 * @details Shifting 1 byte of the address to be sent for FT800 series controllers.
 */
#define FT800_OFFSET_SENT_ADDRESS_BYTES_1                      ( 8 )

/**
 * @brief FT800 Offset Sent Address Bytes 2.
 * @details Shifting 2 byte of the address to be sent for FT800 series controllers.
 */
#define FT800_OFFSET_SENT_ADDRESS_BYTES_2                       ( 16 )

/**
 * @brief FT800 Offset Sent Address Bytes 3.
 * @details Shifting 3 byte of the address to be sent for FT800 series controllers.
 */
#define FT800_OFFSET_SENT_ADDRESS_BYTES_3                      ( 24 )

/**
 * @brief FT800 Offset Sent Address Bytes 4.
 * @details Shifting 4 byte of the address to be sent for FT800 series controllers.
 */
#define FT800_OFFSET_SENT_ADDRESS_BYTES_4                      ( 32 )

/**
 * @brief FT800 Data Length Offset 1 Byte.
 * @details Used to shift 1 byte data fields for FT800 series controllers.
 */
#define FT800_DATA_LENGTH_BYTES_1                              ( 8 )

/**
 * @brief FT800 Data Length Offset 2 Bytes.
 * @details Used to shift 2 bytes of data fields for FT800 series controllers.
 */
#define FT800_DATA_LENGTH_BYTES_2                              ( 16 )

/**
 * @brief FT800 Data Length Offset 3 Bytes.
 * @details Used to shift 3 bytes of data fields for FT800 series controllers.
 */
#define FT800_DATA_LENGTH_BYTES_3                              ( 24 )

/**
 * @brief FT800 Data Length Offset 4 Bytes.
 * @details Used to shift 4 bytes of data fields for FT800 series controllers.
 */
#define FT800_DATA_LENGTH_BYTES_4                              ( 32 )

/**
 * @brief FT800 Touch Number Limit.
 * @details Maximum number of touch recognition for FT800 series controllers.
 */
#define FT800_TOUCH_NUM                                        ( 1 )

/**
 * @brief FT800 Gesture Items Limit Setting.
 * @details Gesture items limit for FT800 series controllers.
 */
#define FT800_GESTURE_ITEMS_MAX                                ( 7 )

  /*! @} */ // ft800_constants
 /*! @} */ // ft800
/*! @} */ // mwgroup

#endif
// ------------------------------------------------------------------------- END
