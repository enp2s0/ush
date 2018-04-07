#ifndef SIGNALS_H
#define SIGNALS_H

void sig_handler(int sig);
int init_signals();
int unhandle_signal(int sig);
#endif
