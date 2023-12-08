#include "../lib/sw.h"

#define RIGHTS_CAPACITY 128
#define NUMBERS_CAPACITY 128

void part1() {
	sw *input = slurp_file("data2.txt"); 
	int sum = 0;
	while (input->length > 0) {
		sw *line = sw_split(input, '\n');
		sw *left = sw_split(input, ':');
		sw *rights = sw_trim(sw_split(line, '|'));
		sw *numbers = sw_trim(sw_split(line, '|'));
		int rights_arr[RIGHTS_CAPACITY];
		int rights_arr_size = 0;
		int numbers_arr[NUMBERS_CAPACITY];
		int numbers_arr_size = 0;
		int res = 0;

		printf("Rights:");
		while (rights->length > 0) {
			sw *splt_right = sw_split(rights, ' ');
			if (splt_right->length < 1) {
				continue;
			}
			int current_right = atoi(sw_trim(splt_right)->data);		
			rights_arr[rights_arr_size++] = current_right;
			printf(" %d", current_right);
		}
		printf("\n");

		printf("is clear:");
		while (numbers->length > 0) {
			sw *splt_number = sw_split(numbers, ' ');	
			if (splt_number->length < 1) {
				continue;
			}
			int current_number = atoi(sw_trim(splt_number)->data);		
			for (int i = 0; i < rights_arr_size; i++) {
				if (current_number == rights_arr[i]) {
					if (res == 0) {
						res = 1;
					} else {
						res *= 2;
					}

					printf(" %d", current_number);
				}
			}
		}
		printf("\n");
		printf("Current res: %d\n", res);
		sum += res;
	}

	printf("Current sum: %d\n", sum);
}

#define COPY_CARDS_CAPACITY 512

void part2() {
	sw *input = slurp_file("data2.txt"); 
	int sum = 0;
	int copy_cards[COPY_CARDS_CAPACITY];
	for (int i = 0; i < COPY_CARDS_CAPACITY; i++) {
		copy_cards[i] = 1;
	}
	int copy_cards_size;
	int line_num = 0;
	while (input->length > 0) {
		sw *line = sw_split(input, '\n');
		sw *copy_of_line = sw_create(line->data, line->length);
		sw *left = sw_split(input, ':');
		sw *rights = sw_trim(sw_split(line, '|'));
		sw *numbers = sw_trim(sw_split(line, '|'));
		int rights_arr[RIGHTS_CAPACITY];
		int rights_arr_size = 0;
		int numbers_arr[NUMBERS_CAPACITY];
		int numbers_arr_size = 0;
		int res = 0;

		printf("Rights:");
		while (rights->length > 0) {
			sw *splt_right = sw_split(rights, ' ');
			if (splt_right->length < 1) {
				continue;
			}
			int current_right = atoi(sw_trim(splt_right)->data);		
			rights_arr[rights_arr_size++] = current_right;
			printf(" %d", current_right);
		}
		printf("\nRights arr size: %d\n", rights_arr_size);

		printf("is clear:");
		while (numbers->length > 0) {
			sw *splt_number = sw_split(numbers, ' ');	
			if (splt_number->length < 1) {
				continue;
			}
			int current_number = atoi(sw_trim(splt_number)->data);		
			for (int i = 0; i < rights_arr_size; i++) {
				if (current_number == rights_arr[i]) {
					res += 1;
					printf(" %d", current_number);
				}
			}
		}
		printf("\n");
		printf("Current res: %d\n", res);

		for (int j = 0; j < res; j++) {
			copy_cards[line_num + j + 1] += copy_cards[line_num];
			copy_cards_size = line_num;
		}

		for (int i = 0; i < 6; i++) {
			printf("%d --> %d\n", i, copy_cards[i]);
		}

		printf("--------------\n");
		sum += copy_cards[line_num];
		line_num += 1;
	}

	printf("Current sum: %d\n", sum);
}

int main() {
	//part1();
	part2();
	return 0;
}
