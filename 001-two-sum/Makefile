include ../environment.mk

SRC = main.c error.c options.c test.c
SRC_1 = $(SRC) solution-1.c
SRC_2 = $(SRC) solution-2.c
HEADERS = types.h error.h options.c test.h solution.h
TARGET_1 = two-sum-1.exe
TARGET_2 = two-sum-2.exe


.PHONY: all build-1 build-2 clean


all: build-1 build-2

build-1: $(TARGET_1)

build-2: $(TARGET_2)

# Just recompile everything if something changes
$(TARGET_1): $(SRC_1) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SRC_1)

$(TARGET_2): $(SRC_2) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SRC_2)

clean:
	rm ./*.exe