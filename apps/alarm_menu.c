/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 *
 * Copyright (C) 2003 Uwe Freese
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/
#include "config.h"

#include <stdbool.h>

#include "lcd.h"
#include "action.h"
#include "kernel.h"
#include <string.h>
#include "settings.h"
#include "power.h"
#include "icons.h"
#include "rtc.h"
#include "misc.h"
#include "screens.h"
#include "talk.h"
#include "lang.h"
#include "alarm_menu.h"
#include "splash.h"
#include "viewport.h"

int alarm_screen(void)
{
    bool usb, update;
    struct tm *now = get_time();
    struct tm atm;
    memcpy(&atm, now, sizeof(struct tm));
    rtc_get_alarm(&atm.tm_hour, &atm.tm_min);

    /* After a battery change the RTC values are out of range */
    if (!valid_time(&atm))
        memcpy(&atm, now, sizeof(struct tm));
    atm.tm_sec = 0;

    usb = set_time_screen(str(LANG_ALARM_MOD_TIME), &atm, false);
    update = valid_time(&atm); /* set_time returns invalid time if canceled */

    if (!usb && update)
    {
            /* Custom change (from 11_alarm_menu_plus, r30186 era):
             * upstream rejects alarms less than 2 minutes ahead to
             * avoid the alarm firing during the shutdown procedure;
             * here alarms are accepted at any time, and the splash /
             * voice feedback reports the alarm time that was set
             * instead of the remaining time. */
            rtc_init();
            rtc_set_alarm(atm.tm_hour,atm.tm_min);
            rtc_enable_alarm(true);
            if (global_settings.talk_menu)
            {
                talk_id(LANG_ALARM_MOD_TIME_TO_GO, true);
                talk_value(atm.tm_hour, UNIT_HOUR, true);
                talk_value(atm.tm_min, UNIT_MIN, true);
                talk_force_enqueue_next();
            }
            /* (voiced above) */
            splashf(HZ*2, str(LANG_ALARM_MOD_TIME_TO_GO),
                           atm.tm_hour, atm.tm_min);
    }

    if (usb || !update)
    {
        if (!usb)
            splash(HZ*2, ID2P(LANG_ALARM_MOD_DISABLE));
        rtc_enable_alarm(false);
        return 1;
    }
    return 0;
}
