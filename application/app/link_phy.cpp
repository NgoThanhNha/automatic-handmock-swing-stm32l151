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

uint8_t link_phy_buffer_trans[LINK_PHY_UART_TRANS_BUFFER_SIZE];
uint8_t link_phy_buffer_receive[LINK_PHY_UART_RECEIVE_BUFFER_SIZE];
uint8_t index_receive = 0;
uint8_t flag_start_transmiss;

link_phy_fw_data_t esplink_fw_data;
stk_msg_parser_t* get_msg = (stk_msg_parser_t*)0;

void link_phy_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SIG_LINK_PHY_GET_BUFF:
        APP_PRINT("[LINK_PHY] SIG_LINK_PHY_GET_BUFF\n");
        switch (link_phy_buffer_receive[1]) {
            case TASK_POST:
                task_post_pure_msg(LINK_PHY_ID, SIG_LINK_PHY_GET_MSG_RES);
            break;

            default:
            break;
        }
        break;
    
    case SIG_LINK_PHY_GET_MSG_RES:
        APP_PRINT("[LINK_PHY] SIG_LINK_PHY_GET_MSG_RES\n");
        get_msg = (stk_msg_parser_t*)(&link_phy_buffer_receive[2]);
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

void link_phy_send_data(uint8_t* buffer, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        usart2_put_char(buffer[i]);
    }
}

void link_phy_fw_msg(uint8_t des_task_id, uint8_t sig) {
    link_phy_buffer_trans[0] = 0xFD;
    link_phy_buffer_trans[1] = TASK_POST;
    link_phy_buffer_trans[2] = des_task_id;
    link_phy_buffer_trans[3] = sig;
    link_phy_buffer_trans[4] = 0xFE;
    link_phy_send_data(&link_phy_buffer_trans[0], 5);
}

void usart2_get_char(uint8_t c) {

    ENTRY_CRITICAL();
    link_phy_buffer_receive[index_receive] = c;
    EXIT_CRITICAL();

    /* start transmission */
    if (link_phy_buffer_receive[index_receive] == 0xFD) {
        flag_start_transmiss = 1;
    }

    /* end of transmission */
    if (flag_start_transmiss) {
        if (link_phy_buffer_receive[index_receive] == 0xFE) {
            task_post_pure_msg(LINK_PHY_ID, SIG_LINK_PHY_GET_BUFF);
            index_receive = 0;
            flag_start_transmiss = 0;
        }
        else {
            index_receive++;
        }
    }
}