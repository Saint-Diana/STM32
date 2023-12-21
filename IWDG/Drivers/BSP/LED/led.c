/*
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-08 14:30:31
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-08 15:19:14
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\LED_2\Drivers\BSP\LED\led.c
 * @Description:
 *
 * Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#include "led.h"

void led_init(void)
{
    /* 使能 GPIO 时钟 */
    LED0_GPIO_CLK_ENABLE();
    LED1_GPIO_CLK_ENABLE();

    /* 设置初始化参数 */
    GPIO_InitTypeDef gpio_init_struct;
    gpio_init_struct.Pin = LED0_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_NOPULL;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;

    /* 初始化 LED0 */
    HAL_GPIO_Init(LED0_GPIO_PORT, &gpio_init_struct);

    /* 初始化 LED1*/
    gpio_init_struct.Pin = LED1_GPIO_PIN;
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);

    /* 初始关闭 LED0、LED1*/
    LED0(1);
    LED1(1);
}