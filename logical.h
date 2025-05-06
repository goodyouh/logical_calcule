#pragma once

typedef struct logical_data             logical_data;
typedef struct logical_data_v           logical_data_v;
typedef struct logical_data_next        logical_data_next;
typedef struct logical_data_opt         logical_data_opt;

struct logical_data_v {
        int                             value;
};

struct logical_data_next {
        int                             oprate;  // 0:无  1:!
        logical_data*                   pnext;
};

struct logical_data_opt {
        int                             type;   // 0:&  1:|   2:^
        logical_data*                   pleft;
        logical_data*                   pright;
};

struct logical_data
{
        int                             type;   // 1:单个值:a  2:单个表达式 !(a&b)  3:a&b  a|b  a^b
        union {
                logical_data_v          value;  // 1:单个值:a
                logical_data_next       next;   // 2:下一级表达式，可以为！
                logical_data_opt        opt;    // 3:&|^表达式
        }data;
};


int logical_calculus(logical_data* pdata);
logical_data* str2logical(char str[]);
void loggical_destroy(logical_data* pdata);
