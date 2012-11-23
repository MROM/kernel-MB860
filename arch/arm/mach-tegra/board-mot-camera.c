#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>

#include <mach/nvodmcam.h>

#include "board-mot.h"
#include "gpio-names.h"

static struct nvodmcam_platform_data pdata;

static struct platform_device nvodmcam_platform_device = {
	.name = NVODMCAM_DRIVER_NAME,
	.id = -1,
	.dev = {
		.platform_data = &pdata,
	},
};

#define SENSOR(g,t)   {g.sensor = t;}
#define ASSIGN(g,n,s) {g.num = TEGRA_GPIO_P##n; g.state = s;}
#define UNASSIGN(g)   {g.num = -1;              g.state = -1;}

int __init mot_nvodmcam_init(void)
{
	int i;

	memset((unsigned char *)&pdata, 0, sizeof(pdata));

	for(i = 0; i < NVODMCAM_MAX_CAMERAS; i++) {
		UNASSIGN(pdata.camera[i].cam_pd);
		UNASSIGN(pdata.camera[i].cam_rs);
		UNASSIGN(pdata.camera[i].flash_rs);
	}

	pdata.num_cameras = 2;

	/* camera 0 - back camera */
	if (system_rev == HWREV_UNDEFINED ||
		(HWREV_TYPE_IS_MORTABLE(system_rev) &&
		 (HWREV_REV(system_rev) == HWREV_REV_1 ||
		  HWREV_REV(system_rev) == HWREV_REV_1B))) {
		/* Olympus UND,M1,M1B -> OV5650 pd=N5,rs=D2 */
		SENSOR(pdata.camera[0], OV5650);
		ASSIGN(pdata.camera[0].cam_pd, N5, 0);
		ASSIGN(pdata.camera[0].cam_rs, D2, 1);
	}
	else {
		/* Olympus other -> OV5650 pd=BB1,rs=D2 */
		SENSOR(pdata.camera[0], OV5650);
		ASSIGN(pdata.camera[0].cam_pd, BB1, 0);
		ASSIGN(pdata.camera[0].cam_rs, D2,  1);
	}

	/* camera 0 - flash */
	if (system_rev == HWREV_UNDEFINED ||
		(HWREV_TYPE_IS_MORTABLE(system_rev) &&
		 (HWREV_REV(system_rev) == HWREV_REV_1 ||
		  HWREV_REV(system_rev) == HWREV_REV_1B)) ||
		(HWREV_TYPE_IS_PORTABLE(system_rev) &&
		 (HWREV_REV(system_rev) == HWREV_REV_0))) {
		/* Olympus UND,M1,M1B,P0 -> LM3554 rs=BB4 */
		ASSIGN(pdata.camera[0].flash_rs, BB4, 1);
	}
	else {
		/* Olympus other -> LM3554 rs=T3 */
		ASSIGN(pdata.camera[0].flash_rs, T3, 1);
	}

	/* camera 1 - front camera */
	if (HWREV_TYPE_IS_FINAL(system_rev) ||
		(HWREV_TYPE_IS_PORTABLE(system_rev) &&
		 HWREV_REV(system_rev) >= HWREV_REV_2C)) {
		/* Olympus P2C+ -> SOC380 pd=BB5,rs=L4 */
		SENSOR(pdata.camera[1], SOC380);
		ASSIGN(pdata.camera[1].cam_pd, BB5, 0);
		ASSIGN(pdata.camera[1].cam_rs, L4,  1);
	}
	else {
		/* Olympus other -> OV7692 pd=BB5,no rs */
		SENSOR(pdata.camera[1], OV7692);
		ASSIGN(pdata.camera[1].cam_pd, BB5, 0);
	}

	return platform_device_register(&nvodmcam_platform_device);
}
