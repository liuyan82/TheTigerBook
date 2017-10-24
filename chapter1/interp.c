#include <stdio.h>
#include "util.h"
#include "slp.h"
#include "interp.h"
#include "table.h"

int interpIDexp(string id, Table_ table);
int interpOPExp(A_exp left, A_exp right, A_binop op, Table_ table);
int interpEseqExp(A_stm stm, A_exp exp, Table_ table);
int interpExp(A_exp exp, Table_ table);
Table_ interpCompoundStm(A_stm stm1, A_stm stm2, Table_ table);
Table_ interpAssignStm(string id, A_exp exp, Table_ table);
Table_ interpPrintStm(A_expList exps, Table_ table);
Table_ interpStm(A_stm stm, Table_ table);


int interpIDexp(string id, Table_ table)
{
    return lookup(id, table);
}

int interpNumberExp(int num)
{
    return num;
}

int interpOPExp(A_exp left, A_exp right, A_binop op, Table_ table)
{
    switch(op)
    {
        case A_plus:
            return interpExp(left, table) + interpExp(right, table);
            break;
        case A_minus:
            return interpExp(left, table) - interpExp(right, table);
            break;
        case A_times:
            return interpExp(left, table) * interpExp(right, table);
            break;
        case A_div:
            return interpExp(left, table) / interpExp(right, table);
            break;
    }
}

int interpEseqExp(A_stm stm, A_exp exp, Table_ table)
{
    interpStm(stm, table);
    return interpExp(exp, table);
}

int interpExp(A_exp exp, Table_ table)
{
    switch(exp->kind)
    {
        case A_idExp:
            return interpIDexp(exp->u.id, table);
            break;
        case A_numExp:
            return interpNumberExp(exp->u.num);
            break;
        case A_opExp:
            return interpOPExp(exp->u.op.left, exp->u.op.right,
                    exp->u.op.oper, table);
            break;
        case A_eseqExp:
            return interpEseqExp(exp->u.eseq.stm, exp->u.eseq.exp, table);
            break;
    }
    return 0;
}

Table_ interpCompoundStm(A_stm stm1, A_stm stm2, Table_ table)
{
    return interpStm(stm2, 
        interpStm(stm1, table));
}

Table_ interpAssignStm(string id, A_exp exp, Table_ table)
{
    return Table(id, interpExp(exp, table), table);
}

Table_ interpPrintStm(A_expList exps, Table_ table)
{
    for (A_expList head = exps; 
            head != NULL; 
            head = head->u.pair.tail)
    {
       printf("%d ", 
               head->kind == A_lastExpList ?
                 interpExp(head->u.last, table) :
                 interpExp(head->u.pair.head, table)); 
       if (head->kind == A_lastExpList)
           break;
    }
    printf("\n");
}

Table_ interpStm(A_stm stm, Table_ table)
{
    switch(stm->kind)
    {
        case A_compoundStm:
            return interpCompoundStm(stm->u.compound.stm1, stm->u.compound.stm2, table);
           break;
        case A_assignStm:
            return interpAssignStm(stm->u.assign.id, stm->u.assign.exp, table);
            break;
        case A_printStm:
            return interpPrintStm(stm->u.print.exps, table);
            break;
    }
    return NULL;
}


void interp(A_stm stm)
{
    interpStm(stm, NULL);
}

