#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define ABS(x) (((x) < 0) ? (-(x)) : ((x)))

#define RANGE(curr, min, max)\
        for (((curr) = min); ((curr) <= max); (curr++))\


#define RANGE_DESC(curr, max, min)\
        for (((curr) = max); ((curr) >= min); (curr--))\


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
