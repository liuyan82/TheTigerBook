#include "util.h"
#include "slp.h"
#include "maxarg.h"
#include "prog1.h"
#include <stdio.h>

static int max(int l, int r)
{
    return l > r ? l : r;
}

int numExpInExpList(A_expList extList)
{
    int n = 0;
    A_expList cur = extList;
    while (cur->kind == A_pairExpList)
    {
        cur = cur->u.pair.tail;
        n++;
    }
    return (n + 1);
}

int maxargsInExp(A_exp exp, int maxArgsDiscovered)
{
    switch(exp->kind)
    {
        case A_idExp:
        case A_numExp:
            return maxArgsDiscovered;
        case A_opExp:
            return max(maxargsInExp(exp->u.op.left, maxArgsDiscovered), maxargsInExp(exp->u.op.right, maxArgsDiscovered));
        case A_eseqExp: 
            return max(maxargsInStm(exp->u.eseq.stm, maxArgsDiscovered), maxargsInExp(exp->u.eseq.exp, maxArgsDiscovered));
        default:
            return maxArgsDiscovered;
    }
}

int maxargsInStm(A_stm stm, int maxArgsDiscovered)
{
    switch(stm->kind)
    {
        case A_compoundStm:
            return max(maxargsInStm(stm->u.compound.stm1, maxArgsDiscovered), maxargsInStm(stm->u.compound.stm2, maxArgsDiscovered));
            break;
        case A_assignStm:
            return maxargsInExp(stm->u.assign.exp, maxArgsDiscovered);
            break;
        case A_printStm:
            return max(numExpInExpList(stm->u.print.exps), maxArgsDiscovered);
            break;
    }
    return maxArgsDiscovered;
}

int maxargs(A_stm stm)
{
    return maxargsInStm(stm, 0);
}

