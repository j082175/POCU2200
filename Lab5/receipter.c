#include "receipter.h"

static s_recipt_count = 0;
static s_add_item_count = 0;


static char s_item_arr[ITEM_LENGTH][1024] = { 0, };
static double s_price_arr[ITEM_LENGTH] = { 0, };

static int s_is_tip_exist = 0;
static int s_is_message_exist = 0;

static double s_subtotal = 0;
static double s_tip_count = 0;
static double s_tax_count = 0;

static char s_message[77] = { 0, };

double round_by_two(double num)
{
    double backup_num = 0;
    int real = num / 1;
    double mantissa = num - real;
    double two = mantissa * 100;
    int two_real = two / 1;
    double two_mantissa = two - two_real;
    if (two_mantissa >= 0.4999999) {
        two_real++;
        backup_num = real + (double)(two_real / 100.0);
    } else {
        backup_num = real + (double)(two_real / 100.0);
    }
    return backup_num;
}

int string_length(const char* name)
{
    int length = 0;

    while (*(name + length) != '\0') {
        length++;
    }

    return length;
}

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

void buffer_reset(char* buffer)
{
    int i;
    for (i = 0; i < MAX_LENGTH; i++) {
        buffer[i] = 0;
    }
}

int add_item(const char* name, double price)
{

    if (s_add_item_count >= ITEM_LENGTH) {
        return FALSE;
    }

    {
        if (string_length(name) < 25) {
            int i;
            for (i = 0; i < string_length(name); i++) {
                s_item_arr[s_add_item_count][i] = *(name + i);
            }
            s_item_arr[s_add_item_count][string_length(name)] = '\0';

        } else {
            int i;
            for (i = 0; i < 25; i++) {
                s_item_arr[s_add_item_count][i] = *(name + i);
            }
            s_item_arr[s_add_item_count][25] = '\0';
        }
    }


    s_price_arr[s_add_item_count] = price;

    printf("%s", s_item_arr[s_add_item_count]);
    printf("%lf\n", s_price_arr[s_add_item_count]);

    s_add_item_count++;


    return TRUE;
}

void set_tip(double tip)
{
    if (tip > 999.99) {
        tip = 999.99;
    }
    s_is_tip_exist = 1;
    s_tip_count = round_by_two(tip);
}

void set_message(const char* message)
{
    char buffer[76] = { 0, };
    {
        if (string_length(message) > MAX_LENGTH) {
            if (string_length(message) > 75) {
                int i;
                int j;
                for (i = 0; i < MAX_LENGTH; i++) {
                    buffer[i] = *(message + i);
                }
                buffer[MAX_LENGTH] = '\n';

                for (j = 0; j < 25; j++) {
                    buffer[j + MAX_LENGTH + 1] = message[MAX_LENGTH + j];
                }
            } else {
                int i;
                int j;
                for (i = 0; i < MAX_LENGTH; i++) {
                    buffer[i] = *(message + i);
                }
                buffer[MAX_LENGTH] = '\n';

                for (j = 0; j < string_length(message) - MAX_LENGTH; j++) {
                    buffer[j + MAX_LENGTH + 1] = message[MAX_LENGTH + j];
                }
            }
        } else {
            int i;
            for (i = 0; i < string_length(message); i++) {
                buffer[i] = *(message + i);
            }
        }
    }
    s_is_message_exist = 1;

    {
        int i;
        for (i = 0; i < 76; i++) {
            s_message[i] = buffer[i];
        }
        s_message[76] = '\0';
    }
}

