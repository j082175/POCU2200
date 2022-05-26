#include "my_string.h"

void reverse(char* str)
{
    char backup[100] = { 0, };
    int str_length = 0;
    int space_count = 0;
    int current_position = 0;
    int current_space_position = -1;
    int count = 0;

    if (str == 0) {
        return;
    }

    while (*(str + str_length) != '\0') {
        if (*(str + str_length) == ' ') {
            space_count++;
        }
        str_length++;
    }

    {
        int i;
        int j;
        for (i = 0; i < str_length + 1; i++) {

            if (*(str + i) == '0' || *(str + i) == '\0') {
                for (j = current_position - 1; j >= current_space_position + 1; j--) {
                    backup[count] = *(str + j);
                    count++;
                }
                backup[current_position] = ' ';
                current_space_position = current_position;
                count = current_space_position + 1;
            }
            current_position++;
        }
    }

    {
        int i;
        for (i = 0; i < str_length; i++) {
            *(str + i) = backup[i];
        }
    }
}

int index_of(const char* str, const char* word)
{
    int word_length = 0;
    int str_count = 0;
    char word_backup[100] = {0, };
    int check_count = 0;
    int check_first_word_count = 0;
    int is_check = 1;

    while (*(word + word_length) != '\0') {
        ++word_length;
    }

{
    int i;
    for (i = 0; i < word_length; i++){
        word_backup[i] = *(word + i);
    }
}

    while (*(str + str_count) != '\0') {
        if (*(str + str_count) == word_backup[check_count]) {
            check_count++;
            if (is_check) {
                check_first_word_count = str_count;
                is_check = 0;
            }
            if (check_count == 5) {
                goto label1;
            }
        } else {
            check_count = 0;
            is_check = 1;
        }
        str_count++;
    }

label1:
    return check_first_word_count;
}

void reverse_by_words(char* str)
{
    char backup[100] = { 0, };
    int str_length = 0;
    int space_count = 0;
    int current_position = 0;
    int current_space_position = -1;
    int count = 0;

    while (*(str + str_length) != '\0') {
        if (*(str + str_length) == ' ') {
            space_count++;
        }
        str_length++;
    }

    {
        int i;
        int j;
        for (i = 0; i < str_length + 1; i++) {

            if (*(str + i) == ' ' || *(str + i) == '\0') {
                for (j = current_position - 1; j >= current_space_position + 1; j--) {
                    backup[count] = *(str + j);
                    count++;
                }
                backup[current_position] = ' ';
                current_space_position = current_position;
                count = current_space_position + 1;
            }
            current_position++;
        }
    }

    {
        int i;
        for (i = 0; i < str_length; i++) {
            *(str + i) = backup[i];
        }
    }
}

char* tokenize(char* str_or_null, const char* delims)
{
    int delims_length = 0;
    int str_or_null_length = 0;
    static char* s_str_or_null_backup_ptr;
    int current_position = 0;


    if (str_or_null == 0) {
        if (s_str_or_null_backup_ptr == 0) {
            return 0;
        }
        str_or_null = s_str_or_null_backup_ptr;
    }

    while (*(delims + delims_length) != '\0') {
        delims_length++;
    }

    while (*(str_or_null + str_or_null_length) != '\0') {
        str_or_null_length++;
    }

    {
        int i;
        int j;

        for (j = 0; j < delims_length; j++) {
            do {
                for (i = 0; i < delims_length; i++) {
                    if (*(str_or_null) == *(delims + i)) {
                        str_or_null = str_or_null + 1;
                        break;
                    }
                }
            } while (*(str_or_null) == *(delims + j));
        }

    }


    {
        int i;
        int j;
        for (i = 0; i < str_or_null_length; i++) {
            for (j = 0; j < delims_length; j++) {
                if (*(str_or_null + current_position) == *(delims + j)) {
                    *(str_or_null + current_position) = '\0';

                    s_str_or_null_backup_ptr = str_or_null + current_position + 1;

                    goto label1;

                }
            }
            current_position++;
        }
    }


label1:
    if (str_or_null_length == 0) {
        str_or_null = 0;
    }
    return str_or_null;
}

char* reverse_tokenize(char* str_or_null, const char* delims)
{
    char* backup = tokenize(str_or_null, delims);
    reverse(backup);
    str_or_null = backup;

    return str_or_null;
}
