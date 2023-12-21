#include "key.h"
#include "./SYSTEM/delay/delay.h"

void key_init(void)
{
    /* 使能 GPIOE 时钟 */
    KEY0_CLK_ENABLE(); // __HAL_RCC_GPIOE_CLK_ENABLE();

    /* GPIO 初始化参数 */
    GPIO_InitTypeDef gpio_init_struct;
    gpio_init_struct.Pin = KEY0_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;

    /* 初始化 KEY 0(GPIOE) */
    HAL_GPIO_Init(KEY0_GPIO_PORT, &gpio_init_struct);
}

uint8_t key_scan(void)
{
    /* 读取 KEY 0 */
    if (KEY0 == 0)
    {
        /* 消抖 */
        delay_ms(10);
        if (KEY0 == 0)
        {
            /* 按键如果按下不松，就持续等待 */
            while (KEY0 == 0)
            {
            }
            return 1; /* 按下 KEY 0，松开返回 1 */
        }
    }
    return 0; /* KEY 0 没有按下返回 0 */
}