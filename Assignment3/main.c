#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "document_analyzer.h"

/*문서는 올바른 문법과 구두점을 사용합니다
문단들은 최소한 하나의 새 줄 문자(\n)로 구분되어 있습니다.
문장은 .!? 중의 한 문자로 구분되어 있습니다
단어들은 빈칸(스페이스)이나 , 문자로 구분되어 있습니다.*/

int main()
{
	char*** paragraph = NULL;
	int total_paragraph_count = 3;
	int total_word_count[] = {6, 3, 4, 6, 5, 9, 3, 8, 14};
	int total_sentence_count_int = 9;
	int total_sentence_count[] = { 4, 2, 3 };
	char data_backup[512];
	strcpy(data_backup, "Let's make a simple sentence here. My second sentence. Is this too easy? Should I make the assignments harder?\n\nThis is the second paragraph.I wonder how many sentences you will see here ?\n\nPOCU is fun!Stick around and you will have MORE fun.Just one more assignment after this one, and that one will be fun too!");

	paragraph = (char***)malloc(sizeof(char**) * total_paragraph_count);
	{
		int i;
		for (i = 0; i < total_paragraph_count; i++)
		{
			paragraph[i] = (char**)malloc(sizeof(char*) * total_sentence_count[i]);
			printf("%d\n", _msize(paragraph[i]));
		}
	}

	{
		int i;
		int j;
		int count = 0;
		for (i = 0; i < total_sentence_count_int; i++)
		{
			for (j = 0; j < total_word_count[i]; j++)
			{
				paragraph[i][j] = (char*)malloc(sizeof(char) * strlen(data_backup[count]) + 1);
				strcpy(paragraph[i][j], data_backup[count]);
				printf("%s\n", paragraph[i][j]);
				count++;
			}
		}
	}

    const char* filepath = "input.txt";
    load_document(filepath);
    int i = get_total_word_count();
}
