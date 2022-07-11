#ifndef MACROS_H
#define MACROS_H

#endif


#define MAX(x, y) (((x) > (y)) ? (x) : (y))



#define MIN(x, y) (((x) < (y)) ? (x) : (y))


#define ABS(x) (((x) < 0) ? (-(x)) : ((x)))


#define RANGE(curr, min, max)\
        for (((curr) = (min)); ((curr) <= (max)); (curr++))\


#define RANGE_DESC(curr, max, min)\
        for (((curr) = (max)); ((curr) >= (min)); (curr--))\

#define TEST(i) unsigned i 

#ifndef SET
#define SET(ary, start, count, value)\
    {\
        TEST(i);\
        for (i = (start); i < ((count) + (start)); i++) {\
            (ary[i]) = (value);\
        }\
    }\

void test();

#endif /* MACROS_H */
