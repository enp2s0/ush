#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "config.h"
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

int builtin_num()
{
	return sizeof(builtin_names) / sizeof(char *);
}

int check_builtin(char *name)
{
	int i;
	
	for(i = 0; i < builtin_num(); i++)
		if(strcmp(name, builtin_names[i]) == 0)
			return TRUE;
	return FALSE;
}

int run_builtin(char **args)
{
	int i;
	int retval;
	
	printf("Scanning...\n");
	for(i = 0; i < builtin_num(); i++)
		if(strcmp(args[0], builtin_names[i]) == 0)
			break;
	printf("Running, i = %d\n", i);
	return builtin_func[i](args);
}

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
