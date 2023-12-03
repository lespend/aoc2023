#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "../lib/sw.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))
#define WORD_DIGIT_CAPACITY 12

sw *word_to_digit(sw *digit) {
	if (sw_eq(digit, sw_dup("one"))) {
		return sw_dup("1");
	} else if (sw_eq(digit, sw_dup("two"))) {
		return sw_dup("2");	
	} else if (sw_eq(digit, sw_dup("three"))) {
		return sw_dup("3");
	} else if (sw_eq(digit, sw_dup("four"))) {
		return sw_dup("4");
	} else if (sw_eq(digit, sw_dup("five"))) {
		return sw_dup("5");
	} else if (sw_eq(digit, sw_dup("six"))) {
		return sw_dup("6");
	} else if (sw_eq(digit, sw_dup("seven"))) {
		return sw_dup("7");
	} else if (sw_eq(digit, sw_dup("eight"))) {
		return sw_dup("8");
	} else if (sw_eq(digit, sw_dup("nine"))) {
		return sw_dup("9");
	} else {
		return sw_dup("");	
	}
}

int main() {
	sw *str = slurp_file("data2.txt");
	sw *digits[] = {
		sw_dup("one"),
		sw_dup("two"),
		sw_dup("three"),
		sw_dup("four"),
		sw_dup("five"),
		sw_dup("six"),
		sw_dup("seven"),
		sw_dup("eight"),
		sw_dup("nine"),
	};

	int sum = 0;
	int first = 0;
	int last = 0;

	while (str->length > 0) {
		sw *part = sw_split(str, '\n');
		char word_digit[WORD_DIGIT_CAPACITY];
		first = 0;
		last = 0;

		for (int i = 0; i < part->length; i++) {
			if (isdigit(part->data[i])) {
				last = part->data[i] - '0';

				if (first == 0) {
					first = part->data[i] - '0';	
				}
			} else {
				memset(word_digit, 0, WORD_DIGIT_CAPACITY);
				for (int j = i; j < part->length || j < WORD_DIGIT_CAPACITY; j++) {
					word_digit[j - i] = part->data[j];	
					if (!sw_eq(word_to_digit(sw_create(word_digit, j - i + 1)), sw_dup(""))) {
						int digit = atoi(word_to_digit(sw_create(word_digit, j - i + 1))->data);
						last = digit;

						if (first == 0) {
							first = digit;	
						}
							
					}
				}
			}
		}

		sum += first * 10 + last;
	}

	printf("SUM: %d\n", sum);
	return 0;
}
