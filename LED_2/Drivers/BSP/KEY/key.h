#ifndef _KEY_H
#define _KEY_H
#include "./SYSTEM/sys/sys.h"

/* KEY 0 */
#define KEY0_GPIO_PORT GPIOE
#define KEY0_GPIO_PIN GPIO_PIN_4
#define KEY0_CLK_ENABLE()             \
    do                                \
    {                                 \
        __HAL_RCC_GPIOE_CLK_ENABLE(); \
    } while (0)
#define KEY0 HAL_GPIO_ReadPin(KEY0_GPIO_PORT, KEY0_GPIO_PIN)

/* KEY 1 */
#define KEY1_GPIO_PORT GPIOE
#define KEY1_GPIO_PIN GPIO_PIN_3

/* KEY_UP */
#define KEY_UP_GPIO_PORT GPIOA
#define KEY_UP_GPIO_PIN GPIO_PIN_0

/* 函数声明 */
void key_init(void);
uint8_t key_scan(void);

#endif