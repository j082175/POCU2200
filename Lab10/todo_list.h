#ifndef TODO_LIST_H
#define TODO_LIST_H

//#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

typedef struct todo_list todo_list_t;

typedef struct list {
	int priority;
	char* task;
} list_t;

typedef struct todo_list {
	// Make your own members
	todo_list_t* pointer;
	int size;
	int length;
	list_t* list;
} todo_list_t;

todo_list_t init_todo_list(size_t max_size);

void finalize_todo_list(todo_list_t* todo_list);

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task);

bool complete_todo(todo_list_t* todo_list);

const char* peek_or_null(const todo_list_t* todo_list);

size_t get_count(const todo_list_t* todo_list);

bool is_empty(const todo_list_t* todo_list);

#endif /* TODO_LIST_H */
