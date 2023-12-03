#include "../lib/sw.h"

#define ARRAY_SIZE(x) sizeof(x) / sizeof((x)[0])

void part1() {
	sw *input = slurp_file("data2.txt");
	int rgb[] = {12, 13, 14};
	int res = 0;
	
	while (input->length > 0) {
		sw *line = sw_split(input, '\n');	
		sw *left = sw_split(line, ':');
		sw_split(left, ' ');
		int game_id = atoi(left->data);
		int is_correct = 1;
		while (line->length > 0) {
			sw *cubes = sw_split(line, ';');
			while (cubes->length > 0) {
				sw *cube = sw_trim(sw_split_sw(cubes, sw_dup(", ")));
				sw *count = sw_split(cube, ' ');
				sw *color = sw_split(cube, ' ');
				int color_index;
				
				if (sw_eq(color, sw_dup("red"))) {
					color_index = 0;	
				} else if (sw_eq(color, sw_dup("green"))) {
					color_index = 1;	
				} else if (sw_eq(color, sw_dup("blue"))) {
					color_index = 2;	
				}

				if (atoi(count->data) > rgb[color_index]) {
					is_correct = 0;
				}
			}
		}

		if (is_correct) {
			res += game_id;
		}
	}

	printf("Part 1 answer: %d\n", res);
	
}

void part2() {
	sw *input = slurp_file("data2.txt");
	int rgb[] = {0, 0, 0};
	int res = 0;
	
	while (input->length > 0) {
		sw *line = sw_split(input, '\n');	sw *left = sw_split(line, ':');
		sw_split(left, ' ');
		memset(&rgb, 0, sizeof(rgb));

		while (line->length > 0) {
			sw *cubes = sw_split(line, ';');
			while (cubes->length > 0) {
				sw *cube = sw_trim(sw_split_sw(cubes, sw_dup(", ")));
				sw *count = sw_split(cube, ' ');
				sw *color = sw_split(cube, ' ');
				int color_index;
				
				if (sw_eq(color, sw_dup("red"))) {
					color_index = 0;	
				} else if (sw_eq(color, sw_dup("green"))) {
					color_index = 1;	
				} else if (sw_eq(color, sw_dup("blue"))) {
					color_index = 2;	
				}

				if (atoi(count->data) > rgb[color_index]) {
					rgb[color_index] = atoi(count->data);
				}
			}
		}

		int power = 1;
		for(int i = 0; i < ARRAY_SIZE(rgb); i++) {
			power *= rgb[i];
		}

		res += power;
	}

	printf("Part 2 answer: %d\n", res);
}

int main() {
	part1();
	part2();
	return 0;
}
