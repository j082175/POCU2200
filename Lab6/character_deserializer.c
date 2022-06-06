#include "character_deserializer.h"
/* 이 실습에서 계산을 할 때 소수점 이하는 무시하세요. 즉, 모든 결과는 무조건 내림을 합니다.
이 실습에서 전역(global) 변수와 정적(static) 변수의 사용을 금합니다. 전역/정적 변수 없이도 이 실습을 끝낼 수 있으니 저를 믿으세요. :)*/

int string_length(const char* str) {
	int str_length = 0;
	while (*(str + str_length) != '\0')
	{
		str_length++;
	}
	return str_length;
}

int string_length_before_carriage_return(const char* str) {
	int str_length = 0;
	while (*(str + str_length) != '\n')
	{
		if (*(str + str_length) == '\0')
		{
			break;
		}
		str_length++;
	}
	return str_length;
}

void string_copy(char* dst, const char* source) {
	int i;
	for (i = 0; i < string_length(source); i++)
	{
		dst[i] = source[i];
	}
}

int token_count(const char* str, const char delim) {
	int str_length = 0;
	int delim_count = 0;
	while (*(str + str_length) != '\n')
	{
		if (*(str + str_length) == delim)
		{
			delim_count++;
		}
		str_length++;
	}
	return delim_count;
}

int string_compare(const char* str1, const char* str2) {
	if (str2 == NULL)
	{
		return 0;
	}

	int is_same = FALSE;
	{
		int i;
		for (i = 0; i < string_length(str1); i++)
		{
			if (*(str1 + i) == *(str2 + i))
			{
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

int get_character(const char* filename, character_v3_t* out_character) {
	/* , 인지 : 인지, | 인지 먼저 검사 */
	FILE* fp = NULL;
	char buffer[1024] = { 0, };
	char* words_backup[1024] = { 0, };
	char* values_backup[1024] = { 0, };
	char* minions_word[1024] = { 0, };
	char* minions_value[1024] = { 0, };
	int version_check = 0;
	if ((fp = (fopen(filename, "r"))) == NULL)
	{
		return 0;
	}

	/* 파일에 있는거 전부 가져오기 */
	{
		int count = 0;
		char c = 0;
		while (1)
		{
			c = fgetc(fp);
			switch (c)
			{
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

			if (c == EOF)
			{
				break;
			}
			buffer[count] = c;
			count++;
		}
	}
	/* end */

	printf("%s\nversion : %d\n", buffer, version_check);

	switch (version_check)
	{
	case 1:
	{
		int count = 0;
		int word_count = 0;
		int value_count = 0;
		char* ptr = buffer;
		char* temp = NULL;
		char* backup_temp = NULL;
		while (TRUE)
		{
			if (count % 2 == 0)
			{
				temp = tokenize(ptr, ":,");
				if (string_compare(temp, backup_temp))
				{
					break;
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
	}
		break;
	case 2:
	{
		int count = 0;
		int word_count = 0;
		int value_count = 0;
		char backup_buffer[1024] = { 0, };
		char* ptr = buffer;
		char* temp = NULL;
		char* backup_temp = NULL;


		string_copy(backup_buffer, buffer);
		{
			int i;
			int limit = token_count(backup_buffer, ',') + 1;
			for (i = 0; i < limit; i++)
			{
				temp = tokenize(ptr, ",\n");
				words_backup[word_count] = temp;
				word_count++;
				ptr = NULL;
			}
		}

		string_copy(backup_buffer, buffer);
		temp = NULL;
		{
			int i;
			int limit = token_count(backup_buffer, ',') + 1;
			ptr = backup_buffer + string_length_before_carriage_return(backup_buffer) + 1;

			for (i = 0; i < limit; i++)
			{
				temp = tokenize(ptr, ",\n");
				values_backup[value_count] = temp;
				value_count++;
				ptr = NULL;
			}
		}
	}
		break;
	case 3:
	{
		int count = 0;
		int word_count = 0;
		int value_count = 0;
		char backup_buffer[1024] = { 0, };
		char* ptr = buffer;
		char* temp = NULL;
		char* backup_temp = NULL;
		char* backup_ptr = NULL;
		int total_count = 0;
		/*                */
		string_copy(backup_buffer, buffer);
		{
			int i;
			int limit = token_count(backup_buffer, '|') + 1;
			for (i = 0; i < limit; i++)
			{
				temp = tokenize(ptr, "|  \n");
				words_backup[word_count] = temp;
				word_count++;
				ptr = NULL;
			}
		}

		total_count = string_length_before_carriage_return(backup_buffer);

		string_copy(backup_buffer, buffer);
		temp = NULL;
		{
			int i;
			int limit = token_count(backup_buffer, '|') + 1;
			ptr = backup_buffer + total_count + 1;

			total_count += string_length_before_carriage_return(ptr) + 1;

			backup_ptr = ptr;
			for (i = 0; i < limit; i++)
			{
				temp = tokenize(ptr, "|  \n");
				values_backup[value_count] = temp;
				value_count++;
				ptr = NULL;
			}
		}
		/*                 */


		string_copy(backup_buffer, backup_ptr);
		total_count = string_length_before_carriage_return(backup_buffer) + 1;
		char* b = backup_buffer + total_count;
		if (backup_buffer + total_count == NULL)
		{
			int a = 1;
			int b = 2;
		}
	}
		break;
	default:
		break;
	}

	switch (version_check)
	{
	case 1:
		
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}


	if (fclose(fp) == EOF)
	{
		return 0;
	}

	return 1;
}
