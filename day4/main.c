#include "../lib/sw.h"

#define RIGHTS_CAPACITY 128
#define NUMBERS_CAPACITY 128

int main() {
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
	return 0;
}
