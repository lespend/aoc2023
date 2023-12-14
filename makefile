CC=gcc
FLAGS=-std=c11 -Wall -pedantic -g
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

day5: day5/main.c
	$(CC) $(FLAGS) $(INCLUDES) day5/main.c lib/sw.c -o day5/run.out
	cd day5 && ./run.out

day6: day6/main.c
	$(CC) $(FLAGS) $(INCLUDES) day6/main.c lib/sw.c -o day6/run.out
	cd day6 && ./run.out

day7: day7/main.c
	$(CC) $(FLAGS) $(INCLUDES) day7/main.c lib/sw.c -o day7/run.out
	cd day7 && ./run.out

.PHONY: day1 day2 day3 day4 day5 day6 day7 
