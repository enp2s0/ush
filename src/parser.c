#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>

#include "parser.h"
#include "config.h"

char **split(char* cmd)
{
	char **args = malloc(CFG_BUFSIZE * sizeof(char *));
	
	cmd = skipwhite(cmd);
	char* next = strchr(cmd, ' ');
	int i = 0;
 
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
	
	//int cnt = 0;
	//while(1)
	//{
	//	printf("%s\n", args[cnt]);
	//	cnt++;
	//	if(args[cnt] == NULL) break;
	//}
	//printf("Done!\n");
	return args;
}

char* skipwhite(char* s)
{
	while (isspace(*s)) ++s;
	return s;
}