#include "cyber_spaceship.h"

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{

    int total_length = 0;
    int longest_length = 0;
    int longest_safe_ptr = 0;

    int travel_count = 0;

    if (cab_length == 0) {
        out_longest_safe_area_length = 0;
        return 0;
    }

    if (cluster_count == 0) {
        cluster_start_locations = 0;
        cluster_lengths = 0;

        *out_longest_safe_area_length = (size_t)cab_length;
        return (char*)cab_start_location;
    }

    {
        int total_moved_count = 0;
        size_t i;
        size_t j;
        size_t cluster_start_loacations_backup;
        int adder = 0;

        size_t cab_start_location_backup = (int)cab_start_location;

        for (i = 0; i < cab_length; i++) { /* CAB 끝까지 한 블록당 클러스터가 몇개인지 조사  */
            for (j = 0; j < cluster_count; j++) { /* 한 블록당 차례대로 모든 클러스터의 주소값 비교 */

                cluster_start_loacations_backup = (int)cluster_start_locations[j];

                if (cab_start_location_backup >= cluster_start_loacations_backup && cab_start_location_backup < cluster_start_loacations_backup + cluster_lengths[j]) {

                    adder++;
                }
            }

            if (adder % 2 == 0) {
                total_length++;
            } else {
                travel_count++;

                if (total_length >= longest_length) {
                    longest_length = total_length;
                    longest_safe_ptr = cab_start_location_backup - total_length;
                }
                total_length = 0;
            }

            adder = 0;
            cab_start_location_backup++;
            total_moved_count++;
        }

        if (i == cab_length) {
            if (total_length >= longest_length) {
                longest_length = total_length;
                longest_safe_ptr = cab_start_location_backup - total_length;
            }
        }

        *out_longest_safe_area_length = (size_t)longest_length;
        return (char*) longest_safe_ptr;
    }
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{

    int total_length = 0;
    int longest_length = 0;

    double total_travel_time = 0;
    int safe_travel_count = 0;
    int unsafe_travel_count = 0;

    if (cluster_count == 0) {
        cluster_start_locations = 0;
        cluster_lengths = 0;

        {
            double a;
            int integer;
            double real;
            a = (double)cab_length / 10.0;

            integer = (double)cab_length / 10.0;
            real = a - integer;

            if (real >= 0.5) {
                total_travel_time = integer + 1;
            } else {
                total_travel_time = integer;
            }
        }

        return (int)total_travel_time;
    }

    {
        int total_moved_count = 0;
        size_t i;
        size_t j;
        size_t cluster_start_loacations_backup;
        int adder = 0;

        size_t cab_start_location_backup = (int)cab_start_location;

        for (i = 0; i < cab_length; i++) { /* CAB 끝까지 한 블록당 클러스터가 몇개인지 조사  */
            for (j = 0; j < cluster_count; j++) { /* 한 블록당 차례대로 모든 클러스터의 주소값 비교 */

                cluster_start_loacations_backup = (int)cluster_start_locations[j];

                if (cab_start_location_backup >= cluster_start_loacations_backup && cab_start_location_backup < cluster_start_loacations_backup + cluster_lengths[j]) {

                    adder++;
                }
            }

            if (adder % 2 == 0) {
                total_length++;
                safe_travel_count++;
            } else {
                unsafe_travel_count++;

                if (total_length >= longest_length) {
                    longest_length = total_length;
                }
                total_length = 0;
            }

            adder = 0;
            cab_start_location_backup++;
            total_moved_count++;
        }

        if (i == cab_length) {
            if (total_length >= longest_length) {
                longest_length = total_length;
            }
        }

        {
            double a;
            int integer;
            double real;
            a = (double)safe_travel_count / 10.0 + (double)unsafe_travel_count / 5.0;

            integer = (double)safe_travel_count / 10.0 + (double)unsafe_travel_count / 5.0;
            real = a - integer;

            if (real >= 0.5) {
                total_travel_time = integer + 1;
            } else {
                total_travel_time = integer;
            }
        }
    }

    return (int)total_travel_time;
}
