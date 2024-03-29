#include "translate.h"

void check_newline_func(int* newline_arr, char* source)
{
    int index = 0;
    int buf_count = 0;
    int check_count = 0;
    while (*(source + index) != '\0') {
        if (*(source + index) == '\n') {
            if (check_count > 0) {
                newline_arr[buf_count - 1]++;
                check_count++;
            } else {
                check_count++;
                newline_arr[buf_count]++;
                buf_count++;
            }
        } else {
            check_count = 0;
        }
        index++;
    }
}

int check_range(char* argv, int* total_range_ch_count, int* check)
{
    int first_index = 0;
    int last_index = 0;
    int left_index = -1;
    int right_index = -1;
    char left_buf[MAX_VALUE] = { 0, };
    char right_buf[MAX_VALUE] = { 0, };
    char buf[MAX_VALUE] = { 0, };
    int is_delim = FALSE;


    size_t i;

    {
        for (i = 1; i < strlen(argv) - 1; i++) {
            if (argv[i] == '-') {
                is_delim = TRUE;
                first_index = argv[i - 1];
                last_index = argv[i + 1];
                left_index = i - 2;
                right_index = i + 2;

                if (first_index > last_index) {
                    continue;
                } else {
                    if (*check == TRUE) {
                        return 0;
                    }
                    *check = 1;
                    goto next;
                }
            }
        }
        if (first_index != last_index) {
            if (first_index > last_index) {
                return ERROR_CODE_INVALID_RANGE;
            }
        }
    }

next:

    if (left_index >= 0) {
        {
            int i;
            for (i = 0; i < left_index + 1; i++) {
                left_buf[i] = argv[i];
            }
        }
    }

    if ((size_t)right_index < strlen(argv)) {
        {
            size_t i;
            for (i = 0; i < strlen(argv) - right_index; i++) {
                right_buf[i] = argv[right_index + i];
            }
        }
    }

    {
        int i;
        for (i = 0; i < last_index - first_index + 1; i++) {
            buf[i] = (char)first_index + i;
        }
    }

    if (is_delim) {
        if (strlen(left_buf) + strlen(right_buf) + strlen(argv) >= MAX_VALUE) {
            return ERROR_CODE_ARGUMENT_TOO_LONG;
        }
        strcat(left_buf, buf);
        strcat(left_buf, right_buf);
        strcpy(argv, left_buf);
    }

    if (i == (size_t)*total_range_ch_count) {
        return -1;
    }

    --(*total_range_ch_count);
    return 0;
}

