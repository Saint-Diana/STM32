/***
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-25 15:25:22
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-25 15:30:05
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\GeneralTIM\Drivers\BSP\Timer\gtim.h
 * @Description: 通过定时器输出的PWM控制LED0，实现类似手机呼吸灯的效果
 * @
 * @Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#ifndef _GTIM_H
#define _GTIM_H

#include "sys.h"

extern TIM_HandleTypeDef g_handle_tim;

void gtim_pwm_chy_init(uint16_t arr, uint16_t psc);

#endif