#include "my_string.h"

void reverse(char* str) {
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

    for (int i = 0; i < str_length + 1; i++) {

        if (*(str + i) == '0' || *(str + i) == '\0') {
            for (int i = current_position - 1; i >= current_space_position + 1; i--) {
                backup[count] = *(str + i);
                count++;
            }
            backup[current_position] = ' ';
            current_space_position = current_position;
            count = current_space_position + 1;
        }



        current_position++;
    }

    for (int i = 0; i < str_length; i++) {
        *(str + i) = backup[i];
    }
}

int index_of(const char* str, const char* word) {
    return 1;
}

void reverse_by_words(char* str) {
    char backup[100] = {0, };
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

    for (int i = 0; i < str_length + 1; i++) {

        if (*(str + i) == ' ' || *(str + i) == '\0') {
            for (int i = current_position - 1; i >= current_space_position + 1; i--) {
                backup[count] = *(str + i);
                count++;
            }
            backup[current_position] = ' ';
            current_space_position = current_position;
            count = current_space_position + 1;
        }



        current_position++;
    }

    for (int i = 0; i < str_length; i++) {
        *(str + i) = backup[i];
    }
}

char* tokenize(char* str_or_null, const char* delims) {
    int delims_length = 0;
    int str_or_null_length = 0;
    char backup[100] = {0, };
    static char* str_or_null_backup_ptr;
    int current_position = 0;
    char* token_str = 0;
    int count = 0;
    char* ptr = 0;


    if (str_or_null == 0) {
        str_or_null = str_or_null_backup_ptr;
    }

    while (*(delims + delims_length) != '\0') {
        delims_length++;
    }

    while (*(str_or_null + str_or_null_length) != '\0') {
        str_or_null_length++;
    }


    for (int i = 0; i < delims_length; i++) {
        if (*(str_or_null) == *(delims + i)) {
            str_or_null = str_or_null + 1;
            break;
        }
    }





    for (int i = 0; i < str_or_null_length; i++)
    {
        for (int j = 0; j < delims_length; j++)
        {

            if (*(str_or_null + current_position) == *(delims + j)) {
                *(str_or_null + current_position) = '\0';
                str_or_null_backup_ptr = str_or_null + current_position + 1;

                goto label1;
            }


        }



        current_position++;
    }


label1:
    return str_or_null;
}

char* reverse_tokenize(char* str_or_null, const char* delims) {


        char* backup = tokenize(str_or_null , delims);
        reverse(backup);
        str_or_null = backup;

    return str_or_null;
}
