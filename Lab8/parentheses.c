#include "parentheses.h"

typedef int element;

typedef struct QueueType {
    element* data;
    int front, rear;
}QueueType;

//큐 초기화 
void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

//큐가 비어 있는지 확인
int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

//큐가 가득 찼는지 확인
int is_full(QueueType* q, size_t size) {
    return (q->front == ((q->rear + 1) % size));
}

//큐가 가득 차 있는지 확인 후 삽입 연산
void enqueue(QueueType* q, int data, size_t size) {
    if (is_full(q, size)) {
        printf("Queue is full \n");
    }
    else {
        q->rear = (q->rear + 1) % size;
        q->data[q->rear] = data;
    }
}

//큐가 비어 있는지 확인 후 삭제 연산
element dequeue(QueueType* q, size_t size) {
    if (is_empty(q)) {
        printf("Queue is empty \n");
        exit(1);
    }
    else {
        q->front = (q->front + 1) % size;
        int data = q->data[q->front];
        return data;
    }
}

//큐의 모든 요소 출력
void print_queue(QueueType* q, size_t size) {
    if (is_empty(q)) {
        printf("Empty Queue \n");
    }
    else {
        printf("Queue:");
        if (!is_empty(q)) {
            int i = q->front;
            do {
                i = (i + 1) % size;
                printf(" %d |", q->data[i]);
                if (i == q->rear)
                    break;
            } while (i != q->front);
            printf("\n");
        }
    }
}



size_t find_matching_parentheses(ringbuffer_t* ringbuffer, const char* str)
{
    const char outter[] = { '}', ')', ']', '>' };
    const char inner[] = { '{',  '(',  '[',  '<' };

    int* arr = NULL;
    int* arr2 = NULL;
    const size_t MAX_SIZE = ringbuffer->max_size;
    const size_t STR_LENGTH = strlen(str);
    size_t count = 0;
    size_t total_length = 0;
    char* str_buf = (char*)malloc(sizeof(char) * strlen(str) + 1);
    if (str_buf == NULL) {
        assert(FALSE);
        return 0;
    }


    //for (int i = 0; i < 5; i++) {
    //	enqueue(&q, i);
    //	queue_print(q);
    //}

    //for (int i = 0; i < 5; i++) {
    //	dequeue(&q);
    //	queue_print(q);
    //}

    arr = (int*)malloc(sizeof(int) * MAX_SIZE);
    arr2 = (int*)malloc(sizeof(int) * MAX_SIZE);

    strcpy(str_buf, str);

    memset(ringbuffer->parentheses, 0, MAX_SIZE);
    ringbuffer->start_index = 0;

    while (count < STR_LENGTH / 2) {
        {
            size_t i;
            int j;
            int k;
            for (i = 0; i < STR_LENGTH; i++) {
                for (j = 0; j < 4; j++) {
                    if (str_buf[i] == outter[j]) {
                        for (k = i - 1; k >= 0; k--) {
                            if (str_buf[k] == inner[j]) {
                                str_buf[k] = '?';
                                str_buf[i] = '?';

                                arr[count % MAX_SIZE] = k;
                                arr2[count % MAX_SIZE] = i;

                                if (count / MAX_SIZE) {
                                    ringbuffer->start_index++;
                                }

                                total_length++;
                                goto end;
                            }
                        }
                    }
                }
            }
        }

    end:
        count++;
    }



    {
        int i;
        for (i = 0; i < MAX_SIZE; i++)
        {
            ringbuffer->parentheses[(ringbuffer->start_index + i) % MAX_SIZE].opening_index = arr[(ringbuffer->start_index + i) % MAX_SIZE];
            ringbuffer->parentheses[(ringbuffer->start_index + i) % MAX_SIZE].closing_index = arr2[(ringbuffer->start_index + i) % MAX_SIZE];
        }
    }


    free(arr);

    if (str_buf != NULL) {
        free(str_buf);
    }
    str_buf = NULL;

    return total_length;
}
