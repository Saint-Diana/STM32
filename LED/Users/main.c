#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "led.h"

int main(void)
{
    /* 初始化 HAL 库 */
    HAL_Init();

    /* 设置时钟，72 Mhz，也就是锁相环使用 9 倍频 */
    sys_stm32_clock_init(RCC_PLL_MUL9);

    /* 延时初始化 */
    delay_init(72);

    /* LED 初始化 */
    led_init();

    /* 逻辑处理 */
    while (1)
    {
        /* 需要实现 LED 闪烁*/

        /* LED 灭 */
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);

        /* 延迟 500 ms */
        delay_ms(500);

        /* LED 亮 */
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);

        /* 延迟 500 ms */
        delay_ms(500);
    }
}