int print_receipt(const char* filename, time_t timestamp)
{
    FILE* f1 = 0;
    struct tm tm = *gmtime(&timestamp);
    char buffer[1024] = { 0, };
    char buffer2[1024] = { 0, };
    char buffer_space[1024] = { 0, };
    char buffer_space2[1024] = { 0, };
    char* buffer_ptr = 0;
    int check = 0;

    if (s_add_item_count == 0) {
        return FALSE;
    }

    if ((f1 = fopen(filename, "w")) == 0) {
        return FALSE;
    }

    fprintf(f1, "%s\n", "Charles' Seafood");

    {
        int i;
        for (i = 0; i < MAX_LENGTH; i++) {
            buffer[i] = '-';
        }
    }

    fprintf(f1, "%s\n", buffer);
    buffer_reset(buffer);


    sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    {
        int i;
        for (i = 19; i < 45; i++) {
            buffer[i] = ' ';
        }
    }

    {
        sprintf(buffer2, "%05d\n", s_recipt_count);
        printf("%s", buffer2);
    }

    printf("%s\n", buffer);
    string_concat(buffer, buffer2);
    fprintf(f1, "%s", buffer);
    {
        int i;
        for (i = 0; i < MAX_LENGTH; i++) {
            buffer[i] = '-';
        }
    }

    fprintf(f1, "%s", buffer);
    buffer_reset(buffer);
    buffer_reset(buffer2);
    /* 기본 동작 끝 */

    /* add start*/
    {
        int i;
        if (s_add_item_count != 0) {
            check = 1;
            for (i = 0; i < s_add_item_count; i++) {
                snprintf(buffer, 26, "%.25s", s_item_arr[i]);
                sprintf(buffer2, "%.2lf", round_by_two(s_price_arr[i]));

                {
                    int j;
                    int k;
                    for (j = 0; j < MAX_NAME_LENGTH - string_length(buffer); j++) {
                        buffer_space[j] = ' ';
                    }

                    for (k = 0; k < MAX_PRICE_LENGTH - string_length(buffer2); k++) {
                        buffer_space2[k] = ' ';
                    }
                }
                string_concat(buffer_space, buffer);
                string_concat(buffer_space2, buffer2);
                string_concat(buffer_space, buffer_space2);

                fprintf(f1, "%s\n", buffer_space);

                buffer_reset(buffer_space);
                buffer_reset(buffer_space2);
                buffer_reset(buffer);
                buffer_reset(buffer2);
            }
        }
    }
    /* add end*/


    fputc('\n', f1);

    /* subtotal start */
    {
        int j;
        int k;
        int i;

        for (i = 0; i < s_add_item_count; i++) {
            s_subtotal += round_by_two(s_price_arr[i]);
        }

        sprintf(buffer2, "%.2lf", s_subtotal);

        for (j = 0; j < MAX_NAME_LENGTH - string_length("Subtotal"); j++) {
            buffer_space[j] = ' ';
        }


        for (k = 0; k < MAX_PRICE_LENGTH - string_length(buffer2); k++) {
            buffer_space2[k] = ' ';
        }

        string_concat(buffer_space, "Subtotal");
        string_concat(buffer_space2, buffer2);
        string_concat(buffer_space, buffer_space2);

        fprintf(f1, "%s\n", buffer_space);

        buffer_reset(buffer_space);
        buffer_reset(buffer_space2);
        buffer_reset(buffer);
        buffer_reset(buffer2);
    }
    /* subtotal end */


    /* set tip start */
    if (s_is_tip_exist) {
        int j;
        int k;
        if (!(s_tip_count == 0.00)) {
            sprintf(buffer, "%.2lf", s_tip_count);

            for (j = 0; j < MAX_NAME_LENGTH - string_length("Tip"); j++) {
                buffer_space[j] = ' ';
            }

            for (k = 0; k < MAX_PRICE_LENGTH - string_length(buffer); k++) {
                buffer_space2[k] = ' ';
            }

            string_concat(buffer_space, "Tip");
            string_concat(buffer_space2, buffer);
            string_concat(buffer_space, buffer_space2);

            fprintf(f1, "%s\n", buffer_space);

            buffer_reset(buffer_space);
            buffer_reset(buffer_space2);
            buffer_reset(buffer);
            buffer_reset(buffer2);
        }
    }
    /* set tip end */

    /* Tax start */
    {
        int j;
        int k;
        s_tax_count = round_by_two(s_subtotal * 0.05);
        sprintf(buffer, "%.2lf", s_tax_count);

        for (j = 0; j < MAX_NAME_LENGTH - string_length("Tax"); j++) {
            buffer_space[j] = ' ';
        }

        for (k = 0; k < MAX_PRICE_LENGTH - string_length(buffer); k++) {
            buffer_space2[k] = ' ';
        }

        string_concat(buffer_space, "Tax");
        string_concat(buffer_space2, buffer);
        string_concat(buffer_space, buffer_space2);

        fprintf(f1, "%s\n", buffer_space);

        buffer_reset(buffer_space);
        buffer_reset(buffer_space2);
        buffer_reset(buffer);
        buffer_reset(buffer2);
    }
    /* Tax End */

    /* Total Start */
    {
        int j;
        int k;
        double total_count = round_by_two(s_subtotal + s_tip_count + s_tax_count);

        sprintf(buffer, "%.2lf", total_count);

        for (j = 0; j < MAX_NAME_LENGTH - string_length("Total"); j++) {
            buffer_space[j] = ' ';
        }

        for (k = 0; k < MAX_PRICE_LENGTH - string_length(buffer); k++) {
            buffer_space2[k] = ' ';
        }

        string_concat(buffer_space, "Total");
        string_concat(buffer_space2, buffer);
        string_concat(buffer_space, buffer_space2);

        fprintf(f1, "%s\n", buffer_space);

        buffer_reset(buffer_space);
        buffer_reset(buffer_space2);
        buffer_reset(buffer);
        buffer_reset(buffer2);
    }
    /* Total End */

    fputc('\n', f1);

    /* message start */
    if (s_is_message_exist) {
        fprintf(f1, "%s\n", s_message);
    }
    /* message end */

    {
        int i;
        for (i = 0; i < MAX_LENGTH; i++) {
            fputc('=', f1);
        }
    }
    fputc('\n', f1);

    /* Tax# start */
    {
        int i;
        for (i = 0; i < MAX_LENGTH - 10; i++) {
            buffer[i] = ' ';
        }

        buffer_ptr = "Tax#-51234";

        string_concat(buffer, buffer_ptr);

        fprintf(f1, "%s", buffer);
    }
    /* Tax# end */

    if (fclose(f1) == EOF) {
        return FALSE;
    }

    if (!check) {
        return FALSE;
    }
    s_add_item_count = 0;
    s_recipt_count++;
    s_subtotal = 0;
    s_tip_count = 0;
    s_tax_count = 0;

    {
        int i;
        for (i = 0; i < 77; i++) {
            s_message[i] = 0;
        }
    }
    return TRUE;
}
