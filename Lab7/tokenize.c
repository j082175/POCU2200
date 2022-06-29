#include "tokenize.h"
/*I like cookies. Do you like cookies? Cookies are good!*/
/* ?!.*/
char** tokenize_malloc(const char* str, const char* delim)
{
    char* str_backup = NULL;
    int str_length = strlen(str);
    int delim_length = strlen(delim);
    int str_start_index = 0;
    char** arr = (char**)malloc(sizeof(char*) * str_length);
    char* backup = NULL;
    int arr_count = 0;

    if (str_length == 0)
    {
        arr = (char**)malloc(sizeof(char*) * 1);
    }

    if (arr == NULL)
    {
        return NULL;
    }
    str_backup = (char*)malloc(sizeof(char) * str_length + 1);
    if (str_backup == NULL)
    {
        return NULL;
    }
    strncpy(str_backup, str, str_length + 1);
    backup = str_backup;
    {
        int i;
        int j;
        for (i = 0; i < str_length; i++)
        {
            if (delim_length == 0 || str_length == 1)
            {
                char** str2 = (char**)malloc(sizeof(char*) * 2);
                if (str2 == NULL)
                {
                    return NULL;
                }
                str2[0] = (char*)malloc(sizeof(char) * str_length + 1);
                if (str2[0] == NULL)
                {
                    return NULL;
                }
                strcpy(str2[0], str);
                str2[1] = NULL;
                return str2;
            }

            for (j = 0; j < delim_length; j++)
            {
                if (*(str + i) == *(delim + j))
                {
                    if (i - str_start_index == 0)
                    {
                        str_start_index++;
                        break;
                    }
                    arr[arr_count] = (char*)malloc(sizeof(char) * (i - str_start_index + 1));
                    if (arr[arr_count] == NULL)
                    {
                        return NULL;
                    }
                    strncpy(arr[arr_count], backup, i - str_start_index + 1);
                    arr[arr_count][i - str_start_index] = '\0';
                    str_start_index = i + 1;
                    arr_count++;
                    break;
                }
            }

            backup = str_backup + str_start_index;
        }
        if (*backup != '\0')
        {
            arr[arr_count] = (char*)malloc(sizeof(char) * (i - str_start_index + 1));
            if (arr[arr_count] == NULL)
            {
                return NULL;
            }
            strncpy(arr[arr_count], backup, i - str_start_index + 1);
            arr[arr_count][i - str_start_index] = '\0';
            str_start_index = i + 1;
            arr_count++;
        }
        arr[arr_count] = NULL;
    }

    free(str_backup);
    return arr;
}
