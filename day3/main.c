#include "../lib/sw.h"

typedef struct {
	int x;
	int y;
	sw *s;
} Element;

int main() {
	sw *input = slurp_file("data2.txt");		
	
	for (int i = 0; input->length > 0; i++) {
		sw *line = sw_split(input, '\n');
		int digit = 0;
		int is_horizontal_correct = 0;
		int is_vertical_correct = 0;

		for (int j = 0; j < line->length; j++) {
			// horizontal correct check
			if (isdigit(line->data[j])) {
				digit = digit * 10 + (line->data[j] - '0');
			} else if (j < line->length - 1 && line->data[j] != '.' && isdigit(line->data[j + 1])) {
				is_horizontal_correct = 1;
			} else if (j > 1 && line->data[j] != '.' && isdigit(line->data[j - 1])) {
				is_horizontal_correct = 1;
			}

			if (!isdigit(line->data[j]) && digit != 0) {
				if (is_horizontal_correct) {
					printf("%d\n", digit);
					is_horizontal_correct = 0;
					digit = 0;
				}
			}
		}

		printf("\n");
	}
	return 0;
}
