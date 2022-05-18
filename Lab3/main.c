#include <assert.h>
#include "cyber_spaceship.h"

#define CAB_LENGTH (50)

int main(void)
{
    const char cyber_asteroid_belt[30];
const char* cluster_start_addresses[2];
size_t cluster_lengths[2];
size_t out_longest_safe_area_length = 0;
size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
const char* longest_safe_cluster_start_address;

const char* cluster1 = &cyber_asteroid_belt[12];
const char* cluster2 = &cyber_asteroid_belt[3];

cluster_start_addresses[0] = cluster1;
cluster_start_addresses[1] = cluster2;

cluster_lengths[0] = 15U;
cluster_lengths[1] = 25U;

longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cyber_asteroid_belt, 30, cluster_start_addresses, cluster_lengths, 2, out_longest_safe_area_length_p); /* longest_safe_cluster_start_address: (cyber_asteroid_belt + 12), out_longest_safe_area_length: 15 */
printf("%d\n",longest_safe_cluster_start_address);
}
