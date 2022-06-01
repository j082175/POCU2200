#ifndef RECEIPTER_H
#define RECEIPTER_H
#define _CRT_SECURE_NO_WARNINGS
#define TRUE (1)
#define FALSE (0)
#define ITEM_LENGTH 10
#define MAX_LENGTH 50
#define MAX_NAME_LENGTH 33
#define MAX_PRICE_LENGTH 17

#include <time.h>
#include <stdio.h>

int add_item(const char* name, double price);

void set_tip(double tip);

void set_message(const char* message);

int print_receipt(const char* filename, time_t timestamp);

#endif /* RECEIPTER_H */