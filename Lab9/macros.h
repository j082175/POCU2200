#ifndef MACROS_H
#define MACROS_H

#undef MAX
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

#undef MIN
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#undef ABS
#define ABS(x) (((x) < 0) ? (-(x)) : ((x)))

//#define RANGE(curr, min, max)\
//        for (((curr) = (min)); ((curr) <= (max)); (curr++))\
//
//
//#define RANGE_DESC(curr, max, min)\
//        for (((curr) = (max)); ((curr) >= (min)); (curr--))\

#undef RANGE
#define RANGE(curr, min, max)\
        (curr) = (min);\
        (curr--);\
        while ((curr++) < (max))\


#undef RANGE_DESC
#define RANGE_DESC(curr, max, min)\
        (curr) = (max);\
        (curr++);\
        while ((curr--) > (min))\


#undef SET
#define SET(ary, start, count, value)\
        do\
        {\
            {\
                unsigned i;\
                for (i = (start); i < ((count) + (start)); i++) {\
                (ary[i]) = (value);\
            }\
            }\
        } while (0)\

#endif /* MACROS_H */
