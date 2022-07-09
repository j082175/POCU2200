#include "document_analyzer.h"
/* 단락 : 개행문자로 구분
   문장 : . ? ! 3개의 문자로 구분
   단어 : 띄어쓰기 , 문자로 구분
   단락과 단락사이엔 개행이 존재
   각각의 간격은 4개 */


#define DATA_MAX_SIZE 40960
static int is_empty = FALSE;
static int paragraph_index_store;
static int sentence_index_store;

static int wcount = 0;
static int scount = 0;
static int pcount = 0;


//static char data[512] = { 0, };
//static char* data;
//
//static char** data_backup;

static const char* recent_document = NULL;

static int total_paragraph_count = 0;

//static int total_sentence_count[128] = { 0, };
//static int total_word_count[256] = { 0, };
static int* total_sentence_count = NULL;
static int* total_word_count = NULL;

static int total_sentence_count_int = 0;

static int is_paragraph;
static int is_word;
static int check;

static int s_word_count;

char paragraph_division = '\n';
char sentence_division[] = { '.', '?', '!' };
char word_division[] = { ' ', ',' , '.', '?', '!' };

//char**** doc;
char**** paragraph = NULL;
//char** sentence;
//char* word;



//char* word_store[512] = { 0, };
//char** sentence_store[128] = { 0, };
//char*** paragraph_store[64] = { 0, };

char** word_store = NULL;
char*** sentence_store = NULL;
char**** paragraph_store = NULL;

void clear(void)
{
    total_paragraph_count = 0;
    total_sentence_count = 0;
    total_sentence_count_int = 0;
    total_word_count = 0;

    s_word_count = 0;
    wcount = 0;
    scount = 0;
    pcount = 0;

    paragraph_index_store = 0;
    sentence_index_store = 0;
}

