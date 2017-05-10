#ifndef SENSOR_H
#define SENSOR_H

#define ADDRESS 	0x29
#define COMMAND 	0x80
#define ENABLE 		0x00
#define ID 			0x12
#define STATUS 		0x13
#define CLEAR_LOW 	0x14
#define CLEAR_HIGH 	0x15
#define RED_LOW 	0x16
#define RED_HIGH 	0x17
#define GREEN_LOW 	0x18
#define GREEN_HIGH 	0x19
#define BLUE_LOW 	0x1A
#define BLUE_HIGH 	0x1B
#define POWER_ON 	0x01
#define POWER_OFF 	0x00
#define AEN 		0x02
#define ATIME		0x01
#define ATIME_2MS	0xFF
#define ATIME_24MS	0xF6
#define ATIME_101MS	0xD5
#define ATIME_154MS	0xC0
#define ATIME_700MS	0x00

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
