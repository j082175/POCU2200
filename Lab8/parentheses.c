#include "parentheses.h"

int MAX;

int front = -1;
int rear = -1;
int* queue;

int IsEmpty(void) {
	if (front == rear)//front와 rear가 같으면 큐는 비어있는 상태 
		return TRUE;
	else return FALSE;
}
int IsFull(void) {
	int tmp = (rear + 1) % MAX; //원형 큐에서 rear+1을 MAX로 나눈 나머지값이
	if (tmp == front)//front와 같으면 큐는 가득차 있는 상태 
		return TRUE;
	else
		return FALSE;
}
void addq(int value) {
	if (IsFull())
		printf("Queue is Full.\n");
	else {
		rear = (rear + 1) % MAX;
		queue[rear] = value;
	}

}
int deleteq() {
	if (IsEmpty())
		printf("Queue is Empty.\n");
	else {
		front = (front + 1) % MAX;
		return queue[front];
	}
}



size_t find_matching_parentheses(ringbuffer_t* ringbuffer, const char* str)
{
	const char outter[] = { '}', ')', ']', '>' };
	const char inner[] = { '{',  '(',  '[',  '<' };
	int* arr1;
	int* arr2;

	const size_t MAX_SIZE = ringbuffer->max_size;
	const size_t STR_LENGTH = strlen(str);
	size_t count = 0;
	size_t total_length = 0;
	char* str_buf = (char*)malloc(sizeof(char) * strlen(str) + 1);
	if (str_buf == NULL) {
		assert(FALSE);
		return 0;
	}

	arr1 = (int*)malloc(sizeof(int) * STR_LENGTH);
	arr2 = (int*)malloc(sizeof(int) * STR_LENGTH);


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

								arr1[count] = k;
								arr2[count] = i;

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
			ringbuffer->parentheses[i].opening_index = arr1[i + ringbuffer->start_index];
			ringbuffer->parentheses[i].closing_index = arr2[i + ringbuffer->start_index];
		}
	}


	free(arr1);
	free(arr2);

	if (str_buf != NULL) {
		free(str_buf);
	}
	str_buf = NULL;

	return total_length;
}
