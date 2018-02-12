#ifndef BUILTIN_H
#define BUILTIN_H

int builtin_help(char argc, char **arguments);
int builtin_exit(char argc, char **arguments);
int builtin_cd(char argc, char **arguments);
int builtin_pwd(char argc, char **arguments);

int check_builtin(char *name);
int run_builtin(char **args);

#endif
