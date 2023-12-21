/***
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-21 11:47:54
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-21 11:50:39
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\IWDG\Drivers\BSP\WDG\wdg.h
 * @Description: Watchdog相关代码
 * @
 * @Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#ifndef _WDG_H
#define _WDG_H

#include "sys.h"

extern IWDG_HandleTypeDef g_handle_iwdg;

void iwdg_init(uint32_t prer, uint32_t reload);

void iwdg_refresh(void);

#endif