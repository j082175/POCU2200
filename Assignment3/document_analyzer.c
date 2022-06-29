#include "document_analyzer.h"
static char data[512] = { 0, };
static char* recent_document = NULL;
char**** document = data;

typedef struct data1 {
	char* arr;
	data1_t d;
}data1_t;

int load_document(const char* document)
{
	FILE* fp;
	recent_document = document;
	fp = fopen(document, "r");
	if (fp == NULL)
	{
		return FALSE;
	}

	for (int i = 0; i < 512; i++)
	{
		data[i] = fgetc(fp);
		if (data[i] == EOF)
		{
			data[i] = '\0';
			break;
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
