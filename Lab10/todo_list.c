#include "todo_list.h"

todo_list_t init_todo_list(size_t max_size)
{
    todo_list_t* todo_list = (todo_list_t*)malloc(sizeof(todo_list_t));
    if (todo_list == NULL) {
        assert(false);
    }
    todo_list->list = (list_t*)malloc(sizeof(list_t) * max_size);
    if (todo_list->list == NULL) {
        assert(false);
    }
    for (size_t i = 0; i < max_size; i++) {
        todo_list->list[i].priority = 0;
        todo_list->list[i].task = NULL;
    }
    todo_list->length = 0;
    todo_list->size = max_size;

    todo_list->pointer = todo_list;

    return *todo_list;
}

void finalize_todo_list(todo_list_t* todo_list)
{
    todo_list_t* pointer = todo_list->pointer;

    int size = todo_list->size;

    for (size_t i = 0; i < size; i++) {
        if (todo_list->list[i].task != NULL)
        {
            free(todo_list->list[i].task);
            todo_list->list[i].task = NULL;
        }
    }


    if (todo_list->list != NULL) {
        free(todo_list->list);
        todo_list->list = NULL;
    }
    

    if (pointer != NULL) {
        free(pointer);
    }


}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    /* O(n) */
    int size = todo_list->size;
    int length = todo_list->length;
    if (size == length) {
        return false;
    }
    todo_list->list[length].priority = priority;
    todo_list->list[length].task = (char*)malloc(sizeof(char) * strlen(task) + 1);
    strcpy(todo_list->list[length].task, task);

    todo_list->length++;
    return true;
}

bool complete_todo(todo_list_t* todo_list)
{
    /* O(n) */
    int size = todo_list->size;
    int max_value = 0;
    int index = 0;

    if (todo_list->length == 0) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        if (max_value < todo_list->list[i].priority)
        {
            max_value = todo_list->list[i].priority;
            index = i;
        }
    }

    free(todo_list->list[index].task);
    todo_list->list[index].task = NULL;
    todo_list->list[index].priority = 0;
    todo_list->length--;
    return true;
}

const char* peek_or_null(const todo_list_t* todo_list)
{
    /* O(n) */
    int size = todo_list->size;
    int max_value = 0;
    int index = 0;

    if (todo_list->length == 0) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        if (max_value < todo_list->list[i].priority)
        {
            max_value = todo_list->list[i].priority;
            index = i;
        }
    }

    return todo_list->list[index].task;
}

size_t get_count(const todo_list_t* todo_list)
{
    /* O(1) */
    return (size_t)todo_list->length;
}

bool is_empty(const todo_list_t* todo_list)
{
    /* O(1) */
    if (todo_list->length == 0) {
        return true;
    } else {
        return false;
    }
}
