#ifndef DATA_STORE
#define DATA_STORE

#define _CRT_SECURE_NO_WARNINGS

#include "user.h"

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id);

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username);

int update_email(user_t** users_or_null, size_t id, const char* email);

int update_password(user_t** users_or_null, size_t id, const char* password);


#endif // !DATA_STORE
