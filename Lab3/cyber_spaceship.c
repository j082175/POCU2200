#include "cyber_spaceship.h"

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length) {

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
		for (i = 0; i < cab_length; i++) {
			cab_start_location[i] = 0;
		}
	}

	{
		int i;
		int j;
		int k;
		int m;
		int beforeIndex = 0;
		int totalLength = 0;
		for (i = 0; i < cluster_count; i++) { /* 총 5개 */
			for (j = 0; j < cluster_lengths[i]; j++) {
				
				beforeIndex = cluster_start_locations[i] - cab_start_location;
				totalLength = cluster_lengths[i] + beforeIndex;

				for (k = 0; k < totalLength; k++) {
					*(cab_start_location + k)++;
				}

				for (m = 0; m < beforeIndex; m++) {
					*(cab_start_location + m)--;
				}
			}
		}
	}

	return 0;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count) {
    


	return 0;
}
