#include "sw.h"

sw *sw_create(const char *data, int length) {
	sw *s = (sw*) malloc(sizeof(sw));
	s->data = data;
	s->length = length;
	return s;
}

sw *sw_dup(const char *s) {
	return sw_create(s, strlen(s));			
}

sw *sw_trim_left(sw *s) {
	const char *ps = s->data;
	while (isspace(*ps))
		ps++;
	s->length = s->length - (ps - s->data); 
	s->data = ps;
	return s;
}

sw *sw_trim_right(sw *s) {
	const char *ps = s->data + s->length - 1;
	while (isspace(*ps))
		ps--;
	s->length = ps - s->data + 1; 
	return s;
}

sw *sw_trim(sw *s) {
	return sw_trim_left(sw_trim_right(s));
}

int sw_find_sw(sw *source, sw *value) {
	for (int i = 0; i < source->length; i++) {
		int match = 1;
		for (int j = 0; j < value->length && i + j < source->length; j++) {
			if (source->data[i + j] != value->data[j]) {
				match = 0;
				break;
			}
		}

		if (match) {
			return i;
		}
	}

	return -1;
}

sw *sw_split(sw *s, char sep) {
	sw *parsed = sw_create(s->data, s->length);

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

sw *sw_split_sw(sw *s, sw *sep) {
	sw *parsed = sw_create(s->data, s->length);
	int start_index = sw_find_sw(s, sep);	
	
	if (start_index != -1) {
		s->data = s->data + start_index + sep->length;
		s->length = s->length - start_index - sep->length;
		parsed->length = start_index;
		return parsed;
	}

	s->data = "";
	s->length = 0;
	return parsed;
}

int sw_eq(sw *s1, sw *s2) {
	if (s1->length == s2->length) {
		return strncmp(s1->data, s2->data, s1->length) == 0 ? 1 : 0;
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
	printf("sw->data:\n|%.*s| sw->length: %d\n", s->length, s->data, s->length);
}

int sw_replace_sw(sw *source, sw *oldvalue, sw *newvalue) {
	int index = sw_find_sw(source, oldvalue);
	if (index == -1) {
		return 0; 
	}

	int newlength = source->length - oldvalue->length + newvalue->length;
	char *buffer = (char*) malloc(sizeof(char) * newlength);
	char *pbuf = buffer;
	memcpy(pbuf, source->data, index);
	pbuf += index;
	memcpy(pbuf, newvalue->data, newvalue->length);
	pbuf += newvalue->length;
	memcpy(pbuf, source->data + index + oldvalue->length, source->length - oldvalue->length - index);

	source->data = buffer;
	source->length = newlength;
	return 1;
}

void sw_replace_all_sw(sw *source, sw *oldvalue, sw *newvalue) {
	while (sw_replace_sw(source, oldvalue, newvalue))
		;
}

char sw_get(sw *source, int index, char nop) {
	if (index < 0 || index > source->length) {
		return nop;	
	}

	return source->data[index];
}
