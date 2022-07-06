#include "document_analyzer.h"
/* 단락 : 개행문자로 구분
   문장 : . ? ! 3개의 문자로 구분
   단어 : 띄어쓰기 , 문자로 구분
   단락과 단락사이엔 개행이 존재
   각각의 간격은 4개 */
#define MAX_SIZE 768

int g_total_malloc_word_count = 0;

static int is_empty = FALSE;

static const char* recent_document = NULL;

static int total_paragraph_count = 0;
static int total_sentence_count = 0;
static int total_word_count = 0;

static int s_total_word_count = 0;
static int s_total_sentence_count = 0;
static int s_total_paragraph_count = 0;

static int total_sentence_count_int = 0;

static int is_paragraph;

static int s_word_count;

char paragraph_division = '\n';
char sentence_division[] = { '.', '?', '!' };

char word_division[] = { ',', ' ' };

char**** doc;
char**** paragraph = NULL;
char** sentence;
char* word;

void clear(void)
{

	total_sentence_count_int = 0;

	s_total_paragraph_count = 0;
	s_total_sentence_count = 0;
	s_word_count = 0;

	total_paragraph_count = 0;
	total_sentence_count = 0;
	total_word_count = 0;
}



int load_document(const char* document)
{
	char**** doc1 = NULL;
	char*** paragraph1 = NULL;
	char** sentence1 = NULL;

	char* word_store[128] = { 0, };
	char** sentence_store[64] = { 0, };
	char*** paragraph_store[32] = { 0, };
	char data[MAX_SIZE] = { 0, };


	FILE* fp;

	int count = 0;


	dispose();
	clear();

	fp = fopen(document, "r");
	if (fp == NULL)
	{
		return FALSE;
	}

	recent_document = document;

	{
		data[0] = fgetc(fp);
		if (data[0] == EOF)
		{
			is_empty = TRUE;
			return TRUE;
		}
		else {
			fseek(fp, 0, SEEK_SET);
		}
	}


	/* 총 단락 개수 구하기 */
	do
	{
		data[count] = fgetc(fp);

		if (count - 1 == 0)
		{
			if (data[count - 1] == '\n')
			{
				data[0] = data[count];
				data[count] = '\0';
				count--;
			}
		}

		is_empty = FALSE;


		if (data[count] != paragraph_division)
		{
			is_paragraph = FALSE;
		}

		 //if (data[count] == EOF)
		 //{
		 //	int l;

		 //	/**/
		 //	paragraph1 = (char***)malloc(sizeof(char**) * s_total_sentence_count);
		 //	if (paragraph1 == NULL)
		 //	{
		 //		return FALSE;
		 //	}

		 //	for (l = 0; l < s_total_sentence_count; l++)
		 //	{
		 //		*paragraph1 = sentence_store[l];
		 //		paragraph1++;
		 //	}
		 //	paragraph1 = paragraph1 - s_total_sentence_count;
		 //	paragraph_store[s_total_paragraph_count] = paragraph1;

		 //	s_total_paragraph_count++;




		 //	s_total_sentence_count = 0;
		 //	/**/
		 //	total_paragraph_count++;
		 //	is_paragraph = TRUE;
		 //	{
		 //		int m;
		 //		doc1 = (char****)malloc(sizeof(char***) * s_total_paragraph_count);
		 //		if (doc1 == NULL)
		 //		{
		 //			return FALSE;
		 //		}
		 //		for (m = 0; m < s_total_paragraph_count; m++)
		 //		{
		 //			*doc1 = paragraph_store[m];
		 //			doc1++;
		 //		}
		 //		doc1 = doc1 - s_total_paragraph_count;
		 //		break;
		 //	}

		 //	count = -1;
		 //	memset(data, 0, strlen(data));
		 //	memset(sentence_store, 0, 64);
		 //}

		if (data[count] == paragraph_division && !is_paragraph)
		{
			/* 단락 추가 */

			/**/
			char buf[32];
			int l;

			strcpy(buf, data);
			buf[count] = '\0';


			/**/
			paragraph1 = (char***)malloc(sizeof(char**) * s_total_sentence_count);
			if (paragraph1 == NULL)
			{
				return FALSE;
			}

			for (l = 0; l < s_total_sentence_count; l++)
			{
				*paragraph1 = sentence_store[l];
				paragraph1++;
			}
			paragraph1 = paragraph1 - s_total_sentence_count;
			paragraph_store[s_total_paragraph_count] = paragraph1;

			s_total_paragraph_count++;




			s_total_sentence_count = 0;
			/**/
			total_paragraph_count++;
			is_paragraph = TRUE;

			if (data[count] == EOF && strlen(buf) == 0)
			{
				int m;
				doc1 = (char****)malloc(sizeof(char***) * s_total_paragraph_count);
				if (doc1 == NULL)
				{
					return FALSE;
				}
				for (m = 0; m < s_total_paragraph_count; m++)
				{
					*doc1 = paragraph_store[m];
					doc1++;
				}
				doc1 = doc1 - s_total_paragraph_count;
				break;
			}

			count = -1;
			memset(data, 0, strlen(data));
			memset(sentence_store, 0, 64);
		}



		/* 문장 추가 */
		{
			int k;
			int l;
			char buf[32] = { 0, };
			for (k = 0; k < 3; k++)
			{
				if (data[count] == sentence_division[k])
				{
					/**/
					strcpy(buf, data);

					if (count >= 0)
					{
						buf[count] = '\0';


						if (strlen(buf) != 0)
						{
							word_store[s_total_word_count] = (char*)malloc(sizeof(char) * strlen(buf) + 1);
							strcpy(word_store[s_total_word_count], buf);
							s_total_word_count++;
							total_word_count++;
							count = -1;
							memset(data, 0, strlen(data));
						}
						/**/
						sentence1 = (char**)malloc(sizeof(char*) * s_total_word_count);
						if (sentence1 == NULL)
						{
							return 0;
						}
						for (l = 0; l < s_total_word_count; l++)
						{
							*sentence1 = word_store[l];

							sentence1++;
						}

						sentence1 = sentence1 - s_total_word_count;

						sentence_store[s_total_sentence_count] = sentence1;


						memset(word_store, 0, 128);
						s_total_sentence_count++;
						total_sentence_count++;
						s_total_word_count = 0;
						break;
					}
				}
			}
		}
		/**/

		/* 단어 추가 */
		{
			int k;
			char buf[32] = { 0, };
			for (k = 0; k < 2; k++)
			{
				if (data[count] == word_division[k])
				{
					strcpy(buf, data);
					if (count < 32)
					{

						buf[count] = '\0';
						if (strlen(buf) != 0)
						{
							word_store[s_total_word_count] = (char*)malloc(sizeof(char) * strlen(buf) + 1);

							if (word_store[s_total_word_count] == NULL)
							{
								return 0;
							}
							strcpy(word_store[s_total_word_count], buf);
							s_total_word_count++;
							total_word_count++;
							count = -1;
							memset(data, 0, strlen(data));
							break;
						}
						else {
							memset(data, 0, strlen(data));
							count = -1;
							break;
						}
					}
				}
			}
		}
	} while (data[count] != EOF && count++ < MAX_SIZE - 1);



	{
		int l;

		/**/
		paragraph1 = (char***)malloc(sizeof(char**) * s_total_sentence_count);
		if (paragraph1 == NULL)
		{
			return FALSE;
		}

		for (l = 0; l < s_total_sentence_count; l++)
		{
			*paragraph1 = sentence_store[l];
			paragraph1++;
		}
		paragraph1 = paragraph1 - s_total_sentence_count;
		paragraph_store[s_total_paragraph_count] = paragraph1;

		s_total_paragraph_count++;




		s_total_sentence_count = 0;
		/**/
		total_paragraph_count++;
		is_paragraph = TRUE;
		{
			int m;
			doc1 = (char****)malloc(sizeof(char***) * s_total_paragraph_count);
			if (doc1 == NULL)
			{
				return FALSE;
			}
			for (m = 0; m < s_total_paragraph_count; m++)
			{
				*doc1 = paragraph_store[m];
				doc1++;
			}
			doc1 = doc1 - s_total_paragraph_count;

		}

		count = -1;
		memset(data, 0, strlen(data));
		memset(sentence_store, 0, 64);
	}

	paragraph = doc1;

	if (fclose(fp) == EOF)
	{
		return FALSE;
	}

	return TRUE;
}

