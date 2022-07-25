#include "data_store.h"

user_t* get_user_by_id_or_null(user_t** users_or_null, size_t id)
{
    size_t count = 0;
    user_t* return_user = NULL;

    if (users_or_null == NULL) {
        return return_user;
    }

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

    if (users_or_null == NULL) {
        return return_user;
    }

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
    char* old_email = NULL;

    if (users_or_null == NULL) {
        return FALSE;
    }

    {
        size_t count = 0;

        while (*(users_or_null + count) != NULL) {
            if ((*(users_or_null + count))->id == id) {
                old_email = malloc(sizeof(char) * strlen((*(users_or_null + count))->email) + 1);
                strcpy(old_email, (*(users_or_null + count))->email);
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
        char* email1;
        char* old_email1;
        size_t length = 0;
        size_t old_email1_length = 0;
        size_t i;

        email1 = malloc(sizeof(char) * strlen(user->email) + 1);
        strcpy(email1, user->email);

        old_email1 = malloc(sizeof(char) * strlen(old_email) + 1);
        strcpy(old_email1, old_email);

        while (*(user->email + length) != '@') {
            length++;
        }

        if (length == 1) {
            email1[0] = '*';
        } else if (length == 2) {
            email1[1] = '*';
        } else {
            for (i = 1; i < length - 1; i++) {
                email1[i] = '*';
            }
        }

        while (*(old_email1 + old_email1_length) != '@') {
            old_email1_length++;
        }

        if (old_email1_length == 1) {
            old_email1[0] = '*';
        } else if (old_email1_length == 2) {
            old_email1[1] = '*';
        } else {
            for (i = 1; i < old_email1_length - 1; i++) {
                old_email1[i] = '*';
            }
        }

        fprintf(fp, "TRACE: User %zu updated email from \"%s\" to \"%s\"\n", user->id, old_email1, email1);

        free(old_email1);
        free(email1);
    }
#endif // RELEASE


    /* debug mode */
#ifndef RELEASE
    fprintf(fp, "TRACE: User %zu updated email from \"%s\" to \"%s\"\n", user->id, old_email, email);
#endif // !RELEASE


    if (fclose(fp) == EOF) {
        assert(FALSE);
    }

    free(old_email);

    return TRUE;
}

int update_password(user_t** users_or_null, size_t id, const char* password)
{
    user_t* user = NULL;
    FILE* fp;
    char* old_password = NULL;

    if (users_or_null == NULL) {
        return FALSE;
    }

    {
        size_t count = 0;

        while (*(users_or_null + count) != NULL) {
            if ((*(users_or_null + count))->id == id) {
                old_password = malloc(sizeof(char) * strlen((*(users_or_null + count))->password) + 1);
                strcpy(old_password, (*(users_or_null + count))->password);
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
        char* password1;
        char* old_password1;
        size_t length = 0;
        size_t length1 = 0;
        size_t i;

        password1 = malloc(sizeof(char) * strlen(user->password) + 1);
        strcpy(password1, user->password);

        old_password1 = malloc(sizeof(char) * strlen(old_password) + 1);
        strcpy(old_password1, old_password);

        length = strlen(user->password);
        length1 = strlen(old_password1);

        if (length == 1) {
            password1[0] = '*';
        } else if (length == 2) {
            password1[1] = '*';
        } else {
            for (i = 1; i < length - 1; i++) {
                password1[i] = '*';
            }
        }

        if (length1 == 1) {
            old_password1[0] = '*';
        } else if (length1 == 2) {
            old_password1[1] = '*';
        } else {
            for (i = 1; i < length1 - 1; i++) {
                old_password1[i] = '*';
            }
        }

        fprintf(fp, "TRACE: User %zu updated password from \"%s\" to \"%s\"\n", user->id, old_password1, password1);

        free(old_password1);
        free(password1);
    }
#endif // RELEASE

    /* debug mode */
#ifndef RELEASE
    fprintf(fp, "TRACE: User %zu updated password from \"%s\" to \"%s\"\n", user->id, old_password, password);
#endif // !RELEASE

    if (fclose(fp) == EOF) {
        assert(FALSE);
    }

    free(old_password);

    return TRUE;
}
