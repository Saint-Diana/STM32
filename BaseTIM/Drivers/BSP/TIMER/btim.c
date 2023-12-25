/*
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-25 11:12:27
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-25 11:47:43
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\BaseTIM\Drivers\BSP\TIMER\btim.c
 * @Description: 基本定时器。使用定时器6，实现500ms定时器更新中断，在中断里翻转LED0
 *
 * Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#include "btim.h"
#include "led.h"

TIM_HandleTypeDef g_handle_tim_base;

void btim_timx_int_init(uint16_t arr, uint16_t psc)
{
    g_handle_tim_base.Instance = TIM6;      /* 定时器6基地址 */
    g_handle_tim_base.Init.Prescaler = psc; /* psc + 1 == PSC 寄存器值 */
    g_handle_tim_base.Init.Period = arr;    /* 自动重装载值 ARR 寄存器 */
    HAL_TIM_Base_Init(&g_handle_tim_base);
    HAL_TIM_Base_Start_IT(&g_handle_tim_base); /* 使能更新中断并且启动计数器 */
}

/* HAL_TIM_Base_Init() 的回调函数 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    /* 真正的初始化操作 */
    if (htim->Instance == TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();           /* 初始化CLK */
        HAL_NVIC_SetPriority(TIM6_IRQn, 0, 0); /* 设置中断优先级 */
        HAL_NVIC_EnableIRQ(TIM6_IRQn);         /* 使能中断 */
    }
}

/* 编写TIM6的中断服务函数 */
void TIM6_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_handle_tim_base);    /* 调用公共处理函数 */
    HAL_TIM_Base_Start_IT(&g_handle_tim_base); /* 需要重新开中断 */
}

/* 重写更新中断回调 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5); /* 翻转LED0 */
    }
}