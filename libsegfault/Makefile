EXE = ./test
SRCS = test.c
CFLAGS += -rdynamic

$(EXE): $(SRCS)

.PHONY: clean
clean:
	rm -rf $(EXE) a.out *.o

.PHONY: run
run: $(EXE)
	SEGFAULT_SIGNALS="abrt segv" LD_PRELOAD=libSegFault.so $(EXE)
