#include "../I2C/i2c.h"
#include "../utils/utils.h"
#include "sensor.h"

int TCS3472_setIntegrationTime(i2c bus, char time) {
	if (time != ATIME_2MS && time != ATIME_24MS && time != ATIME_101MS && time != ATIME_154MS && time != ATIME_700MS)
		return -1;

	unsigned char buf[2];

	buf[0] = COMMAND | ATIME;
	buf[1] = time;
	if (i2cWrite(bus, ADDRESS, buf, 1) == -1)
		return -1;

	return 1;
}

unsigned char TCS3472_status(i2c bus) {
	unsigned char buf[1];

	buf[0] = COMMAND | STATUS;
	if (i2cWrite(bus, ADDRESS, buf, 1) == -1)
		return -1;
	if (i2cRead(bus, ADDRESS, buf, 1) == -1)
		return -1;

	return buf[0];
}

int TCS3472_powerOn(i2c bus) {
	unsigned char buf[2];

	buf[0] = COMMAND | ENABLE;
	buf[1] = POWER_ON;
	if (i2cWrite(bus, ADDRESS, buf, 2) == -1)
		return -1;

	// "A minimum interval of 2.4 ms must pass after PON is asserted before an RGBC can be initiated."
		delay(3);

	buf[0] = COMMAND | ENABLE;
	buf[1] = POWER_ON | AEN; // 0x03
	if (i2cWrite(bus, ADDRESS, buf, 2) == -1)
		return -1;

	delay(700); // max integration time (0x00)

	return 1;
}

int TCS3472_powerOff(i2c bus) {
	unsigned char buf[2];

	buf[0] = COMMAND | ENABLE;
	buf[1] = POWER_OFF;
	if (i2cWrite(bus, ADDRESS, buf, 2) == -1)
		return -1;

	return 1;
}

int TCS3472_getColor(i2c bus, color* C) {
	unsigned char buf[2];

	buf[0] = COMMAND | CLEAR_LOW;
	if (i2cWrite(bus, ADDRESS, buf, 1) == -1)
		return -1;
	if (i2cRead(bus, ADDRESS, buf, 2) == -1)
		return -1;

	C->clear = (buf[1] << 8) | buf[0];

	buf[0] = COMMAND | RED_LOW;
	if (i2cWrite(bus, ADDRESS, buf, 1) == -1)
		return -1;
	if (i2cRead(bus, ADDRESS, buf, 2) == -1)
		return -1;

	C->red = (buf[1] << 8) | buf[0];

	buf[0] = COMMAND | GREEN_LOW;
	if (i2cWrite(bus, ADDRESS, buf, 1) == -1)
		return -1;
	if (i2cRead(bus, ADDRESS, buf, 2) == -1)
		return -1;

	C->green = (buf[1] << 8) | buf[0];

	buf[0] = COMMAND | BLUE_LOW;
	if (i2cWrite(bus, ADDRESS, buf, 1) == -1)
		return -1;
	if (i2cRead(bus, ADDRESS, buf, 2) == -1)
		return -1;

	C->blue = (buf[1] << 8) | buf[0];

	return 1;
}