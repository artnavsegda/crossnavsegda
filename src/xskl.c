
unsigned char xskl(unsigned short start, unsigned short length);
{
	int byteshift = start / 8;
	int bitshift = start % 8;

	if (byteshift > 20)
		return 0x00;

	unsigned char interim = crmassive[byteshift] << bitshift;

	if (byteshift != 19)
		interim = interim & (crmassive[byteshift+1] >> 8-bitshift);

	if (length > 8)
		return interim;
	else
	{
		return interim & (0xFF >> length);
	}
}

void xslk2(unsigned char *accessmassive,int startpostion,int amount)
{

}
