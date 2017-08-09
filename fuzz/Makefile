GCC=gcc

BASE_FLAGS=-Wall -Wextra -Wshadow
DEBUG_FLAGS=$(BASE_FLAGS) -O0 -g

debug:
	$(GCC) $(DEBUG_FLAGS) -L../lib -I../src/c/include main.c parser.c -lwaxeye