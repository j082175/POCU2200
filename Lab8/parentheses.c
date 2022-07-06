#include "parentheses.h"
#define MAX_LENGTH 8


/* { } */
/* ( ) */
/* [ ] */
/* < > */
const char g_ch_outter[] = { '}', ')', ']', '>' };
const char g_ch_inner[] = { '{',  '(',  '[',  '<' };

void delete_at(char* nums, size_t index, size_t max_count)
{
    size_t i;
    for (i = index; i < max_count; i++)
    {
        nums[i] = nums[i + 1];
    }
    --max_count;
}


size_t find_matching_parentheses(ringbuffer_t* ringbuffer, const char* str)
{
    const size_t MAX_SIZE = ringbuffer->max_size;
    const size_t STR_LENGTH = strlen(str);
    size_t count = 0;



    size_t total_length = 0;
    char str_buf[32] = { 0, };






    strcpy(str_buf, str);
    ringbuffer->start_index = 0;

    while (count < STR_LENGTH)
    {
        {
            size_t i;
            int j;
            int k;
            for (i = 0; i < STR_LENGTH; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    if (str_buf[i] == g_ch_outter[j])
                    {

                        for (k = i - 1; k >= 0; k--)
                        {
                            if (str_buf[k] == g_ch_inner[j])
                            {
                                str_buf[k] = '?';
                                str_buf[i] = '?';
                                ringbuffer->parentheses[count % MAX_SIZE].opening_index = k;
                                ringbuffer->parentheses[count % MAX_SIZE].closing_index = i;
                                if (count / MAX_SIZE)
                                {
                                    ringbuffer->start_index++;
                                }

                                total_length++;
                                goto end;
                            }
                        }
                    }
                }
            }
        }




    end:


        count++;
    }



    return total_length;
}