void dispose(void)
{
	/*동적으로 할당된 메모리를 모두 해제*/

	if (is_empty)
	{
		return;
	}

	if (paragraph == NULL)
	{
		return;
	}

	{
		unsigned int i;
		unsigned int j;
		unsigned int k;
		int word_count = 0;
		for (i = 0; i < get_total_paragraph_count(); i++)
		{
			for (j = 0; j < get_paragraph_sentence_count((const char***)*(paragraph + i)); j++)
			{
				for (k = 0; k < get_sentence_word_count((const char**)paragraph[i][j]); k++)
				{
					free(paragraph[i][j][k]);
				}
				word_count++;
			}
		}
	}

	{
		unsigned int i;
		unsigned int j;
		for (i = 0; i < get_total_paragraph_count(); i++)
		{
			for (j = 0; j < get_paragraph_sentence_count((const char***)*(paragraph + i)); j++)
			{
				free(paragraph[i][j]);
			}
		}
	}

	{
		unsigned int i;
		for (i = 0; i < get_total_paragraph_count(); i++)
		{
			free(paragraph[i]);
		}
	}

	free(paragraph);
	paragraph = NULL;
}

unsigned int get_total_word_count(void)
{

	if (is_empty)
	{
		return 0;
	}

	return total_word_count;
}

