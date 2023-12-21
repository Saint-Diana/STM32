/*
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-21 11:47:47
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-21 11:59:35
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\IWDG\Drivers\BSP\WDG\wdg.c
 * @Description: Watchdog相关代码
 *
 * Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#include "wdg.h"

IWDG_HandleTypeDef g_handle_iwdg;

void iwdg_init(uint32_t prer, uint32_t reload)
{
    g_handle_iwdg.Instance = IWDG;
    g_handle_iwdg.Init.Prescaler = prer;
    g_handle_iwdg.Init.Reload = reload;
    HAL_IWDG_Init(&g_handle_iwdg);
}

void iwdg_refresh(void)
{
    HAL_IWDG_Refresh(&g_handle_iwdg);
}