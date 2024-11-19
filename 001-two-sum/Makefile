include ../environment.mk


SRC = main.c error.c solution-1-wrapper.c test.c
HEADERS = types.h error.h test.h solution-1.h 
TARGET = two-sum.exe

.PHONY: all build clean


all: build

build: $(TARGET)

# Just recompile everything if something changes
$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SRC)

clean:
	rm ./*.exe