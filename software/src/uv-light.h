/* uv-light-bricklet
 * Copyright (C) 2015 Olaf Lüke <olaf@tinkerforge.com>
 *
 * uv-light.h: Implementation of UV Light Bricklet messages
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

#ifndef UV_LIGHT_H
#define UV_LIGHT_H

#include <stdint.h>
#include "bricklib/com/com_common.h"

#define VEML6070_CONF_RESERVED_VALUES  (0b00000010)

#define VEML6070_CONF_STUDOWN_DISABLE  (0 << 0)
#define VEML6070_CONF_STUDOWN_ENABLE   (1 << 0)
#define VEML6070_CONF_INTEGRATION_HALF (0 << 2)
#define VEML6070_CONF_INTEGRATION_ONE  (1 << 2)
#define VEML6070_CONF_INTEGRATION_TWO  (2 << 2)
#define VEML6070_CONF_INTEGRATION_FOUR (3 << 2)
#define VEML6070_CONF_ACK_THD_102      (0 << 4)
#define VEML6070_CONF_ACK_THD_145      (1 << 4)
#define VEML6070_CONF_ACK_DISABLE      (0 << 5)
#define VEML6070_CONF_ACK_ENABLE       (1 << 5)

#define I2C_EEPROM_ADDRESS_HIGH 84

#define I2C_ADDRESS1_VEML6070 0x38
#define I2C_ADDRESS2_VEML6070 0x39

#define I2C_INTERNAL_ADDRESS_BYTES 1
#define I2C_DATA_LENGTH 1

#define I2C_READ  1
#define I2C_WRITE 0

#define FID_GET_UV_LIGHT 1
#define FID_SET_UV_LIGHT_CALLBACK_PERIOD 2
#define FID_GET_UV_LIGHT_CALLBACK_PERIOD 3
#define FID_SET_UV_LIGHT_CALLBACK_THRESHOLD 4
#define FID_GET_UV_LIGHT_CALLBACK_THRESHOLD 5
#define FID_SET_DEBOUNCE_PERIOD 6
#define FID_GET_DEBOUNCE_PERIOD 7
#define FID_UV_LIGHT 8
#define FID_UV_LIGHT_REACHED 9

#define FID_LAST 23

int32_t analog_value_from_mc(const int32_t value);
int32_t illuminance_from_analog_value(const int32_t value);

void invocation(const ComType com, const uint8_t *data);
void constructor(void);
void destructor(void);
void tick(const uint8_t tick_type);

uint32_t veml6070_read_uv_light(void);
void veml6070_write_configuration(const uint8_t configuration);
bool i2c_scl_value(void);
void i2c_scl_high(void);
void i2c_scl_low(void);
bool i2c_sda_value(void);
void i2c_sda_high(void);
void i2c_sda_low(void);
void i2c_sleep_halfclock(void);
void i2c_stop(void);
void i2c_start(void);
uint8_t i2c_recv_byte(bool ack);
bool i2c_send_byte(const uint8_t value);

#endif
