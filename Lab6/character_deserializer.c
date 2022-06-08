#include "character_deserializer.h"
/* 이 실습에서 계산을 할 때 소수점 이하는 무시하세요. 즉, 모든 결과는 무조건 내림을 합니다.
이 실습에서 전역(global) 변수와 정적(static) 변수의 사용을 금합니다. 전역/정적 변수 없이도 이 실습을 끝낼 수 있으니 저를 믿으세요. :)*/



void swap(char* x, char* y) {
    char t = *x; *x = *y; *y = t;
}

char* reverse(char* buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }

    return buffer;
}

//char* itoa_ft(int value, char* buffer, int base, int buf_size)
//{
//    int n = abs(value);
//    int i = 0;
//    int num_size = 0;
//    int check = value;
//
//    while (check != 0)
//    {
//        check = check / 10;
//        ++num_size;
//    }
//
//    if (buf_size <= num_size)
//    {
//        return 0;
//    }
//
//    if (base < 2 || base > 32) {
//        return buffer;
//    }
//    while (n)
//    {
//        int r = n % base;
//
//        if (r >= 10) {
//            buffer[i++] = 65 + (r - 10);
//        }
//        else {
//            buffer[i++] = 48 + r;
//        }
//
//        n = n / base;
//    }
//    if (i == 0) {
//        buffer[i++] = '0';
//    }
//    if (value < 0 && base == 10) {
//        buffer[i++] = '-';
//    }
//    buffer[i] = '\0';
//    return reverse(buffer, 0, i - 1);
//}

int string_length(const char* str);

char* string_concat(char* s1, char* s2)
{
    while (*s1 != '\0') {
        s1++;
    }
    while (*s2 != '\0') {
        *s1 = *s2;
        s1++;
        s2++;
    }
    *s1 = '\0';

    return s1;
}

//void itoa_ft(int num, char* str)
//{
//    const int MAX_VALUE = 999999999;
//    int i = 0;
//    int radix = 10;
//    int deg = 1;
//    int cnt = 0;
//
//    if (num >= MAX_VALUE)
//    {
//        num = MAX_VALUE;
//    }
//
//    while (1) {
//        if ((num / deg) > 0) {
//            cnt++;
//        }
//        else {
//            break;
//        }
//        deg *= radix;
//    }
//    deg /= radix;
//
//    for (i = 0; i < cnt; i++) {
//        *(str + i) = num / deg + '0';
//        num -= ((num / deg) * deg);
//        deg /= radix;
//    }
//    *(str + i) = '\0';
//}

char* itoa_ft(int num, char* str, int base, int buf_size)
{
    const int MAX_VALUE = 999999999;
    int i = 0;
    int radix = 10;
    int deg = 1;
    int cnt = 0;
    int num_size = 0;
    int check = num;
    while (check != 0)
    {
        check = check / 10;
        ++num_size;
    }

    if (num >= MAX_VALUE)
    {
        num = MAX_VALUE;
    }

    if (buf_size <= num_size)
    {
        return;
    }

    while (1) {
        if ((num / deg) > 0) {
            cnt++;
        }
        else {
            break;
        }
        deg *= radix;
    }
    deg /= radix;

    for (i = 0; i < cnt; i++) {
        *(str + i) = num / deg + '0';
        num -= ((num / deg) * deg);
        deg /= radix;
    }
    *(str + i) = '\0';
}

int isspace_ft(const char* str)
{
    int i;

    i = 0;
    while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32)) {
        i++;
    }
    return (i);
}

int isdigit_ft(int c)
{
    if (c >= '0' && c <= '9') {
        return (1);
    }
    return (0);
}

int atoi_ft(char* str) {
    int result, positive;

    result = 0;
    positive = 1;
    while ((9 <= *str && *str <= 13) || *str == ' ')
        str++;
    if (*str == '+' || *str == '-') {
        if (*str == '-')
            positive = -1;
        str++;
    }
    while ('0' <= *str && *str <= '9') {
        result *= 10;
        result += (*str - '0') * positive;
        str++;
    }

    if (result < 0)
    {
        result = INT_MAX;
    }

    return result;
}

void buffer_clear(char* buffer)
{
    int i;
    for (i = 0; i < string_length(buffer); i++) {
        buffer[i] = 0;
    }
}

int string_length(const char* str)
{
    int str_length = 0;
    while (*(str + str_length) != '\0') {
        str_length++;
    }
    return str_length;
}

