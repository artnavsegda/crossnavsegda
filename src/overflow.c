#include <stdio.h>

struct ra915data {
	unsigned short pmt_current;
	unsigned short flow_rate;
	unsigned short pmt_voltage;
	short concentration;
	unsigned short bypass_pressure;
	unsigned short t_analytical_cell;
	unsigned short t_selftest_cell;
	unsigned short pressure_analytical_cell;
	unsigned short vacuum;
	unsigned short dilution_pressure;
	unsigned char status;
};

struct ra915struct {
	unsigned char marker;
	struct ra915data data;
	unsigned char checksum;
};

unsigned char genchecksum(unsigned char *massive)
{
	unsigned char checksum = 0;
	for (int i = 0;i<sizeof(massive);i++)
		checksum = checksum + massive[i];
	return checksum;
}

int main(void)
{
	struct ra915struct frame = {
		.marker = 0xA5
	};
	frame.checksum = genchecksum((unsigned char *)&frame.data);
	return 0;
}
