SOURCES = test.c main.c two-sum-double-loop-wrapper.c
MAIN = main.c
BINARY = two-sum.exe
OPTS = -Wall
DEBUG = -g -O0


build: $(SOURCES)
	gcc $(OPTS) -o $(BINARY) $(SOURCES)

debug: $(SOURCES)
	gcc $(OPTS) $(DEBUG) -o $(BINARY) $(SOURCES)

clean:
	rm ./*.exe