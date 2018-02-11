#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "builtins.h"

char *builtin_names[] = 
{
	"help",
	"exit",
	"shconf"
};

int (*builtin_func[])(char **) = {
	&builtin_help,
	&builtin_exit,
	&builtin_shconf
};

int builtin_help(char **arguments)
{
	return 0;
}

int builtin_exit(char **arguments)
{
	exit(EXIT_SUCCESS);
	fprintf(stderr, "Failed to kill process!\n");
	return -1;
}

int builtin_shconf(char **arguments)
{
	return 0;
}
