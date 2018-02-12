#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
 
#include <sys/types.h>
#include <sys/wait.h>

#include "config.h"
#include "vars.h"

char var_names[CFG_MAX_VARS][CFG_MAX_VAR_LEN];
char var_value[CFG_MAX_VARS][CFG_MAX_VAR_VALUE];

int var_slots_filled = 0;

int init_vars()
{
	int i;
	
	for(i = 0; i < CFG_MAX_VARS; i++)
		var_names[i][0] = '\0';
	
	return 0;
}

int define_var(char *name, char *value)
{
	int i;
	int found = FALSE;
	
	for(i = 0; i < CFG_MAX_VARS; i++)
	{
		if(strcmp(var_names[i], "") == 0)
		{
			found = TRUE;
			break;
		}
	}

	if(found == FALSE)
	{
		fprintf(stderr, "No more available variable slots!\n");
		return -1;
	}
	
	strcpy(var_names[i], name);
	strcpy(var_value[i], value);
	
	var_slots_filled++;
		
	return 0;
}

char *get_var(char *name)
{
	int i;
	
	for(i = 0; i < num_vars(); i++)
		if(strcmp(name, var_names[i]) == 0)
			return var_value[i];
	return NULL;
}

int del_var(char *name)
{
	int i;
	int found = FALSE;
	
	for(i = 0; i < num_vars(); i++)
		if(strcmp(name, var_names[i]) == 0)
		{
			found = TRUE;
			break;
		}
	
	if(found == FALSE)
	{
		fprintf(stderr, "No such variable!\n");
		return 1;
	}
	
	strcpy(var_names[i], "\0");
	return 0;
}

int num_vars(void)
{
	return var_slots_filled;
}
