CC=gcc
FLAGS=-std=c11 -Wall -pedantic
INCLUDES=-I lib

day1: day1/main.c
	$(CC) $(FLAGS) $(INCLUDES) day1/main.c lib/sw.c -o day1/run.out

day2: day2/main.c
	$(CC) $(FLAGS) $(INCLUDES) day2/main.c lib/sw.c -o day2/run.out
	cd day2 && ./run.out

.PHONY: day1 day2
