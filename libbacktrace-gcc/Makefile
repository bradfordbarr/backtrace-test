EXE = ./test
SRCS = test.c

CFLAGS += -rdynamic
LIBS += 

$(EXE): $(SRCS)

.PHONY: clean
clean:
	rm -rf $(EXE) a.out *.o

.PHONY: run
run: $(EXE)
	$(EXE)
