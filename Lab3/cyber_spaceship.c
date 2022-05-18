#include "cyber_spaceship.h"

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length) {
	int count = 0;
	int arr[1000];
	int safe = FALSE;


	int total_length = 0;
	int longest_length = 0;
	int longest_safe_ptr = 0;

	if (cab_length == 0) {
		out_longest_safe_area_length = 0;
		return 0;
	}

	if (cluster_count == 0) {
		cluster_start_locations = 0;
		cluster_lengths = 0;
	}


	{
		int i;
		int j;

		int location = (int)cab_start_location;

		for (i = 0; i < cab_length; i++) { /* 한 인자씩 검사 */
			for (j = 0; j < cluster_count; j++) { /* 차례대로 모든 클러스터의 주소값 비교 */
				if (location == (int)cluster_start_locations[j] || safe) {
					if (count < cluster_lengths[j]) {
						count++;
						safe = TRUE;
					} else {
						safe = FALSE;
					}

			}
			if (count % 2 == 0 ) {
				total_length++;
			} else {
				if (total_length >= longest_length) {
					longest_length = total_length;
					longest_safe_ptr = location - total_length;
				}
				total_length = 0;
			}
			count = 0;
			location++;
		}



	}

	return (char*)longest_safe_ptr;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count) {
    


	return 0;
}
