#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))

typedef struct {
	const char *data;
	int length;
} sw;

sw *sw_create(const char *data, int length) {
	sw *s = (sw*) malloc(sizeof(sw));
	s->data = data;
	s->length = length;
	return s;
}

sw *sw_dup(const char *s) {
	return sw_create(s, strlen(s));			
}

sw *sw_split(sw *s, char sep) {
	sw *parsed = sw_dup(s->data);

	for (int i = 0; i < s->length; i++) {
		if (s->data[i] == sep) {
			s->data = s->data + i + 1;
			s->length = s->length - i - 1;
			parsed->length = i;
			return parsed;
		}
	}
	
	s->data = "";
	s->length = 0;
	return parsed; 
}

int sw_eq(sw *s1, sw *s2) {
	if (s1->length == s2->length) {
		return !strncmp(s1->data, s2->data, s1->length);
	}
	return 0; 
}

sw *slurp_file(char *file_path) {
	FILE *f = fopen(file_path, "r");
	if (f == NULL) {
		fprintf(stderr, "ERROR: file `%s` is not opened\n", file_path); 
		exit(1);
	}

	if (fseek(f, 0, SEEK_END) != 0) {
		fprintf(stderr, "ERROR: Could not read the file `%s`: %s", file_path, strerror(errno));
		exit(1);
	}

	long m = ftell(f);
	if (m < 0) {	
		fprintf(stderr, "ERROR: Could not read the file `%s`: %s", file_path, strerror(errno));
		exit(1);	
	}

	if (fseek(f, 0, SEEK_SET) != 0) {
		fprintf(stderr, "ERROR: Could not read the file `%s`: %s", file_path, strerror(errno));
		exit(1);
	}

	char *buffer = (char*) malloc(m);
	fread(buffer, sizeof(char), m, f);
	
	return sw_create(buffer, m);
}

void sw_dump(sw *s) {
	printf("sw->data: %.*s, sw->length: %d\n", s->length, s->data, s->length);
}

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

#define WORD_DIGIT_CAPACITY 12

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
