#include "../lib/sw.h"
#include <assert.h>

void part1() {
	sw *input = slurp_file("data2.txt");
	int line_size = sw_find_sw(input, sw_dup("\n"));
	sw_replace_all_sw(input, sw_dup("\n"), sw_dup(""));

	int res = 0;
	int start_index = 0;
	int num = 0;
	int is_correct = 0;
	for (int i = 0; i < input->length; i++) {
		int c = input->data[i];
		if (isdigit(c)) {
			if(num == 0) {
				start_index = i - 1;
			}

			num = num * 10 + (c - '0');

			if (sw_get(input, i - line_size, '.') != '.') {
				is_correct = 1;	
			} else if (sw_get(input, i + line_size, '.') != '.') {
				is_correct = 1;	
			}
		} else if (num != 0) {
			if (sw_get(input, start_index, '.') != '.') {
				is_correct = 1;	
			} else if (sw_get(input, i, '.') != '.') {
				is_correct = 1;
			} else if (sw_get(input, start_index - line_size, '.') != '.') {
				is_correct = 1;
			} else if (sw_get(input, start_index + line_size, '.') != '.') {
				is_correct = 1;
			} else if (sw_get(input, i - line_size, '.') != '.') {
				is_correct = 1;
			} else if (sw_get(input, i + line_size, '.') != '.') {
				is_correct = 1;
			}
			
			if (is_correct) {
				res += num;
			}

			printf("%d:%d\n", is_correct, num);
			num = 0;
			start_index = 0;
			is_correct = 0;
		}
	}

	printf("Part 1 answer: %d\n", res);
}	

typedef struct {
	int index;
	int num;
	int count;
} Gear;

#define GEARS_CAPACITY 1024

void part2() {
	sw *input = slurp_file("data2.txt");
	int line_size = sw_find_sw(input, sw_dup("\n"));
	sw_replace_all_sw(input, sw_dup("\n"), sw_dup(""));

	int res = 0;
	int start_index = 0;
	int num = 0;
	int is_correct = 0;
	int current_index = -1;

	Gear gears[GEARS_CAPACITY];
	int gears_size = 0;

	for (int i = 0; i < input->length; i++) {
		int c = input->data[i];
		if (isdigit(c)) {
			if(num == 0) {
				start_index = i - 1;
			}

			num = num * 10 + (c - '0');

			if (sw_get(input, i - line_size, '.') == '*') {
				is_correct = 1;	
				current_index = i - line_size;
			} else if (sw_get(input, i + line_size, '.') == '*') {
				is_correct = 1;	
				current_index = i + line_size;
			}
		} else if (num != 0) {
			if (sw_get(input, start_index, '.') == '*') {
				is_correct = 1;
				current_index = start_index;
			} else if (sw_get(input, i, '.') == '*') {
				is_correct = 1;
				current_index = i;
			} else if (sw_get(input, start_index - line_size, '.') == '*') {
				is_correct = 1;
				current_index = start_index - line_size;
			} else if (sw_get(input, start_index + line_size, '.') == '*') {
				is_correct = 1;
				current_index = start_index + line_size;
			} else if (sw_get(input, i - line_size, '.') == '*') {
				is_correct = 1;
				current_index = i - line_size;
			} else if (sw_get(input, i + line_size, '.') == '*') {
				is_correct = 1;
				current_index = i + line_size;
			}
			
			if (is_correct) {
				int found = 0;
				for (int j = 0; j < gears_size; j++) {
					if (gears[j].index == current_index) {
						gears[j].num *= num;	
						gears[j].count += 1;
						found = 1;
					}
				}

				if (!found && current_index != -1) {
					gears[gears_size++] = (Gear) {.index = current_index, .num = num, .count = 1};
				}
			}

			num = 0;
			start_index = 0;
			is_correct = 0;
			current_index = -1;
		}
	}

	for (int i = 0; i < gears_size; i++) {
		printf("Index: %d, Count: %d, Num: %d\n", gears[i].index, gears[i].count, gears[i].num);
		if (gears[i].count == 2) {
			res += gears[i].num;
		}
	}

	printf("Part 2 answer: %d\n", res);

}

int main() {
	part1();
	part2();
	return 0;
}
