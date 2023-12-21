/***
 * @Author: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @Date: 2023-12-21 15:41:41
 * @LastEditors: Huichang Shen 85936940+Saint-Diana@users.noreply.github.com
 * @LastEditTime: 2023-12-21 15:46:06
 * @FilePath: \MDK-ARMd:\work\CodeSpace\STM32\WWDG\Drivers\BSP\WDG\wdg.h
 * @Description: WWDG
 * @
 * @Copyright (c) 2023 by Huichang Shen 85936940+Saint-Diana@users.noreply.github.com, All Rights Reserved.
 */
#ifndef _WDG_H
#define _WDG_H

#include "sys.h"

extern WWDG_HandleTypeDef g_handle_wwdg;

void wwdg_init(uint8_t tr, uint8_t wr, uint32_t fprer);

#endif