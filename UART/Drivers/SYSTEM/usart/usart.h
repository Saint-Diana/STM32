#ifndef __USART_H
#define __USART_H

#include "./SYSTEM/sys/sys.h"
#include "stdio.h"

/* UART 句柄 */
extern UART_HandleTypeDef init_struct;

/* HAL库使用的串口接收数据缓冲区 */
extern uint8_t rx_buffer[1];

/* 串口 1 接收数据标志位(0：未接受到数据；1：接收到数据了) */
extern uint8_t usart1_rx_flag;

void usart_init(uint32_t baudrate);

#endif
