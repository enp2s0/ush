#ifndef VARS_H
#define VARS_H

int define_var(char *name, char *value);
char *get_var(char *name);
char *get_var_idx(int index);
char *get_var_name_idx(int index);
int del_var(char *name);
int num_vars(void);
int init_vars(void);

#endif
