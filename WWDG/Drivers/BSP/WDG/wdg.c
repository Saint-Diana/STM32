/*
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-21 15:41:46
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-21 16:12:05
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\WWDG\Drivers\BSP\WDG\wdg.c
 * @Description: WWDG
 *
 * Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#include "wdg.h"
#include "led.h"

WWDG_HandleTypeDef g_handle_wwdg;

void wwdg_init(uint8_t tr, uint8_t wr, uint32_t fprer)
{
    g_handle_wwdg.Instance = WWDG;
    g_handle_wwdg.Init.Prescaler = fprer;         /* 预分频值 */
    g_handle_wwdg.Init.Counter = tr;              /* 计数器值 T[6:0] */
    g_handle_wwdg.Init.Window = wr;               /* 窗口上限值 W[6:0] */
    g_handle_wwdg.Init.EWIMode = WWDG_EWI_ENABLE; /* 是否允许产生提前唤醒中断 */
    HAL_WWDG_Init(&g_handle_wwdg);
}

/* WWDG Msp 回调函数 */
void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{
    /* 配置 NVIC、CLOCK 等 */
    __HAL_RCC_WWDG_CLK_ENABLE();           /* 使能 WWDG 时钟 */
    HAL_NVIC_SetPriority(WWDG_IRQn, 0, 0); /* 设置优先级 */
    HAL_NVIC_EnableIRQ(WWDG_IRQn);         /* 使能中断请求 */
}

/* WWDG 中断服务函数 */
void WWDG_IRQHandler(void)
{
    HAL_WWDG_IRQHandler(&g_handle_wwdg); /* 调用 HAL 库提供的 WWDG 中断的公共处理函数 */
}

/* WWDG 提前唤醒回调函数 */
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
    /* 如果提前唤醒，就翻转LED0 */
    LED0_TOGGLE();
}