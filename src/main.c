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

char* line = NULL;
FILE* in_pipe = NULL;

void init_shell()
{
	char digits[16];
	
	
	if(get_var("SH_SCRIPT") == NULL)
	{
		define_var("SH_SCRIPT", "(none)");
		in_pipe = stdin;
	}
	
	if(get_var("SH_MINIMAL") == NULL || strcmp(get_var("SH_MINIMAL"), "true") != 0)
	{
		define_var("SH_PROMPT", CFG_PROMPT);
		define_var("SH_NAME", CFG_SHORT_NAME);
		define_var("SH_DESC", CFG_LONG_NAME);
		define_var("SH_VERSION", CFG_VERSION);
		sprintf(digits, "%d", get_bufsize());
		define_var("SH_BUFSIZE", digits);
		sprintf(digits, "%d", CFG_MAX_VARS);
		define_var("SH_MAXVARS", digits);
	}
	
	if(get_var("SH_SCRIPT") == NULL)
		define_var("SH_SCRIPT", "(none)");
	
	if(get_bufsize() != CFG_BUFSIZE)
	{
		fprintf(stderr, "Warning: Using custom buffer size: %d bytes.\n", get_bufsize());
	}
	
	if(strcmp(get_var("SH_SCRIPT"), "(none)") == 0 && get_var("SH_MINIMAL") == NULL)
	{
		printf("Done!\n");
		printf(CFG_LONG_NAME "\n");
	}
	
	if(get_var("SH_MINIMAL") == NULL)
		define_var("SH_MINIMAL", "false");
}

void uninit_shell()
{
	uninit_vars();
	if(in_pipe != NULL && in_pipe != stdin)
		fclose(in_pipe);
	free(line);
	return;
}

void parse_args(char argc, char **argv)
{
	int i = 1;
	
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
			exit(0);
		}
		else if(strcmp(argv[i], "--version") == 0)
		{
			printf("%s v%s\n", CFG_SHORT_NAME, CFG_VERSION);
			exit(0);
		}
		else if(strcmp(argv[i], "--bufsize") == 0)
		{
			set_bufsize(atoi(argv[i + 1]));
			i++;
		}
		else if(strcmp(argv[i], "--script") == 0)
		{
			if(argc <= i + 1)
			{
				fprintf(stderr, "--script requires an argument!\n");
				uninit_vars();
				exit(-1);
			}
			define_var("SH_SCRIPT", argv[i + 1]);
		}
		else if(strcmp(argv[i], "--minimal") == 0)
		{
			define_var("SH_MINIMAL", "true");
		}
	}
}

int ush_main_loop()
{	
	if(strcmp(get_var("SH_SCRIPT"), "(none)") != 0)
	{
		in_pipe = fopen(get_var("SH_SCRIPT"), "r");
		if(in_pipe == NULL)
		{
			fprintf(stderr, "Could not open script file!\n");
			return -1;
		}
	}
	
	while (1) {
		if(strcmp(get_var("SH_SCRIPT"), "(none)") == 0)	
			printf("%s ", get_var("SH_PROMPT"));
		fflush(NULL);
		
		line = malloc(get_bufsize() * sizeof(char));
		if(line == NULL)
		{
			fprintf(stderr, "Memory allocation error!\n");
			return -1;
		}
 
		if (!fgets(line, get_bufsize(), in_pipe)) 
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
	int retval = 255;
	
	init_vars();
	parse_args(argc, argv);	
	init_shell();
	retval = ush_main_loop();
	uninit_shell();
	return retval;
}
