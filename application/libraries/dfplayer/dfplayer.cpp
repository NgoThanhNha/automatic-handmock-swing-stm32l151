/**
 ******************************************************************************
 * @author: Nark
 * @date:   03/06/2024
 ******************************************************************************
**/

#include "dfplayer.h"
#include "io_cfg.h"
#include "hard_timer.h"

static uint8_t send_buffer[10];

void dfplayer_init() {
    send_buffer[0] = 0x7E; /* start byte */
    send_buffer[1] = 0xFF; /* version */
    send_buffer[2] = 0x06; /* len */
    send_buffer[3] = 0x00; /* command */
    send_buffer[4] = 0x00; /* feedback */
    send_buffer[5] = 0x00; /* query high data byte */
    send_buffer[6] = 0x00; /* query low data byte */
    send_buffer[7] = 0x00; /* check sum high byte */
    send_buffer[8] = 0x00; /* check sum low byte */
    send_buffer[9] = 0xEF; /* stop byte */
}

void dfplayer_fill_uint16_bigend(uint8_t *buffer, uint16_t data) {
	*buffer =	(uint8_t)(data >> 8);
	*(buffer+1) =	(uint8_t)data;
}

uint16_t dfplayer_checksum(uint8_t *buffer_check) {
	uint16_t sum = 0;
	for (int i = 1; i < 7; i++) {
		sum += buffer_check[i];
	}
	return -sum;
}

void dfplayer_fill_checksum() {
	uint16_t checksum = dfplayer_checksum(send_buffer);
	dfplayer_fill_uint16_bigend(send_buffer + 7, checksum);
}

void dfplayer_send_cmd(uint8_t command, uint16_t high_arg, uint16_t low_arg) {
	send_buffer[3] = command;

	send_buffer[5] = high_arg;
	send_buffer[6] = low_arg;

	dfplayer_fill_checksum();

    /* send buffer to usart */
	usart3_put_chars(send_buffer, 10);
}

void dfplayer_send_cmd(uint8_t cmd, uint16_t low_arg) {
	dfplayer_send_cmd(cmd, 0, low_arg);
}

void dfplayer_send_cmd(uint8_t cmd) {
	dfplayer_send_cmd(cmd, 0, 0);
}

void dfplayer_play(uint16_t track) {
	dfplayer_send_cmd(0x03, (uint8_t)(track >> 8), (uint8_t)(track));
}

void dfplayer_stop() {
	dfplayer_send_cmd(0x16);
}

void dfplayer_pause() {
	dfplayer_send_cmd(0x0E);
}

void dfplayer_play_continous() {
	dfplayer_send_cmd(0x0d);
}

void dfplayer_set_volume(uint16_t volume) {
	dfplayer_send_cmd(0x06, volume);
}