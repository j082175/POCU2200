#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "receipter.h"
#include <assert.h>

int main() {
	time_t now = time(NULL);

	for (int i = 0; i < 10; i++)
	{
		assert(add_item("hoho", 4.44) == TRUE);
	}

	
	print_receipt("test.txt", now);
}
