/*
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-08 14:29:22
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-25 16:16:20
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\GeneralTIM\Users\main.c
 * @Description: 实现 KEY 0 作为 LED 0 的开关
 *
 * Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "led.h"
#include "key.h"
#include "gtim.h"

extern TIM_HandleTypeDef g_handle_tim;

int main(void)
{
    uint16_t ledrpwmval = 0;
    uint8_t dir = 1;

    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
    usart_init(115200);                 /* 串口初始化为115200 */
    led_init();                         /* 初始化LED */
    gtim_pwm_chy_init(500 - 1, 72 - 1); /* 1Mhz的计数频率,2Khz的PWM. */

    while (1)
    {
        delay_ms(10);

        if (dir)
            ledrpwmval++; /* dir==1 ledrpwmval递增 */
        else
            ledrpwmval--; /* dir==0 ledrpwmval递减 */

        if (ledrpwmval > 300)
            dir = 0; /* ledrpwmval到达300后，方向为递减 */
        if (ledrpwmval == 0)
            dir = 1; /* ledrpwmval递减到0后，方向改为递增 */

        /* 修改比较值控制占空比 */
        __HAL_TIM_SET_COMPARE(&g_handle_tim, TIM_CHANNEL_2, ledrpwmval);
    }
}