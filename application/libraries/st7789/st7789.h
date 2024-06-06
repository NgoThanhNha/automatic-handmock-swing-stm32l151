/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#ifndef __ST7789_H__
#define __ST7789_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <cstring>
#include <stdlib.h>

#include "Adafruit_GFX.h"

#define LCD_WIDTH                   (320)
#define LCD_HEIGHT                  (172)

#define HORIZONTAL                  (0)
#define VERTICAL                    (1)

#define WHITE_COLOR					(0xFFFF)
#define BLACK_COLOR					(0x0000)	  
#define BLUE_COLOR					(0x001F) 
#define ORANGE_COLOR                (0xFCA0) 
#define BRED_COLOR 					(0XF81F)
#define GRED_COLOR 					(0XFFE0)
#define GBLUE_COLOR					(0X07FF)
#define RED_COLOR  					(0xF800)
#define MAGENTA_COLOR				(0xF81F)
#define GREEN_COLOR					(0x07E0)
#define CYAN_COLOR 					(0x7FFF)
#define YELLOW_COLOR				(0xFFE0)
#define BROWN_COLOR					(0XBC40) 
#define BRRED_COLOR					(0XFC07) 
#define GRAY_COLOR 					(0X8430) 
#define DARKBLUE_COLOR			    (0X01CF)	
#define LIGHTBLUE_COLOR			    (0X7D7C)	 
#define GRAYBLUE_COLOR              (0X5458) 
#define LIGHTGREEN_COLOR            (0X841F) 
#define LGRAY_COLOR 			    (0XC618) 
#define LGRAYBLUE_COLOR             (0XA651)
#define LBBLUE_COLOR                (0X2B12)

typedef struct {
    uint16_t width;
    uint16_t height;
    uint8_t scan_dir;
} st7789_arrt_t;

/* st7789 functions */
class Adafruit_ST7789 : public Adafruit_GFX {
public:
    Adafruit_ST7789();
	~Adafruit_ST7789();

    virtual void initialize(uint8_t scan_dir);
    virtual void clear_screen(uint16_t color);
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color);
    virtual void fill_rectangle(int16_t x, int16_t y, int16_t w, int16_t h ,uint16_t color);
    virtual void draw_bitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *bitmap_image);
    virtual void clear_bitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    virtual void view_render_dma_bitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *bitmap_image);
};

#ifdef __cplusplus
}
#endif

#endif /* __ST7789_H__ */