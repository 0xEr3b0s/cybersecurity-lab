#include "signals.h"
#include "utils.h"

volatile sig_atomic_t g_running = 1;

void signalHandler(int sig) {
	(void)sig;
	g_running = 0;
}

void setup_signals(void) {
	struct sigaction sa;
	sa.sa_handler = signalHandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) != 0)
		error("sigaction failed", 1, NULL);
}
