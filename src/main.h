#ifndef MAIN_H
#define MAIN_H

void init_shell();
void uninit_shell();
void parse_args(char argc, char **argv);
int ush_main_loop();
int main(char argc, char **argv);

#endif
