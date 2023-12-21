/*
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-08 14:29:22
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-18 17:29:13
 * @FilePath: \Projectsd:\work\CodeSpace\STM32\EXTI_GPIO\Users\main.c
 * @Description: 使用EXTI实现 KEY 0 作为 LED 0 的开关
 *
 * Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "led.h"
#include "key.h"
#include "exti.h"

int main(void)
{
    /* 初始化 HAL*/
    HAL_Init();

    /* 初始化系统时钟 */
    sys_stm32_clock_init(RCC_PLL_MUL9);

    /* 延时初始化 */
    delay_init(72);

    /* LED 初始化 */
    led_init();

    /* EXTI 初始化 */
    exti_init();

    while (1)
    {
        LED1(1);
        delay_ms(500);
        LED1(0);
        delay_ms(500);
    }
}