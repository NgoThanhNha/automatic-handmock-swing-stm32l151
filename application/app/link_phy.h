/**
 ******************************************************************************
 * @author: Nark
 * @date:   06/06/2024
 ******************************************************************************
**/

#ifndef __LINK_PHY_H__
#define __LINK_PHY_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

#include "screen_manager.h"

#define ESPLINK_UART_RECEIVE_BUFFER_SIZE            (100)

/* stk msg from esplink */
typedef struct {
    uint8_t des_task_id;
    uint8_t sig;
} stk_msg_parser_t;

/* data attribute of msg */
typedef struct {
    uint8_t voltage;
    uint8_t current;
    uint8_t speed_level;
    uint8_t weight;
} esplink_fw_data_t;

/* type of function call by link phy */
typedef enum {
    TASK_POST = 0x01,
    SEND_DATA,
} link_dect_t;

extern uint8_t esplink_buffer_receive[ESPLINK_UART_RECEIVE_BUFFER_SIZE];
extern void usart2_get_char(uint8_t c);
extern void link_phy_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __LINK_PHY_H_ */