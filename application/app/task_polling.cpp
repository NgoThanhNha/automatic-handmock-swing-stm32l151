/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#include "task_polling.h"

#include "stk.h"
#include "message.h"

#include "app.h"
#include "bsp.h"
#include "io_cfg.h"

#include "console.h"
#include "led.h"
#include "button.h"

#include "ina219.h"

#include "app.h"
#include "task_list.h"
#include "task_safety.h"

void task_polling_handler() {
    led_polling(&led_life);
    button_polling(&button_up);
    button_polling(&button_down);
    button_polling(&button_mode);
    polling_checking_current();
}

