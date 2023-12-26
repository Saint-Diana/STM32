/***
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-26 10:08:38
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-26 10:13:43
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\GeneralTIM_Capture\Drivers\BSP\Timer\gtim.h
 * @Description: 通用定时器输入捕获实验：通过定时器5通道1来捕获按键高电平脉宽时间，通过串口打印出来。
 * @
 * @Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#ifndef _GTIM_H
#define _GTIM_H

#include "sys.h"

extern TIM_HandleTypeDef g_handle_tim;

void gtim_capture_init(uint32_t arr, uint32_t psc);

#endif