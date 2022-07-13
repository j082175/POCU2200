#include "hashmap.h"
/* 모든 함수의 포인터형에 NULL 은 들어가지 않는다고 가정한다. */
/* hashmap 이란? 데이터가 2개가 있는 거 + 배열이 아닌 링크드 리스트로 구현 */

size_t get_prime_number(size_t length)
{
    size_t prime_number;
    {
        int count = 0;
        size_t i;
        int is_prime = FALSE;
        size_t double_num = length * 2;
        while (TRUE)
        {
            for (i = 3; i < double_num; i++)
            {
                if (double_num % i != 0 && double_num % 2 != 0)
                {
                    is_prime = TRUE;
                    continue;
                }
                else
                {
                    is_prime = FALSE;
                    break;
                }
            }
            if (is_prime)
            {
                prime_number = double_num;
                break;
            }
            double_num++;
        }
    }

    return prime_number;
}

hashmap_t* init_hashmap_malloc(size_t length, size_t(*p_hash_func)(const char* key))
{
    size_t prime_number;
    node_t** hash_table;
    hashmap_t* hashmap;

    prime_number = get_prime_number(length);

    hash_table = (node_t**)malloc(sizeof(node_t*) * prime_number);
    if (hash_table == NULL)
    {
        assert(FALSE);
    }

    {
        int i;
        for (i = 0; i < prime_number; i++)
        {
            hash_table[i] = NULL;
        }
    }

    hashmap = (hashmap_t*)malloc(sizeof(hashmap_t));
    if (hashmap == NULL)
    {
        assert(FALSE);
    }

    hashmap->plist = hash_table;

    hashmap->length = prime_number;
    hashmap->hash_func = p_hash_func;

    return hashmap;
}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{
    int is_added = FALSE;
    size_t count = 0;
    size_t hash = 0;
    node_t* node = (node_t*)malloc(sizeof(node_t));
    if (node == NULL)
    {
        assert(FALSE);
    }

    node->key = (char*)malloc(sizeof(char) * strlen(key) + 1);
    if (node->key == NULL)
    {
        assert(FALSE);
    }
    strcpy(node->key, key);

    node->value = value;

    hash = (hashmap->hash_func(key)) % (hashmap->length);

    {
        int i;
        int start_index;

        start_index = hash;
        if (start_index < 0)
        {
            start_index += hashmap->length;
        }

        i = start_index;

        do
        {
            if (hashmap->plist[i] == NULL)
            {
                hashmap->plist[i] = node;
                return TRUE;
            }

            if (!strcmp(hashmap->plist[i]->key, node->key))
            {
                free(node->key);
                free(node);
                return FALSE;
            }


            i = (i + 1) % hashmap->length;

        } while (i != start_index);
    }

    //{
    //	hashmap_t* hashmap2;
    //	size_t length = hashmap->length;
    //	size_t(*hash_func)(const char*) = hashmap->hash_func;

    //	hashmap2 = init_hashmap_malloc(length * 2, hash_func);

    //	{
    //		size_t i;
    //		for (i = 0; i < length; i++)
    //		{
    //			add_key(hashmap2, hashmap->plist[i]->key, hashmap->plist[i]->value);
    //		}
    //	}

    //	destroy(hashmap);

    //	*hashmap = *hashmap2;

    //	add_key(hashmap2, key, value);
    //}
    


    free(node->key);
    free(node);

    return FALSE;


    //return TRUE;
}

int get_value(const hashmap_t* hashmap, const char* key)
{
    size_t hash = hashmap->hash_func(key) % hashmap->length;

    {
        int i;
        int start_index;

        start_index = hash;
        if (start_index < 0)
        {
            start_index += hashmap->length;
        }

        i = start_index;

        do
        {
            if (hashmap->plist[i] == NULL)
            {
                i = (i + 1) % hashmap->length;
                continue;
            }

            if (!strcmp(hashmap->plist[i]->key, key))
            {
                return hashmap->plist[i]->value;
            }


            i = (i + 1) % hashmap->length;

        } while (i != start_index);
    }

    return EOF;
}

int update_value(hashmap_t* hashmap, const char* key, const int value)
{
    size_t hash = hashmap->hash_func(key) % hashmap->length;

    {
        int i;
        int start_index;

        start_index = hash;
        if (start_index < 0)
        {
            start_index += hashmap->length;
        }

        i = start_index;

        do
        {
            if (!strcmp(hashmap->plist[i]->key, key))
            {
                hashmap->plist[i]->value = value;
                return TRUE;
            }


            i = (i + 1) % hashmap->length;

        } while (i != start_index);
    }

    return FALSE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    size_t hash = hashmap->hash_func(key) % hashmap->length;

    {
        int i;
        int start_index;

        start_index = hash;
        if (start_index < 0)
        {
            start_index += hashmap->length;
        }

        i = start_index;

        do
        {
            if (hashmap->plist[i] == NULL)
            {
                i = (i + 1) % hashmap->length;
                continue;
            }

            if (!strcmp(hashmap->plist[i]->key, key))
            {
                free(hashmap->plist[i]->key);
                hashmap->plist[i]->key = NULL;
                free(hashmap->plist[i]);
                hashmap->plist[i] = NULL;
                return TRUE;
            }


            i = (i + 1) % hashmap->length;

        } while (i != start_index);
    }

    return FALSE;
}

void destroy(hashmap_t* hashmap)
{
    int i;
    for (i = 0; i < hashmap->length; i++)
    {

        if (hashmap->plist[i] != NULL)
        {

            if (hashmap->plist[i]->key != NULL)
            {
                free(hashmap->plist[i]->key);
                hashmap->plist[i]->key = NULL;
            }

            free(hashmap->plist[i]);
            hashmap->plist[i] = NULL;
        }
    }

    if (hashmap->plist != NULL)
    {
        free(hashmap->plist);
        hashmap->plist = NULL;
    }

    if (hashmap != NULL)
    {
        free(hashmap);
        hashmap = NULL;
    }
}