unsigned int get_total_sentence_count(void)
{
	if (is_empty)
	{
		return 0;
	}

	return total_sentence_count;
}

unsigned int get_total_paragraph_count(void)
{

	if (paragraph == NULL)
	{
		return 0;
	}

	return s_total_paragraph_count;
}

const char*** get_paragraph_or_null(const unsigned int paragraph_index)
{
	if (paragraph == NULL)
	{
		return NULL;
	}
	if (paragraph_index >= (const unsigned int)s_total_paragraph_count)
	{
		return NULL;
	}

	return (const char***)paragraph[paragraph_index];
}

unsigned int get_paragraph_word_count(const char*** paragraph)
{
	unsigned int count = 0;

	{
		size_t i;
		size_t j;
		for (i = 0; i < _msize(paragraph) / sizeof(char***); i++)
		{
			for (j = 0; j < _msize(*(paragraph + i)) / sizeof(char**); j++)
			{
				count++;
			}
		}
	}

	return count;
}

unsigned int get_paragraph_sentence_count(const char*** paragraph)
{
	unsigned int count = 0;
	size_t i;

	for (i = 0; i < _msize(paragraph) / sizeof(char**); i++)
	{
		count++;
	}
	return count;
}

const char** get_sentence_or_null(const unsigned int paragraph_index, const unsigned int sentence_index)
{
	if (paragraph_index >= (unsigned)s_total_paragraph_count)
	{
		return NULL;
	}


	if (sentence_index >= _msize(paragraph[paragraph_index]) / sizeof(char***))
	{
		return NULL;
	}

	return (const char**)paragraph[paragraph_index][sentence_index];
}

unsigned int get_sentence_word_count(const char** sentence)
{
	unsigned int count = 0;
	size_t i;

	for (i = 0; i < _msize(sentence) / sizeof(char*); i++)
	{
		count++;
	}

	return count;
}

int print_as_tree(const char* filename)
{
	const char* param_str = "Paragraph";
	const char* sentence_str = "Sentence";
	const char delim = ':';
	int param_count = 0;
	int sentence_count = 0;
	FILE* fp;

	if (is_empty)
	{
		return FALSE;
	}

	if (recent_document == NULL)
	{
		return FALSE;
	}

	if (s_total_paragraph_count == 0)
	{
		return FALSE;
	}

	if (paragraph == NULL)
	{
		return FALSE;
	}

	fp = fopen(filename, "w");
	if (fp == NULL)
	{
		return FALSE;
	}


	{
		int i;
		unsigned int j;
		unsigned int k;
		int word_count = 0;
		for (i = 0; i < s_total_paragraph_count; i++)
		{
			fprintf(fp, "%s %d%c\n", param_str, param_count, delim);
			for (j = 0; j < get_paragraph_sentence_count((const char***)*(paragraph + i)); j++)
			{
				fprintf(fp, "    %s %d%c\n", sentence_str, sentence_count, delim);
				for (k = 0; k < get_sentence_word_count((const char**)paragraph[i][j]); k++)
				{
					fprintf(fp, "        %s\n", paragraph[i][j][k]);
				}
				word_count++;
				sentence_count++;
			}
			fputc('\n', fp);
			param_count++;
			sentence_count = 0;
		}
	}

	if (fclose(fp) == EOF)
	{
		return FALSE;
	}
	return TRUE;
}
