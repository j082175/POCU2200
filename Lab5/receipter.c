#include "receipter.h"

static g_add_item_count = 0;

static char* g_item_arr[ITEM_LENGTH] = { 0, };
static double g_price_arr[ITEM_LENGTH] = { 0, };

static int g_is_tip_exist = 0;
static int g_is_message_exist = 0;

static double g_subtotal = 0;
static double g_tip_count = 0;
static double g_tax_count = 0;

static char* g_message = 0;

int string_length(const char* name) {
    int length = 0;

    while (*(name + length) != '\0')
    {
        length++;
    }

    return length;
}

char* string_concat(char* s1, char* s2) {
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

void buffer_reset(char* buffer) {
    int i;
    for (i = 0; i < MAX_LENGTH; i++)
    {
        buffer[i] = 0;
    }
}

int add_item(const char* name, double price) {
    char buffer[100] = { 0, };

    if (g_add_item_count >= ITEM_LENGTH)
    {
        return FALSE;
    }

    if (string_length(name) > 25)
    {

    }

    //{
    //	int i;
    //	for (i = 0; i < string_length(name); i++)
    //	{
    //		buffer[i] = *(name + i);
    //	}
    //	buffer[string_length(name)] = '\0';
    //}

    g_item_arr[g_add_item_count] = name;

    printf("%s\n", g_item_arr[g_add_item_count]);
    g_price_arr[g_add_item_count] = price;

    g_add_item_count++;

    return TRUE;
}

void set_tip(double tip) {
    g_is_tip_exist = 1;
    g_tip_count = tip;
}

void set_message(const char* message) {
    g_is_message_exist = 1;
    g_message = message;
}

int print_receipt(const char* filename, time_t timestamp) {
    FILE* f1 = 0;
    struct tm tm = *localtime(&timestamp);
    char buffer[1024] = { 0, };
    char buffer2[1024] = { 0, };
    char buffer_space[1024] = { 0, };
    char buffer_space2[1024] = { 0, };
    char* buffer_ptr = 0;

    if (g_add_item_count == 0)
    {
        return FALSE;
    }

    if ((f1 = fopen(filename, "w")) == 0)
    {
        return FALSE;
    }

    fprintf(f1, "%s\n", "Charles' Seafood");

    {
        int i;
        for (i = 0; i < MAX_LENGTH; i++)
        {
            buffer[i] = '-';
        }
    }

    fprintf(f1, "%s\n", buffer);
    buffer_reset(buffer);


    sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
        tm.tm_hour, tm.tm_min, tm.tm_sec);

    {
        int i;
        for (i = 19; i < 45; i++)
        {
            buffer[i] = ' ';
        }
    }

    {
        int i;
        sprintf(buffer2, "%05d\n", g_add_item_count);
        printf("%s", buffer2);
    }

    printf("%s\n", buffer);
    string_concat(buffer, buffer2);
    fprintf(f1, "%s", buffer);
    //fprintf(f1, "%d\n", add_item_count);
    {
        int i;
        for (i = 0; i < MAX_LENGTH; i++)
        {
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
        int j;
        for (i = 0; i < g_add_item_count; i++)
        {
            sprintf(buffer, "%s", g_item_arr[i]);
            sprintf(buffer2, "%.2lf", g_price_arr[i]);

            {
                int j;
                int k;
                for (j = 0; j < MAX_NAME_LENGTH - string_length(buffer); j++)
                {
                    buffer_space[j] = ' ';
                }

                for (k = 0; k < MAX_PRICE_LENGTH - string_length(buffer2); k++)
                {
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
    /* add end*/


    fputc('\n', f1);

    /* subtotal start */
    {
        int j;
        int k;
        int i;

        for (i = 0; i < g_add_item_count; i++)
        {
            g_subtotal += g_price_arr[i];
        }

        sprintf(buffer2, "%.2lf", g_subtotal);

        for (j = 0; j < MAX_NAME_LENGTH - string_length("Subtotal"); j++)
        {
            buffer_space[j] = ' ';
        }


        for (k = 0; k < MAX_PRICE_LENGTH - string_length(buffer2); k++)
        {
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
    if (g_is_tip_exist)
    {
        int j;
        int k;
        sprintf(buffer, "%.2lf", g_tip_count);

        for (j = 0; j < MAX_NAME_LENGTH - string_length("Tip"); j++)
        {
            buffer_space[j] = ' ';
        }

        for (k = 0; k < MAX_PRICE_LENGTH - string_length(buffer); k++)
        {
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
    /* set tip end */

    /* Tax start */
    {
        int j;
        int k;
        g_tax_count = g_subtotal * 0.05;
        sprintf(buffer, "%.2lf", g_tax_count);

        for (j = 0; j < MAX_NAME_LENGTH - string_length("Tax"); j++)
        {
            buffer_space[j] = ' ';
        }

        for (k = 0; k < MAX_PRICE_LENGTH - string_length(buffer); k++)
        {
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
        double total_count = g_subtotal + g_tip_count + g_tax_count;

        sprintf(buffer, "%.2lf", total_count);

        for (j = 0; j < MAX_NAME_LENGTH - string_length("Total"); j++)
        {
            buffer_space[j] = ' ';
        }

        for (k = 0; k < MAX_PRICE_LENGTH - string_length(buffer); k++)
        {
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
    if (g_is_message_exist)
    {
        fprintf(f1, "%s\n", g_message);
    }
    /* message end */

    {
        int i;
        for (i = 0; i < MAX_LENGTH; i++)
        {
            fputc('=', f1);
        }
    }
    fputc('\n', f1);

    /* Tax# start */
    {
        int i;
        for (i = 0; i < MAX_LENGTH - 10; i++)
        {
            buffer[i] = ' ';
        }

        buffer_ptr = "Tax#-51234";

        string_concat(buffer, buffer_ptr);

        fprintf(f1, "%s", buffer);
    }
    /* Tax# end */

    if (fclose(f1) == EOF)
    {
        return FALSE;
    }

    return TRUE;
}
