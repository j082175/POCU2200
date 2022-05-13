#include "array.h"
#include <stdio.h>

int get_index_of(const int numbers[], const size_t element_count, const int num)
{
    unsigned int i;
    for (i = 0; i < element_count; i++) {
    if (numbers[i] == num) {
        return i;
    }
    }

    return -1;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num)
{
    int i;
    for (i = (int)element_count - 1; i >= 0; i--) {
    if (numbers[i] == num) {
        return i;
    }
    }

    return -1;

}

int get_max_index(const int numbers[], const size_t element_count)
{
    int max_number = numbers[0];
    int count_index = 0;
    size_t i = 0;

    if (element_count == 0) {
    return -1;
    }

    {


    for (i = 1; i < element_count; i++){
        if (max_number < numbers[i]){
        max_number = numbers[i];
        count_index = i;
        }
    }
    }

    return count_index;
}

int get_min_index(const int numbers[], const size_t element_count)
{
    int min_number = numbers[0];
    int count_index = 0;
    size_t i = 0;

    if (element_count == 0) {
    return -1;
    }

    {


    for (i = 1; i < element_count; i++) {
        if (min_number > numbers[i]) {
        min_number = numbers[i];
        count_index = i;
        }
    }
    }

    return count_index;
}

int is_all_positive(const int numbers[], const size_t element_count)
{
    int is_positive = 0;
    size_t i;
    for (i = 0; i < element_count; i++) {
    if (numbers[i] > 0) {
        is_positive = 1;
    }
    else {
        is_positive = 0;
        break;
    }
    }

    return is_positive;
}

int has_even(const int numbers[], const size_t element_count)
{
    int even = 0;
    size_t i;

    for (i = 0; i < element_count; i++) {
    if (numbers[i] % 2 == 0) {
        even = 1;
        break;
    }
    else {
        even = 0;
    }
    }
    return even;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos)
{
    size_t i;

    if (element_count < pos) {
    return 0;
    }

    for (i = element_count; i > pos; i--) {
    numbers[i] = numbers[i - 1];
    numbers[i - 1] = 99999;
    }

    numbers[pos] = num;

    return 1;
}

int remove_at(int numbers[], const size_t element_count, const size_t index)
{
    size_t i;

    if (element_count <= index) {
    return 0;
    }

    for (i = index; i < element_count; i++) {
    numbers[i] = numbers[i + 1];
    }



    return 1;
}
