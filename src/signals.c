#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>

#include "main.h"
#include "signals.h"
#include "vars.h"

int init_signals()
{
	signal(SIGINT, sig_handler);
	return 0;
}

int unhandle_signal(int sig)
{
	signal(sig, SIG_DFL);
	return 0;
}

void sig_handler(int sig)
{	
	int c;
	
	switch(sig)
	{
		case SIGINT:
			if(strcmp(get_var("SH_SCRIPT"), "(none)") == 0)
			{	
				fflush(NULL);
				return;
			}
			
			exit(-1);
			
			break;
		default:
			fprintf(stderr, "Unhandled signal %d caught!\n", sig);
			break;
	}
	
	return;
}
