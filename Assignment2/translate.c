#include "translate.h"

void check_newline_func(int* newline_arr, char* source)
{
    int index = 0;
    int buf_count = 0;
    int check_count = 0;
    while (*(source + index) != '\0')
    {
        if (*(source + index) == '\n')
        {
            if (check_count > 0)
            {
                newline_arr[buf_count - 1]++;
                check_count++;
            }
            else {
                check_count++;
                newline_arr[buf_count]++;
                buf_count++;
            }
        }
        else {
            check_count = 0;
        }
        index++;
    }
}

int translate(int argc, const char** argv)
{
    const unsigned int MAX_VALUE = 512;
    char first_argv[512] = { 0, };
    char second_argv[512] = { 0, };
    char buffer_origin[128] = { 0, };
    char buffer_backup[128] = { 0, };
    char read_buffer[32][128] = { 0, };

    char* ptr = NULL;

    int read_buffer_count = 0;
    int check_newline_arr[16] = { 0, };

    char check_character_left[16] = { 0, };
    char check_character_right[16] = { 0, };

    char buffer_overlap_second[128] = { 0, };
    char buffer_overlap_first[128] = { 0, };
    int index_arr[512] = { 0, };
    int index_arr_backup[16] = { 0, };
    int argc_index = 1;
    int is_flag = FALSE;

    if (argc > 3)
    {
        argc_index++;
        is_flag = TRUE;
    }

    if (argc >= 3)
    {
        if (strlen(argv[argc_index]) > MAX_VALUE || strlen(argv[argc_index + 1]) > MAX_VALUE)
        {
            return ERROR_CODE_ARGUMENT_TOO_LONG;
        }


        /* argv에 escape 문자가 들어올 경우 */



        strcpy(first_argv, argv[argc_index]);
        strcpy(second_argv, argv[argc_index + 1]);



        /* first argv 가 더 클때 start */
        if (strlen(first_argv) > strlen(second_argv))
        {
            int second_argv_length = strlen(second_argv);
            int sub_both_length = strlen(first_argv) - strlen(second_argv);
            {
                int i;
                for (i = 0; i < sub_both_length; i++)
                {
                    second_argv[second_argv_length + i] = second_argv[strlen(second_argv) - 1];
                }
            }
        }
        /* first argv 가 더 클때 end */


        /* 중복 check start */
        {
            int total_count = 0;
            {
                size_t i;
                size_t j;
                int count = 0;
                int index = 0;
                for (i = 0; i < strlen(first_argv); i++)
                {
                    for (j = 0; j < strlen(first_argv); j++)
                    {
                        if (first_argv[i] == first_argv[j])
                        {
                            index = j;
                        }
                    }
                    //buffer[index] = second_argv[index];
                    index_arr[index] = index + 1;
                }
            }

            {
                size_t i;
                int count = 0;
                for (i = 0; i < strlen(first_argv); i++)
                {
                    if (index_arr[i] != 0)
                    {
                        index_arr_backup[count] = index_arr[i];
                        count++;
                    }
                }
                total_count = count;
            }

            {
                int i;
                for (i = 0; i < total_count; i++)
                {
                    buffer_overlap_second[i] = second_argv[index_arr_backup[i] - 1];
                    buffer_overlap_first[i] = first_argv[index_arr_backup[i] - 1];
                }
            }
        }

        strcpy(second_argv, buffer_overlap_second);
        strcpy(first_argv, buffer_overlap_first);
        /* 중복 check end */
    }



    /* 모든 문자열 읽기 start */
    {
        int count = 0;
        while ((buffer_origin[count] = getchar()) != EOF)
        {
            count++;
        }
    }
    /* 모든 문자열 읽기 end */



    buffer_origin[strlen(buffer_origin) - 1] = '\0';

    strcpy(buffer_backup, buffer_origin);

    check_newline_func(check_newline_arr, buffer_origin);


    /* 문자열 변환 start */
    if (argc >= 3)
    {
        {
            size_t i;
            int count = 0;
            if (is_flag) /* 대소문자 flag가 활성화 될경우 */
            {
                while (buffer_backup[count] != '\0')
                {
                    for (i = 0; i < strlen(first_argv); i++)
                    {
                        if (buffer_backup[count] == first_argv[i] || buffer_backup[count] == (first_argv[i] - 32))
                        {
                            buffer_backup[count] = second_argv[i];
                            break;
                        }
                    }
                    count++;
                }
            }
            else {
                while (buffer_backup[count] != '\0')
                {
                    for (i = 0; i < strlen(first_argv); i++)
                    {
                        if (buffer_backup[count] == first_argv[i])
                        {
                            buffer_backup[count] = second_argv[i];
                            break;
                        }
                    }
                    count++;
                }
            }
        }
    }
    /* 문자열 변환 end */



    /* 읽은 문자열 쪼개기 start */
    ptr = buffer_backup;
    {
        char* temp = NULL;
        while (1)
        {
            temp = strtok(ptr, "\n");
            if (temp == NULL)
            {
                break;
            }
            strcpy(read_buffer[read_buffer_count++], temp);
            ptr = NULL;
        }
    }
    /* 읽은 문자열 쪼개기 end */

    /* 문자열 내보내기 전 개행문자 추가  start */
    {
        int i;
        int j;
        int length = 0;
        for (i = 0; i < read_buffer_count; i++)
        {
            length = strlen(read_buffer[i]);
            for (j = 0; j < check_newline_arr[i]; j++)
            {
                read_buffer[i][length + j] = '\n';
            }
        }
    }
    /* 문자열 내보내기 전 개행문자 추가  end */



    /* 문자열 출력 start */
    {
        int i;
        for (i = 0; i < read_buffer_count; i++)
        {
            printf("%s", read_buffer[i]);
        }
    }
    /* 문자열 출력 end */



    /*return translate(argc, argv);*/

    return TRUE;
}
