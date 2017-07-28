/***
 * Lifted from here: http://panthema.net/2008/0901-stacktrace-demangled/
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <execinfo.h>

#ifdef __cplusplus
#include <cxxabi.h>
#endif 

#define BT_BUF_SIZE 100

void handler(int sig, siginfo_t *si, void *unused) {
	int i, nptrs;
	void *buffer[BT_BUF_SIZE];
	char **strings;

	nptrs = backtrace(buffer, BT_BUF_SIZE);
	printf("backtrace() returned %d addresses\n", nptrs);

	strings = backtrace_symbols(buffer, nptrs);
	if (strings == NULL) {
		perror("backtrace_symbols");
		exit(EXIT_FAILURE);
	}

#ifdef __cplusplus
	size_t funcnamesize = 256;
	char *funcname = (char *)malloc(funcnamesize);

	for (i = 0; i < nptrs; i++) {
		char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

		for (char *p = strings[i]; *p; ++p) {
			if (*p == '(') {
				begin_name = p;
			} else if (*p == '+') {
				begin_offset = p;
			} else if (*p == ')' && begin_offset) {
				end_offset = p;
				break;
			}
		}

		if (begin_name && begin_offset && end_offset) {
			*begin_name++ = '\0';
			*begin_offset++ = '\0';
			*end_offset = '\0';

			int status;
			char *ret = abi::__cxa_demangle(begin_name, funcname, &funcnamesize, &status);

			if (status == 0) {
				funcname = ret;
				printf("  %s : %s+%s\n", strings[i], funcname, begin_offset);
			} else {
				printf("  %s : %s+%s\n", strings[i], begin_name, begin_offset);
			}

		} else {
			printf("%s\n", strings[i]);
		}
	}

	free(strings);
	free(funcname);
#else
	for (i = 0; i < nptrs; i++) {
		printf("%s\n", strings[i]);		
	}

	free(strings);
#endif
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