int load_document(const char* document)
{
    char**** doc1 = NULL;
    char*** paragraph1 = NULL;
    char** sentence1 = NULL;
    char* word1 = NULL;

    char* data = NULL;
    char** data_backup = NULL;
    FILE* fp;
    int i = 0;

    dispose();

    recent_document = document;


    fp = fopen(document, "r");
    if (fp == NULL)
    {
        return FALSE;
    }



    data = (char*)malloc(sizeof(char) * DATA_MAX_SIZE);
    memset(data, 0, DATA_MAX_SIZE);

    total_sentence_count = (int*)malloc(sizeof(int) * DATA_MAX_SIZE / 2);
    total_word_count = (int*)malloc(sizeof(int) * DATA_MAX_SIZE / 2);
    memset(total_sentence_count, 0, DATA_MAX_SIZE / 2);
    memset(total_word_count, 0, DATA_MAX_SIZE / 2);

    word_store = (char**)malloc(sizeof(char*) * DATA_MAX_SIZE);
    sentence_store = (char***)malloc(sizeof(char**) * DATA_MAX_SIZE / 2);
    paragraph_store = (char****)malloc(sizeof(char***) * DATA_MAX_SIZE / 3);
    memset(word_store, 0, DATA_MAX_SIZE);
    memset(sentence_store, 0, DATA_MAX_SIZE / 2);
    memset(paragraph_store, 0, DATA_MAX_SIZE / 3);


    /* 총 단락 개수 구하기 */
    while (data[i] != EOF)
    {
        data[i] = fgetc(fp);

        if (data[0] == EOF)
        {
            is_empty = TRUE;
            goto end;
        }

        is_empty = FALSE;

        if (data[i] == EOF)
        {
            if (data[i - 1] != '\n')
            {
                total_paragraph_count++;
            }
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
                    break;
                    //word_count++;
                }
            }
        }

        {
            int j;
            for (j = 0; j < 5; j++)
            {
                if (data[i] == word_division[j] && !is_word)
                {
                    //total_word_count++;
                    total_word_count[s_word_count]++;
                    if (check)
                    {
                        s_word_count++;
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
        i++;
    }
    /**/

    {
        int i;
        int dsize = 32;
        data_backup = (char**)malloc(sizeof(char*) * DATA_MAX_SIZE);
        if (data_backup == NULL)
        {
            assert(FALSE);
        }
        data_backup[0] = (char*)malloc(sizeof(char) * DATA_MAX_SIZE * dsize);
        for (i = 1; i < DATA_MAX_SIZE; i++)
        {
            data_backup[i] = data_backup[i - 1] + dsize;
        }


        //for (i = 0; i < DATA_MAX_SIZE; i++)
        //{
        //    data_backup[i] = (char*)malloc(sizeof(char) * 32);
        //    if (data_backup[i] == NULL)
        //    {
        //        assert(FALSE);
        //    }
        //    memset(data_backup[i], 0, 32);
        //}
    }

    /* word tokenizer */
    {
        int count = 0;
        char* ptr;
        char* a;
        //char* data_backup1 = (char*)malloc(sizeof(char) * 512);/* 메모리 문제 1*/
        //if (data_backup1 == NULL)
        //{
        //    assert(FALSE);
        //}
        //memset(data_backup1, 0, 512);
        //strcpy(data_backup1, data);
        //ptr = data_backup1;
        ptr = data;
        a = strtok(ptr, " ,.!?\n");
        if (a == NULL)
        {
            assert(FALSE);
        }
        strcpy(data_backup[count], ptr);
        count++;
        while (TRUE)
        {
            ptr = strtok(NULL, " ,.!?\n");
            if (ptr == NULL)
            {
                break;
            }
			strcpy(data_backup[count], ptr);
            count++;
        }

        //free(data_backup1);
    }
    /**/

    //paragraph1 = (char****)malloc(sizeof(char***) * total_paragraph_count + 1);
    //if (paragraph1 == NULL)
    //{
    //    assert(FALSE);
    //}

    //paragraph1[0] = (char***)malloc(sizeof(char**) * total_paragraph_count * total_sentence_count_int);

    //{
    //    int i;
    //    for (i = 1; i < total_paragraph_count + 1; i++)
    //    {
    //        paragraph1[i] = paragraph1[i - 1] + total_sentence_count[i - 1];
    //    }
    //}

    //{
    //    sentence1 = (char**)malloc(sizeof(char*) * total_sentence_count_int + 1);

    //    //sentence1[0] = (char*)malloc(sizeof(char) )
    //}

    {
        int i;
        int j;
        int k;
        int count = 0;
        int word_count = 0;
        doc1 = (char****)malloc(sizeof(char***) * total_paragraph_count);
        for (i = 0; i < total_paragraph_count; i++)
        {
            paragraph1 = (char***)malloc(sizeof(char**) * total_sentence_count[i]);
            for (j = 0; j < total_sentence_count[i]; j++)
            {
                sentence1 = (char**)malloc(sizeof(char*) * total_word_count[word_count]);
                for (k = 0; k < total_word_count[word_count]; k++)
                {
                    word1 = (char*)malloc(sizeof(char) * strlen(data_backup[count]) + 1);/* 메모리 문제 */
                    if (word1 == NULL)
                    {
                        assert(FALSE);
                    }
                    strcpy(word1, data_backup[count++]);
                    word_store[wcount++] = word1;
                    *sentence1 = word1;
                    sentence1++;
                }
                //*sentence1 = NULL;
                //sentence1++;
                sentence_store[scount++] = sentence1 - total_word_count[word_count];

                *paragraph1 = sentence1 - total_word_count[word_count];
                paragraph1++;
                word_count++;
            }
            //*paragraph1 = NULL;
            //paragraph1++;
            paragraph_store[pcount++] = paragraph1 - total_sentence_count[i];

            *doc1 = paragraph1 - total_sentence_count[i];
            doc1++;
        }
        //*doc1 = NULL;
        //doc1++;

        doc1 = doc1 - total_paragraph_count;
    }
    //print();

    //free(data);
    //data = NULL;
    paragraph = doc1;
end:

    if (data != NULL)
    {
        free(data);
        data = NULL;
    }

    if (data_backup != NULL)
    {
        free(data_backup[0]);
        free(data_backup);
        data_backup = NULL;
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


    if (total_word_count != NULL)
    {
		free(total_word_count);
        total_word_count = NULL;
    }

    if (total_sentence_count != NULL)
    {
		free(total_sentence_count);
        total_sentence_count = NULL;
    }


	if (paragraph != NULL)
	{
		free(paragraph);
		paragraph = NULL;

	}

	if (word_store != NULL)
	{
		{
			int i;
			for (i = 0; i < wcount; i++)
			{
				free(word_store[i]);
				word_store[i] = NULL;
			}
		}
		free(word_store);
		word_store = NULL;
	}

	if (sentence_store != NULL)
	{
		{
			int i;
			for (i = 0; i < scount; i++)
			{
				free(sentence_store[i]);
				sentence_store[i] = NULL;
			}
		}
		free(sentence_store);
		sentence_store = NULL;
	}

	if (paragraph_store != NULL)
	{
		{
			int i;
			for (i = 0; i < pcount; i++)
			{
				free(paragraph_store[i]);
				paragraph_store[i] = NULL;
			}
		}
		free(paragraph_store);
		paragraph_store = NULL;
	}

    clear();
}

unsigned int get_total_word_count(void)
{
    int sum = 0;
    int i;
    for (i = 0; i < total_sentence_count_int; i++)
    {
        sum += total_word_count[i];
    }
    return (unsigned int)sum;
}

unsigned int get_total_sentence_count(void)
{
    return (unsigned int)total_sentence_count_int;
}

unsigned int get_total_paragraph_count(void)
{
    return (unsigned int)total_paragraph_count;
}

const char*** get_paragraph_or_null(const unsigned int paragraph_index)
{
    if (paragraph == NULL)
    {
        return NULL;
    }
    if (paragraph_index >= (const unsigned int)total_paragraph_count)
    {
        return NULL;
    }

    paragraph_index_store = paragraph_index;

    return (const char***)paragraph[paragraph_index];
}

unsigned int get_paragraph_word_count(const char*** paragraph)
{
    unsigned int count = 0;
    unsigned int sentence_sum = 0;

    {
        size_t i;
        for (i = 0; i < paragraph_index_store; i++)
        {
            sentence_sum += total_sentence_count[i];
        }
    }

    {
        size_t i;
        for (i = 0; i < total_sentence_count[paragraph_index_store]; i++)
        {
            count += total_word_count[i + sentence_sum];
        }
    }

    return count;
}

unsigned int get_paragraph_sentence_count(const char*** paragraph)
{
    return (unsigned int)total_sentence_count[paragraph_index_store];
}

const char** get_sentence_or_null(const unsigned int paragraph_index, const unsigned int sentence_index)
{
    if (paragraph_index >= (unsigned)total_paragraph_count)
    {
        return NULL;
    }

    if (sentence_index >= total_sentence_count[paragraph_index])
    {
        return NULL;
    }

    paragraph_index_store = paragraph_index;
    sentence_index_store = sentence_index;

    return (const char**)paragraph[paragraph_index][sentence_index];
}

unsigned int get_sentence_word_count(const char** sentence)
{
    unsigned int count = 0;
    unsigned int sentence_sum = 0;

    {
        size_t i;
        for (i = 0; i < paragraph_index_store; i++)
        {
            sentence_sum += total_sentence_count[i];
        }
    }

    count += total_word_count[sentence_sum + sentence_index_store];

    return count;
}

int print_as_tree(const char* filename)
{
    const char* param_str = "Paragraph";
    const char* sentence_str = "Sentence";
    const char delim = ':';
    int param_count = 0;
    int sentence_count = 0;

    FILE* fp2;

    if (is_empty)
    {
        return FALSE;
    }

    if (recent_document == NULL)
    {
        return FALSE;
    }

    if (total_paragraph_count == 0)
    {
        return FALSE;
    }

    fp2 = fopen(filename, "w");
    if (fp2 == NULL)
    {
        return FALSE;
    }

    {
        int i;
        int j;
        int k;
        int word_count = 0;
        int count = 0;
        for (i = 0; i < total_paragraph_count; i++)
        {
            fprintf(fp2, "%s %d%c\n", param_str, param_count, delim);
            for (j = 0; j < total_sentence_count[i]; j++)
            {
                fprintf(fp2, "    %s %d%c\n", sentence_str, sentence_count, delim);
                for (k = 0; k < total_word_count[word_count]; k++)
                {
                    fprintf(fp2, "        %s\n", word_store[count]);
                    count++;
                }
                word_count++;
                sentence_count++;
            }
            fputc('\n', fp2);
            param_count++;
            sentence_count = 0;
        }
    }


    if (fclose(fp2) == EOF)
    {
        return FALSE;
    }
    return TRUE;
}