int string_length_before_carriage_return(const char* str)
{
    int str_length = 0;
    while (*(str + str_length) != '\n') {
        if (*(str + str_length) == '\0') {
            break;
        }
        str_length++;
    }
    return str_length;
}

void string_copy(char* dst, const char* source)
{
    int i;
    for (i = 0; i < string_length(source); i++) {
        dst[i] = source[i];
    }
    dst[i + 1] = '\0';
}

int count_token(const char* str, const char delim)
{
    int str_length = 0;
    int delim_count = 0;
    while ((*(str + str_length) != '\n') && (*(str + str_length) != '\0')) {
        if (*(str + str_length) == delim) {
            delim_count++;
        }
        str_length++;
    }
    return delim_count;
}

int string_compare(const char* str1, const char* str2)
{
    int is_same = FALSE;

    if (str2 == NULL) {
        return 0;
    }

    {
        int i;
        for (i = 0; i < string_length(str1); i++) {
            if (*(str1 + i) == *(str2 + i)) {
                is_same = TRUE;
                continue;
            }
            else {
                is_same = FALSE;
                break;
            }
        }
    }
    return is_same;
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

int get_character(const char* filename, character_v3_t* out_character)
{
    /* , 인지 : 인지, | 인지 먼저 검사 */
    /*const int version1_size = 8;*/
    /*const int version2_size = 10;*/
    const int VERSION3_SIZE = 14;

    FILE* fp = NULL;
    char buffer[1024] = { 0, };
    char* words_backup[512] = { 0, };
    char* values_backup[512] = { 0, };



    /*char* version1_out_character_arr[] = { "id", "lvl", "str", "dex", "intel", "def", "hp", "mp" };*/
    /*char* version2_out_character_arr[] = { "level", "strength", "dexterity", "intelligence", "armour", "health", "mana", "name", "evasion", "magic_resistance" };*/
    char* version3_out_character_arr[] = { "name", "level", "health", "mana", "strength", "dexterity", "intelligence", "armour", "evasion", "leadership", "minion_count", "fire_res", "cold_res", "lightning_res" };

    char* minions_out_arr[] = { "name", "health", "strength", "defence" };

    int values_check[20] = { 0, };

    int version_check = 0;
    if ((fp = (fopen(filename, "r"))) == NULL) {
        return 0;
    }

    /* 파일에 있는거 전부 가져오기 */
    {
        int count = 0;
        char c = 0;
        while (1) {
            c = fgetc(fp);
            switch (c) {
            case ':':
                version_check = 1;
                break;
            case ',':
                version_check = 2;
                break;
            case '|':
                version_check = 3;
                break;
            default:
                break;
            }

            if (c == EOF) {
                break;
            }
            buffer[count] = c;
            count++;
        }
    }
    /* end */

    printf("%s\nversion : %d\n", buffer, version_check);

    switch (version_check) {
    case 1:
    {
        int count = 0;
        int word_count = 0;
        int value_count = 0;
        char* ptr = buffer;
        char* temp = NULL;
        char* backup_temp = NULL;
        while (TRUE) {
            if (count % 2 == 0) {
                temp = tokenize(ptr, ":,");
                if (string_compare(temp, backup_temp)) {
                    break;
                }
                if (string_compare(temp, "lvl")) {
                    words_backup[word_count++] = "level";
                    ptr = NULL;
                    count++;
                    continue;
                }
                if (string_compare(temp, "str")) {
                    words_backup[word_count++] = "strength";
                    ptr = NULL;
                    count++;
                    continue;
                }
                if (string_compare(temp, "dex")) {
                    words_backup[word_count++] = "dexterity";
                    ptr = NULL;
                    count++;
                    continue;
                }
                if (string_compare(temp, "intel")) {
                    words_backup[word_count++] = "intelligence";
                    ptr = NULL;
                    count++;
                    continue;
                }
                if (string_compare(temp, "def")) {
                    words_backup[word_count++] = "armour";
                    ptr = NULL;
                    count++;
                    continue;
                }
                if (string_compare(temp, "hp")) {
                    words_backup[word_count++] = "health";
                    ptr = NULL;
                    count++;
                    continue;
                }
                if (string_compare(temp, "mp")) {
                    words_backup[word_count++] = "mana";
                    ptr = NULL;
                    count++;
                    continue;
                }
                if (string_compare(temp, "id")) {
                    words_backup[word_count++] = "name";

                    ptr = NULL;
                    count++;
                    continue;
                }
                words_backup[word_count] = temp;
                backup_temp = temp;
                word_count++;
            }
            else {
                temp = tokenize(ptr, ":,");
                values_backup[value_count] = temp;
                backup_temp = temp;
                value_count++;
            }

            ptr = NULL;
            count++;
        }

        words_backup[word_count++] = "evasion";
        words_backup[word_count] = "magic_resistance";

        {
            int num = 0;
            int i;
            int j;
            char buf[10];
            char buf2[10];
            for (i = 0; i < 10; i++) {
                if (string_compare(words_backup[i], "dexterity")) {
                    num = atoi_ft(values_backup[i]) / 2;
                    itoa_ft(num, buf, 10, sizeof(buf));
                    values_backup[value_count++] = buf;
                    break;
                }
            }
            for (j = 0; j < 11; j++) {
                if (string_compare(words_backup[j], "armour")) {
                    num = atoi_ft(values_backup[j]) / 4;
                    itoa_ft(num, buf2, 10, sizeof(buf2));
                    values_backup[value_count++] = buf2;
                    break;
                }
            }
        }

        goto label2;


    }
    break;
    case 2:
    {
        int word_count = 0;
        int value_count = 0;
        char backup_buffer[1024] = { 0, };
        char* ptr = backup_buffer;
        char* temp = NULL;
        int limit = 0;

        string_copy(backup_buffer, buffer);
        limit = count_token(backup_buffer, ',') + 1;
        {
            int i;
            for (i = 0; i < limit; i++) {
                temp = tokenize(ptr, ",\n");
                if (string_compare(temp, "magic_resistance")) {
                    words_backup[word_count] = "fire_res";
                    word_count++;
                    words_backup[word_count] = "cold_res";
                    word_count++;
                    words_backup[word_count] = "lightning_res";
                    word_count++;
                    continue;
                }
                words_backup[word_count] = temp;
                word_count++;
                ptr = NULL;
            }
        }

    label2:
        if (version_check == 1)
        {
            int i;
            int num;
            char buf1[3];
            word_count = 12;
            value_count = 12;

            for (i = 0; i < 12; i++) {
                if (string_compare(words_backup[i], "magic_resistance")) {
                    words_backup[i] = "fire_res";
                    words_backup[i + 1] = "cold_res";
                    words_backup[i + 2] = "lightning_res";

                    num = atoi_ft(values_backup[i]);
                    itoa_ft(num / 3, buf1, 10, sizeof(buf1));

                    values_backup[i] = buf1;
                    values_backup[i + 1] = buf1;
                    values_backup[i + 2] = buf1;

                    break;
                }
            }
            words_backup[word_count++] = "leadership";
            words_backup[word_count] = "minion_count";

            goto version1_next;
        }

        words_backup[word_count++] = "leadership";
        words_backup[word_count] = "minion_count";



        /* magic_resistance 지우기 , leadership, minion_count, fire_res, cold_res, lightning_res 추가됨 */


        {
            int i;
            int j;
            int count1 = 0;
            for (i = 0; i < 14; i++) {
                for (j = 0; j < VERSION3_SIZE; j++) {
                    if (string_compare(version3_out_character_arr[i], words_backup[j])) {
                        values_check[count1] = j;
                        count1++;
                        break;
                    }
                }
            }
        }


        string_copy(backup_buffer, buffer);
        temp = NULL;
        {
            int i;
            int limit = count_token(backup_buffer, ',') + 1;
            ptr = backup_buffer + string_length_before_carriage_return(buffer) + 1;

            for (i = 0; i < limit; i++) {
                temp = tokenize(ptr, ",\n");
                if (i == 7) {
                    values_backup[value_count] = temp;
                    value_count++;
                    values_backup[value_count] = temp;
                    value_count++;
                    values_backup[value_count] = temp;
                    value_count++;
                    continue;
                }
                values_backup[value_count] = temp;
                value_count++;
                ptr = NULL;
            }
        }

        if (version_check == 1) {
        version1_next:
            {
                int num = 0;
                int i;
                char buf[10];
                for (i = 0; i < 14; i++) {
                    if (string_compare(words_backup[i], "level")) {
                        num = atoi_ft(values_backup[i]);
                        itoa_ft(num / 10, buf, 10, sizeof(buf));
                        values_backup[value_count++] = buf;
                        values_backup[value_count] = "0";
                        break;
                    }
                }
            }


            /* 순서 세팅 작업 */
            {
                int i;
                int j;
                int count1 = 0;
                for (i = 0; i < 14; i++) {
                    for (j = 0; j < VERSION3_SIZE; j++) {
                        if (string_compare(version3_out_character_arr[i], words_backup[j])) {
                            values_check[count1] = j;
                            count1++;
                            break;
                        }
                    }
                }
            }

            goto deserializer;
        }


        {
            int i;
            int num;
            char buf1[3];
            for (i = 0; i < 14; i++) {
                if (string_compare(version3_out_character_arr[i], "level")) {
                    num = atoi_ft(values_backup[i]);
                    itoa_ft(num / 10, buf1, 10, sizeof(buf1));
                    values_backup[value_count++] = buf1;
                    break;
                }
            }
        }
        values_backup[value_count++] = "0";


        goto deserializer;

    }
    break;
    case 3:
    {
        int word_count = 0;
        int value_count = 0;


        char backup_buffer[1024] = { 0, };
        char* ptr = backup_buffer;
        char* temp = NULL;


        int total_count = 0;

        int limit = 0;

        /* 1열  토큰화 */
        string_copy(backup_buffer, buffer);

        limit = count_token(backup_buffer, '|') + 1;
        {
            int i;
            for (i = 0; i < limit; i++) {
                temp = tokenize(ptr, "|  \n");
                words_backup[word_count] = temp;
                word_count++;
                ptr = NULL;
            }
        }

        /* 순서 세팅 작업 */
        {
            int i;
            int j;
            int count1 = 0;
            for (i = 0; i < limit; i++) {
                for (j = 0; j < VERSION3_SIZE; j++) {
                    if (string_compare(version3_out_character_arr[i], words_backup[j])) {
                        values_check[count1] = j;
                        count1++;
                        break;
                    }
                }
            }
        }

        total_count = string_length_before_carriage_return(buffer) + 1;

        /* 2열 (데이터) 토큰화 */

        string_copy(backup_buffer, buffer + total_count);
        temp = NULL;
        {
            int i;
            int limit = count_token(backup_buffer, '|') + 1;
            ptr = backup_buffer;

            total_count += string_length_before_carriage_return(buffer + total_count + 1) + 1;


            for (i = 0; i < limit; i++) {
                temp = tokenize(ptr, "|  \n");
                values_backup[value_count] = temp;
                value_count++;
                ptr = NULL;
            }
        }





        {
            int i;

        deserializer:

            for (i = 0; i < VERSION3_SIZE; i++) {
                switch (i)
                {
                case 0:
                    if (version_check == 1) {
                        char buf[50] = { 0, };
                        strncpy(buf, "player_", 49);
                        strcat(buf, values_backup[values_check[i]]);


                        strncpy(out_character->name, buf, 49);
                    }
                    else {
                        char buf[50] = { 0, };
                        strncpy(buf, values_backup[values_check[i]], 49);

                        {
                            int i;
                            int j;
                            int k;
                            int l;
                            int check = 0;
                            for (i = 0; i < strlen(buf); i++)
                            {
                                for (j = 'A'; j < 'Z' + 1; j++)
                                {
                                    if (j == buf[i] || '_' == buf[i])
                                    {
                                        check = 1;
                                        goto end;
                                    }
                                    else {
                                        check = 0;
                                    }
                                }

                                for (k = 'a'; k < 'z' + 1; k++)
                                {
                                    if (k == buf[i] || '_' == buf[i])
                                    {
                                        check = 1;
                                        goto end;
                                    }
                                    else {
                                        check = 0;
                                    }
                                }

                                for (l = '1'; l < '9' + 1; l++)
                                {
                                    if (l == buf[i] || '_' == buf[i])
                                    {
                                        check = 1;
                                        goto end;
                                    }
                                    else {
                                        check = 0;
                                    }
                                }

							end:
                                if (check == 0)
                                {
                                    return version_check;
                                }
                            }
                        }
						strncpy(out_character->name, values_backup[values_check[i]], 49);
                        int r = 4;
                    }
                    break;
                case 1:
                    out_character->level = atoi_ft(values_backup[values_check[i]]);
                    break;
                case 2:
                    out_character->health = atoi_ft(values_backup[values_check[i]]);
                    break;
                case 3:
                    out_character->mana = atoi_ft(values_backup[values_check[i]]);
                    break;
                case 4:
                    out_character->strength = atoi_ft(values_backup[values_check[i]]);
                    break;
                case 5:
                    out_character->dexterity = atoi_ft(values_backup[values_check[i]]);
                    break;
                case 6:
                    out_character->intelligence = atoi_ft(values_backup[values_check[i]]);
                    break;
                case 7:
                    out_character->armour = atoi_ft(values_backup[values_check[i]]);
                    break;
                case 8:
                    out_character->evasion = atoi_ft(values_backup[values_check[i]]);
                    break;
                case 9:
                    if (version_check == 4) {
                        out_character->leadership = atoi_ft(values_backup[values_check[i]]) / 10;
                    }
                    else {
                        out_character->leadership = atoi_ft(values_backup[values_check[i]]);
                    }
                    break;
                case 10:
                    out_character->minion_count = atoi_ft(values_backup[values_check[i]]);
                    break;
                case 11:
                    if (version_check == 2) {
                        out_character->elemental_resistance.fire = atoi_ft(values_backup[values_check[i]]) / 3;
                    }
                    else {
                        out_character->elemental_resistance.fire = atoi_ft(values_backup[values_check[i]]);

                    }
                    break;
                case 12:
                    if (version_check == 2) {
                        out_character->elemental_resistance.cold = atoi_ft(values_backup[values_check[i]]) / 3;
                    }
                    else {
                        out_character->elemental_resistance.cold = atoi_ft(values_backup[values_check[i]]);

                    }
                    break;
                case 13:
                    if (version_check == 2) {
                        out_character->elemental_resistance.lightning = atoi_ft(values_backup[values_check[i]]) / 3;
                    }
                    else {
                        out_character->elemental_resistance.lightning = atoi_ft(values_backup[values_check[i]]);

                    }
                    break;
                default:
                    break;
                }
            }
        }

        temp = NULL;


        if (out_character->minion_count) {
            int count = out_character->minion_count;
            int values_check1[4] = { 0, };
            word_count = 0;
            value_count = 0;

            string_copy(backup_buffer, buffer + total_count + 1);
            total_count += string_length_before_carriage_return(buffer + total_count + 1) + 1;
            /*char* b = backup_buffer + total_count + 1;*/
            if (*(backup_buffer + total_count + 1) != '\0') {
                {
                    int i;
                    int limit = count_token(backup_buffer, '|') + 1;
                    ptr = backup_buffer;

                    /*total_count += string_length_before_carriage_return(backup_buffer + total_count + 1) + 1;*/

                    /*backup_ptr = ptr;*/
                    /*buffer_clear(words_backup);*/
                    for (i = 0; i < limit; i++) {
                        temp = tokenize(ptr, "|  \n");
                        words_backup[word_count] = temp;
                        word_count++;
                        ptr = NULL;
                    }
                }

                temp = NULL;
                /*b = backup_buffer + total_count;*/


                        /* 순서 세팅 작업 */
                {
                    int i;
                    int j;
                    int count1 = 0;

                    for (i = 0; i < 4; i++) {
                        for (j = 0; j < 4; j++) {
                            if (string_compare(minions_out_arr[i], words_backup[j])) {
                                values_check1[count1] = j;
                                count1++;
                                break;
                            }
                        }
                    }
                }



                /* 4열 */

                {
                    int i = 0;
                    int k;

                    string_copy(backup_buffer, buffer + total_count + 1);
                    /*b = backup_buffer + total_count;*/
                    while (*backup_buffer != '\0') {

                        {
                            int j;
                            int limit = count_token(backup_buffer, '|') + 1;
                            ptr = backup_buffer;

                            total_count += string_length_before_carriage_return(backup_buffer + total_count + 1) + 1;

                            /*backup_ptr = ptr;*/
                            for (j = 0; j < limit; j++) {
                                temp = tokenize(ptr, "|  \n");
                                if (temp == 0) {
                                    break;
                                }
                                values_backup[value_count] = temp;
                                value_count++;
                                ptr = NULL;
                            }
                        }












                        for (k = 0; k < 4; k++) {
                            switch (k) {
                            case 0:
                                //string_copy(out_character->minions[i].name, values_backup[values_check1[k]]);
                                strcpy(out_character->minions[i].name, values_backup[values_check[k]]);
                                break;
                            case 1:
                                out_character->minions[i].health = atoi_ft(values_backup[values_check1[k]]);
                                break;
                            case 2:
                                out_character->minions[i].strength = atoi_ft(values_backup[values_check1[k]]);
                                break;
                            case 3:
                                out_character->minions[i].defence = atoi_ft(values_backup[values_check1[k]]);
                                break;

                            default:
                                break;
                            }
                        }













                        buffer_clear(backup_buffer);
                        string_copy(backup_buffer, buffer + total_count + 1);

                        if (i >= count) {
                            return version_check;
                        }
                        else {
                            i++;
                        }
                    }

                }
            }

        }




    }
    break;
    default:
        break;
    }


    if (fclose(fp) == EOF) {
        return 0;
    }

    return version_check;
}
