#include "config.h"

int bufsize = CFG_BUFSIZE;

void set_bufsize(int size)
{
	bufsize = size;
	return;
}

int get_bufsize(void)
{
	return bufsize;
}
