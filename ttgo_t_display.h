/*

MIT No Attribution

Copyright (c) 2020-2021 Mika Tuupola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-cut-

SPDX-License-Identifier: MIT-0

*/

#ifndef _HAGL_HAL_CONFIG_H
#define _HAGL_HAL_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mipi_dcs.h>

#define MIPI_DISPLAY_ADDRESS_MODE   (MIPI_DCS_ADDRESS_MODE_SWAP_XY|MIPI_DCS_ADDRESS_MODE_MIRROR_Y)

#define MIPI_DISPLAY_OFFSET_X       (40)
#define MIPI_DISPLAY_OFFSET_Y       (52)
#define MIPI_DISPLAY_PIN_BL         (GPIO_PIN_10)
#define MIPI_DISPLAY_PORT_BL        (GPIOB)
#define MIPI_DISPLAY_GPIO_MODE_BL   (GPIO_MODE_OUT_PP)
#define MIPI_DISPLAY_PIN_CLK        (GPIO_PIN_5)
#define MIPI_DISPLAY_PORT_CLK       (GPIOA)
#define MIPI_DISPLAY_PIN_MISO       (-1)
#define MIPI_DISPLAY_PORT_MISO      (-1)

#define MIPI_DISPLAY_WIDTH          (240)
#define MIPI_DISPLAY_HEIGHT         (135)

#ifdef __cplusplus
}
#endif
#endif /* _HAGL_HAL_CONFIG_H */