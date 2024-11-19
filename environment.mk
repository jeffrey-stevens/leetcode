# LeetCode environment

CC = gcc

CSTANDARD = -std=gnu11
WARNINGS_CFLAGS = -Wall -Wextra

ifeq ($(DEBUG), 1)
OPTIM = -O0
DEBUG_CFLAGS = -g -DDEBUG

else
OPTIM = -O2
DEBUG_CFLAGS = -DDEBUG

endif


CFLAGS = $(CSTANDARD) $(WARNINGS_CFLAGS) $(OPTIM) $(DEBUG_CFLAGS)