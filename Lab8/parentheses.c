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
	const int STR_LENGTH = (int)strlen(str);
	size_t count = 0;
	size_t index = 0;
	size_t current_index_check = 0;
	size_t current_parenthesis_index = 0;
	size_t total_length = 0;
	char str_buf[32] = { 0, };

	size_t opening_index = 0;
	size_t closing_index = 0;

	size_t buf_length = MAX_LENGTH;
	int check = FALSE;
	size_t discount = 0;
	strcpy(str_buf, str);
	while (strlen(str_buf) > 1)
	{
		{
			int i;
			int j;
			char c = 0;
			index = 0;

			/* 먼저 어떤 문자인지 검사하는거 */
			for (j = 0; j < 4; j++)
			{
				int count1 = STR_LENGTH - 1 - discount;
				if (str_buf[count1] == g_ch_outter[j])
				{
					while (count1 >= 0)
					{
						if (str_buf[count1] == g_ch_outter[j])
						{
							closing_index = count1 + discount;
						}
						count1--;
					}

					index = j;
					check = TRUE;
					break;
				}
			}
			/**/

			/* 어떤문자인지 선택됬으면 그 반대문자 있는지 검사 있다면 인덱스 저장 없다면 x */
			if (check)
			{
				int count1 = 0;

				while (count1 < STR_LENGTH - 1 - discount)
				{
					if (str_buf[count1] == g_ch_inner[index])
					{
						opening_index = count1;
					}
					count1++;
				}

				ringbuffer->parentheses[count].opening_index = opening_index;
				ringbuffer->parentheses[count].closing_index = closing_index;
				total_length++;
				delete_at(str_buf, opening_index, STR_LENGTH - discount);
				delete_at(str_buf, closing_index - 1 - discount, STR_LENGTH - discount - 1);

				discount = discount + 2;

			}

		}
		

		check = FALSE;
		count++;
	}

	ringbuffer->start_index = current_index_check;

	return total_length;
}
