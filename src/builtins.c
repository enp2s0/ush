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
	"cd"
};

int (*builtin_func[])(char, char **) = {
	&builtin_help,
	&builtin_exit,
	&builtin_cd
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
	char argc;
	
	for(i = 0; i < builtin_num(); i++)
		if(strcmp(args[0], builtin_names[i]) == 0)
			break;
	
	argc = -1;
	while (args[++argc] != NULL) ;;
	return (*builtin_func[i])(argc, args);
}

int builtin_help(char argc, char **arguments)
{
	printf(CFG_LONG_NAME "\n");
	printf("Written by Noah Brecht\n");
	printf("\n");
	
	printf("Shell Builtins:\n");
	int cnt;
	for(cnt = 0; cnt < builtin_num(); cnt++)
		printf("%s\n", builtin_names[cnt]);
	
	return 0;
}

int builtin_exit(char argc, char **arguments)
{
	exit(EXIT_SUCCESS);
	fprintf(stderr, "Failed to kill process!\n");
	return -1;
}

int builtin_cd(char argc, char **arguments)
{
	if(argc != 2)
	{
		fprintf(stderr, "cd: expects exactly one argument!\n");
		return 1;
	}
	
	char* path = malloc(sizeof(arguments[1] + 2));
	strcpy(path, arguments[1]);
	strcat(path, "/");
	
	errno = 0;
	if(chdir(path) != 0)
	{
		switch(errno)
		{
			case EPERM:
				fprintf(stderr, "%s: %s: Access denied!\n", CFG_SHORT_NAME, arguments[0]);
				break;
			case ENOENT:
				fprintf(stderr, "%s: %s: No such file or directory!\n", CFG_SHORT_NAME, arguments[0]);
				break;
			default:
				fprintf(stderr, "%s, %s: Unknown execution error!\n", CFG_SHORT_NAME, arguments[0]);
				break;
		}
		return 1;
	}
	return 0;
}
