#ifndef USER
#define USER

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

typedef struct user {
    size_t id;
    char username[51];
    char email[51];
    char password[51];
} user_t;




#endif // !USER
