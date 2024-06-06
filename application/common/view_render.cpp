/**
 ******************************************************************************
 * @author: Nark
 * @date:   30/04/2024
 ******************************************************************************
**/

#include "view_render.h"

Adafruit_ST7789 st7789_view_render;
view_render_t view_render_dynamic;
view_render_t view_render_static;

void view_render_init(uint8_t scan_dir) {
    st7789_view_render.initialize(scan_dir);
    st7789_view_render.clear_screen(BLACK_COLOR);
    st7789_view_render.setRotation(2);
}

void view_render_draw_line(view_render_t* me, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    if (me->index_line_item < NUMBER_ITEM_LINE_SIZE) {
        me->line_item[me->index_line_item].x0 = x0;
        me->line_item[me->index_line_item].y0 = y0;
        me->line_item[me->index_line_item].x1 = x1;
        me->line_item[me->index_line_item].y1 = y1;
        me->line_item[me->index_line_item].color = color;

        st7789_view_render.drawLine(x0, y0, x1, y1, color);

        me->index_line_item++;
    }
}

void view_render_draw_circle(view_render_t* me, int16_t x, int16_t y, uint16_t r, uint16_t color) {
    if (me->index_circle_item < NUMBER_ITEM_CIRCLE_SIZE) {
        me->circle_item[me->index_circle_item].x = x;
        me->circle_item[me->index_circle_item].y = y;
        me->circle_item[me->index_circle_item].radius = r;
        me->circle_item[me->index_circle_item].color = color;
        
        st7789_view_render.drawCircle(x, y, r, color);

        me->index_circle_item++;
    }
}

void view_render_draw_rect(view_render_t* me, int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t color) {
    if (me->index_rectangle_item < NUMBER_ITEM_RECTANGLE_SIZE) {
        me->rectangle_item[me->index_rectangle_item].x = x;
        me->rectangle_item[me->index_rectangle_item].y = y;
        me->rectangle_item[me->index_rectangle_item].w = w;
        me->rectangle_item[me->index_rectangle_item].h = h;
        me->rectangle_item[me->index_rectangle_item].color = color;
        
        st7789_view_render.drawRect(x, y, w, h, color);

        me->index_rectangle_item++;
    }
}

void view_render_fill_rect(view_render_t* me, int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t color) {
    if (me->index_fill_rectangle_item < NUMBER_ITEM_CIRCLE_SIZE) {
        me->fill_rectangle_item[me->index_fill_rectangle_item].x = x;
        me->fill_rectangle_item[me->index_fill_rectangle_item].y = y;
        me->fill_rectangle_item[me->index_fill_rectangle_item].w = w;
        me->fill_rectangle_item[me->index_fill_rectangle_item].h = h;
        me->fill_rectangle_item[me->index_fill_rectangle_item].color = color;
        
        st7789_view_render.fill_rectangle(x, y, w, h, color);

        me->index_fill_rectangle_item++;
    }
}

void view_render_draw_round_rect(view_render_t* me, int16_t x, int16_t y, uint16_t w, uint16_t h, int16_t radius, uint16_t color) {
    if (me->index_round_rectangle_item < NUMBER_ITEM_ROUND_RECTANGLE_SIZE) {
        me->round_rectangle_item[me->index_round_rectangle_item].x = x;
        me->round_rectangle_item[me->index_round_rectangle_item].y = y;
        me->round_rectangle_item[me->index_round_rectangle_item].w = w;
        me->round_rectangle_item[me->index_round_rectangle_item].h = h;
        me->round_rectangle_item[me->index_round_rectangle_item].r = radius;
        me->round_rectangle_item[me->index_round_rectangle_item].color = color;
        
        st7789_view_render.drawRoundRect(x, y, w, h, radius, color);

        me->index_round_rectangle_item++;
    }
}

void view_render_fill_round_rect(view_render_t* me, int16_t x, int16_t y, uint16_t w, uint16_t h, int16_t radius, uint16_t color) {
    if (me->index_fill_round_rectangle_item < NUMBER_ITEM_FILL_ROUND_RECTANGLE_SIZE) {
        me->fill_round_rectangle_item[me->index_fill_round_rectangle_item].x = x;
        me->fill_round_rectangle_item[me->index_fill_round_rectangle_item].y = y;
        me->fill_round_rectangle_item[me->index_fill_round_rectangle_item].w = w;
        me->fill_round_rectangle_item[me->index_fill_round_rectangle_item].h = h;
        me->fill_round_rectangle_item[me->index_fill_round_rectangle_item].r = radius;
        me->fill_round_rectangle_item[me->index_fill_round_rectangle_item].color = color;
        
        st7789_view_render.fillRoundRect(x, y, w, h, radius, color);

        me->index_fill_round_rectangle_item++;
    }
}

