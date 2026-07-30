#ifndef SIGNAL_H
# define SIGNAL_H

#include <signal.h>

extern volatile sig_atomic_t g_running;

void signalHandler(int sig);
void setup_signals(void);

#endif
