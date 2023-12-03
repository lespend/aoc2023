#include "../lib/sw.h"
#include <assert.h>


int main() {
	sw *input = slurp_file("./data1.txt");
	sw *test = sw_dup("abcdefg");
	sw *test1 = sw_dup("    abc bc");
	sw_dump(sw_trim_left(test1));
	assert(sw_find_sw(test, sw_dup("a")) == 0);
	assert(sw_find_sw(test, sw_dup("b")) == 1);
	assert(sw_find_sw(test, sw_dup("f")) == 5);
	assert(sw_find_sw(test, sw_dup("h")) == -1);
	assert(sw_eq(sw_dup("123"), sw_dup("123")));
	assert(sw_eq(sw_trim_left(test1), sw_dup("abc bc")));
	assert(sw_eq(sw_trim(test1), sw_dup("abc bc")));
	printf("%d\n", sw_find_sw(input, sw_dup(",")));
	printf("%d\n", sw_find_sw(input, sw_dup("askfljaslfkj")));
	printf("%d\n", sw_find_sw(input, sw_dup("red")));
	
	while (input->length > 0) {
		sw *line = sw_split(input, '\n');	
		sw_split(line, ':');
		while (line->length > 0) {
			sw *cubes = sw_split(line, ';');
			while (cubes->length > 0) {
				sw *cube = sw_trim(sw_split_sw(cubes, sw_dup(", ")));
				sw_dump(cube);
			}
		}
	}

	return 0;
}
