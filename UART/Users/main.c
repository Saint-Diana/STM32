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

    /* 初始化串口 */
    usart_init(115200); /* 波特率设置为 115200 */

    /* 逻辑处理 */
    while (1)
    {
        if (usart1_rx_flag == 1)
        {
            HAL_UART_Transmit(&init_struct, rx_buffer, 1, 3000); /* 串口、发送数据、发送数据的大小、超时时间(ms) */
            while (__HAL_UART_GET_FLAG(&init_struct, UART_FLAG_TC) != 1)
            {
            }
            printf("\r\n");
            usart1_rx_flag = 0;
        }
        else
        {
            delay_ms(10);
        }
    }
}