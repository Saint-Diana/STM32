/*
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-08 14:29:22
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-08 16:26:18
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\LED_2\Users\main.c
 * @Description: 实现 KEY 0 作为 LED 0 的开关
 *
 * Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "led.h"
#include "key.h"

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

    /* KEY 初始化 */
    key_init();

    while (1)
    {
        if (key_scan())
        {
            /* 按下 KEY 0，反转 LED 0 (GPIOB GPIO_PIN_5) 的值 */
            HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_GPIO_PIN);
        }
        else
        {
            delay_ms(10);
        }
    }
}