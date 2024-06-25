/**
 ******************************************************************************
 * @author: Nark
 * @date:   30/04/2024
 * Mechanism of render lcd to display the dynamic items
 ******************************************************************************
**/

#ifndef __VIEW_RENDER_H__
#define __VIEW_RENDER_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#include <stdint.h>
#include <stdio.h>

#include "st7789.h"

/* define the number of each item type to rendering */
#define NUMBER_ITEM_LINE_SIZE                          (16)
#define NUMBER_ITEM_CIRCLE_SIZE                        (16)
#define NUMBER_ITEM_RECTANGLE_SIZE                     (16)
#define NUMBER_ITEM_FILL_RECTANGLE_SIZE                (16)
#define NUMBER_ITEM_ROUND_RECTANGLE_SIZE               (16)
#define NUMBER_ITEM_FILL_ROUND_RECTANGLE_SIZE          (16)
#define NUMBER_ITEM_FILL_TRIANLE_SIZE                  (16)
#define NUMBER_ITEM_TEXT_STRING_SIZE                   (32)
#define NUMBER_ITEM_TEXT_INTEGER_SIZE                  (32)
#define NUMBER_ITEM_TEXT_FLOAT_SIZE                    (32)
#define NUMBER_ITEM_BITMAP_SIZE                        (16)

typedef struct {
    int16_t x0;
    int16_t y0;
    int16_t x1;
    int16_t y1;
    uint16_t color;
} line_item_t;

typedef struct {
    int16_t x;
    int16_t y;
    uint16_t radius;        
    uint16_t color;
} circle_item_t;

typedef struct {
    int16_t x;
    int16_t y;
    uint8_t w;
    uint8_t h;
    uint16_t color;
} rectangle_item_t;

typedef struct {
    int16_t x;
    int16_t y;
    uint8_t w;
    uint8_t h;
    uint16_t color;
} fill_rectangle_item_t;

typedef struct {
    int16_t x;
    int16_t y;
    uint8_t w;
    uint8_t h;
    int16_t r;
    uint16_t color;
} round_rectangle_item_t;

typedef struct {
    int16_t x;
    int16_t y;
    uint8_t w;
    uint8_t h;
    int16_t r;
    uint16_t color;
} fill_round_rectangle_item_t;

typedef struct {
    int16_t x0;
    int16_t y0;
    int16_t x1;
    int16_t y1;
    int16_t x2;
    int16_t y2;
    uint16_t color;
} fill_triangle_item_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t number_print;
    uint8_t text_size;
    uint16_t color;
} text_integer_item_t;

typedef struct {
    int16_t x;
    int16_t y;
    float number_print;
    uint8_t text_size;
    uint16_t color;
} text_float_item_t;

typedef struct {
    int16_t x;
    int16_t y;
    const char* string_ptr;
    uint8_t text_size;
    uint16_t color;
} text_string_item_t;

typedef struct {
    int16_t x;
    int16_t y;
    uint16_t w;
    uint16_t h;
    uint16_t* bitmap_image;
} bitmap_item_t;

typedef struct {
    /* line items */
    line_item_t line_item[NUMBER_ITEM_LINE_SIZE];
    uint16_t index_line_item;

    /* circle items */
    circle_item_t circle_item[NUMBER_ITEM_CIRCLE_SIZE];
    uint16_t index_circle_item;

    /* rectangle items */
    rectangle_item_t rectangle_item[NUMBER_ITEM_RECTANGLE_SIZE];
    uint16_t index_rectangle_item;

    /* fill rectangle items */
    fill_rectangle_item_t fill_rectangle_item[NUMBER_ITEM_FILL_RECTANGLE_SIZE];
    uint16_t index_fill_rectangle_item;

    /* round rectangle items */
    round_rectangle_item_t round_rectangle_item[NUMBER_ITEM_ROUND_RECTANGLE_SIZE];
    uint16_t index_round_rectangle_item;

    /* fill round rectangle items */
    fill_round_rectangle_item_t fill_round_rectangle_item[NUMBER_ITEM_FILL_ROUND_RECTANGLE_SIZE];
    uint16_t index_fill_round_rectangle_item;

    /* round rectangle items */
    fill_triangle_item_t fill_triangle_item[NUMBER_ITEM_FILL_TRIANLE_SIZE];
    uint16_t index_fill_triangle_item;

    /* string items */
    text_string_item_t text_string_item[NUMBER_ITEM_TEXT_STRING_SIZE];
    uint16_t index_text_string_item;

    /* integer items */
    text_integer_item_t text_integer_item[NUMBER_ITEM_TEXT_INTEGER_SIZE];
    uint16_t index_text_integer_item;

    /* float items */
    text_float_item_t text_float_item[NUMBER_ITEM_TEXT_FLOAT_SIZE];
    uint16_t index_text_float_item;

    /* bitmap items */
    bitmap_item_t bitmap_item[NUMBER_ITEM_BITMAP_SIZE];
    uint16_t index_bitmap_item; 

} view_render_t;

extern Adafruit_ST7789 st7789_view_render;
extern view_render_t view_render_dynamic;
extern view_render_t view_render_static;

extern void view_render_init(uint8_t scan_dir);
extern void view_render_draw_line(view_render_t* me, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
extern void view_render_draw_circle(view_render_t* me, int16_t x, int16_t y, uint16_t r, uint16_t color);
extern void view_render_draw_rect(view_render_t* me, int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t color);
extern void view_render_fill_rect(view_render_t* me, int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t color);
extern void view_render_draw_round_rect(view_render_t* me, int16_t x, int16_t y, uint16_t w, uint16_t h, int16_t radius, uint16_t color);
extern void view_render_fill_round_rect(view_render_t* me, int16_t x, int16_t y, uint16_t w, uint16_t h, int16_t radius, uint16_t color);
extern void view_render_fill_triangle(view_render_t* me, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
extern void view_render_print_string(view_render_t* me ,int16_t x, int16_t y, const char* string, uint8_t text_size, uint16_t color);
extern void view_render_print_integer(view_render_t* me, int16_t x, int16_t y, int16_t number_print, uint8_t text_size, uint16_t color);
extern void view_render_print_float(view_render_t* me, int16_t x, int16_t y, float number_print, uint8_t text_size, uint16_t color);
extern void view_render_draw_bitmap(view_render_t* me, int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap_image);
extern void view_render_clear(view_render_t* me);
extern void view_render_force_clear();

#ifdef __cplusplus
}
#endif

#endif /* __VIEW_RENDER_H__ */