CC=gcc
FLAGS=-std=c11 -Wall -pedantic
INCLUDES=-I lib

day1: day1/main.c
	$(CC) $(FLAGS) $(INCLUDES) day1/main.c lib/sw.c -o day1/run.out

day2: day2/main.c
	$(CC) $(FLAGS) $(INCLUDES) day2/main.c lib/sw.c -o day2/run.out
	cd day2 && ./run.out

day3: day3/main.c
	$(CC) $(FLAGS) $(INCLUDES) day3/main.c lib/sw.c -o day3/run.out
	cd day3 && ./run.out

day4: day4/main.c
	$(CC) $(FLAGS) $(INCLUDES) day4/main.c lib/sw.c -o day4/run.out
	cd day4 && ./run.out

.PHONY: day1 day2 day3 day4
