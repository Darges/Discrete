/********************************************************************/
/* Copyright (C) SongGuantao-USTC, 2013                             */
/*                                                                  */
/*  FILE NAME             :  stack.c                                */
/*  PRINCIPAL AUTHOR      :  SongGuantao                            */
/*  SUBSYSTEM NAME        :  truth table                            */
/*  MODULE NAME           :  stack                                  */
/*  LANGUAGE              :  C                                      */
/*  TARGET ENVIRONMENT    :  ANY                                    */
/*  DATE OF FIRST RELEASE :  2013/03/31                             */
/*  DESCRIPTION           :  Abstract Interface of stack API        */
/********************************************************************/

/*
 * Revision log:
 *
 * Created by SongGuantao,2013/03/31
 *
 */

#include"stack.h"


/*³õÊ¼»¯¶ÑÕ»*/
void initStack(Mystack* stackInit,int size)
{
    stackInit->size = size;
    stackInit->top = -1;
    stackInit->symbol = (char*)malloc(sizeof(char)*size);
}
/*push data*/
void push(Mystack* stackInit,char target)
{
    if(stackInit->top>stackInit->size)
    {
        printf("Stack Full\n");
        exit(0);
    }
    stackInit->top++;
    stackInit->symbol[stackInit->top] = target;
}
/*pop data*/
void pop(Mystack* stackInit,char* target)
{
    if(stackInit->top==-1)
    {
        printf("Stack Empty\n");
        exit(0);
    }
    *target = stackInit->symbol[stackInit->top];
    stackInit->top--;
}
/*get the top data*/
int getTop(Mystack* stackInit)
{
    if(stackInit->top==-1)
    {
        //printf("Stack Empty\n");
        //exit(0);
        return -1;
    }
    return stackInit->symbol[stackInit->top];
}
/*release the stack*/
void stackRelease(Mystack* stackInit)
{
    free(stackInit->symbol);
}
