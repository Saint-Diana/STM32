/***
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-25 11:12:33
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-25 11:18:53
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\BaseTIM\Drivers\BSP\TIMER\btim.h
 * @Description: 基本定时器
 * @
 * @Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#ifndef _BTIM_H
#define _BTIM_H

#include "sys.h"

/* 全局变量：定时器初始化句柄 */
extern TIM_HandleTypeDef g_handle_tim_base;

/* 定时器中断初始化函数 */
void btim_timx_int_init(uint16_t arr, uint16_t psc);

#endif