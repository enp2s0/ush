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
 
char* args[CFG_BUFSIZE];

void init_shell(void)
{
	char digits[16];
	
	printf("Loading...");
	init_vars();
	
	define_var("SH_PROMPT", CFG_PROMPT);
	define_var("SH_NAME", CFG_SHORT_NAME);
	define_var("SH_DESC", CFG_LONG_NAME);
	define_var("SH_VERSION", CFG_VERSION);
	sprintf(digits, "%d", CFG_BUFSIZE);
	define_var("SH_BUFSIZE", digits);
	sprintf(digits, "%d", CFG_MAX_VARS);
	define_var("SH_MAXVARS", digits);
	
	printf("[ DONE ]\n");
	printf(CFG_LONG_NAME "\n");
}

int ush_main_loop()
{
	while (1) {
		printf("%s ", get_var("SH_PROMPT"));
		fflush(NULL);
 
		if (!fgets(line, CFG_BUFSIZE, stdin)) 
			return 0;
 
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
	}
	return 0;
}

int main(char *argc, char **argv)
{
	init_shell();
	return ush_main_loop();
}
