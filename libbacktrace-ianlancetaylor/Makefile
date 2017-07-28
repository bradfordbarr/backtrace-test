EXE = ./test
SRCS = test.c

CFLAGS += -rdynamic -g
LIBS += libbacktrace.a

$(EXE): $(SRCS) $(LIBS)


.PHONY: clean
clean:
	rm -rf $(EXE) a.out *.o

.PHONY: run
run: $(EXE)
	$(EXE)
