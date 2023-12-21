#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"

#if SYS_SUPPORT_OS
#include "os.h"
#endif

/******************************************************************************************/
#if 1

#if (__ARMCC_VERSION >= 6010050)
__asm(".global __use_no_semihosting\n\t");
__asm(".global __ARM_use_no_argv \n\t");

#else
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

FILE __stdout;

int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0)
        ;

    USART1->DR = (uint8_t)ch;
    return ch;
}
#endif
/******************************************************************************************/
/*
    以下自己实现UART的初始化
*/
/* UART 句柄 */
UART_HandleTypeDef init_struct;

/* HAL库使用的串口接收数据缓冲区 */
uint8_t rx_buffer[1];

/* 串口 1 接收数据标志位(0：未接受到数据；1：接收到数据了) */
uint8_t usart1_rx_flag = 0;

/* 串口初始化函数 */
void usart_init(uint32_t baudrate)
{
    init_struct.Instance = USART1;                    /* 串口 1 寄存器基地址 */
    init_struct.Init.BaudRate = baudrate;             /* 波特率 */
    init_struct.Init.WordLength = UART_WORDLENGTH_8B; /* 字长 */
    init_struct.Init.StopBits = UART_STOPBITS_1;      /* 停止位长 */
    init_struct.Init.Parity = UART_PARITY_NONE;       /* 奇/偶校验 */
    init_struct.Init.HwFlowCtl = UART_HWCONTROL_NONE; /* 硬件流控 */
    init_struct.Init.Mode = UART_MODE_TX_RX;          /* 收发模式 */
    HAL_UART_Init(&init_struct);

    /* 开启 USART1 的接收中断 */
    HAL_UART_Receive_IT(&init_struct, rx_buffer, 1);
}

/* HAL_UART_Init() 会调用 HAL_UART_MspInit(); 自定义串口的 MSP 回调函数 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_struct;
    /* 如果是串口 1 */
    if (huart->Instance == USART1)
    {
        /* 使能 USART1 和对应 IO 时钟 */
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE(); // USART1 IO 对应 PA9 和 PA10

        /* 初始化 IO */
        gpio_init_struct.Pin = GPIO_PIN_9;             /* PA9 对应 USART1 的 TXD */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;       /* 推挽复用输出 */
        gpio_init_struct.Pull = GPIO_NOPULL;           /* 没有上下拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; /* 高速 */
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);       /* 初始化 PA9 */
        gpio_init_struct.Pin = GPIO_PIN_10;            /* PA10 对应 USART1 的 RXD */
        gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;    /* 复用输入 */
        gpio_init_struct.Pull = GPIO_PULLUP;           /* 上拉 */
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);       /* 初始化 PA10 */

        /* 使能 USART1 中断，设置优先级 */
        HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
}

/* USART1 中断服务函数 */
void USART1_IRQHandler(void)
{
    /* 调用公共处理函数 */
    HAL_UART_IRQHandler(&init_struct);               /* 里面会调用 __HAL_UART_DISABLE_IT() */
    HAL_UART_Receive_IT(&init_struct, rx_buffer, 1); /* 所以调用完公共处理函数后，还需要重新使能接收中断 */
}

/* 自定义串口数据接收完成回调函数 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* 数据接收完成，将标志位赋值为 1 */
    usart1_rx_flag = 1;
}
