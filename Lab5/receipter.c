#include "receipter.h"

static add_item_count = 0;

static char** item_arr[ITEM_LENGTH] = { 0, };
static double price_arr[ITEM_LENGTH] = { 0, };

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

	if (add_item_count >= ITEM_LENGTH)
	{
		return FALSE;
	}

	item_arr[add_item_count] = name;
	price_arr[add_item_count] = price;
	
	add_item_count++;

	return TRUE;
}

void set_tip(double tip) {

}

void set_message(const char* message) {

}

int print_receipt(const char* filename, time_t timestamp) {
	FILE* f1 = 0;
	struct tm tm = *localtime(&timestamp);
	char buffer[1024] = { 0, };
	char buffer2[1024] = { 0, };
	
	if (add_item_count == 0)
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
		sprintf(buffer2, "%05d\n", add_item_count);
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

	fprintf(f1, "%s\n", buffer);
	buffer_reset(buffer);
	buffer_reset(buffer2);
	/* 기본 동작 끝 */


	{
		int i;
		int j;
		for (i = 0; i < add_item_count; i++)
		{
			for (j = 0; j < string_length(item_arr[i]); j++)
			{
				
			}
		}
	}


	
	if (fclose(f1) == EOF)
	{
		return FALSE;
	}

	return TRUE;
}