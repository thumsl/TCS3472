#ifndef SENSOR_H
#define SENSOR_H

#define TCS3472_ADDRESS 	0x29
#define TCS3472_COMMAND 	0x80
#define TCS3472_ENABLE 		0x00
#define TCS3472_ID 			0x12
#define TCS3472_STATUS 		0x13
#define TCS3472_CLEAR_LOW 	0x14
#define TCS3472_CLEAR_HIGH 	0x15
#define TCS3472_RED_LOW 	0x16
#define TCS3472_RED_HIGH 	0x17
#define TCS3472_GREEN_LOW 	0x18
#define TCS3472_GREEN_HIGH 	0x19
#define TCS3472_BLUE_LOW 	0x1A
#define TCS3472_BLUE_HIGH 	0x1B
#define TCS3472_POWER_ON 	0x01
#define TCS3472_POWER_OFF 	0x00
#define TCS3472_AEN 		0x02
#define TCS3472_ATIME		0x01
#define TCS3472_ATIME_2MS	0xFF
#define TCS3472_ATIME_24MS	0xF6
#define TCS3472_ATIME_101MS	0xD5
#define TCS3472_ATIME_154MS	0xC0
#define TCS3472_ATIME_700MS	0x00

typedef struct {
	short red;
	short green;
	short blue;
	short clear;
} color;

int TCS3472_powerOn(i2c bus);
int TCS3472_powerOff(i2c bus);
int TCS3472_getColor(i2c bus, color* C);
int TCS3472_setIntegrationTime(i2c bus, char time);
unsigned char TCS3472_status(i2c bus);

#endif // SENSOR_H
