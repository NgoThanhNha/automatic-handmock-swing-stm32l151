/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#include "st7789.h"

#include "io_cfg.h"
#include "hard_timer.h"

using namespace std;

st7789_arrt_t st7789;

void st7789_reset() {
    st7789_rst_write_pin_high();
    delay_ms(100);
    st7789_rst_write_pin_low();
    delay_ms(100);
    st7789_rst_write_pin_high();
    delay_ms(100);
}

void st7789_send_command(uint8_t reg) {
	st7789_dc_write_pin_low();
	st7789_cs_write_pin_low();
	spi1_send_data(reg);
}

void st7789_send_data_8bit(uint8_t data) {
	st7789_dc_write_pin_high();
	spi1_send_data(data);
}

void st7789_send_data_16bit(uint16_t data) {
	st7789_dc_write_pin_high();
	st7789_cs_write_pin_low();
	spi1_send_data((data >> 8) & 0xFF);
    spi1_send_data(data & 0xFF);
	st7789_cs_write_pin_high();
}

void st7789_init_reg() {
	st7789_send_command(0x11);
	delay_ms(120);

	st7789_send_command(0x3A);
	st7789_send_data_8bit(0x05);

	st7789_send_command(0xB2);
	st7789_send_data_8bit(0x0C);
	st7789_send_data_8bit(0x0C);
	st7789_send_data_8bit(0x00);
	st7789_send_data_8bit(0x33);
	st7789_send_data_8bit(0x33);

	st7789_send_command(0xB7);
	st7789_send_data_8bit(0x35);

	st7789_send_command(0xBB);
	st7789_send_data_8bit(0x35);

	st7789_send_command(0xC0);
	st7789_send_data_8bit(0x2C);

	st7789_send_command(0xC2);
	st7789_send_data_8bit(0x01);

	st7789_send_command(0xC3);
	st7789_send_data_8bit(0x13);

	st7789_send_command(0xC4);
	st7789_send_data_8bit(0x20);

	st7789_send_command(0xC6);
	st7789_send_data_8bit(0x0F);

	st7789_send_command(0xD0);
	st7789_send_data_8bit(0xA4);
	st7789_send_data_8bit(0xA1);

	st7789_send_command(0xD6);
	st7789_send_data_8bit(0xA1);

	st7789_send_command(0xE0);
	st7789_send_data_8bit(0xF0);
	st7789_send_data_8bit(0x00);
	st7789_send_data_8bit(0x04);
	st7789_send_data_8bit(0x04);
	st7789_send_data_8bit(0x04);
	st7789_send_data_8bit(0x05);
	st7789_send_data_8bit(0x29);
	st7789_send_data_8bit(0x33);
	st7789_send_data_8bit(0x3E);
	st7789_send_data_8bit(0x38);
	st7789_send_data_8bit(0x12);
	st7789_send_data_8bit(0x12);
	st7789_send_data_8bit(0x28);
	st7789_send_data_8bit(0x30);

	st7789_send_command(0xE1);
	st7789_send_data_8bit(0xF0);
	st7789_send_data_8bit(0x07);
	st7789_send_data_8bit(0x0A);
	st7789_send_data_8bit(0x0D);
	st7789_send_data_8bit(0x0B);
	st7789_send_data_8bit(0x07);
	st7789_send_data_8bit(0x28);
	st7789_send_data_8bit(0x33);
	st7789_send_data_8bit(0x3E);
	st7789_send_data_8bit(0x36);
	st7789_send_data_8bit(0x14);
	st7789_send_data_8bit(0x14);
	st7789_send_data_8bit(0x29);
	st7789_send_data_8bit(0x32);

	st7789_send_command(0x21);

	st7789_send_command(0x11);
	delay_ms(120);
	st7789_send_command(0x29);
}

void st7789_set_attr(uint16_t scan_dir) {
	/* get the screen scan direction */
	st7789.scan_dir = scan_dir;
	uint8_t memory_access_reg = 0x00;

	/* get GRAM and LCD width and height */
	if (st7789.scan_dir == HORIZONTAL) {
		st7789.height = LCD_WIDTH;
		st7789.width = LCD_HEIGHT;
		memory_access_reg = 0X00;
	}
	else {
		st7789.height = LCD_HEIGHT;
		st7789.width = LCD_WIDTH;		
		memory_access_reg = 0X70;
	}

    /* set the read / write scan direction of the frame memory */
    st7789_send_command(0x36); /* MX, MY, RGB mode */
    st7789_send_data_8bit(memory_access_reg); /* 0x08 set RGB */
}

void st7789_init(uint8_t scan_dir) {
    /* hardware reset */
    st7789_reset();

    /* set the resolution and scanning method of the screen */
    st7789_set_attr(scan_dir);

    /* set the initialization register */
    st7789_init_reg();
}

