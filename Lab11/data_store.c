#include "data_store.h"

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id)
{
    size_t count = 0;
    user_t* return_user = NULL;

    while (*(users_or_null + count) != NULL) {
        if ((*(users_or_null + count))->id == id) {
            return_user = (*(users_or_null + count));
            break;
        }
        count++;
    }

    return return_user;
}

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username)
{
    size_t count = 0;
    user_t* return_user = NULL;

    while (*(users_or_null + count) != NULL) {
        if (!strcmp((*(users_or_null + count))->username, username)) {
            return_user = (*(users_or_null + count));
        }
        count++;
    }

    return return_user;
}

int update_email(user_t** users_or_null, size_t id, const char* email)
{
    user_t* user = NULL;
    FILE* fp;

    {
        size_t count = 0;

        while (*(users_or_null + count) != NULL) {
            if ((*(users_or_null + count))->id == id) {
                strcpy((*(users_or_null + count))->email, email);

                user = (*(users_or_null + count));
                break;
            }
            count++;
        }

    }

    if (user == NULL) {
        return FALSE;
    }

    fp = fopen("log.txt", "a");
    if (fp == NULL) {
        assert(FALSE);
    }

    /* release mode */
#ifdef RELEASE
    {
        char email1[50];
        size_t length = 0;
        size_t i;

        strcpy(email1, user->email);

        while (*(user->email + length) != '@') {
            length++;
        }

        if (length == 1) {
            email1[0] = '*';
        } else if (length == 2) {
            strcpy(email1, user->email);
            email1[1] = '*';
        } else {
            for (i = 1; i < length - 1; i++) {
                email1[i] = '*';
            }
        }

        fprintf(fp, "TRACE: User %zu updated email from \"%s\" to \"%s\"\n", user->id, user->email, email1);
    }
#endif // RELEASE


    /* debug mode */
#ifndef RELEASE
    fprintf(fp, "TRACE: User %zu updated email from \"%s\" to \"%s\"\n", user->id, user->email, email);
#endif // !RELEASE


    if (fclose(fp) == EOF) {
        assert(FALSE);
    }

    return TRUE;
}

int update_password(user_t** users_or_null, size_t id, const char* password)
{
    user_t* user = NULL;
    FILE* fp;

    {
        size_t count = 0;

        while (*(users_or_null + count) != NULL) {
            if ((*(users_or_null + count))->id == id) {
                strcpy((*(users_or_null + count))->password, password);

                user = (*(users_or_null + count));
                break;
            }
            count++;
        }
    }

    if (user == NULL) {
        return FALSE;
    }

    fp = fopen("log.txt", "a");
    if (fp == NULL) {
        assert(FALSE);
    }

    /* release mode */
#ifdef RELEASE
    {
        char password1[50];
        size_t length = 0;
        size_t i;

        strcpy(password1, user->password);

        length = strlen(user->password);

        if (length == 1) {
            password1[0] = '*';
        } else if (length == 2) {
            strcpy(password1, user->password);
            password1[1] = '*';
        } else {
            for (i = 1; i < length - 1; i++) {
                password1[i] = '*';
            }
        }

        fprintf(fp, "TRACE: User %zu updated password from \"%s\" to \"%s\"\n", user->id, user->password, password1);
    }
#endif // RELEASE

    /* debug mode */
#ifndef RELEASE
    fprintf(fp, "TRACE: User %zu updated password from \"%s\" to \"%s\"\n", user->id, user->password, password);
#endif // !RELEASE

    if (fclose(fp) == EOF) {
        assert(FALSE);
    }

    return TRUE;
}
