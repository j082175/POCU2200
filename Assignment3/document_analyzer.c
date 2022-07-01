#include "document_analyzer.h"
/* 단락 : 개행문자로 구분
   문장 : . ? ! 3개의 문자로 구분
   단어 : 띄어쓰기 , 문자로 구분
   단락과 단락사이엔 개행이 존재
   각각의 간격은 4개 */


static int is_empty = FALSE;
static int paragraph_index_store;
static int sentence_index_store;


static char data[512] = { 0, };
//static char data_backup[128][32] = { 0, };
static char** data_backup;

static const char* recent_document = NULL;

static int total_paragraph_count = 0;
static int total_sentence_count[32] = { 0, };
static int total_word_count[64] = { 0, };

static int total_sentence_count_int = 0;

static int is_paragraph;
static int is_word;
static int check;

static int s_word_count;

char paragraph_division = '\n';
char sentence_division[] = { '.', '?', '!' };
char word_division[] = { ' ', ',' , '.', '?', '!' };

char**** doc;
char**** paragraph = NULL;
char** sentence;
char* word;

void clear()
{
    total_paragraph_count = 0;
    memset(total_sentence_count, 0, 32);
    memset(total_word_count, 0, 64);
    total_sentence_count_int = 0;
    s_word_count = 0;
    paragraph = NULL;
}

void print(void)
{
    {
        int i;
        int j;
        int k;
        int word_count = 0;
        for (i = 0; i < total_paragraph_count; i++)
        {
            for (j = 0; j < total_sentence_count[i]; j++)
            {
                for (k = 0; k < total_word_count[word_count]; k++)
                {
                    printf("%s ", *(*(*(paragraph + i) + j) + k));
                    //printf("%d ", _msize(*(*(*(paragraph + i) + j) + k)));

                }
                printf("\n");
                word_count++;
            }
            printf("\n");
        }
    }
}


