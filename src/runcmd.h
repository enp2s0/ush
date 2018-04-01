#ifndef RUNCMD_H
#define RUNCMD_H

#define READ  0
#define WRITE 1

int command(int input, int first, int last, char **args);
int run(char* cmd, int input, int first, int last);

#endif

