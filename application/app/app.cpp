/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#include "app.h"

/* kernel includes */
#include "stk.h"
#include "message.h"
#include "timer.h"

/* peripheral includes */
#include "io_cfg.h"

/* driver includes */
#include "hard_timer.h"
#include "console.h"
#include "led.h"
#include "button.h"
#include "screen_manager.h"
#include "view_render.h"

/* library includes */
#include "st7789.h"
#include "ina219.h"
#include "dfplayer.h"

/* task includes */
#include "bsp.h"
#include "task_list.h"
#include "task_pid.h"
#include "task_display.h"

/* screen includes */
#include "screen_idle.h"
#include "screen_info.h"
#include "screen_main.h"
#include "screen_setting.h"
#include "screen_network.h"
#include "screen_track.h"

void main_app() {
    /* system tick init */
    systick_init();

    /* io init */
    io_init();

    /* kernel init */
    msg_init();
    task_create(app_task_table);
    timer_init();

    /* led init */
    led_init_func(&led_life, led_life_on, led_life_off);
    led_blink_set(&led_life, 1000);

    /* button init */
    button_init_func(&button_up, button_up_read, button_up_callback);
    button_init_func(&button_down, button_down_read, button_down_callback);
    button_init_func(&button_mode, button_mode_read, button_mode_callback);

    /* view render init */
    view_render_init(VERTICAL);

    /* screen manager init */
    scr_mng_init(&app_screen, screen_main_handler);

    /* power sensing init */
    ina219_init();

    /* music player init */
    dfplayer_init();
    delay_ms(5);
    screen_track_info.volume = 10;
    
    /* pid init */
    task_post_pure_msg(TASK_PID_ID, SIG_PID_INIT);
    // timer_set(TASK_SAFETY_ID, SIG_CHECK_CURRENT_WARNING, 1000, TIMER_PERIODIC);

    /* kernel start */
    task_run();
}
 