int load_document(const char* document)
{
    FILE* fp;
    int i;
    fp = fopen(document, "r");
    if (fp == NULL)
    {
        return FALSE;
    }

    recent_document = document;

    dispose();

    memset(data, 0, 512);

    clear();




    /* 총 단락 개수 구하기 */
    for (i = 0; i < 512; i++)
    {
        data[i] = fgetc(fp);

        if (data[0] == EOF)
        {
            is_empty = TRUE;
            return TRUE;
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
    }
    /**/

    {
        int i;
        data_backup = (char**)malloc(sizeof(char*) * 128);
        if (data_backup == NULL)
        {
            assert(FALSE);
        }
        for (i = 0; i < 128; i++)
        {
            data_backup[i] = (char*)malloc(sizeof(char) * 32 + 1);
            if (data_backup[i] == NULL)
            {
                assert(FALSE);
            }
            memset(data_backup[i], 0, 32);
        }
    }

    /* word tokenizer */
    {
        int count = 0;
        char* ptr;
        char* a;
        char* data_backup1 = (char*)malloc(sizeof(char) * strlen(data) + 1);/* 메모리 문제 1*/
        if (data_backup1 == NULL)
        {
            assert(FALSE);
        }
        memset(data_backup1, 0, strlen(data) + 1);
        strcpy(data_backup1, data);
        ptr = data_backup1;
        a = strtok(ptr, " ,.!?\n");
        if (a == NULL)
        {
            assert(FALSE);
        }
        strcpy(data_backup[count++], ptr);
        while (TRUE)
        {
            ptr = strtok(NULL, " ,.!?\n");
            if (ptr == NULL)
            {
                break;
            }
            strcpy(data_backup[count++], ptr);
        }

        free(data_backup1);
    }
    /**/

    paragraph = (char****)malloc(sizeof(char***) * total_paragraph_count);
    if (paragraph == NULL)
    {
        assert(FALSE);
    }
    {
        int i;
        for (i = 0; i < total_paragraph_count; i++)
        {
            paragraph[i] = (char***)malloc(sizeof(char**) * total_sentence_count[i]);
            if (paragraph[i] == NULL)
            {
                assert(FALSE);
            }
        }
    }

    {
        int i;
        int j;
        int count = 0;
        for (i = 0; i < total_paragraph_count; i++)
        {
            for (j = 0; j < total_sentence_count[i]; j++)
            {
                paragraph[i][j] = (char**)malloc(sizeof(char*) * total_word_count[count++]);
                if (paragraph[i][j] == NULL)
                {
                    assert(FALSE);
                }
            }
        }
    }

    {
        int i;
        int j;
        int k;
        int count = 0;
        int word_count = 0;
        for (i = 0; i < total_paragraph_count; i++)
        {
            for (j = 0; j < total_sentence_count[i]; j++)
            {
                for (k = 0; k < total_word_count[word_count]; k++)
                {
                    paragraph[i][j][k] = (char*)malloc(sizeof(char) * strlen(data_backup[count]) + 1);/* 메모리 문제 */
                    if (paragraph[i][j][k] == NULL)
                    {
                        assert(FALSE);
                    }

                    strcpy(*(*(*(paragraph + i) + j) + k), data_backup[count++]);
                    /*printf("%s ", *(*(*(paragraph + i) + j) + k));*/
                }
                /*printf("\n");*/
                word_count++;
            }
            /*printf("\n"); */
        }
    }
    //print();

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

    {
        int i;
        if (data_backup != NULL)
        {
            for (i = 0; i < 128; i++)
            {
                free(data_backup[i]);
            }
            free(data_backup);
        }
        data_backup = NULL;
    }

    if (paragraph == NULL)
    {
        return;
    }


    {
        int i;
        int j;
        int k;
        int word_count = 0;
        for (i = 0; i < total_paragraph_count; i++)
        {
            for (j = 0; j < total_sentence_count[i]; j++)
            {
                for (k = 0; k < total_word_count[word_count]; k++)
                {
                    free(paragraph[i][j][k]);
                }
                word_count++;
            }
        }
    }

    {
        int i;
        int j;
        for (i = 0; i < total_paragraph_count; i++)
        {
            for (j = 0; j < total_sentence_count[i]; j++)
            {
                free(paragraph[i][j]);
            }
        }
    }

    {
        int i;
        for (i = 0; i < total_paragraph_count; i++)
        {
            free(paragraph[i]);
        }
    }

    free(paragraph);

    clear();
    //char* a = paragraph[2][2][12];
    //free(paragraph[2][2]);
    //a = paragraph[2][2][11];
    //char** b = paragraph[2][2];
    //char*** c = paragraph[2];
    //char**** d = paragraph;

   //if (paragraph != NULL)
   //{
   //    free(paragraph);
   //    paragraph = NULL;
   //}

   //a = paragraph[2][2][13];
   //b = paragraph[2][2];
   //c = paragraph[2];
   //d = paragraph;

}

unsigned int get_total_word_count(void)
{
    if (is_empty)
    {
        return 0;
    }

    if (recent_document != NULL)
    {
        int sum = 0;
        int i;
        for (i = 0; i < total_sentence_count_int; i++)
        {
            sum += total_word_count[i];
        }
        return (unsigned int)sum;
    }
    else {
        return 0;
    }
}

unsigned int get_total_sentence_count(void)
{
    if (is_empty)
    {
        return 0;
    }
    return (unsigned int)total_sentence_count_int;
}

unsigned int get_total_paragraph_count(void)
{
    if (is_empty)
    {
        return 0;
    }
    return (unsigned int)total_paragraph_count;
}

const char*** get_paragraph_or_null(const unsigned int paragraph_index)
{
    int buf_count = 0;
    char buf[128][32] = { 0, };
    char*** buf_malloc;

    if (paragraph_index >= (unsigned int)total_paragraph_count)
    {
        return NULL;
    }

    paragraph_index_store = paragraph_index;

    buf_malloc = *(paragraph + paragraph_index);


    return (const char***)buf_malloc;
}

unsigned int get_paragraph_word_count(const char*** paragraph)
{
    unsigned int count = 0;
    int checker = 0;
    int total_sentence_move_count = 0;

    {
        int i;
        for (i = 0; i < paragraph_index_store; i++)
        {
            total_sentence_move_count += total_sentence_count[i];
        }
    }

    {
        int i;
        int j;
        for (i = 0; i < total_sentence_count[paragraph_index_store]; i++)
        {
            if (paragraph_index_store - 1 < 0)
            {
                checker = 0;
            }
            else {
                checker = total_sentence_move_count;
            }

            for (j = 0; j < total_word_count[checker + i]; j++)
            {
                /*printf("%s ", paragraph[i][j]);*/
                count++;
            }
            /*printf("\n");*/
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
    int buf_count = 0;
    char buf[128][32] = { 0, };
    char** buf_malloc;

    int total_sentence_move_count = 0;

    int total_word_move_count = 0;
    int word_count = 0;

    /* paragraph_index check */
    if (paragraph_index >= (unsigned int)total_paragraph_count)
    {
        return NULL;
    }

    /* sentence_index check */
    {
        int count = 0;
        if ((unsigned int)total_sentence_count[paragraph_index] <= sentence_index)
        {
            return NULL;
        }
    }


    paragraph_index_store = paragraph_index;
    sentence_index_store = sentence_index;

    buf_malloc = *(*(paragraph + paragraph_index) + sentence_index);

    {
        unsigned int i;
        for (i = 0; i < paragraph_index; i++)
        {
            total_sentence_move_count += total_sentence_count[i];
        }
    }

    word_count = total_word_count[total_sentence_move_count + sentence_index];


    return (const char**)buf_malloc;
}

unsigned int get_sentence_word_count(const char** sentence)
{
    unsigned int count = 0;
    int i;
    int total_sentence_move_count = 0;

    {
        int i;
        for (i = 0; i < paragraph_index_store; i++)
        {
            total_sentence_move_count += total_sentence_count[i];
        }
    }

    for (i = 0; i < total_word_count[total_sentence_move_count + sentence_index_store]; i++)
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

    FILE* fp2;

    if (is_empty)
    {
        return FALSE;
    }

    fp2 = fopen(filename, "w");
    if (fp2 == NULL)
    {
        return FALSE;
    }


    if (total_paragraph_count == 0)
    {
        if (fclose(fp2) == EOF)
        {
            return FALSE;
        }
        return FALSE;
    }

    {
        int i;
        int j;
        int k;
        int word_count = 0;
        for (i = 0; i < total_paragraph_count; i++)
        {
            fprintf(fp2, "%s %d%c\n", param_str, param_count, delim);
            for (j = 0; j < total_sentence_count[i]; j++)
            {
                fprintf(fp2, "    %s %d%c\n", sentence_str, sentence_count, delim);
                for (k = 0; k < total_word_count[word_count]; k++)
                {
                    fprintf(fp2, "        %s\n", paragraph[i][j][k]);
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
