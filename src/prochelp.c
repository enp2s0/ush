#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>

#include "prochelp.h"

int n = 0; 

void register_process()
{
	n += 1;
}

void cleanup()
{
	int i;
	for (i = 0; i < n; ++i) 
		wait(NULL); 
}
