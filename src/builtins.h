#ifndef BUILTIN_H
#define BUILTIN_H

int builtin_help(char **arguments);
int builtin_exit(char **arguments);
int builtin_shconf(char **arguments);

int check_builtin(char *name);
int run_builtin(char **args);

#endif
