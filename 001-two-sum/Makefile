include ../environment.mk


SOURCES = test.c main.c solution-1-wrapper.c
TARGET = two-sum.exe

all: $(TARGET)

build: $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm ./*.exe