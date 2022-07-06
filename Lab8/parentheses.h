#ifndef PARENTHESES_H
#define PARENTHESES_H

//#define _CRT_SECURE_NO_WARNINGS

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <string.h>

typedef struct {
    size_t opening_index;
    size_t closing_index;
} parenthesis_t;

typedef struct {
    size_t start_index;
    parenthesis_t* parentheses;
    size_t max_size;
} ringbuffer_t;

size_t find_matching_parentheses(ringbuffer_t* ringbuffer, const char* str);

#endif /* PARENTHESES_H */
