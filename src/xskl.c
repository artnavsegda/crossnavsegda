
unsigned char xskl(unsigned short start, unsigned short length);
{
	int byteshift = start / 8;
	int bitshift = start % 8;

	if (byteshift > 20)
		return 0x00;

	unsigned char interim = crmassive[byteshift] << bitshift;

	if (length > 8)
		return interim;
	else
	{
		return interim & (0xFF >> length);
	}
}

