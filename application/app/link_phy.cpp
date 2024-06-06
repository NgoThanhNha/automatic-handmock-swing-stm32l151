/**
 ******************************************************************************
 * @author: Nark
 * @date:   06/06/2024
 ******************************************************************************
**/

#include "link_phy.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "io_cfg.h"
#include "console.h"
#include "platform.h"

#include "app.h"
#include "task_list.h"
#include "task_pid.h"
#include "task_display.h"
#include "task_safety.h"

uint8_t esplink_buffer_receive[ESPLINK_UART_RECEIVE_BUFFER_SIZE];
uint8_t index_receive = 0;
esplink_fw_data_t esplink_fw_data;
stk_msg_parser_t* get_msg = (stk_msg_parser_t*)0;

void link_phy_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SIG_LINK_PHY_GET_BUFF:
        APP_PRINT("[LINK_PHY] SIG_LINK_PHY_GET_BUFF\n");
        switch (esplink_buffer_receive[0]) {
            case TASK_POST:
                task_post_pure_msg(LINK_PHY_ID, SIG_LINK_PHY_GET_MSG_IN);
            break;

            default:
            break;
        }
        break;
    
    case SIG_LINK_PHY_GET_MSG_IN:
        APP_PRINT("[LINK_PHY] FW_MSG_TASK_POST\n");
        get_msg = (stk_msg_parser_t*)(&esplink_buffer_receive[1]);
        APP_PRINT("[LINK_PHY] Destination task id: %d\n", get_msg->des_task_id);
        APP_PRINT("[LINK_PHY] Signal: %d\n", get_msg->sig);

        /* dispatch msg */
        task_post_pure_msg(get_msg->des_task_id, get_msg->sig);
        break;

    case SIG_LINK_PHY_SEND_DATA:
        APP_PRINT("[LINK_PHY] SIG_LINK_PHY_SEND_DATA\n");
        break;

    default:
        break;
    }
}

void esplink_send_msg(uint8_t* buffer, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        usart2_put_char(buffer[i]);
    }
}

void usart2_get_char(uint8_t c) {

    ENTRY_CRITICAL();
    esplink_buffer_receive[index_receive] = c;
    EXIT_CRITICAL();

    if (c == 0xFE) {
        index_receive = 0;
        task_post_pure_msg(LINK_PHY_ID, SIG_LINK_PHY_GET_BUFF);
    }
    else {
        index_receive++;
    }
    
}