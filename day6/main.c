#include "../lib/sw.h"
#include <stdint.h>

#define TIME_CAPACITY 32
#define DISTANCE_CAPACITY 32

int count_break_record(int time, int record_distance) {
	int count = 0;
	for (int velocity = 0; velocity <= time; velocity++) {
		int64_t distance = velocity * (time - velocity);	
		if (distance > record_distance) {
			count += 1;
		}
	}
	return count;
}

int count_break_record_large(int64_t time, int64_t record_distance) {
	int64_t count = 0;
	for (int64_t velocity = 0; velocity <= time; velocity++) {
		int64_t distance = velocity * (time - velocity);	
		if (distance > record_distance) {
			count += 1;
		}
	}
	return count;
}

void part1() {
	int time[TIME_CAPACITY];
	int time_size = 0;
	int distance[TIME_CAPACITY];
	int distance_size = 0;

	sw *data = slurp_file("data3.txt"); 

	while (data->length > 0) {
		sw *line = sw_split(data, '\n');
		sw *property_name = sw_split(line, ':');
		sw *line_data = line;
		while(line_data->length > 0) {
			sw_trim(line_data);	
			int value = atoi(sw_split(line_data, ' ')->data);

			if (sw_eq(property_name, sw_dup("Time"))) {
				time[time_size++] = value;		
			} else if (sw_eq(property_name, sw_dup("Distance"))) {
				distance[distance_size++] = value;		
			}
		}
	}


	int res = 1;
	for (int i = 0; i < time_size; i++) {
		//printf(" %d:%d", time[i], distance[i]);
		int count = count_break_record(time[i], distance[i]);
		res *= count;
		printf("%d:%d\n", i, count); 
	}
	printf("Res: %d\n", res);
}

void part2() {
	int64_t time;
	int64_t distance;

	sw *data = slurp_file("data3.txt"); 

	while (data->length > 0) {
		sw *line = sw_split(data, '\n');
		sw *property_name = sw_split(line, ':');
		sw *line_data = line;
		while(line_data->length > 0) {
			sw_trim(line_data);	
			int64_t value = strtoll(sw_split(line_data, ' ')->data, NULL, 10);

			if (sw_eq(property_name, sw_dup("Time"))) {
				time = value;
			} else if (sw_eq(property_name, sw_dup("Distance"))) {
				distance = value;
			}
		}
	}

	printf("Res: %d\n", count_break_record_large(time, distance));
}

int main() {
	part1();
	part2();
	return 0;
}
