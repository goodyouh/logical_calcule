#include <stdlib.h>
#include "logical.h"

static int calculus(logical_data* pdata);

static int calculus_v(logical_data_v* pdata)
{
        return pdata->value;
}

static int calculus_next(logical_data_next* pdata)
{
        // int a = calculus(pdata->pnext);
        return calculus(pdata->pnext) ^ pdata->oprate;
}

static int calculus_opt(logical_data_opt* pdata)
{
        switch (pdata->type){
                case 0: return calculus(pdata->pleft) == 0 ? 0 : calculus(pdata->pright);
                case 1: return calculus(pdata->pleft) == 1 ? 1 : calculus(pdata->pright);
                case 2: return calculus(pdata->pleft) ^ calculus(pdata->pright);
                default:return 0;
        }
}

static int calculus(logical_data* pdata)
{
        if (pdata == NULL) {
                return 0;
        }
        switch (pdata->type){
                case 1: return calculus_v(&pdata->data.value);
                case 2: return calculus_next(&pdata->data.next);
                case 3: return calculus_opt(&pdata->data.opt);
                default:return 0;
        }
}



static logical_data* create_data(int type)
{
        logical_data*           pdata = malloc(sizeof(logical_data));
        if (pdata == NULL) {
                return NULL;
        }
        pdata->type = type;
        return pdata;
}

static logical_data* create_data_v(int value)
{
        logical_data*         pdata = create_data(1);
        if (pdata == NULL) {
                return NULL;
        }
        pdata->data.value.value = value;
        return pdata;
}

static logical_data* create_data_next(int oprate, logical_data* pnext)
{
        logical_data*         pdata = create_data(2);
        if (pdata == NULL) {
                return NULL;
        }
        pdata->data.next.oprate = oprate;
        pdata->data.next.pnext = pnext;
        return pdata;
}

static logical_data* create_data_opt(int type, logical_data* pleft, logical_data* pright)
{
        logical_data*         pdata = create_data(3);
        if (pdata == NULL) {
                return NULL;
        }
        pdata->data.opt.type = type;
        pdata->data.opt.pleft = pleft;
        pdata->data.opt.pright = pright;
        return pdata;
}

static logical_data* create_data_and(logical_data* pleft, logical_data* pright)
{
        return create_data_opt(0, pleft, pright);
}

static logical_data* create_data_or(logical_data* pleft, logical_data* pright)
{
        return create_data_opt(1, pleft, pright);
}

static logical_data* create_data_xor(logical_data* pleft, logical_data* pright)
{
        return create_data_opt(2, pleft, pright);
}



static logical_data* parse(char** pp);

static void skip_space(char** pp) {
        while (**pp == ' ') {
                (*pp)++;
        }
}

/*
解析一个值  如 1 0
且返回的pp指向值的最后一个字符
*/
static logical_data* parse_value(char** pp)
{
        return create_data_v(**pp - '0');
}

/*
解析一个子表达式
如1   !1  (0)  !(0&1)
且返回的pp指向当前子表达式的最后一个字符
*/
static logical_data* parse_next(char** pp)
{

        skip_space(pp);
        int opt = 0;
        if (**pp == '!') {
                opt = 1;
                (*pp)++;
        }
        skip_space(pp);
        if (**pp == '(') {
                (*pp)++;
                return create_data_next(opt, parse(pp));;
        }
        else {
                return parse_value(pp);
        }
}

/*
解析一个层级的表达式  如 a&b|c^d
且返回的pp指向当前子表达式的下一个字符
*/
static logical_data* parse(char** pp)
{
        logical_data*           pdata = NULL;
        char*                   pcur = *pp;

        pdata = parse_next(&pcur);
        ++pcur;
        while (*pcur && *pcur != ')') {
                switch (*pcur)
                {
                case '&':
                        ++pcur;
                        pdata = create_data_and(pdata, parse_next(&pcur));
                        break;
                case '|':
                        ++pcur;
                        pdata = create_data_or(pdata, parse_next(&pcur));
                        break;
                case '^':
                        ++pcur;
                        pdata = create_data_xor(pdata, parse_next(&pcur));
                        break;
                }
                ++pcur;
        }
        *pp = pcur;
        return pdata;
}




int logical_calculus(logical_data* pdata){
        return calculus(pdata);
}
logical_data* str2logical(char str[]) {
        return parse(&str);
}
