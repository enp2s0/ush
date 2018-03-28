#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>

#include "config.h"
#include "runcmd.h"
#include "prochelp.h"
#include "vars.h"
#include "cfgopts.h"

void init_shell()
{
	char digits[16];
	
	printf("Loading...\n");
	init_vars();
	
	define_var("SH_PROMPT", CFG_PROMPT);
	define_var("SH_NAME", CFG_SHORT_NAME);
	define_var("SH_DESC", CFG_LONG_NAME);
	define_var("SH_VERSION", CFG_VERSION);
	sprintf(digits, "%d", get_bufsize());
	define_var("SH_BUFSIZE", digits);
	sprintf(digits, "%d", CFG_MAX_VARS);
	define_var("SH_MAXVARS", digits);
	
	if(get_bufsize() != CFG_BUFSIZE)
	{
		printf("Warning: Using custom buffer size: %d bytes.\n", get_bufsize());
	}
	
	printf("Done!\n");
	printf(CFG_LONG_NAME "\n");
}

void uninit_shell()
{
	uninit_vars();
	return;
}

int ush_main_loop()
{
	while (1) {
		char* line;
		
		printf("%s ", get_var("SH_PROMPT"));
		fflush(NULL);
		
		line = malloc(get_bufsize() * sizeof(char));
		if(line == NULL)
		{
			fprintf(stderr, "Memory allocation error!\n");
			return -1;
		}
 
		if (!fgets(line, get_bufsize(), stdin)) 
			return -1;
		
		if ((strlen(line) <= 0) ||(line[strlen(line) - 1] != '\n'))
		{
			char ch;
			while ((ch = getchar()) != '\n' && ch != EOF);
			fprintf(stderr, "Error: Line is truncated! Increase bufsize with --bufsize or 'buffer'.\n");
			continue;
		}
 
		int input = 0;
		int first = 1;
 
		char* cmd = line;
		char* next = strchr(cmd, '|');
 
		while (next != NULL) {
			*next = '\0';
			input = run(cmd, input, first, 0);
 
			cmd = next + 1;
			next = strchr(cmd, '|');
			first = 0;
		}
		input = run(cmd, input, first, 1);
		wait_on_process();
		free(line);
	}
	return 0;
}

int main(char argc, char **argv)
{
	int i = 1;
	int retval = 255;
	
	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "--help") == 0)
		{
			printf("%s\n", CFG_LONG_NAME);
			printf("Version %s", CFG_VERSION);
			printf("\n");
			printf("Options:\n");
			printf("--help   : Display this help.\n");
			printf("--version: Display version info.\n");
			printf("--bufsize: Override default text buffer size.\n");
			return 0;
		}
		else if(strcmp(argv[i], "--version") == 0)
		{
			printf("%s v%s\n", CFG_SHORT_NAME, CFG_VERSION);
			return 0; 
		}
		else if(strcmp(argv[i], "--bufsize") == 0)
		{
			set_bufsize(atoi(argv[i + 1]));
		}
	}
	
	init_shell();
	retval = ush_main_loop();
	uninit_shell();
	return retval;
}
