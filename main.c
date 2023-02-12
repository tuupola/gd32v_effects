/*

MIT No Attribution

Copyright (c) 2018-2020 Mika Tuupola

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

#include <stdio.h>

#include "nuclei_sdk_soc.h"

#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>

#include <hagl_hal.h>
#include <hagl.h>
#include <font6x9.h>
#include <fps.h>
#include <aps.h>

#include "metaballs.h"
#include "plasma.h"
#include "rotozoom.h"

static char demo[3][32] = {
    "METABALLS",
    "PLASMA",
    "ROTOZOOM",
};


static fps_instance_t fps;
static aps_instance_t bps;

static uint8_t effect = 2;
static hagl_bitmap_t *bb;
static uint32_t irq_count = 0;
static uint8_t switch_flag = 0;
static uint8_t fps_flag = 0;

static hagl_backend_t *display;

void eclic_mtip_handler(void)
{
    /* Fire IRQ every two seconds. */
    uint64_t now = SysTimer_GetLoadValue();
    SysTimer_SetCompareValue(now + 2 * SOC_TIMER_FREQ);

    /* Demo is changed every five IRQs. */
    if (0 == (++irq_count % 5)) {
        switch_flag = 1;
    } else {
        fps_flag = 1;
    }
}

void systimer_init()
{
    uint64_t now = SysTimer_GetLoadValue();
    uint64_t future = now + 2 * SOC_TIMER_FREQ;

    printf("Init and start timer.\n\r");

    ECLIC_Register_IRQ(
        SysTimer_IRQn, ECLIC_NON_VECTOR_INTERRUPT, ECLIC_LEVEL_TRIGGER,
        1, 0,
        eclic_mtip_handler
    );

    __enable_irq();

    SysTimer_SetCompareValue(future);
}

void main()
{
    display = hagl_init();

    hagl_color_t green = hagl_color(display, 0, 255, 0);
    wchar_t message[32];

    printf("Hello\r\n");
    systimer_init();

    fps_init(&fps);

    hagl_clear(display);
    hagl_set_clip(display, 0, 20, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 21);

    switch_flag = 1;

    while (1) {
        switch(effect) {
        case 0:
            metaballs_animate();
            metaballs_render(display);
            break;
        case 1:
            plasma_render(display);
            break;
        case 2:
            rotozoom_animate();
            rotozoom_render(display);
            break;
        }

        hagl_flush(display);
        fps_update(&fps);

        if (switch_flag) {
            switch_flag = 0;
            printf("%s at %d FPS\r\n", demo[effect], (uint32_t)fps.current);
            effect = (effect + 1) % 3;

            switch(effect) {
            case 0:
                metaballs_init();
                break;
            case 1:
                plasma_init(display);
                break;
            case 2:
                // rotozoom_init();
                break;
            }

            /* Print the message on top left corner. */
            swprintf(message, sizeof(message), L"%s    ", demo[effect]);
            hagl_set_clip(display, 0, 0, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1);
            hagl_put_text(display, message, 4, 4, green, font6x9);
            hagl_set_clip(display, 0, 20, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 21);

            fps_reset(&fps);
        }

        if (fps_flag) {
            fps_flag = 0;
            /* Print the message on lower right corner. */
            swprintf(message, sizeof(message), L"%.*f FPS  ", 0, fps.current);
            hagl_set_clip(display, 0, 0, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1);
            hagl_put_text(display, message, DISPLAY_WIDTH - 40, DISPLAY_HEIGHT - 14, green, font6x9);
            hagl_set_clip(display, 0, 20, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 21);

        }
    }
}
