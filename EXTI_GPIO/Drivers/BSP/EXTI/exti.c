/*
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-18 16:38:40
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-20 14:27:00
 * @FilePath: \Projectsd:\work\CodeSpace\STM32\EXTI_GPIO\Drivers\BSP\EXTI\exti.c
 * @Description: EXTI 相关配置
 *
 * Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#include "exti.h"
#include "delay.h"

void exti_init(void)
{
    /* 1. 使能 GPIO 时钟 */
    __HAL_RCC_GPIOE_CLK_ENABLE();

    /* 2. 初始化 GPIO */
    GPIO_InitTypeDef init_struct;
    /* GPIO E 的 PIN 4*/
    init_struct.Pin = GPIO_PIN_4;
    /* 下降沿触发外部中断 */
    init_struct.Mode = GPIO_MODE_IT_FALLING;
    /* 上拉 */
    init_struct.Pull = GPIO_PULLUP;
    /* 3. 绑定 EXTI 和 GPIO 的映射关系(也在 HAL_GPIO_Init() 函数中一并完成了) */
    /*
        __HAL_RCC_AFIO_CLK_ENABLE();
        temp = AFIO->EXTICR[position >> 2u];
        CLEAR_BIT(temp, (0x0Fu) << (4u * (position & 0x03u)));
        SET_BIT(temp, (GPIO_GET_INDEX(GPIOx)) << (4u * (position & 0x03u)));
        AFIO->EXTICR[position >> 2u] = temp;
    */
    HAL_GPIO_Init(GPIOE, &init_struct);

    /* 4. 设置中断分组(在 HAL_Init() 中已经实现) */

    /* 5. 设置中断优先级 */
    HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 0); // 中断号、抢占优先级、响应优先级

    /* 6. 使能中断 */
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

/* 7. 设计中断服务函数 */
void EXTI4_IRQHandler(void)
{
    /* 调用 HAL 库中断处理公共函数 */
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
    /*
        HAL_GPIO_EXTI_IRQHandler函数中又调用了 HAL_GPIO_EXTI_Callback(GPIO_Pin)
    */

    /* HAL 库数据处理回调函数 */

    /* 先清中断，再执行中断服务程序 */
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
}

/* HAL_GPIO_EXTI_Callback函数 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    /* 消抖 */
    delay_ms(20);

    /* 只有当 GPIO E 的 PIN 4 按下 */
    if (GPIO_Pin == GPIO_PIN_4)
    {
        if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == 0)
        {
            /* LED 0 */
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
        }
    }
}