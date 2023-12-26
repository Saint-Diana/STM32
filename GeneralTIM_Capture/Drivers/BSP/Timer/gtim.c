/*
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-26 10:08:44
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-26 11:09:12
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\GeneralTIM_Capture\Drivers\BSP\Timer\gtim.c
 * @Description: 通用定时器输入捕获实验：通过定时器5通道1来捕获按键高电平脉宽时间，通过串口打印出来。 1MHz 计数频率 ==> PSC = 71; ARR = 65535
 *               上升沿捕获、IC1映射在TI1上、不分频、不滤波。
 *
 * Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#include "gtim.h"

TIM_HandleTypeDef g_handle_tim;

/* 配置定时器基础工作参数 */
void gtim_capture_init(uint32_t arr, uint32_t psc)
{
    g_handle_tim.Instance = TIM5;
    g_handle_tim.Init.Period = arr;
    g_handle_tim.Init.Prescaler = psc;
    g_handle_tim.Init.CounterMode = TIM_COUNTERMODE_UP; /* 递增计数 */
    HAL_TIM_IC_Init(&g_handle_tim);                     /* IC == Input Capture 输入捕获 */

    TIM_IC_InitTypeDef init_struct = {0};
    init_struct.ICPolarity = TIM_ICPOLARITY_RISING;                       /* 上升沿捕获 */
    init_struct.ICSelection = TIM_ICSELECTION_DIRECTTI;                   /* 映射到TI1上 */
    init_struct.ICPrescaler = TIM_ICPSC_DIV1;                             /* 配置输入分频 */
    init_struct.ICFilter = 0;                                             /* 不滤波 */
    HAL_TIM_IC_ConfigChannel(&g_handle_tim, &init_struct, TIM_CHANNEL_1); /* 配置输入通道映射、捕获边沿等 */

    __HAL_TIM_ENABLE_IT(&g_handle_tim, TIM_IT_UPDATE); /* 使能定时器更新中断 */
    HAL_TIM_IC_Start_IT(&g_handle_tim, TIM_CHANNEL_1); /* 使能输入捕获和捕获中断 */
}

/* 定时器输入捕获MSP初始化 */
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM5)
    {
        GPIO_InitTypeDef gpio_init_struct;
        __HAL_RCC_TIM5_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        gpio_init_struct.Pin = GPIO_PIN_0;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLDOWN;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);

        HAL_NVIC_SetPriority(TIM5_IRQn, 0, 0); /* 设置优先级 */
        HAL_NVIC_EnableIRQ(TIM5_IRQn);         /* 使能中断 */
    }
}

/* 输入捕获状态(g_timxchy_cap_sta)
 * [7]  :0,没有成功的捕获;1,成功捕获到一次.
 * [6]  :0,还没捕获到高电平;1,已经捕获到高电平了.
 * [5:0]:捕获高电平后溢出的次数,最多溢出63次,所以最长捕获值 = 63*65536 + 65535 = 4194303
 *       注意:为了通用,我们默认ARR和CCRy都是16位寄存器,对于32位的定时器(如:TIM5),也只按16位使用
 *       按1us的计数频率,最长溢出时间为:4194303 us, 约4.19秒
 *
 *      (说明一下：正常32位定时器来说,1us计数器加1,溢出时间:4294秒)
 */
uint8_t g_timxchy_cap_sta = 0;  /* 输入捕获状态 */
uint16_t g_timxchy_cap_val = 0; /* 输入捕获值 */

void TIM5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_handle_tim); /* 定时器中断公共处理函数 */
}

/* 定时器输入捕获中断处理回调函数 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM5)
    {
        /* g_timxchy_cap_sta[7] == 0 -> 没有成功捕获 */
        if ((g_timxchy_cap_sta & 0x80) == 0)
        {
            /* g_timxchy_cap_sta[6] == 1 -> 已经捕获到高电平了(捕获到一个下降沿) */
            if ((g_timxchy_cap_sta & 0x40))
            {
                g_timxchy_cap_sta |= 0x80;                                                    /* 置g_timxchy_cap_sta[7]为1 */
                g_timxchy_cap_val = HAL_TIM_ReadCapturedValue(&g_handle_tim, TIM_CHANNEL_1);  /* 获取当前的捕获值 */
                TIM_RESET_CAPTUREPOLARITY(&g_handle_tim, TIM_CHANNEL_1);                      /* 修改前需要先清除原先设置 */
                TIM_SET_CAPTUREPOLARITY(&g_handle_tim, TIM_CHANNEL_1, TIM_ICPOLARITY_RISING); /* 修改边沿检测为上升沿 */
            }
            /* g_timxchy_cap_sta[6] == 0 -> 还未捕获到高电平(第一次捕获上升沿) */
            else
            {
                g_timxchy_cap_sta = 0; /* 清空 */
                g_timxchy_cap_val = 0;

                g_timxchy_cap_sta |= 0X40;                                                     /* 标记捕获到了上升沿 */
                __HAL_TIM_DISABLE(&g_handle_tim);                                              /* 关闭定时器5 */
                __HAL_TIM_SET_COUNTER(&g_handle_tim, 0);                                       /* 定时器5计数器清零 */
                TIM_RESET_CAPTUREPOLARITY(&g_handle_tim, TIM_CHANNEL_1);                       /* 一定要先清除原来的设置！！ */
                TIM_SET_CAPTUREPOLARITY(&g_handle_tim, TIM_CHANNEL_1, TIM_ICPOLARITY_FALLING); /* 定时器5通道1设置为下降沿捕获 */
                __HAL_TIM_ENABLE(&g_handle_tim);                                               /* 使能定时器5 */
            }
        }
    }
}

/* 定时器更新中断回调函数 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM5)
    {
        if ((g_timxchy_cap_sta & 0x80) == 0)
        {
            if ((g_timxchy_cap_sta & 0x40))
            {
                if ((g_timxchy_cap_sta & 0X3F) == 0X3F) /* 高电平太长了 */
                {
                    TIM_RESET_CAPTUREPOLARITY(&g_handle_tim, TIM_CHANNEL_1);                      /* 一定要先清除原来的设置 */
                    TIM_SET_CAPTUREPOLARITY(&g_handle_tim, TIM_CHANNEL_1, TIM_ICPOLARITY_RISING); /* 配置TIM5通道1上升沿捕获 */
                    g_timxchy_cap_sta |= 0X80;                                                    /* 标记成功捕获了一次 */
                    g_timxchy_cap_val = 0XFFFF;
                }
                else /* 累计定时器溢出次数 */
                {
                    g_timxchy_cap_sta++;
                }
            }
        }
    }
}