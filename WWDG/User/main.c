#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "wdg.h"

int main(void)
{
    HAL_Init();
    sys_stm32_clock_init(RCC_PLL_MUL9);
    delay_init(72);
    usart_init(115200);
    led_init();
    wwdg_init(0x7F, 0x5F, WWDG_PRESCALER_8); /* 根据这里提供的 计数器值、窗口值和预分频系数 可以计算出窗口的时间范围 [29.13ms, 58.25ms) */
    printf("还未喂狗！\r\n");

    while (1)
    {
        /* 如果这里延迟小于 29.13ms，会产生复位；如果这里延迟大于等于 58.25ms，则会产生提前唤醒中断 */
        delay_ms(57);
        HAL_WWDG_Refresh(&g_handle_wwdg);
        printf("已经喂狗！\r\n");
    }
}
