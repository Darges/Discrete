/********************************************************************/
/* Copyright (C) SongGuantao-USTC, 2013                             */
/*                                                                  */
/*  FILE NAME             :  stack.h                                */
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

#ifndef STACK_H
#define STACK_H

typedef struct stack{
    char* symbol;
    int   size;
    int   top;
}Mystack;


void initStack(Mystack* stackInit,int size);
void push(Mystack* stackInit,char target);
void pop(Mystack* stackInit,char* target);
int getTop(Mystack* stackInit);
void stackRelease(Mystack* stackInit);

#endif
