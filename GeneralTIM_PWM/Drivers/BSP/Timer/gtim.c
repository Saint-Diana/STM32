/*
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-25 15:25:29
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-25 15:59:19
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\GeneralTIM\Drivers\BSP\Timer\gtim.c
 * @Description: 通过定时器输出的PWM控制LED0，实现类似手机呼吸灯的效果
 *
 * PWM周期 = (ARR + 1) * (PSC + 1) / Ft    ==> Ft = 72MHz
 *
 * Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */

#include "gtim.h"

TIM_HandleTypeDef g_handle_tim; /* 初始化句柄 */

/* 通用定时器PWM输出初始化函数 */
void gtim_pwm_chy_init(uint16_t arr, uint16_t psc)
{
    g_handle_tim.Instance = TIM3;                       /* 寄存器基地址 */
    g_handle_tim.Init.Prescaler = psc;                  /* 分频系数 */
    g_handle_tim.Init.Period = arr;                     /* 自动重装载值 */
    g_handle_tim.Init.CounterMode = TIM_COUNTERMODE_UP; /* 向上计数模式 */
    HAL_TIM_PWM_Init(&g_handle_tim);

    TIM_OC_InitTypeDef tim_oc_init_struct;
    tim_oc_init_struct.OCMode = TIM_OCMODE_PWM1;        /* 输出比较模式设置为PWM模式1 */
    tim_oc_init_struct.Pulse = arr / 2;                 /* 比较值：设置占空比。如果设置为 arr / 2，那么占空比就是50% */
    tim_oc_init_struct.OCPolarity = TIM_OCPOLARITY_LOW; /* 输出极性：低电平有效 */
    HAL_TIM_PWM_ConfigChannel(&g_handle_tim, &tim_oc_init_struct, TIM_CHANNEL_2);

    HAL_TIM_PWM_Start(&g_handle_tim, TIM_CHANNEL_2);
}

/* 初始化回调函数，设置NVIC、GPIO、CLK等 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        /* 初始化GPIO */
        GPIO_InitTypeDef gpio_init_struct;
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_TIM3_CLK_ENABLE(); /* 使能TIM3时钟 */

        gpio_init_struct.Pin = GPIO_PIN_5;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP; /* 推挽复用 */
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &gpio_init_struct);

        __HAL_RCC_AFIO_CLK_ENABLE();     /* 使能AFIO时钟 */
        __HAL_AFIO_REMAP_TIM3_PARTIAL(); /* 把TIM3的四个通道重映射到PB4，PB5，PB0，PB1 */
    }
}