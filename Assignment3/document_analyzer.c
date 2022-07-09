#include "document_analyzer.h"
/* 단락 : 개행문자로 구분
   문장 : . ? ! 3개의 문자로 구분
   단어 : 띄어쓰기 , 문자로 구분
   단락과 단락사이엔 개행이 존재
   각각의 간격은 4개 */


#define DATA_MAX_SIZE 40960
static int s_is_empty = FALSE;
static int s_paragraph_index_store;
static int s_sentence_index_store;

static int s_wcount = 0;
static int s_scount = 0;
static int s_pcount = 0;


static const char* recent_document = NULL;

static int s_total_paragraph_count = 0;

static int* s_total_sentence_count = NULL;
static int* s_total_word_count = NULL;

static int s_total_sentence_count_int = 0;

static int s_is_paragraph;
static int s_is_word;
static int s_check;

static int s_word_count;

static char s_paragraph_division = '\n';
static char s_sentence_division[] = { '.', '?', '!' };
static char s_word_division[] = { ' ', ',' , '.', '?', '!' };


static char**** s_paragraph = NULL;


static char** s_word_store = NULL;
static char*** s_sentence_store = NULL;
static char**** s_paragraph_store = NULL;

void clear(void)
{
    s_total_paragraph_count = 0;
    s_total_sentence_count = 0;
    s_total_sentence_count_int = 0;
    s_total_word_count = 0;

    s_word_count = 0;
    s_wcount = 0;
    s_scount = 0;
    s_pcount = 0;

    s_paragraph_index_store = 0;
    s_sentence_index_store = 0;
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
    if (fp == NULL) {
        return FALSE;
    }



    data = (char*)malloc(sizeof(char) * DATA_MAX_SIZE);
    memset(data, 0, DATA_MAX_SIZE);

    s_total_sentence_count = (int*)malloc(sizeof(int) * DATA_MAX_SIZE / 2);
    s_total_word_count = (int*)malloc(sizeof(int) * DATA_MAX_SIZE / 2);
    memset(s_total_sentence_count, 0, DATA_MAX_SIZE / 2);
    memset(s_total_word_count, 0, DATA_MAX_SIZE / 2);

    s_word_store = (char**)malloc(sizeof(char*) * DATA_MAX_SIZE);
    s_sentence_store = (char***)malloc(sizeof(char**) * DATA_MAX_SIZE / 2);
    s_paragraph_store = (char****)malloc(sizeof(char***) * DATA_MAX_SIZE / 3);
    memset(s_word_store, 0, DATA_MAX_SIZE);
    memset(s_sentence_store, 0, DATA_MAX_SIZE / 2);
    memset(s_paragraph_store, 0, DATA_MAX_SIZE / 3);


    /* 총 단락 개수 구하기 */
    while (data[i] != EOF) {
        data[i] = fgetc(fp);

        if (data[0] == EOF) {
            s_is_empty = TRUE;
            goto end;
        }

        s_is_empty = FALSE;

        if (data[i] == EOF) {
            if (data[i - 1] != '\n') {
                s_total_paragraph_count++;
            }
            data[i] = '\0';
            break;
        }

        if (data[i] == s_paragraph_division && !s_is_paragraph) {
            s_total_paragraph_count++;
            s_is_paragraph = TRUE;
        }

        if (data[i] != s_paragraph_division) {
            s_is_paragraph = FALSE;
        }

        {
            int j;
            for (j = 0; j < 3; j++) {
                if (data[i] == s_sentence_division[j]) {
                    s_total_sentence_count[s_total_paragraph_count]++;
                    s_total_sentence_count_int++;
                    s_check = TRUE;
                    break;
                    //word_count++;
                }
            }
        }

        {
            int j;
            for (j = 0; j < 5; j++) {
                if (data[i] == s_word_division[j] && !s_is_word) {

                    s_total_word_count[s_word_count]++;
                    if (s_check) {
                        s_word_count++;
                        s_check = FALSE;
                    }
                    s_is_word = TRUE;
                    break;
                } else {
                    s_is_word = FALSE;
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
        if (data_backup == NULL) {
            assert(FALSE);
        }
        data_backup[0] = (char*)malloc(sizeof(char) * DATA_MAX_SIZE * dsize);
        for (i = 1; i < DATA_MAX_SIZE; i++) {
            data_backup[i] = data_backup[i - 1] + dsize;
        }
    }

    /* word tokenizer */
    {
        int count = 0;
        char* ptr;
        char* a;
        ptr = data;
        a = strtok(ptr, " ,.!?\n");
        if (a == NULL) {
            assert(FALSE);
        }
        strcpy(data_backup[count], ptr);
        count++;
        while (TRUE) {
            ptr = strtok(NULL, " ,.!?\n");
            if (ptr == NULL) {
                break;
            }
            strcpy(data_backup[count], ptr);
            count++;
        }

    }
    /**/

    {
        int i;
        int j;
        int k;
        int count = 0;
        int word_count = 0;
        doc1 = (char****)malloc(sizeof(char***) * s_total_paragraph_count);
        for (i = 0; i < s_total_paragraph_count; i++) {
            paragraph1 = (char***)malloc(sizeof(char**) * s_total_sentence_count[i]);
            for (j = 0; j < s_total_sentence_count[i]; j++) {
                sentence1 = (char**)malloc(sizeof(char*) * s_total_word_count[word_count]);
                for (k = 0; k < s_total_word_count[word_count]; k++) {
                    word1 = (char*)malloc(sizeof(char) * strlen(data_backup[count]) + 1);/* 메모리 문제 */
                    if (word1 == NULL) {
                        assert(FALSE);
                    }
                    strcpy(word1, data_backup[count++]);
                    s_word_store[s_wcount++] = word1;
                    *sentence1 = word1;
                    sentence1++;
                }
                /*sentence1 = NULL;
                sentence1++;*/
                s_sentence_store[s_scount++] = sentence1 - s_total_word_count[word_count];

                *paragraph1 = sentence1 - s_total_word_count[word_count];
                paragraph1++;
                word_count++;
            }
            /*paragraph1 = NULL;
            paragraph1++;*/
            s_paragraph_store[s_pcount++] = paragraph1 - s_total_sentence_count[i];

            *doc1 = paragraph1 - s_total_sentence_count[i];
            doc1++;
        }
        /**doc1 = NULL;
        doc1++;*/

        doc1 = doc1 - s_total_paragraph_count;
    }

    s_paragraph = doc1;
end:

    if (data != NULL) {
        free(data);
        data = NULL;
    }

    if (data_backup != NULL) {
        free(data_backup[0]);
        free(data_backup);
        data_backup = NULL;
    }

    if (fclose(fp) == EOF) {
        return FALSE;
    }

    return TRUE;
}

void dispose(void)
{
    /*동적으로 할당된 메모리를 모두 해제*/


    if (s_total_word_count != NULL) {
        free(s_total_word_count);
        s_total_word_count = NULL;
    }

    if (s_total_sentence_count != NULL) {
        free(s_total_sentence_count);
        s_total_sentence_count = NULL;
    }


    if (s_paragraph != NULL) {
        free(s_paragraph);
        s_paragraph = NULL;

    }

    if (s_word_store != NULL) {
        {
            int i;
            for (i = 0; i < s_wcount; i++) {
                free(s_word_store[i]);
                s_word_store[i] = NULL;
            }
        }
        free(s_word_store);
        s_word_store = NULL;
    }

    if (s_sentence_store != NULL) {
        {
            int i;
            for (i = 0; i < s_scount; i++) {
                free(s_sentence_store[i]);
                s_sentence_store[i] = NULL;
            }
        }
        free(s_sentence_store);
        s_sentence_store = NULL;
    }

    if (s_paragraph_store != NULL) {
        {
            int i;
            for (i = 0; i < s_pcount; i++) {
                free(s_paragraph_store[i]);
                s_paragraph_store[i] = NULL;
            }
        }
        free(s_paragraph_store);
        s_paragraph_store = NULL;
    }

    clear();
}

unsigned int get_total_word_count(void)
{
    int sum = 0;
    int i;
    for (i = 0; i < s_total_sentence_count_int; i++) {
        sum += s_total_word_count[i];
    }
    return (unsigned int)sum;
}

unsigned int get_total_sentence_count(void)
{
    return (unsigned int)s_total_sentence_count_int;
}

unsigned int get_total_paragraph_count(void)
{
    return (unsigned int)s_total_paragraph_count;
}

const char*** get_paragraph_or_null(const unsigned int paragraph_index)
{
    if (s_paragraph == NULL) {
        return NULL;
    }
    if (paragraph_index >= (const unsigned int)s_total_paragraph_count) {
        return NULL;
    }

    s_paragraph_index_store = paragraph_index;

    return (const char***)s_paragraph[paragraph_index];
}

unsigned int get_paragraph_word_count(const char*** paragraph)
{
    unsigned int count = 0;
    unsigned int sentence_sum = 0;

    {
        size_t i;
        for (i = 0; i < s_paragraph_index_store; i++) {
            sentence_sum += s_total_sentence_count[i];
        }
    }

    {
        size_t i;
        for (i = 0; i < s_total_sentence_count[s_paragraph_index_store]; i++) {
            count += s_total_word_count[i + sentence_sum];
        }
    }

    return count;
}

unsigned int get_paragraph_sentence_count(const char*** paragraph)
{
    return (unsigned int)s_total_sentence_count[s_paragraph_index_store];
}

const char** get_sentence_or_null(const unsigned int paragraph_index, const unsigned int sentence_index)
{
    if (paragraph_index >= (unsigned)s_total_paragraph_count) {
        return NULL;
    }

    if (sentence_index >= s_total_sentence_count[paragraph_index]) {
        return NULL;
    }

    s_paragraph_index_store = paragraph_index;
    s_sentence_index_store = sentence_index;

    return (const char**)s_paragraph[paragraph_index][sentence_index];
}

unsigned int get_sentence_word_count(const char** sentence)
{
    unsigned int count = 0;
    unsigned int sentence_sum = 0;

    {
        size_t i;
        for (i = 0; i < s_paragraph_index_store; i++) {
            sentence_sum += s_total_sentence_count[i];
        }
    }

    count += s_total_word_count[sentence_sum + s_sentence_index_store];

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

    if (s_is_empty) {
        return FALSE;
    }

    if (recent_document == NULL) {
        return FALSE;
    }

    if (s_total_paragraph_count == 0) {
        return FALSE;
    }

    fp2 = fopen(filename, "w");
    if (fp2 == NULL) {
        return FALSE;
    }

    {
        int i;
        int j;
        int k;
        int word_count = 0;
        int count = 0;
        for (i = 0; i < s_total_paragraph_count; i++) {
            fprintf(fp2, "%s %d%c\n", param_str, param_count, delim);
            for (j = 0; j < s_total_sentence_count[i]; j++) {
                fprintf(fp2, "    %s %d%c\n", sentence_str, sentence_count, delim);
                for (k = 0; k < s_total_word_count[word_count]; k++) {
                    fprintf(fp2, "        %s\n", s_word_store[count]);
                    count++;
                }
                word_count++;
                sentence_count++;
            }
            param_count++;
            sentence_count = 0;
            if (i == s_total_paragraph_count - 1) {
                break;
            }
            fputc('\n', fp2);
        }
    }


    if (fclose(fp2) == EOF) {
        return FALSE;
    }
    return TRUE;
}
