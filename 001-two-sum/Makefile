include ../environment.mk

NDEBUG = $(OPTIM)
DEBUG_OPTIM = -O0
DEBUG = -g $(DEBUG_OPTIM)

SOURCES = test.c main.c solution-1-wrapper.c
BINARY = two-sum.exe


build: $(SOURCES)
	$(CC) $(OPTS) $(NDEBUG) -o $(BINARY) $(SOURCES)

debug: $(SOURCES)
	$(CC) $(OPTS) $(DEBUG) -o $(BINARY) $(SOURCES)

clean:
	rm ./*.exe