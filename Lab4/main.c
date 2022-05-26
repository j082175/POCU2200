#include <stdio.h>
#include <assert.h>
#include "my_string.h"

int main() {
    char testchar[] = "zazazzaaz";
    char str[] = "zazz";
    assert(index_of(testchar, str) == 2);


}
