#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>

#include "parser.h"
#include "config.h"
#include "cfgopts.h"
#include "vars.h"

char **split(char* cmd)
{
	char **args = malloc(get_bufsize() * sizeof(char *));
	
	cmd = skipwhite(cmd);
	char* next = strchr(cmd, ' ');
	int i = 0;
	int c = 0;
	int found = FALSE;
 
	while(next != NULL) {
		next[0] = '\0';
		args[i] = cmd;
		++i;
		cmd = skipwhite(next + 1);
		next = strchr(cmd, ' ');
	}
 
	if (cmd[0] != '\0') {
		args[i] = cmd;
		next = strchr(cmd, '\n');
		next[0] = '\0';
		++i; 
	}
 
	args[i] = NULL;
	
	i = 0;
	
	while(args[i] != NULL)
	{
		if(args[i][0] != '$')
		{
			i++;
			continue;
		}
		
		args[i]++;
		
		for(c = 0; c < num_vars(); c++)
			if(strcmp(get_var_name_idx(c), args[i]) == 0)
			{
				found = TRUE;
				args[i] = malloc(sizeof(get_var_idx(c)));
				if(args[i] == NULL)
				{
					fprintf(stderr, "Memory allocation error!\n");
					exit(-1);
				}
				strcpy(args[i], get_var_idx(c));
			}
		
		if(found == FALSE)
		{
			fprintf(stderr, "$%s: No such variable!\n", args[i]);
			return NULL;
		}
		i++;
	}
	
	return args;
}

char* skipwhite(char* s)
{
	while (isspace(*s)) ++s;
	return s;
}
