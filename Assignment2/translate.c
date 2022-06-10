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

int check_range(char* argv)
{
    int first_index = 0;
    int last_index = 0;
    int left_index = -1;
    int right_index = -1;
    char left_buf[MAX_VALUE] = { 0, };
    char right_buf[MAX_VALUE] = { 0, };
    char buf[MAX_VALUE] = { 0, };
    int is_delim = FALSE;

    {
        size_t i;
        for (i = 1; i < strlen(argv) - 1; i++)
        {
            if (argv[i] == '-')
            {
                is_delim = TRUE;
                first_index = argv[i - 1];
                last_index = argv[i + 1];
                left_index = i - 2;
                right_index = i + 2;
                break;
            }
        }
    }

    if (first_index > last_index)
    {
        return ERROR_CODE_INVALID_RANGE;
    }

    if (left_index >= 0)
    {
        {
            int i;
            for (i = 0; i < left_index + 1; i++)
            {
                left_buf[i] = argv[i];
            }
        }
    }

    if (right_index < strlen(argv))
    {
        {
            size_t i;
            for (i = 0; i < strlen(argv) - right_index; i++)
            {
                right_buf[i] = argv[right_index + i];
            }
        }
    }

    {
        int i;
        for (i = 0; i < last_index - first_index + 1; i++)
        {
            buf[i] = (char)first_index + i;
        }
    }

    if (is_delim)
    {
        if (strlen(left_buf) + strlen(right_buf) + strlen(argv) >= MAX_VALUE)
        {
            return ERROR_CODE_ARGUMENT_TOO_LONG;
        }
		strcat(left_buf, buf);
		strcat(left_buf, right_buf);
		strcpy(argv, left_buf);
    }
}

int translate(int argc, const char** argv)
{
    char first_argv[MAX_VALUE] = { 0, };
    char second_argv[MAX_VALUE] = { 0, };
    char buffer_origin[128] = { 0, };
    char buffer_backup[128] = { 0, };
    char read_buffer[32][128] = { 0, };

    char* ptr = NULL;

    int read_buffer_count = 0;
    int check_newline_arr[16] = { 0, };

    char buffer_overlap_second[128] = { 0, };
    char buffer_overlap_first[128] = { 0, };
    int index_arr[512] = { 0, };
    int index_arr_backup[16] = { 0, };
    int argc_index = 1;
    int is_flag = FALSE;

    if (argc == 4) {
        if ((strcmp(argv[1], "-i") == 0)) {
            argc_index++;
            is_flag = TRUE;
        } else {
            return ERROR_CODE_INVALID_FLAG;
        }
    }

    if (argc < 3 || argc > 4)
    {
        return ERROR_CODE_WRONG_ARGUMENTS_NUMBER;
    }

    /* argv 크기 검사 */
    if (argc >= 3)
    {
        if (strlen(argv[argc_index]) >= MAX_VALUE || strlen(argv[argc_index + 1]) >= MAX_VALUE)
        {
            return ERROR_CODE_ARGUMENT_TOO_LONG;
        }

        strcpy(first_argv, argv[argc_index]);
        strcpy(second_argv, argv[argc_index + 1]);

        /* argv에 escape 문자가 들어올 경우 start */
        /* ASCII 코드의 오름차순을 기준으로함 개행문자가 들어오는 경우는 없는 걸로 치고 작성 */

        if (strlen(first_argv) >= 3)
        {
            int error_code = 0;
            error_code = check_range(first_argv);
            if (error_code == ERROR_CODE_INVALID_RANGE)
            {
                return error_code;
            }
        }

        if (strlen(second_argv) >= 3)
        {
            int error_code = 0;
            error_code = check_range(second_argv);
            if (error_code == ERROR_CODE_INVALID_RANGE)
            {
                return error_code;
            }
        }

        /* argv에 escape 문자가 들어올 경우 end */





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


        /* first argv 중복 check start */
        {
            int total_count = 0;
            {
                size_t i;
                size_t j;
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
        /* first argv 중복 check end */
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

    return 0;
}
