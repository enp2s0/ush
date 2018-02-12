#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>

#include "config.h"
#include "vars.h"

int define_var(char *name, char *value)
{
	return 1;
}

char *get_var(char *name)
{
	return NULL;
}

int num_vars(void)
{
	return 0;
}
