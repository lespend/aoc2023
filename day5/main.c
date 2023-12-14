#include "../lib/sw.h"
#include "assert.h"

typedef struct {
	int *data;
	int size;
	int capacity;
} Array;

Array *create_array() {
	Array *arr = (Array*) malloc(sizeof(Array));
	arr->capacity = sizeof(int) * 2;
	arr->data = (int*) malloc(arr->capacity);
	arr->size = 0;
	return arr;
}

void push_array(Array *arr, int value) {
	if (arr->size >= arr->capacity / sizeof(int)) {
		arr->capacity *= 2;
		arr->data = realloc(arr->data, arr->capacity);	
	}

	arr->data[arr->size++] = value;
}

void push_range(Array *arr, int start, int size) {
	int matched = 0;
	for(int i = 0; i < arr->size; i += 2) {
		if (arr->data[i] == start && arr->data[i + 1] == size) {
			matched = 1;
			break;
		}
	}

	if (!matched) {
		push_array(arr, start);
		push_array(arr, size);
	}
}

void dump_array(Array *arr) {
	printf("Array:");
	for (int i = 0; i < arr->size; i++) {
		printf(" %d", arr->data[i]);
	}
	printf("\n");
}

void sort_array(Array *arr) {
	for (int i = 0; i < arr->size; i++) {
		for (int j = i; j < arr->size; j++) {
			if (arr->data[i] > arr->data[j]) {
				int temp = arr->data[i];
				arr->data[i] = arr->data[j];	
				arr->data[j] = temp;
			}
		}
	}
}

int min_range(Array *arr) {
	int min = -1;
	for (int i = 0; i < arr->size; i += 2) {
		if (min == -1 || min > arr->data[i]) {
			min = arr->data[i];
		}
	}
	return min;
}

Array *concat_array(Array *arr1, Array *arr2) {
	for (int i = 0; i < arr2->size; i++) {
		push_array(arr1, arr2->data[i]);
	}

	return arr1;
}

int transformation_with_map(int start_range_from, int start_range_to, int size_range, int value) {
	if (value >= start_range_from && value < start_range_from + size_range) {
		return value - start_range_from + start_range_to;	
	}

	return -1;
}

void part1() {
	sw *input_data = slurp_file("data2.txt");	
	Array *from = create_array();
	Array *to = create_array();

	while (input_data->length > 0) {
		sw *property = sw_split_sw(input_data, sw_dup("\n\n"));
		sw *property_name = sw_trim(sw_split_sw(property, sw_dup(":")));
		sw *property_data = sw_trim(sw_split_sw(property, sw_dup(":")));

		if (sw_eq(property_name, sw_dup("seeds"))) {
			while(property_data->length > 0) {
				int value = atoi(sw_split(property_data, ' ')->data);
				push_array(from, value);
			}
		} else { 
			for (int i = 0; i < from->size; i++) {
				int is_matched = 0;
				sw *copy_property_data = sw_create(property_data->data, property_data->length);
				while (copy_property_data->length > 0) {
					sw *line = sw_split(copy_property_data, '\n'); 
					int start_range_to = atoi(sw_split(line, ' ')->data);
					int start_range_from = atoi(sw_split(line, ' ')->data);
					int size_range = atoi(sw_split(line, ' ')->data);
					int transformed = transformation_with_map(start_range_from, start_range_to, size_range, from->data[i]);
					printf(" %d", transformed);
					if (transformed != -1) {
						is_matched = 1;
						push_array(to, transformed);
					}
				}
				
				if (!is_matched) {
					push_array(to, from->data[i]);
				}
			}
			printf("\n");

			from = to;
			to = create_array();
		}

		dump_array(from);
		dump_array(to);
	}

	sort_array(from);
	dump_array(from);
}

typedef struct {
	int start;
	int size;
} Range;

Range range_transformation_with_map(int start_range_from, int start_range_to, int size_range, int start_value, int range_value, Array *overs) {
	int s1 = start_range_from;
	int s2 = start_value;
	int f1 = start_range_from + size_range;
	int f2 = start_value + range_value;
	int start_res = 0;
	int size_res = 0;

	if (s1 <= s2 && s2 <= f2 && f2 <= f1) {
		start_res = s2;
		size_res = f2 - s2;
		push_range(overs, s1, s2 - s1);
		push_range(overs, f2, f1 - f2);
	} else if (s2 <= s1 && s1 <= f1 && f1 <= f2) {
		start_res = s1;
		size_res = f1 - s1;
		push_range(overs, s2, s1 - s2);
		push_range(overs, f1, f2 - f1);
	} else if (s1 <= s2 && s2 <= f1 && f1 <= f2) {
		start_res = s2;
		size_res = f1 - s2;
		push_range(overs, s1, s2 - s1);
		push_range(overs, f1, f2 - f1);
	} else if (s2 <= s1 && s1 <= f2 && f2 <= f1) {
		start_res = s1;
		size_res = f2 - s1;
		push_range(overs, s2, s1 - s2);
		push_range(overs, f2, f1 - f2);
	}

	start_res += (start_range_to - start_range_from);
	if (start_res < 0) {
		size_res = 0;
		push_range(overs, start_value, range_value);
	}

	return (Range) {.start = start_res, .size = size_res};
}

int main1() {
	Array *data = create_array();
	push_array(data, 79);
	push_array(data, 14);
	Array *overs = create_array();
	Range r1 = range_transformation_with_map(50, 52, 48, 79, 14, overs);
	Array *res = concat_array(data, overs);
	printf("%d->%d\n", r1.start, r1.size);
	dump_array(res);
	return 0;
}

int main() {
	sw *input_data = slurp_file("data1.txt");	
	Array *from = create_array();
	Array *to = create_array();

	while (input_data->length > 0) {
		sw *property = sw_split_sw(input_data, sw_dup("\n\n"));
		sw *property_name = sw_trim(sw_split_sw(property, sw_dup(":")));
		sw *property_data = sw_trim(sw_split_sw(property, sw_dup(":")));

		if (sw_eq(property_name, sw_dup("seeds"))) {
			while(property_data->length > 0) {
				int value = atoi(sw_split(property_data, ' ')->data);
				push_array(from, value);
			}
		} else { 
			for (int i = 0; i < from->size; i += 2) {
				int is_matched = 0;
				sw *copy_property_data = sw_create(property_data->data, property_data->length);
				while (copy_property_data->length > 0) {
					sw *line = sw_split(copy_property_data, '\n'); 
					int start_range_to = atoi(sw_split(line, ' ')->data);
					int start_range_from = atoi(sw_split(line, ' ')->data);
					int size_range = atoi(sw_split(line, ' ')->data);
					Range transformed = range_transformation_with_map(start_range_from, start_range_to, size_range, from->data[i], from->data[i + 1], to);
					if (transformed.size != 0) {
						is_matched = 1;
						push_range(to, transformed.start, transformed.size);
					}
				}
				
				if (!is_matched) {
				}
			}
			printf("\n");

			from = to;
			to = create_array();
		}

		dump_array(from);
		dump_array(to);
	}

	dump_array(from);
	printf("MIN RANGE: %d\n", min_range(from));

	return 0;
}
