#ifndef SW_H
#define SW_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

typedef struct {
	const char *data;
	int length;
} sw;

sw *sw_create(const char *data, int length);
sw *sw_dup(const char *s);
sw *sw_trim_left(sw *s);
sw *sw_trim_right(sw *s);
sw *sw_trim(sw *s);
int sw_find_sw(sw *source, sw *value);
sw *sw_split(sw *s, char sep);
sw *sw_split_sw(sw *s, sw *sep);
int sw_eq(sw *s1, sw *s2);
sw *slurp_file(char *file_path);
void sw_dump(sw *s);
int sw_replace_sw(sw *source, sw *oldvalue, sw *newvalue);
void sw_replace_all_sw(sw *source, sw *oldvalue, sw *newvalue);
char sw_get(sw *source, int index, char nop);

#endif
