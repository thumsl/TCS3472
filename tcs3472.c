#include "../i2c/i2c.h"
#include "tcs3472.h"

void delay(int ms) {
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = ms < 0 ? 0 : ms * 10e-6;

  nanosleep(&ts, NULL);
}

int TCS3472_setIntegrationTime(i2c bus, char time) {
	if (time != TCS3472_ATIME_2MS && time != TCS3472_ATIME_24MS && time != TCS3472_ATIME_101MS && time != TCS3472_ATIME_154MS && time != TCS3472_ATIME_700MS)
		return -1;

	unsigned char buf[2];

	buf[0] = TCS3472_COMMAND | TCS3472_ATIME;
	buf[1] = time;
	if (i2c_write(bus,TCS3472_ADDRESS, buf, 1) == -1)
		return -1;

	return 1;
}

unsigned char TCS3472_status(i2c bus) {
	unsigned char buf[1];

	buf[0] = TCS3472_COMMAND | TCS3472_STATUS;
	if (i2c_write(bus,TCS3472_ADDRESS, buf, 1) == -1)
		return -1;
	if (i2c_read(bus,TCS3472_ADDRESS, buf, 1) == -1)
		return -1;

	return buf[0];
}

int TCS3472_powerOn(i2c bus) {
	unsigned char buf[2];

	buf[0] = TCS3472_COMMAND | TCS3472_ENABLE;
	buf[1] = TCS3472_POWER_ON;
	if (i2c_write(bus,TCS3472_ADDRESS, buf, 2) == -1)
		return -1;

	// "A minimum interval of 2.4 ms must pass after PON is asserted before an RGBC can be initiated."
		delay(3);

	buf[0] = TCS3472_COMMAND | TCS3472_ENABLE;
	buf[1] = TCS3472_POWER_ON | TCS3472_AEN; // 0x03
	if (i2c_write(bus,TCS3472_ADDRESS, buf, 2) == -1)
		return -1;

	delay(700); // max integration time (0x00)

	return 1;
}

int TCS3472_powerOff(i2c bus) {
	unsigned char buf[2];

	buf[0] =TCS3472_COMMAND | TCS3472_ENABLE;
	buf[1] = TCS3472_POWER_OFF;
	if (i2c_write(bus,TCS3472_ADDRESS, buf, 2) == -1)
		return -1;

	return 1;
}

int TCS3472_getColor(i2c bus, color* C) {
	unsigned char buf[2];

	buf[0] =TCS3472_COMMAND | TCS3472_CLEAR_LOW;
	if (i2c_write(bus,TCS3472_ADDRESS, buf, 1) == -1)
		return -1;
	if (i2c_read(bus,TCS3472_ADDRESS, buf, 2) == -1)
		return -1;

	C->clear = (buf[1] << 8) | buf[0];

	buf[0] =TCS3472_COMMAND | TCS3472_RED_LOW;
	if (i2c_write(bus, TCS3472_ADDRESS, buf, 1) == -1)
		return -1;
	if (i2c_read(bus, TCS3472_ADDRESS, buf, 2) == -1)
		return -1;

	C->red = (buf[1] << 8) | buf[0];

	buf[0] = TCS3472_COMMAND | TCS3472_GREEN_LOW;
	if (i2c_write(bus, TCS3472_ADDRESS, buf, 1) == -1)
		return -1;
	if (i2c_read(bus, TCS3472_ADDRESS, buf, 2) == -1)
		return -1;

	C->green = (buf[1] << 8) | buf[0];

	buf[0] =TCS3472_COMMAND |TCS3472_BLUE_LOW;
	if (i2c_write(bus, TCS3472_ADDRESS, buf, 1) == -1)
		return -1;
	if (i2c_read(bus, TCS3472_ADDRESS, buf, 2) == -1)
		return -1;

	C->blue = (buf[1] << 8) | buf[0];

	return 1;
}
