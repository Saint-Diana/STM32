#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "led.h"
#include "btim.h"

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

    /* 串口初始化 */
    usart_init(115200);

    /* Base Timer 初始化；500 ms */
    btim_timx_int_init(5000 - 1, 7200 - 1);

    /* 逻辑处理 */
    while (1)
    {
        /* 延迟 500 ms */
        delay_ms(500);
    }
}