void view_render_fill_triangle(view_render_t* me, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    if (me->index_fill_triangle_item < NUMBER_ITEM_FILL_TRIANLE_SIZE) {
        me->fill_triangle_item[me->index_fill_triangle_item].x0 = x0;
        me->fill_triangle_item[me->index_fill_triangle_item].y0 = y0;
        me->fill_triangle_item[me->index_fill_triangle_item].x1 = x1;
        me->fill_triangle_item[me->index_fill_triangle_item].y1 = y1;
        me->fill_triangle_item[me->index_fill_triangle_item].x2 = x2;
        me->fill_triangle_item[me->index_fill_triangle_item].y2 = y2;

        me->fill_triangle_item[me->index_fill_triangle_item].color = color;
        
        st7789_view_render.fillTriangle(x0, y0, x1, y1, x2, y2, color);

        me->index_fill_triangle_item++;
    }
}

void view_render_print_string(view_render_t* me , int16_t x, int16_t y, const char* string_print, uint8_t text_size, uint16_t color) {
    if (me->index_text_string_item < NUMBER_ITEM_TEXT_STRING_SIZE) {
        me->text_string_item[me->index_text_string_item].x = x;
        me->text_string_item[me->index_text_string_item].y = y;
        me->text_string_item[me->index_text_string_item].text_size = text_size;
        me->text_string_item[me->index_text_string_item].color = color;
        me->text_string_item[me->index_text_string_item].string_ptr = string_print;
        
        st7789_view_render.setCursor(x, y);
        st7789_view_render.setTextSize(text_size);
        st7789_view_render.setTextColor(color);
        st7789_view_render.print(string_print);

        me->index_text_string_item++;
    }
}

void view_render_print_integer(view_render_t* me, int16_t x, int16_t y, int16_t number_print, uint8_t text_size, uint16_t color) {
    if (me->index_text_integer_item < NUMBER_ITEM_TEXT_INTEGER_SIZE) {
        me->text_integer_item[me->index_text_integer_item].x = x;
        me->text_integer_item[me->index_text_integer_item].y = y;
        me->text_integer_item[me->index_text_integer_item].number_print = number_print;
        me->text_integer_item[me->index_text_integer_item].text_size = text_size;
        me->text_integer_item[me->index_text_integer_item].color = color;

        st7789_view_render.setCursor(x, y);
        st7789_view_render.setTextSize(text_size);
        st7789_view_render.setTextColor(color);
        st7789_view_render.print(number_print);

        me->index_text_integer_item++;
    }
}

void view_render_print_float(view_render_t* me, int16_t x, int16_t y, float number_print, uint8_t text_size, uint16_t color) {
    if (me->index_text_float_item < NUMBER_ITEM_TEXT_FLOAT_SIZE) {
        me->text_float_item[me->index_text_float_item].x = x;
        me->text_float_item[me->index_text_float_item].y = y;
        me->text_float_item[me->index_text_float_item].number_print = number_print;
        me->text_float_item[me->index_text_float_item].text_size = text_size;
        me->text_float_item[me->index_text_float_item].color = color;

        st7789_view_render.setCursor(x, y);
        st7789_view_render.setTextSize(text_size);
        st7789_view_render.setTextColor(color);
        st7789_view_render.print(number_print);

        me->index_text_float_item++;
    }
}

void view_render_draw_bitmap(view_render_t* me, int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap_image) {
    if (me->index_bitmap_item < NUMBER_ITEM_BITMAP_SIZE) {
        me->bitmap_item[me->index_bitmap_item].x = x;
        me->bitmap_item[me->index_bitmap_item].y = y;
        me->bitmap_item[me->index_bitmap_item].w = w;
        me->bitmap_item[me->index_bitmap_item].h = h;
        me->bitmap_item[me->index_bitmap_item].bitmap_image = bitmap_image;

        st7789_view_render.draw_bitmap(x, y, w, h, bitmap_image);
        
        me->index_bitmap_item++;
    }
}

