#include <stdlib.h>
#include <unistd.h>

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
	baz();
	return EXIT_SUCCESS;
}
