#include "tokenize.h"
/*I like cookies. Do you like cookies? Cookies are good!*/
/* ?!.*/
char** tokenize_malloc(const char* str, const char* delim)
{
    char str_backup[128] = { 0, };
    int str_length = strlen(str);
    int delim_length = strlen(delim);
    int str_start_index = 0;
    char** arr = (char**)malloc(sizeof(char) * str_length);
    char* backup = NULL;
    int arr_count = 0;

    strcpy(str_backup, str);
    backup = str_backup;
    {
        int i;
        int j;
        for (i = 0; i < str_length; i++)
        {
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
                    strncpy(arr[arr_count], backup, i - str_start_index);
                    arr[arr_count][i - str_start_index] = '\0';
                    str_start_index = i + 1;
                    arr_count++;
                    break;
                }
            }
            backup = str_backup + str_start_index;
        }
        arr[arr_count] = NULL;
    }

    return arr;
}
