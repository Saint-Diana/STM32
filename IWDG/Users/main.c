/*
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-08 14:29:22
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-21 13:44:46
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\IWDG\Users\main.c
 * @Description: 实现 KEY 0 作为 LED 0 的开关
 *
 * Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "led.h"
#include "key.h"
#include "wdg.h"

int main(void)
{
    /* 初始化 HAL*/
    HAL_Init();

    /* 初始化系统时钟 */
    sys_stm32_clock_init(RCC_PLL_MUL9);

    /* 延时初始化 */
    delay_init(72);

    /* 串口初始化 */
    usart_init(115200);

    /* 串口打印 */
    printf("您还没喂狗，请及时喂狗！！！\r\n");

    /* 初始化IDWG的溢出时间为1s；溢出时间 = prer * reload / 40khz */
    iwdg_init(IWDG_PRESCALER_64, 625);

    while (1)
    {
        delay_ms(500);
        iwdg_refresh();
        printf("已经喂狗\r\n");
    }
}