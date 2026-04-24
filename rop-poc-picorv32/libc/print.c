#include <stdint.h>

#define OUTPORT 0x10000000

void print_chr(char ch)
{
	*((volatile uint32_t*)OUTPORT) = ch;
}

void print_str(const char *p)
{
	while (*p != 0)
		*((volatile uint32_t*)OUTPORT) = *(p++);
}
