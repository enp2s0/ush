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

int ush_main_loop()
{
	while (1) {
		printf(get_var(CFG_PROMPT_VAR));
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
        init_vars();
        define_var(CFG_PROMPT_VAR, CFG_PROMPT);
        
	printf(CFG_LONG_NAME "\n");
	return ush_main_loop();
}
