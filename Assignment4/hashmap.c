#include "hashmap.h"
/* 모든 함수의 포인터형에 NULL 은 들어가지 않는다고 가정한다. */
hashmap_t* init_hashmap_malloc(size_t length, size_t(*p_hash_func)(const char* key))
{

}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{

}

int get_value(const hashmap_t* hashmap, const char* key)
{

}

int update_value(hashmap_t* hashmap, const char* key, const int value)
{

}

int remove_key(hashmap_t* hashmap, const char* key)
{

}

void destroy(hashmap_t* hashmap)
{

}
