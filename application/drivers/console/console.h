/**
 ******************************************************************************
 * @author: Nark
 * @date:   14/03/2024
 ******************************************************************************
**/

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#include <stdint.h>

#include "io_cfg.h"
#include "xprintf.h"

#define DBG_EN          (1)

#if DBG_EN

#define APP_PRINT(fmt, ...)         xprintf("[APP] " fmt, ##__VA_ARGS__)
#define SYS_PRINT(fmt, ...)         xprintf((const char*)fmt, ##__VA_ARGS__)
#define APP_DBG(fmt, ...)           xprintf("[DBG] " fmt, ##__VA_ARGS__)
#define APP_DBG_SIG(fmt, ...)       xprintf("-SIG-> " fmt, ##__VA_ARGS__)

#else

#define APP_PRINT(fmt, ...)    
#define SYS_PRINT(fmt, ...)            
#define APP_DBG(fmt, ...)         
#define APP_DBG_SIG(fmt, ...)  

#endif

extern void console_init();

#ifdef __cplusplus
}
#endif

#endif /* __CONSOLE_H__ */