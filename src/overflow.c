unsigned char genchecksum(unsigned char *massive)
{
	unsigned char checksum = 0;
	for (int i;i<sizeof(massive);i++)
		checksum = checksum + massive[i];
	return checksum;
}

int main(void)
{
	return 0;
}
