#include <stdio.h>
#include "../i2c/i2c.h"
#include "tcs3472.h"

int main() {
	i2c bus = i2c_open("/dev/i2c-1");

	if (bus == NULL) {
		fprintf(stderr, "Failed to open i2c bus.\n");
		return 1;
	}

	color currentColor;

	if (!TCS3472_powerOn(bus)) {
		fprintf(stderr, "Failed to power the device on.\n");
		return 1;
	}

	TCS3472_getColor(bus, &currentColor);
	printf("RED:\t %d\nGREEN:\t %d\nBLUE:\t %d\nALPHA:\t %d\n\n", currentColor.red, currentColor.green, currentColor.blue, currentColor.clear);

	TCS3472_powerOff(bus);
	i2c_close(bus);

	return 0;
}