int translate(int argc, const char** argv)
{
    char first_argv[MAX_VALUE] = { 0, };
    char second_argv[MAX_VALUE] = { 0, };
    char buffer_origin[128] = { 0, };
    char buffer_backup[128] = { 0, };
    /*char read_buffer[32][128] = { 0, };*/

    /*char* ptr = NULL;*/

    /*int read_buffer_count = 0;*/
    int check_newline_arr[16] = { 0, };

    char buffer_overlap_second[128] = { 0, };
    char buffer_overlap_first[128] = { 0, };
    int index_arr[512] = { 0, };
    int index_arr_backup[16] = { 0, };
    int argc_index = 1;
    int is_flag = FALSE;
    int total_range_ch_count1 = 0;
    int total_range_ch_count2 = 0;

    char escape_sequence_arr[] = { '\a', '\b', '\f', '\n', '\r', '\t', '\v', '\"', '\\', '\'' };
    char escape_sequence_check_arr[] = { 'a', 'b', 'f', 'n', 'r', 't', 'v', '"', '\\' };
    char escape_sequence_total_area[32] = { 0, };

    {
        size_t i;
        int count = '\xe';
        for (i = 0; i < '\x1f' + 1 - '\xe'; i++) {
            escape_sequence_total_area[i] = count++;
        }
        escape_sequence_total_area['\x1f'] = '\0';
    }

    if (argc == 4) {
        if ((strcmp(argv[1], "-i") == 0)) {
            argc_index++;
            is_flag = TRUE;
        } else {
            return ERROR_CODE_INVALID_FLAG;
        }
    }

    if (argc < 3 || argc > 4) {
        return ERROR_CODE_WRONG_ARGUMENTS_NUMBER;
    }

    /* argv 크기 검사 */
    if (argc >= 3) {

        /* 입력된 argv 크기 검사 start */
        if (strlen(argv[argc_index]) >= MAX_VALUE || strlen(argv[argc_index + 1]) >= MAX_VALUE) {
            return ERROR_CODE_ARGUMENT_TOO_LONG;
        }
        /* 입력된 argv 크기 검사 end */


        /* (사전조사) \\ 가 2개이상 연속으로 올때? 확인 코드 start */
        {
            size_t i;
            int is_checked = 0;
            int is_escape_exist = FALSE;
            for (i = 0; i < strlen(argv[argc_index]); i++) {
                if (is_checked == 1) {
                    {
                        size_t j;
                        for (j = 0; j < sizeof(escape_sequence_check_arr); j++) {
                            if (escape_sequence_check_arr[j] == argv[argc_index][i]) {
                                is_escape_exist = TRUE;
                                break;
                            }
                        }
                    }
                    if (is_escape_exist == FALSE) {
                        return ERROR_CODE_INVALID_FORMAT;
                    }
                }

                if (argv[argc_index][i] == '\\') {
                    is_checked++;
                    if (is_checked == 2) {
                        is_checked = 0;
                        memmove((void*)(argv[argc_index] + i), (void*)(argv[argc_index] + i + 1), strlen(argv[argc_index]) - i);
                    }
                } else {
                    is_checked = 0;
                }
                is_escape_exist = FALSE;
            }
        }

        {
            size_t i;
            int is_checked = 0;
            int is_escape_exist = FALSE;
            for (i = 0; i < strlen(argv[argc_index + 1]); i++) {
                if (is_checked == 1) {
                    {
                        size_t j;
                        for (j = 0; j < sizeof(escape_sequence_check_arr); j++) {
                            if (escape_sequence_check_arr[j] == argv[argc_index + 1][i]) {
                                is_escape_exist = TRUE;
                                break;
                            }
                        }
                    }
                    if (is_escape_exist == FALSE) {
                        return ERROR_CODE_INVALID_FORMAT;
                    }
                }

                if (argv[argc_index + 1][i] == '\\') {
                    is_checked++;
                    if (is_checked == 2) {
                        is_checked = 0;
                        memmove((void*)(argv[argc_index + 1] + i), (void*)(argv[argc_index + 1] + i + 1), strlen(argv[argc_index + 1]) - i);
                    }
                } else {
                    is_checked = 0;
                }
                is_escape_exist = FALSE;
            }
        }

        /* (사전조사) \\ 가 2개이상 연속으로 올때? 확인 코드 end */


        strcpy(first_argv, argv[argc_index]);
        strcpy(second_argv, argv[argc_index + 1]);





        /* argv에 escape 문자가 들어올 경우1 start */

        {
            size_t i;
            int check = FALSE;
            int check2 = 0;
            /*char buf[MAX_VALUE] = { 0, };*/

            size_t length = strlen(first_argv);
            /*strcpy(buf, first_argv);*/
            for (i = 0; i < length; i++) {
                if (first_argv[i] == '\\') {
                    check = TRUE;
                    check2++;
                    if (check2 == 2) {
                        check2 = 0;
                        goto next;
                    }
                    continue;
                }

            next:
                if (check == TRUE) {
                    size_t j;
                    check = FALSE;
                    check2 = 0;
                    for (j = 0; j < sizeof(escape_sequence_check_arr); j++) {
                        if (escape_sequence_check_arr[j] == first_argv[i]) {
                            first_argv[i - 1] = escape_sequence_arr[j];
                            {
                                size_t k;
                                for (k = i + 1; k < MAX_VALUE; k++) {
                                    /*first_argv[k - 1] = buf[k];*/

                                    {
                                        size_t i;
                                        for (i = k - 1; i < length; i++) {
                                            first_argv[i] = first_argv[i + 1];
                                        }
                                        --length;
                                        break;
                                    }
                                }
                                /*first_argv[k - 1] = '\0';*/
                                i--;
                                break;
                            }
                        }
                    }
                }
            }
        }

        /* argv에 escape 문자가 들어올 경우1 end */

        /* argv에 escape 문자가 들어올 경우2 start */

        {
            size_t i;
            int check = FALSE;
            int check2 = 0;
            char buf[MAX_VALUE] = { 0, };

            size_t length = strlen(second_argv);
            strcpy(buf, second_argv);
            for (i = 0; i < length; i++) {
                if (second_argv[i] == '\\') {
                    check = TRUE;
                    check2++;
                    if (check2 == 2) {
                        check2 = 0;
                        goto next2;
                    }
                    continue;
                }

            next2:
                if (check == TRUE) {
                    size_t j;
                    check = FALSE;
                    check2 = 0;
                    for (j = 0; j < sizeof(escape_sequence_check_arr); j++) {
                        if (escape_sequence_check_arr[j] == second_argv[i]) {
                            second_argv[i - 1] = escape_sequence_arr[j];
                            {
                                size_t k;
                                for (k = i + 1; k < MAX_VALUE; k++) {
                                    /*first_argv[k - 1] = buf[k];*/

                                    {
                                        size_t i;
                                        for (i = k - 1; i < length; i++) {
                                            second_argv[i] = second_argv[i + 1];
                                        }
                                        --length;
                                        break;
                                    }
                                }
                                /*first_argv[k - 1] = '\0';*/
                                i--;
                                break;
                            }
                        }
                    }
                }
            }
        }

        /* argv에 escape 문자가 들어올 경우2 end */






        /* total range count 세기 start*/
        {
            size_t i;
            for (i = 0; i < strlen(first_argv); i++) {
                if (first_argv[i] == '-') {
                    total_range_ch_count1 = i;
                    total_range_ch_count2 = i;
                }
            }
        }

        /* total range count 세기 end*/




        {
            int i;
            int check = 0;
            for (i = 0; i < 128; i++) {
                /* ASCII 코드의 오름차순을 기준으로함 개행문자가 들어오는 경우는 없는 걸로 치고 작성 */
                /* check range */
                if (strlen(first_argv) >= 3) {
                    int error_code = 0;
                    error_code = check_range(first_argv, &total_range_ch_count1, &check);
                    if (error_code > 0) {
                        return error_code;
                    }
                    if (error_code == -1) {
                        break;
                    }
                }

                check = 0;

                if (strlen(second_argv) >= 3) {
                    int error_code = 0;
                    error_code = check_range(second_argv, &total_range_ch_count2, &check);
                    if (error_code > 0) {
                        return error_code;
                    }
                    if (error_code == -1) {
                        break;
                    }
                }
            }
        }
        /* check range */


        /* 허용되지 않는 escape 문자가 있는지 다시 한번더 검사1 start */
        {
            int i;

            for (i = 0; i < strlen(first_argv); i++) {
                {
                    size_t j;
                    for (j = 0; j < strlen(escape_sequence_total_area); j++) {
                        if (escape_sequence_total_area[j] == first_argv[i]) {
                            return ERROR_CODE_INVALID_FORMAT;
                        }
                    }
                }
            }
        }

        /* 허용되지 않는 escape 문자가 있는지 다시 한번더 검사1 end */

        /* 허용되지 않는 escape 문자가 있는지 다시 한번더 검사2 start */
        {
            int i;

            for (i = 0; i < strlen(second_argv); i++) {
                {
                    size_t j;
                    for (j = 0; j < strlen(escape_sequence_total_area); j++) {
                        if (escape_sequence_total_area[j] == second_argv[i]) {
                            return ERROR_CODE_INVALID_FORMAT;
                        }
                    }
                }
            }
        }

        /* 허용되지 않는 escape 문자가 있는지 다시 한번더 검사2 end */


        /* first argv 중복 check start */
        {
            int total_count = 0;
            {
                size_t i;
                size_t j;
                int index = 0;
                for (i = 0; i < strlen(first_argv); i++) {
                    for (j = 0; j < strlen(first_argv); j++) {
                        if (first_argv[i] == first_argv[j]) {
                            index = j;
                        }
                        if (first_argv[i] == '-') {
                            index_arr[index] = index + 1;
                        }
                    }
                    index_arr[index] = index + 1;
                }
            }

            {
                size_t i;
                int count = 0;
                for (i = 0; i < strlen(first_argv); i++) {
                    if (index_arr[i] != 0) {
                        index_arr_backup[count] = index_arr[i];
                        count++;
                    }
                }
                total_count = count;
            }

            {
                int i;
                for (i = 0; i < total_count; i++) {
                    buffer_overlap_second[i] = second_argv[index_arr_backup[i] - 1];
                    buffer_overlap_first[i] = first_argv[index_arr_backup[i] - 1];
                }
            }
        }

        strcpy(second_argv, buffer_overlap_second);
        strcpy(first_argv, buffer_overlap_first);
        /* first argv 중복 check end */








        /* first argv 가 더 클때 start */
        if (strlen(first_argv) > strlen(second_argv)) {
            int second_argv_length = strlen(second_argv);
            int sub_both_length = strlen(first_argv) - strlen(second_argv);
            {
                int i;
                for (i = 0; i < sub_both_length; i++) {
                    second_argv[second_argv_length + i] = second_argv[strlen(second_argv) - 1];
                }
            }
        }
        /* first argv 가 더 클때 end */
    }



    /* 모든 문자열 읽기 start */
    {
        int count = 0;
        while ((buffer_origin[count] = getchar()) != EOF) {
            count++;
        }
    }
    /* 모든 문자열 읽기 end */



    buffer_origin[strlen(buffer_origin) - 1] = '\0';

    strcpy(buffer_backup, buffer_origin);

    check_newline_func(check_newline_arr, buffer_origin);


    /* 문자열 변환 (-i flag 가 들어올시) start */
    if (argc >= 3) {
        {
            size_t i;
            int count = 0;
            /* 대소문자 flag가 활성화 될경우 */
            if (is_flag) {
                while (buffer_backup[count] != '\0') {
                    for (i = 0; i < strlen(first_argv); i++) {
                        if (buffer_backup[count] == first_argv[i] || buffer_backup[count] == (first_argv[i] - 32)) {
                            buffer_backup[count] = second_argv[i];
                            break;
                        }
                    }
                    count++;
                }
            } else {
                while (buffer_backup[count] != '\0') {
                    for (i = 0; i < strlen(first_argv); i++) {
                        if (buffer_backup[count] == first_argv[i]) {
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


    buffer_backup[strlen(buffer_backup)] = '\0';
    printf("%s", buffer_backup);

    return 0;
}
