/*
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-08 11:49:57
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-08 14:11:11
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\LED\Drivers\BSP\LED\led.c
 * @Description: GPIO配置步骤
 *
 * Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#include "./BSP/LED/led.h"

void led_init(void)
{
    /* 使能 GPIOB 时钟 */
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* GPIO 初始化结构体 */
    GPIO_InitTypeDef gpio_init_struct;

    /* 设置 GPIO 初始化参数*/
    /* 1.设置引脚*/
    gpio_init_struct.Pin = GPIO_PIN_5;

    /* 2.设置 GPIO 模式 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;

    /* 3.设置上/下拉 */
    gpio_init_struct.Pull = GPIO_NOPULL;

    /* 4.设置 IO 速度*/
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;

    /* 设置工作模式，初始化GPIOB */
    HAL_GPIO_Init(GPIOB, &gpio_init_struct);

    /* 设置输出状态 */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET); // 0为灯亮；1为灯灭。
}