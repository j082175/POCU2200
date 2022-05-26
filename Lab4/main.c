#include <stdio.h>
#include <assert.h>
#include "my_string.h"

int main() {
    char str[] = "!!!!!Oh !!!!happy!! !!day! My lovely day!";
    printf("%s\n", tokenize(str, " !"));
    printf("%s\n", tokenize(NULL, " !"));
    printf("%s\n", tokenize(NULL, " !"));
    printf("%s\n", tokenize(NULL, " !"));
    printf("%s\n", tokenize(NULL, " !"));
    printf("%s\n", tokenize(NULL, " !"));
    printf("%s\n", tokenize(NULL, " !"));
    printf("%s\n", tokenize(NULL, " !"));



    //tokenize(str, " !#@"); /* &str[0]을 반환. 토큰은 "Oh" */
    //tokenize(NULL, " !#@"); /* &str[3]을 반환. 토큰은 "happy" */
    //tokenize(NULL, " !#@"); /* &str[9]을 반환. 토큰은 "day" */
    //tokenize(NULL, " !#@"); /* &str[14]을 반환. 토큰은 "My" */

}
