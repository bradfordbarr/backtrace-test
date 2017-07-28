/***
 * Uses: https://github.com/ianlancetaylor/libbacktrace
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "backtrace.h"

void handler(int sig, siginfo_t *si, void *unused) {
	struct backtrace_state *bt; 
	bt = backtrace_create_state("./test", 0, NULL, NULL);
	backtrace_print(bt, 1, stdout);
}

#ifdef __cplusplus
#include <stdexcept>

void foo(void) {
	throw std::logic_error("foo");
}
#else
void foo(void) {
	abort();
}
#endif

void bar(void) {
	foo();
}

void baz(void) {
	bar();
}

int main(int argc, char **argv) {
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler;
	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGABRT, &sa, NULL);

	baz();
	return EXIT_SUCCESS;
}
