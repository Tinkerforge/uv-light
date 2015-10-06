/* uv-light-bricklet
 * Copyright (C) 2015 Olaf Lüke <olaf@tinkerforge.com>
 *
 * uv-light.c: Implementation of UV Light Bricklet messages
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "uv-light.h"

#include "bricklib/bricklet/bricklet_communication.h"
#include "bricklib/utility/util_definitions.h"
#include "bricklib/drivers/adc/adc.h"
#include "brickletlib/bricklet_entry.h"
#include "brickletlib/bricklet_simple.h"
#include "config.h"

#define I2C_HALF_CLOCK_400KHZ 1250  // 2.5us per clock

#define ILLUMINANCE_AVERAGE 50

#define SIMPLE_UNIT_UV_LIGHT 0
#define SIMPLE_UNIT_IR_VALUE 1
#define SIMPLE_UNIT_ILLUMINANCE 2

const SimpleMessageProperty smp[] = {
	{SIMPLE_UNIT_UV_LIGHT, SIMPLE_TRANSFER_VALUE, SIMPLE_DIRECTION_GET}, // TYPE_GET_UV_LIGHT
	{SIMPLE_UNIT_UV_LIGHT, SIMPLE_TRANSFER_PERIOD, SIMPLE_DIRECTION_SET}, // TYPE_SET_UV_LIGHT_CALLBACK_PERIOD
	{SIMPLE_UNIT_UV_LIGHT, SIMPLE_TRANSFER_PERIOD, SIMPLE_DIRECTION_GET}, // TYPE_GET_UV_LIGHT_CALLBACK_PERIOD
	{SIMPLE_UNIT_UV_LIGHT, SIMPLE_TRANSFER_THRESHOLD, SIMPLE_DIRECTION_SET}, // TYPE_SET_UV_LIGHT_CALLBACK_THRESHOLD
	{SIMPLE_UNIT_UV_LIGHT, SIMPLE_TRANSFER_THRESHOLD, SIMPLE_DIRECTION_GET}, // TYPE_GET_UV_LIGHT_CALLBACK_THRESHOLD
	{0, SIMPLE_TRANSFER_DEBOUNCE, SIMPLE_DIRECTION_SET}, // TYPE_SET_DEBOUNCE_PERIOD
	{0, SIMPLE_TRANSFER_DEBOUNCE, SIMPLE_DIRECTION_GET}, // TYPE_GET_DEBOUNCE_PERIOD
};

const SimpleUnitProperty sup[] = {
	{NULL, SIMPLE_SIGNEDNESS_UINT, FID_UV_LIGHT, FID_UV_LIGHT_REACHED, SIMPLE_UNIT_UV_LIGHT}, // uv light
};

const uint8_t smp_length = sizeof(smp);


void invocation(const ComType com, const uint8_t *data) {
	simple_invocation(com, data);

	if(((MessageHeader*)data)->fid > FID_LAST) {
		BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_NOT_SUPPORTED, com);
	}
}

void constructor(void) {
	_Static_assert(sizeof(BrickContext) <= BRICKLET_CONTEXT_MAX_SIZE, "BrickContext too big");

	PIN_SDA.type = PIO_INPUT;
	PIN_SDA.attribute = PIO_PULLUP;
	BA->PIO_Configure(&PIN_SDA, 1);

	PIN_SCL.type = PIO_INPUT;
	PIN_SCL.attribute = PIO_PULLUP;
	BA->PIO_Configure(&PIN_SCL, 1);

	PIN_ACK.type = PIO_INPUT;
	PIN_ACK.attribute = PIO_PULLUP;
	BA->PIO_Configure(&PIN_ACK, 1);

	simple_constructor();

	veml6070_write_configuration(VEML6070_CONF_ACK_DISABLE | VEML6070_CONF_INTEGRATION_ONE | VEML6070_CONF_STUDOWN_DISABLE);

}

void destructor(void) {
	simple_destructor();
}

void tick(const uint8_t tick_type) {
	if(tick_type & TICK_TASK_TYPE_CALCULATION) {
		if(BC->tick % 100 == 0) {
			BC->last_value[0] = BC->value[0];
			BC->value[0] = veml6070_read_uv_light();
		}
	}

	simple_tick(tick_type);
}

uint32_t veml6070_read_uv_light(void) {
	uint16_t uv_value = 0;

	i2c_start();
	i2c_send_byte((I2C_ADDRESS1_VEML6070 << 1) | I2C_READ);
	uv_value |= i2c_recv_byte(false);
	i2c_stop();

	i2c_start();
	i2c_send_byte((I2C_ADDRESS2_VEML6070 << 1) | I2C_READ);
	uv_value |= (i2c_recv_byte(false) << 8);
	i2c_stop();

	// 1 step = 5 µW/cm²
	// 187 steps per 1 UVI at 270k/IT=1T (according to application note table 2)
	// Thus we can multiply by 250 (*25 for UVI to mW/m² and *10 for mW/m² to µW/cm²)
	// and divide by 187 (see above) to get a unit of µW/cm²
	return uv_value*250/187;
}

void veml6070_write_configuration(const uint8_t configuration) {
	i2c_start();
	i2c_send_byte((I2C_ADDRESS1_VEML6070 << 1) | I2C_WRITE);
	i2c_send_byte(configuration);
	i2c_stop();
}

bool i2c_scl_value(void) {
	return PIN_SCL.pio->PIO_PDSR & PIN_SCL.mask;
}

void i2c_scl_high(void) {
	PIN_SCL.pio->PIO_ODR = PIN_SCL.mask;
	while(!i2c_scl_value()); // allow slave to clock-stretch
}

void i2c_scl_low(void) {
	PIN_SCL.pio->PIO_OER = PIN_SCL.mask;
}

bool i2c_sda_value(void) {
	return PIN_SDA.pio->PIO_PDSR & PIN_SDA.mask;
}

void i2c_sda_high(void) {
	PIN_SDA.pio->PIO_ODR = PIN_SDA.mask;
}

void i2c_sda_low(void) {
	PIN_SDA.pio->PIO_OER = PIN_SDA.mask;
}

void i2c_sleep_halfclock(void) {
	SLEEP_NS(I2C_HALF_CLOCK_400KHZ);
}

void i2c_stop(void) {
	i2c_scl_low();
	i2c_sda_low();
	i2c_sleep_halfclock();
	i2c_scl_high();
	i2c_sleep_halfclock();
	i2c_sda_high();
	i2c_sleep_halfclock();
}

void i2c_start(void) {
	i2c_scl_high();
	i2c_sleep_halfclock();
	i2c_sda_low();
	i2c_sleep_halfclock();
}

uint8_t i2c_recv_byte(bool ack) {
	uint8_t value = 0;

	for(int8_t i = 7; i >= 0; i--) {
		i2c_scl_low();
		i2c_sda_high(); // allow slave to read
		i2c_sleep_halfclock();
		i2c_scl_high();
		if(i2c_sda_value()) {
			value |= (1 << i);
		}
		i2c_sleep_halfclock();
	}

	// ACK
	i2c_scl_low();
	if(ack) {
		i2c_sda_low();
	} else {
		i2c_sda_high();
	}
	i2c_sleep_halfclock();
	i2c_scl_high();
	i2c_sleep_halfclock();

	return value;
}

bool i2c_send_byte(const uint8_t value) {
	for(int8_t i = 7; i >= 0; i--) {
		i2c_scl_low();
		if((value >> i) & 1) {
			i2c_sda_high();
		} else {
			i2c_sda_low();
		}
		i2c_sleep_halfclock();
		i2c_scl_high();
		i2c_sleep_halfclock();
	}

	i2c_sda_high(); // Make sure SDA is always released

	// Wait for ACK
	bool ret = false;

	i2c_scl_low();
	i2c_sleep_halfclock();
	i2c_scl_high();
	if(!i2c_sda_value()) {
		ret = true;
	}

	i2c_sleep_halfclock();

	return ret;
}
