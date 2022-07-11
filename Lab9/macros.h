#ifndef MACROS_H
#define MACROS_H

#endif

#undef MAX
#define MAX(x, y) (((x) > (y)) ? (x) : (y))


#undef MIN
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#undef ABS
#define ABS(x) (((x) < 0) ? (-(x)) : ((x)))

#undef RANGE
#define RANGE(curr, min, max)\
        for (((curr) = (min)); ((curr) <= (max)); (curr++))\

#undef RANGE_DESC
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
