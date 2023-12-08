/***
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-08 14:30:24
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-08 15:22:23
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\LED_2\Drivers\BSP\LED\led.h
 * @Description: 通过宏定义把 GPIO 时钟使能，GPIO 引脚赋值等操作都进行封装
 * @
 * @Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#ifndef _LED_H
#define _LED_H

#include "./SYSTEM/sys/sys.h"

/* LED0 相关配置 */
#define LED0_GPIO_PORT GPIOB
#define LED0_GPIO_PIN GPIO_PIN_5
#define LED0_GPIO_CLK_ENABLE()        \
    do                                \
    {                                 \
        __HAL_RCC_GPIOB_CLK_ENABLE(); \
    } while (0)

/* LED1 相关配置 */
#define LED1_GPIO_PORT GPIOE
#define LED1_GPIO_PIN GPIO_PIN_5
#define LED1_GPIO_CLK_ENABLE()        \
    do                                \
    {                                 \
        __HAL_RCC_GPIOE_CLK_ENABLE(); \
    } while (0)

/* LED 端口定义 */
#define LED0(x)                                                                                                                                \
    do                                                                                                                                         \
    {                                                                                                                                          \
        x ? HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_SET) : HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, GPIO_PIN_RESET); \
    } while (0)

#define LED1(x)                                                                                                                                \
    do                                                                                                                                         \
    {                                                                                                                                          \
        x ? HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_SET) : HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_RESET); \
    } while (0)

/* 函数声明 */
void led_init(void);

#endif