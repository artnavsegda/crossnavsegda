#include <stdio.h>
#include <stdint.h>

#define MAXLENGTH 255

void hexprint(uint16_t length, uint8_t * buffer)
{
  char hexstring[MAXLENGTH];
  char * hexpointer = hexstring;
  for (int i = 0; i < length; i++)
  {
   sprintf(hexpointer,"%02X ",buffer[i]);
   hexpointer += 3;
  }
  printf("%s\n",hexstring);
}

int main(void)
{
  uint8_t hextest[] = { 0x01, 0x02, 0x03 };
  hexprint(3, hextest);
}

