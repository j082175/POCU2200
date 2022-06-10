#include "character_deserializer.h"
/* 이 실습에서 계산을 할 때 소수점 이하는 무시하세요. 즉, 모든 결과는 무조건 내림을 합니다.
이 실습에서 전역(global) 변수와 정적(static) 변수의 사용을 금합니다. 전역/정적 변수 없이도 이 실습을 끝낼 수 있으니 저를 믿으세요. :)*/

void itoa_ft(int num, char* str, int base, int buf_size)
{
    const int MAX_VALUE = 999999999;
    int i = 0;
    int radix = 10;
    int deg = 1;
    int cnt = 0;
    int num_size = 0;
    int check = num;
    while (check != 0) {
        check = check / 10;
        ++num_size;
    }

    if (num >= MAX_VALUE) {
        num = MAX_VALUE;
    }

    if (buf_size <= num_size) {
        return;
    }

    while (1) {
        if ((num / deg) > 0) {
            cnt++;
        } else {
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

int atoi_ft(char* str)
{
    int result = 0;
    int positive = 1;

    while ((9 <= *str && *str <= 13) || *str == ' ') {
        str++;
    }
    if (*str == '+' || *str == '-') {
        if (*str == '-') {
            positive = -1;
        }
        str++;
    }
    while ('0' <= *str && *str <= '9') {
        if (result > INT_MAX || result < 0) {
            result = INT_MAX;
            return result;
        }
        result *= 10;
        result += (*str - '0') * positive;
        str++;
    }

    if (result < 0) {
        result = INT_MAX;
    }

    return result;
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

    int values_check[128] = { 0, };

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
                buffer[count] = '\0';
                break;
            }
            buffer[count] = c;
            count++;
        }
    }
    /* end */

    printf("%s\nversion : %d\n", buffer, version_check);

    switch (version_check) {
    case 1: {
            int check = 0;
            int count = 0;
            int word_count = 0;
            int value_count = 0;
            char* ptr = buffer;
            char* temp = NULL;
            char* backup_temp = NULL;
            while (TRUE) {
                if (count % 2 == 0) {
                    temp = strtok(ptr, ":,");
                    if (check == 1) {
                        if (temp == NULL || !strcmp(temp, backup_temp)) {
                            break;
                        }
                    } else {
                        check++;
                    }

                    if (!strcmp(temp, "lvl")) {
                        words_backup[word_count++] = "level";
                        ptr = NULL;
                        count++;
                        continue;
                    }
                    if (!strcmp(temp, "str")) {
                        words_backup[word_count++] = "strength";
                        ptr = NULL;
                        count++;
                        continue;
                    }
                    if (!strcmp(temp, "dex")) {
                        words_backup[word_count++] = "dexterity";
                        ptr = NULL;
                        count++;
                        continue;
                    }
                    if (!strcmp(temp, "intel")) {
                        words_backup[word_count++] = "intelligence";
                        ptr = NULL;
                        count++;
                        continue;
                    }
                    if (!strcmp(temp, "def")) {
                        words_backup[word_count++] = "armour";
                        ptr = NULL;
                        count++;
                        continue;
                    }
                    if (!strcmp(temp, "hp")) {
                        words_backup[word_count++] = "health";
                        ptr = NULL;
                        count++;
                        continue;
                    }
                    if (!strcmp(temp, "mp")) {
                        words_backup[word_count++] = "mana";
                        ptr = NULL;
                        count++;
                        continue;
                    }
                    if (!strcmp(temp, "id")) {
                        words_backup[word_count++] = "name";

                        ptr = NULL;
                        count++;
                        continue;
                    }
                    words_backup[word_count] = temp;
                    backup_temp = temp;
                    word_count++;
                } else {
                    temp = strtok(ptr, ":,");
                    if (strlen(temp) > 10) {
                        *(temp + 10) = '\0';
                    }
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
                char buf[16] = { 0, };
                char buf2[16] = { 0, };
                for (i = 0; i < 10; i++) {
                    if (!strcmp(words_backup[i], "dexterity")) {
                        num = atoi_ft(values_backup[i]) / 2;
                        itoa_ft(num, buf, 10, sizeof(buf));
                        values_backup[value_count++] = buf;
                        break;
                    }
                }

                for (j = 0; j < 11; j++) {
                    if (!strcmp(words_backup[j], "armour")) {
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
    case 2: {
        int word_count = 0;
        int value_count = 0;
        char backup_buffer[1024] = { 0, };
        char* ptr = backup_buffer;
        char* temp = NULL;
        int limit = 0;

        strcpy(backup_buffer, buffer);
        limit = count_token(backup_buffer, ',') + 1;
        {
            int i;
            for (i = 0; i < limit; i++) {
                temp = strtok(ptr, ",\n");
                if (!strcmp(temp, "magic_resistance")) {
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
        if (version_check == 1) {
            int i;
            int num;
            char buf1[16] = { 0, };
            word_count = 12;
            value_count = 12;

            for (i = 0; i < 12; i++) {
                if (!strcmp(words_backup[i], "magic_resistance")) {
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
                    if (!strcmp(version3_out_character_arr[i], words_backup[j])) {
                        values_check[count1] = j;
                        count1++;
                        break;
                    }
                }
            }
        }


        strcpy(backup_buffer, buffer);
        temp = NULL;
        {
            int i;
            int limit = count_token(backup_buffer, ',') + 1;
            ptr = backup_buffer + string_length_before_carriage_return(buffer) + 1;

            for (i = 0; i < limit; i++) {
                temp = strtok(ptr, ",\n");
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

        version1_next:{
            int num = 0;
            int i;
            char buf[16] = {
                0,
            };
            for (i = 0; i < 14; i++) {
                if (!strcmp(words_backup[i], "level")) {
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
                        if (!strcmp(version3_out_character_arr[i], words_backup[j])) {
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
            char buf1[16] = { 0, };
            for (i = 0; i < 14; i++) {
                if (!strcmp(version3_out_character_arr[i], "level")) {
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
    case 3: {
        int word_count = 0;
        int value_count = 0;


        char backup_buffer[1024] = { 0, };
        char* ptr = backup_buffer;
        char* temp = NULL;


        int total_count = 0;

        int limit = 0;

        /* 1열  토큰화 */
        strcpy(backup_buffer, buffer);

        limit = count_token(backup_buffer, '|') + 1;
        {
            int i;
            for (i = 0; i < limit; i++) {
                temp = strtok(ptr, "|  \n");
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
                    if (!strcmp(version3_out_character_arr[i], words_backup[j])) {
                        values_check[count1] = j;
                        count1++;
                        break;
                    }
                }
            }
        }

        total_count = string_length_before_carriage_return(buffer) + 1;

        /* 2열 (데이터) 토큰화 */

        strcpy(backup_buffer, buffer + total_count);
        temp = NULL;
        {
            int i;
            int limit = count_token(backup_buffer, '|') + 1;
            ptr = backup_buffer;

            total_count += string_length_before_carriage_return(buffer + total_count + 1) + 1;


            for (i = 0; i < limit; i++) {
                temp = strtok(ptr, "|  \n");

                values_backup[value_count] = temp;
                value_count++;
                ptr = NULL;
            }
        }





        {
            int i;

        deserializer:

            for (i = 0; i < VERSION3_SIZE; i++) {
                switch (i) {
                case 0:
                    if (version_check == 1) {
                        char buf[128] = { 0, };
                        strncpy(buf, "player_", 50);
                        strncat(buf, values_backup[values_check[i]], 50 - strlen("player_"));
                        /*check_name(buf);*/

                        strncpy(out_character->name, buf, 50);
                    } else {
                        char buf[128] = { 0, };
                        strncpy(buf, values_backup[values_check[i]], 50);
                        /*check_name(buf);*/
                        strncpy(out_character->name, buf, 50);
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
                    } else {
                        out_character->leadership = atoi_ft(values_backup[values_check[i]]);
                    }
                    break;
                case 10:
                    out_character->minion_count = atoi_ft(values_backup[values_check[i]]);
                    break;
                case 11:
                    if (version_check == 2) {
                        out_character->elemental_resistance.fire = atoi_ft(values_backup[values_check[i]]) / 3;
                    } else {
                        out_character->elemental_resistance.fire = atoi_ft(values_backup[values_check[i]]);

                    }
                    break;
                case 12:
                    if (version_check == 2) {
                        out_character->elemental_resistance.cold = atoi_ft(values_backup[values_check[i]]) / 3;
                    } else {
                        out_character->elemental_resistance.cold = atoi_ft(values_backup[values_check[i]]);

                    }
                    break;
                case 13:
                    if (version_check == 2) {
                        out_character->elemental_resistance.lightning = atoi_ft(values_backup[values_check[i]]) / 3;
                    } else {
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
            int values_check1[128] = { 0, };
            word_count = 0;
            value_count = 0;

            strcpy(backup_buffer, buffer + total_count + 1);
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
                        temp = strtok(ptr, "|  \n");
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
                            if (!strcmp(minions_out_arr[i], words_backup[j])) {
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

                    strcpy(backup_buffer, buffer + total_count + 1);
                    /*b = backup_buffer + total_count;*/
                    while (*backup_buffer != '\0') {
                        {
                            int j;
                            int limit = count_token(backup_buffer, '|') + 1;
                            ptr = backup_buffer;

                            total_count += string_length_before_carriage_return(backup_buffer + total_count + 1) + 1;

                            /*backup_ptr = ptr;*/
                            for (j = 0; j < limit; j++) {
                                temp = strtok(ptr, "|  \n");
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
                            case 0: {
                                char buf[128] = {
                                    0,
                                };
                                strncpy(buf, values_backup[values_check[k]], 50);
                                // check_name(buf);
                                strncpy(out_character->minions[i].name, buf, 50);
                                }
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














                        strcpy(backup_buffer, buffer + total_count + 1);

                        if (i >= count) {
                            return version_check;
                        } else {
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