void st7789_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	if (st7789.scan_dir == HORIZONTAL) { 
		/* set the X coordinates */
		st7789_send_command(0x2A);
		st7789_send_data_8bit(0x00);
		st7789_send_data_8bit(x0 + 0x22);
		st7789_send_data_8bit(((x1 + 0x22) - 1) >> 8);
		st7789_send_data_8bit((x1 + 0x22) - 1);

		/* set the Y coordinates */
		st7789_send_command(0x2B);
		st7789_send_data_8bit(0x00);
		st7789_send_data_8bit(y0);
		st7789_send_data_8bit((y1 - 1) >> 8);
		st7789_send_data_8bit(y1 - 1);
	}
	else { 
        /* set the X coordinates */
		st7789_send_command(0x2A);
		st7789_send_data_8bit(x0 >> 8);
		st7789_send_data_8bit(x0);
		st7789_send_data_8bit((x1 - 1) >> 8);
		st7789_send_data_8bit(x1 - 1);

		/* set the Y coordinates */
		st7789_send_command(0x2B);
		st7789_send_data_8bit(y0 >> 8);
		st7789_send_data_8bit(y0 + 0x22);
		st7789_send_data_8bit((y1 - 1 + 0x22) >> 8);
		st7789_send_data_8bit(y1 - 1 + 0x22);
	}

	st7789_send_command(0X2C);
}

void st7789_clear_screen(uint16_t color) {
    uint16_t i, j;
    
    st7789_set_window(0, 0, st7789.width, st7789.height);
    st7789_dc_write_pin_high();
    uint8_t buffer_color[2];
    buffer_color[0] = (uint8_t)(color >> 8);
    buffer_color[1] = (uint8_t)(color & 0xFF);
    
    for (i = 0; i < LCD_WIDTH; i++) {
        for(j = 0; j < LCD_HEIGHT; j++) {
            spi1_send_data(buffer_color[0]);
            spi1_send_data(buffer_color[1]);
        }
    }
}

void st7789_draw_pixel(uint16_t x, uint16_t y, uint16_t color) {
	st7789_set_window(x, y, x, y);
	st7789_send_data_16bit(color);
}

Adafruit_ST7789::Adafruit_ST7789():
	Adafruit_GFX(LCD_WIDTH, LCD_HEIGHT) {

}
Adafruit_ST7789::~Adafruit_ST7789() {

}

void Adafruit_ST7789::initialize(uint8_t scan_dir) {
    st7789_init(scan_dir);
}

void Adafruit_ST7789::clear_screen(uint16_t color) {
    st7789_clear_screen(color);
}

void Adafruit_ST7789::drawPixel(int16_t x, int16_t y, uint16_t color) {
    st7789_draw_pixel(x, y, color);
}

void Adafruit_ST7789::fill_rectangle(int16_t x, int16_t y, int16_t w, int16_t h ,uint16_t color)  {
    st7789_set_window(x, y, x + w, y + h);
    st7789_dc_write_pin_high();
    uint8_t buffer_color[2];
    buffer_color[0] = (uint8_t)(color >> 8);
    buffer_color[1] = (uint8_t)(color & 0xFF);
    
    for (uint16_t i = 0; i < w; i++) {
        for(uint16_t j = 0; j < h; j++) {
            spi1_send_data(buffer_color[0]);
            spi1_send_data(buffer_color[1]);
        }
    }
}

void Adafruit_ST7789::draw_bitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *bitmap_image) {
    uint32_t cursor_image = 0;
    
    st7789_set_window(x, y, x + w, y + h);
    st7789_dc_write_pin_high();
    
    for (uint16_t i = y; i < (y + h - 1); i++) {
        for (uint16_t j = x; j < (x + w - 1); j++) {
            spi1_send_data(((bitmap_image[cursor_image]) >> 8) & 0xff);
            spi1_send_data((bitmap_image[cursor_image]));
            cursor_image++;
        }
    }
}

void Adafruit_ST7789::clear_bitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    st7789_set_window(x, y, x + w, y + h);
    st7789_dc_write_pin_high();
    
    for (uint16_t i = y; i < (y + h - 1); i++) {
        for (uint16_t j = x; j < (x + w - 1); j++) {
            spi1_send_data(0x00);
            spi1_send_data(0x00);
        }
    }
}

void Adafruit_ST7789::view_render_dma_bitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *bitmap_image) {
    st7789_set_window(x, y, x + w, y + h);
    st7789_dc_write_pin_high();
    
	spi_send_dma((uint8_t*)(bitmap_image), (172 * 320 * 2));
}