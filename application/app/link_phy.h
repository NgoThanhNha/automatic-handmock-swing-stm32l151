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

#define LINK_PHY_FORWARD_MSG_OUT(des_task_id, sig)          link_phy_fw_msg(des_task_id, sig)

#define LINK_PHY_UART_RECEIVE_BUFFER_SIZE            (100)
#define LINK_PHY_UART_TRANS_BUFFER_SIZE              (16)

/* stk msg from esplink */
typedef struct {
    uint8_t des_task_id;
    uint8_t sig;
} stk_msg_parser_t;

/* data attribute of msg */
typedef struct {
    uint8_t voltage;
    uint16_t current;
    uint8_t speed_level;
    uint8_t weight;
} link_phy_fw_data_t;

typedef struct {
    uint8_t wifi_status;
    uint8_t lenght_ssid;
    uint8_t length_password;
    char ssid[30];
    char password[30];
} link_phy_wl_info_t;

/* type of function call by link phy */
typedef enum {
    TASK_POST = 0x01,
    SEND_TO_PARSER_DATA,
} link_dect_t;

extern uint8_t link_phy_buffer_trans[LINK_PHY_UART_TRANS_BUFFER_SIZE];
extern uint8_t link_phy_buffer_receive[LINK_PHY_UART_RECEIVE_BUFFER_SIZE];
extern link_phy_wl_info_t link_phy_wl_info;
extern link_phy_fw_data_t link_phy_fw_data;

/* get data usart irq */
extern void usart2_get_char(uint8_t c);

/* forward msg to link_phy */
extern void link_phy_fw_msg(uint8_t des_task_id, uint8_t sig);
extern void link_phy_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __LINK_PHY_H_ */