void view_render_clear(view_render_t* me) {
    /* clear the text */
    for (uint16_t i = 0; i < (me->index_text_string_item); i++) {
        st7789_view_render.setCursor(me->text_string_item[i].x, me->text_string_item[i].y);
        st7789_view_render.setTextSize(me->text_string_item[i].text_size);
        st7789_view_render.setTextColor(BLACK_COLOR);
        st7789_view_render.print(me->text_string_item[i].string_ptr);
    }
    me->index_text_string_item = 0;
    
    for (uint16_t i = 0; i < (me->index_text_integer_item); i++) {
        st7789_view_render.setCursor(me->text_integer_item[i].x, me->text_integer_item[i].y);
        st7789_view_render.setTextSize(me->text_integer_item[i].text_size);
        st7789_view_render.setTextColor(BLACK_COLOR);
        st7789_view_render.print(me->text_integer_item[i].number_print);
    }
    me->index_text_integer_item = 0;

    for (uint16_t i = 0; i < (me->index_text_float_item); i++) {
        st7789_view_render.setCursor(me->text_float_item[i].x, me->text_float_item[i].y);
        st7789_view_render.setTextSize(me->text_float_item[i].text_size);
        st7789_view_render.setTextColor(BLACK_COLOR);
        st7789_view_render.print(me->text_float_item[i].number_print);
    }
    me->index_text_float_item = 0;

    /* clear line items */
    for (uint16_t i = 0; i < (me->index_line_item); i++) {
        st7789_view_render.drawLine(me->line_item[i].x0, me->line_item[i].y0, me->line_item[i].x1, me->line_item[i].y1, BLACK_COLOR);
    }
    me->index_line_item = 0;

    /* clear circle items */
    for (uint16_t i = 0; i < (me->index_circle_item); i++) {
        st7789_view_render.drawCircle(me->circle_item[i].x, me->circle_item[i].y, me->circle_item[i].radius, BLACK_COLOR);
    }
    me->index_circle_item = 0;

    /* clear rectangle items */
    for (uint16_t i = 0; i < (me->index_rectangle_item); i++) {
        st7789_view_render.drawRect(me->rectangle_item[i].x, me->rectangle_item[i].y, me->rectangle_item[i].w, me->rectangle_item[i].h, BLACK_COLOR);
    }
    me->index_rectangle_item = 0;

    /* clear fill rectangle items */
    for (uint16_t i = 0; i < (me->index_fill_rectangle_item); i++) {
        st7789_view_render.fill_rectangle(me->fill_rectangle_item[i].x, me->fill_rectangle_item[i].y, me->fill_rectangle_item[i].w, me->fill_rectangle_item[i].h, BLACK_COLOR);
    }
    me->index_fill_rectangle_item = 0;

    /* clear round rectangle items */
    for (uint16_t i = 0; i < (me->index_round_rectangle_item); i++) {
        st7789_view_render.drawRoundRect(me->round_rectangle_item[i].x, me->round_rectangle_item[i].y, me->round_rectangle_item[i].w, me->round_rectangle_item[i].h, me->round_rectangle_item[i].r, BLACK_COLOR);
    }
    me->index_round_rectangle_item = 0;

    /* clear fill round rectangle items */
    for (uint16_t i = 0; i < (me->index_fill_round_rectangle_item); i++) {
        st7789_view_render.fillRoundRect(me->fill_round_rectangle_item[i].x, me->fill_round_rectangle_item[i].y, me->fill_round_rectangle_item[i].w, me->fill_round_rectangle_item[i].h, me->fill_round_rectangle_item[i].r, BLACK_COLOR);
    }
    me->index_fill_round_rectangle_item = 0;

    /* clear fill triangle items */
    for (uint16_t i = 0; i < (me->index_fill_triangle_item); i++) {
        st7789_view_render.fillTriangle(me->fill_triangle_item[i].x0, me->fill_triangle_item[i].y0, me->fill_triangle_item[i].x1, me->fill_triangle_item[i].y1, me->fill_triangle_item[i].x2, me->fill_triangle_item[i].y2, BLACK_COLOR);
    }
    me->index_fill_triangle_item = 0;

    /* clear bitmap items */
    for (uint16_t i = 0; i < (me->index_bitmap_item); i++) {
        st7789_view_render.clear_bitmap(me->bitmap_item[i].x, me->bitmap_item[i].y, me->bitmap_item[i].w, me->bitmap_item[i].h);
    }
    me->index_bitmap_item = 0;
}

void view_render_force_clear() {
    view_render_clear(&view_render_static);
    view_render_clear(&view_render_dynamic);
    st7789_view_render.clear_screen(BLACK_COLOR);
}