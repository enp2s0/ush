#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "runcmd.h"
#include "parser.h"
#include "prochelp.h"
#include "config.h"
#include "builtins.h"
#include "vars.h"

int command(int input, int first, int last, char **args)
{
	pid_t pid;
	int pipettes[2];
 
 	pipe( pipettes );	
	pid = fork();

	if (pid == 0) {
		if (first == 1 && last == 0 && input == 0) {
			dup2(pipettes[WRITE], STDOUT_FILENO);
		} else if (first == 0 && last == 0 && input != 0) {
			dup2(input, STDIN_FILENO);
			dup2(pipettes[WRITE], STDOUT_FILENO);
		} else {
			dup2( input, STDIN_FILENO );
		}
 
		if (execvp( args[0], args) == -1)
		{
			switch(errno)
			{
				case EPERM:
					fprintf(stderr, "%s: %s: Access denied!\n", CFG_SHORT_NAME, args[0]);
					break;
				case ENOENT:
					fprintf(stderr, "%s: %s: No such file or directory!\n", CFG_SHORT_NAME, args[0]);
					break;
				default:
					fprintf(stderr, "%s, %s: Unknown execution error!\n", CFG_SHORT_NAME, args[0]);
					break;
			}
			free(args);
			_exit(EXIT_FAILURE);
		}
	}
 
	if (input != 0) 
		close(input);
 
	close(pipettes[WRITE]);
 
	if (last == 1)
		close(pipettes[READ]);
 
	free(args);
	return pipettes[READ];
}

int run(char* cmd, int input, int first, int last)
{
	char **args;
	int i = 0;
	int c = 0;
	int found = FALSE;

	args = split(cmd);
	
	while(args[i] != NULL)
	{
		if(args[i][0] != '$')
		{
			i++;
			continue;
		}
		
		args[i]++;
		
		for(c = 0; c < num_vars(); c++)
		{
			if(strcmp(get_var_name_idx(c), args[i]) == 0)
			{
				found = TRUE;
				args[i] = malloc(sizeof(get_var_idx(c)));
				if(args[i] == NULL)
				{
					fprintf(stderr, "Memory allocation error!\n");
					return -1;
				}
				strcpy(args[i], get_var_idx(c));
			}
		}
		
		if(found == FALSE)
		{
			fprintf(stderr, "$%s: No such variable!\n", args[i]);
			return -1;
		}
		i++;
	}
	
	if (args[0] != NULL) {
		if(check_builtin(args[0]) == TRUE && args[0][strlen(args[0])-1] != '^')
			return run_builtin(args);
		if(args[0][strlen(args[0])-1] == '^')
		{
			printf("WARN: Overriding builtin function!\n");
			args[0][strlen(args[0])-1] = '\0';
		}
		register_process();
		return command(input, first, last, args);
	}
	
	
	return 0;
}
