/**
 ******************************************************************************
 * @author: Nark
 * @date:   31/03/2024
 ******************************************************************************
**/

#include "ina219.h"
#include "io_cfg.h"

#include "console.h"
#include "hard_timer.h"

ina219_calib_params_t ina219_calib_attr;

uint16_t ina219_read_16(uint8_t reg) {
	uint16_t read_result[2];

	i2c_read(INA219_ADDRESS, reg, (uint8_t *)&read_result, 2);

	return ((read_result[0] << 8) | read_result[1]);
}

void ina219_write_16(uint8_t reg, uint16_t data) {
	uint8_t data_write[2];
	data_write[0] = (data >> 8) & 0xff;  // upper byte
	data_write[1] = (data >> 0) & 0xff; // lower byte
    i2c_write(INA219_ADDRESS, reg, (uint8_t*)&data_write, 2);
}

void ina219_reset() {
	ina219_write_16(INA219_REG_CONFIG, INA219_CONFIG_RESET);
	delay_ms(1);
}

void ina219_set_calibration(int16_t calibration_value)
{
	ina219_write_16(INA219_REG_CALIBRATION, calibration_value);
}

void ina219_set_cfg(uint16_t cfg) {
	ina219_write_16(INA219_REG_CONFIG, cfg);
}

void ina219_set_calibration_32v_2a() {
	uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V |
	             INA219_CONFIG_GAIN_8_320MV | INA219_CONFIG_BADCRES_12BIT |
	             INA219_CONFIG_SADCRES_12BIT_1S_532US |
	             INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;

	ina219_calib_attr.calibration_value = 4096;
	ina219_calib_attr.current_div_mA = 10; // Current LSB = 100uA per bit (1000/100 = 10)
	ina219_calib_attr.power_multiplier_mW = 2; // Power LSB = 1mW per bit (2/1)

	ina219_set_calibration(ina219_calib_attr.calibration_value);
	ina219_set_cfg(config);
}

void ina219_set_calibration_16v_400ma() {
	uint16_t config = INA219_CONFIG_BVOLTAGERANGE_16V |
	                    INA219_CONFIG_GAIN_1_40MV | INA219_CONFIG_BADCRES_12BIT |
	                    INA219_CONFIG_SADCRES_12BIT_1S_532US |
	                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;

	ina219_calib_attr.calibration_value = 8192;
	ina219_calib_attr.current_div_mA = 20;    // Current LSB = 50uA per bit (1000/50 = 20)
	ina219_calib_attr.power_multiplier_mW = 1.0f; // Power LSB = 1mW per bit

	ina219_set_calibration(ina219_calib_attr.calibration_value);
	ina219_set_cfg(config);
}

float ina219_read_bus_voltage() {
	uint16_t result = ina219_read_16(INA219_REG_BUSVOLTAGE);
	return ((result >> 3) * 4) * 0.001;
}

float ina219_read_shunt_voltage() {
	uint16_t result = ina219_read_16(INA219_REG_SHUNTVOLTAGE);
	return (result * 0.01);
}

uint16_t ina219_read_raw_current() {
	uint16_t result = ina219_read_16(INA219_REG_CURRENT);
	return (result);
}

float ina219_read_current() {
	float result = (float)ina219_read_raw_current();
	return (result / ina219_calib_attr.current_div_mA);
}

uint8_t ina219_init() {
	ina219_calib_attr.current_div_mA = 0; 
	ina219_calib_attr.power_multiplier_mW = 0.0;

	uint8_t ina219_isReady = 1;
    delay_ms(10);
	if (ina219_isReady == 1) {

		ina219_reset();
		//ina219_set_calibration_32v_2a();
		ina219_set_calibration_16v_400ma();

		return 1;
	}

	else {
		return 0;
	}
}