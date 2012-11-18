/*
 * arch/arm/mach-tegra/board.h
 *
 * Copyright (C) 2010 Google, Inc.
 *
 * Author:
 *	Colin Cross <ccross@google.com>
 *	Erik Gilling <konkers@google.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __MACH_TEGRA_BOARD_H
#define __MACH_TEGRA_BOARD_H

#include <linux/types.h>

struct tegra_suspend_platform_data;

void __init tegra_init_early(void);
void __init tegra_mc_init(void);
void __init tegra_common_init(void);
void __init tegra_map_common_io(void);
void __init tegra_init_irq(void);
void __init tegra_init_clock(void);
void __init tegra_init_suspend(struct tegra_suspend_platform_data *plat);

void __init generic_reserve(void);

#ifdef CONFIG_CPU_IDLE
void __init tegra_init_idle(struct tegra_suspend_platform_data *plat);
#else
#define tegra_init_idle(plat) (0)
#endif

#ifdef CONFIG_CPU_FREQ
int tegra_start_dvfsd(void);
#else
#define tegra_start_dvfsd() (0)
#endif

#define TEGRA_ALL_REVS (~0ul)
bool tegra_chip_compare(u32 chip, u32 major_rev, u32 minor_rev);

#define tegra_is_ap20_a03() tegra_chip_compare(0x20, 0x1, 0x3)

bool tegra_is_ap20_a03p(void);

extern struct sys_timer tegra_timer;
#endif

struct cpcap_display_led {
        unsigned int display_reg;
        unsigned int display_mask;
        unsigned int display_on;
        unsigned int display_off;
        unsigned int display_init;
        unsigned int poll_intvl;
        unsigned int zone0;
        unsigned int zone1;
        unsigned int zone2;
        unsigned int zone3;
        unsigned int zone4;
};

struct cpcap_button_led {
        unsigned int button_reg;
        unsigned int button_mask;
        unsigned int button_on;
        unsigned int button_off;
        const char *regulator;
};

struct cpcap_kpad_led {
        unsigned int kpad_reg;
        unsigned int kpad_mask;
        unsigned int kpad_on;
        unsigned int kpad_off;
};

struct cpcap_rgb_led {
        unsigned int rgb_reg;
        unsigned int rgb_mask;
        unsigned int rgb_on;
        unsigned int rgb_off;
        const char *regulator;
        bool regulator_macro_controlled;
};

struct cpcap_leds {
        struct cpcap_display_led display_led;
        struct cpcap_button_led button_led;
        struct cpcap_kpad_led kpad_led;
        struct cpcap_rgb_led rgb_led;
};

