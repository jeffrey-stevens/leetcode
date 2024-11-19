include ../environment.mk


SRC = test.c main.c solution-1-wrapper.c
HEADERS = types.h test.h solution-1.h 
TARGET = two-sum.exe

.PHONY: all build clean


all: build

build: $(TARGET)

# Just recompile everything if something changes
$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SRC)

clean:
	rm ./*.exe