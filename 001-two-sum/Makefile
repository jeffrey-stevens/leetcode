SOURCES = two-sum.c test.c main.c
MAIN = main.c
BINARY = two-sum.exe
OPTS = -Wall
DEBUG = -g -O0


build: $(SOURCES)
	gcc $(OPTS) -o $(BINARY) $(MAIN)

debug: $(SOURCES)
	gcc $(OPTS) $(DEBUG) -o $(BINARY) $(MAIN)

clean:
	rm ./*.exe