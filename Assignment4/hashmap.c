#include "hashmap.h"
/* 모든 함수의 포인터형에 NULL 은 들어가지 않는다고 가정한다. */
/* hashmap 이란? 데이터가 2개가 있는 거 + 배열이 아닌 링크드 리스트로 구현 */

int insert_front(node_t** phead, const char* key, int value, int index)
{
    node_t* new_node;

    new_node = malloc(sizeof(node_t));

    new_node->key = (char*)malloc(sizeof(char) * strlen(key) + 1);
    if (new_node->key == NULL) {
        assert(FALSE);
    }
    strcpy(new_node->key, key);

    new_node->value = value;

    new_node->next = *(phead + index);
    *(phead + index) = new_node;

    return TRUE;
}

size_t get_prime_number(size_t length)
{
    size_t prime_number;
    size_t prime_number_divided;
    {
        size_t i;
        int is_prime = FALSE;
        size_t double_num = length * 2;
        while (TRUE) {
            for (i = 3; i < double_num; i++) {
                if (double_num % i != 0 && double_num % 2 != 0) {
                    is_prime = TRUE;
                    continue;
                } else {
                    is_prime = FALSE;
                    break;
                }
            }

            if (is_prime) {
                prime_number = double_num;
                break;
            }
            double_num++;
        }
    }
    prime_number_divided = prime_number % length;
    return prime_number_divided;
}

hashmap_t* init_hashmap_malloc(size_t length, size_t (*p_hash_func)(const char* key))
{

    node_t** hash_table;
    hashmap_t* hashmap;

    hash_table = (node_t**)malloc(sizeof(node_t*) * length);
    if (hash_table == NULL) {
        assert(FALSE);
    }

    {
        size_t i;
        for (i = 0; i < length; i++) {
            hash_table[i] = NULL;
        }
    }

    hashmap = (hashmap_t*)malloc(sizeof(hashmap_t));
    if (hashmap == NULL) {
        assert(FALSE);
    }

    hashmap->plist = hash_table;

    hashmap->length = length;
    hashmap->hash_func = p_hash_func;

    return hashmap;
}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{
    size_t hash = 0;
    node_t** cursor;

    hash = (hashmap->hash_func(key)) % (hashmap->length);

    cursor = &(hashmap->plist)[hash];

    while (*cursor != NULL) {
        if (!strcmp((*cursor)->key, key)) {
            return FALSE;
        }
        cursor = &(*cursor)->next;
    }

    return insert_front(hashmap->plist, key, value, hash);
}

int get_value(const hashmap_t* hashmap, const char* key)
{
    size_t hash = hashmap->hash_func(key) % hashmap->length;

    node_t** cursor;

    cursor = &(hashmap->plist)[hash];

    while (*cursor != NULL) {
        if (!strcmp((*cursor)->key, key)) {
            return (*cursor)->value;
        }
        cursor = &(*cursor)->next;
    }

    return EOF;
}

int update_value(hashmap_t* hashmap, const char* key, const int value)
{
    size_t hash = hashmap->hash_func(key) % hashmap->length;

    node_t** cursor;

    cursor = &(hashmap->plist)[hash];

    while (*cursor != NULL) {
        if (!strcmp((*cursor)->key, key)) {
            (*cursor)->value = value;
            return TRUE;
        }
        cursor = &(*cursor)->next;
    }

    return FALSE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    node_t** cursor;
    node_t* tmp;
    size_t hash = hashmap->hash_func(key) % hashmap->length;

    cursor = &(hashmap->plist)[hash];

    while (*cursor != NULL) {
        if (!strcmp((*cursor)->key, key)) {
            tmp = *cursor;
            *cursor = (*cursor)->next;
            free(tmp->key);
            free(tmp);
            tmp = NULL;
            return TRUE;
        }

        cursor = &(*cursor)->next;
    }

    return FALSE;
}

void destroy(hashmap_t* hashmap)
{
    size_t i;
    node_t* p;
    node_t* next;

    for (i = 0; i < hashmap->length; i++) {
        p = hashmap->plist[i];

        while (p != NULL) {
            next = p->next;
            free(p->key);
            free(p);
            p = next;
        }
    }

    if (hashmap->plist != NULL) {
        free(hashmap->plist);
        hashmap->plist = NULL;
    }

    if (hashmap != NULL) {
        free(hashmap);
        hashmap = NULL;
    }
}
