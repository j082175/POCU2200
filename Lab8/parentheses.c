#include "parentheses.h"

/* { } */
/* ( ) */
/* [ ] */
/* < > */
size_t find_matching_parentheses(ringbuffer_t* ringbuffer, const char* str)
{
    const char outter[] = { '}',')',']','>' };
    const char inner[] = { '{','(','[','<' };

    const size_t MAX_SIZE = ringbuffer->max_size;
    const size_t STR_LENGTH = strlen(str);
    size_t count = 0;
    size_t total_length = 0;
    char* str_buf = (char*)malloc(sizeof(char) * strlen(str) + 1);
    if (str_buf == NULL) {
        assert(FALSE);
        return 0;
    }


    strcpy(str_buf, str);

    memset(ringbuffer->parentheses, 0, MAX_SIZE);
    ringbuffer->start_index = 0;

    while (count < STR_LENGTH / 2) {
        {
            size_t i;
            int j;
            int k;
            for (i = 0; i < STR_LENGTH; i++) {
                for (j = 0; j < 4; j++) {
                    if (str_buf[i] == outter[j]) {
                        for (k = i - 1; k >= 0; k--) {
                            if (str_buf[k] == inner[j]) {
                                str_buf[k] = '?';
                                str_buf[i] = '?';
                                ringbuffer->parentheses[count % MAX_SIZE].opening_index = k;
                                ringbuffer->parentheses[count % MAX_SIZE].closing_index = i;
                                if (count / MAX_SIZE) {
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

    if (str_buf != NULL) {
        free(str_buf);
    }
    str_buf = NULL;

    return total_length;
}
