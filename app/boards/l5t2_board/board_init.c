/*
 * Copyright 2024  NXP
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/init.h>
#include <zephyr/kernel.h>



static int l5t2_board_init(void)
{
    printk("Board Initialized!!!\n");
    return 0;
}

SYS_INIT(l5t2_board_init, POST_KERNEL, 40);
