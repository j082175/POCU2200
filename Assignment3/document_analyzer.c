#include "document_analyzer.h"
/* 단락 : 개행문자로 구분
   문장 : . ? ! 3개의 문자로 구분
   단어 : 띄어쓰기 , 문자로 구분 
   단락과 단락사이엔 개행이 존재 
   각각의 간격은 4개 */
static char data[512] = { 0, };
static char data_backup[128][32] = {0,};
static char* recent_document = NULL;

static int total_paragraph_count = 0;
static int total_sentence_count[128] = { 0, };
static int total_word_count[512] = { 0, };

static int total_sentence_count_int = 0;

static int is_paragraph;
static int is_word;
static int check;

static int word_count;

char paragraph_division = '\n';
char sentence_division[] = {'.', '?', '!'};
char word_division[] = { ' ', ',' , '.', '?', '!' };

char**** doc;
char*** paragraph = NULL;
char** sentence;
char* word;


int load_document(const char* document)
{
	FILE* fp;
	recent_document = document;
	fp = fopen(document, "r");
	if (fp == NULL)
	{
		return FALSE;
	}

	/* 총 단락 개수 구하기 */
	for (int i = 0; i < 512; i++)
	{
		data[i] = fgetc(fp);

		if (data[i] == EOF)
		{
			total_paragraph_count++;
			data[i] = '\0';
			break;
		}

		if (data[i] == paragraph_division && !is_paragraph)
		{
			total_paragraph_count++;
			is_paragraph = TRUE;
		}

		if (data[i] != paragraph_division)
		{
			is_paragraph = FALSE;
		}

		{
			int j;
			for (j = 0; j < 3; j++)
			{
				if (data[i] == sentence_division[j])
				{
					total_sentence_count[total_paragraph_count]++;
					total_sentence_count_int++;
					check = TRUE;
					//word_count++;
				}
			}
		}

		{
			int j;
			int k;
			for (j = 0; j < 5; j++)
			{
				if (data[i] == word_division[j] && !is_word)
				{
					//total_word_count++;
					total_word_count[word_count]++;
					if (check)
					{
						word_count++;
						check = FALSE;
					}
					is_word = TRUE;
					break;
				}
				else {
					is_word = FALSE;
				}
			}
		}
	}

	/* word tokenizer */
	{
		int count = 0;
		char* ptr = data;
		strtok(ptr, " ,.!?");
		strcpy(data_backup[count++], ptr);
		while (TRUE)
		{
			ptr = strtok(NULL, " ,.!?");
			if (ptr == NULL)
			{
				break;
			}
			strcpy(data_backup[count++], ptr);
		}
	}

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


	if (fclose(fp) == EOF)
	{
		return FALSE;
	}

	return TRUE;
}

void dispose(void)
{
	/*동적으로 할당된 메모리를 모두 해제*/
}

unsigned int get_total_word_count(void)
{
	if (recent_document != NULL)
	{
		return strlen(data);
	}
	else {
		return 0;
	}
}

unsigned int get_total_sentence_count(void)
{

}

unsigned int get_total_paragraph_count(void)
{

}

const char*** get_paragraph_or_null(const unsigned int paragraph_index)
{

}

unsigned int get_paragraph_word_count(const char*** paragraph)
{

}

unsigned int get_paragraph_sentence_count(const char*** paragraph)
{

}

const char** get_sentence_or_null(const unsigned int paragraph_index, const unsigned int sentence_index)
{

	
}

unsigned int get_sentence_word_count(const char** sentence)
{

}

int print_as_tree(const char* filename)
{

}
