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
/*  DESCRIPTION           :  Produce a truth table                  */
/********************************************************************/

/*
 * Revision log:
 *
 * Created by SongGuantao,2013/03/31
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

/* Use the postfix expression to get Truth table */
void testStatement(char testString[],int length,int symbles);
/* Get the postfix expression */
int topostfix(char a[],char b[]);

char table[256]={0};  //Symble Map table, we can deal a-z and A-Z
char symbol[200]={0};
char data[20];        //出现的字符个数


int main()
{
    int symbles;
    char input[200]={0};
    char postfix[200]={0};
    /**********************************************************************/
    /*  Type into such a|b&!c statements,only | & ! ( ) are the permitted */
    /**********************************************************************/
    printf("Type into such a|b&!c statements,only | & ! ( ) are the permitted\n");
    while(scanf("%s",input)!=EOF)
    {
        /*  Init the Map table value   */
        memset(table,0,256);
        /*  Change the input into postfix expression  */
        symbles = topostfix(input,postfix);
        /* symbles is the number of symble that appeared in the expression*/
        if(symbles<0)
        {
            printf("Input illegal!\n");
            continue;
        }
        //printf("%s\n",postfix);
        testStatement(postfix,strlen(postfix),symbles);
    }
    printf("Hello world!\n");
    return 0;
}

/* Use the postfix expression to get Truth table */
void testStatement(char testString[],int length,int symbles)
{
    Mystack result;
    int i,t,state=(1<<symbles)-1;
    int mask = 0;
    char sign_temp[2];
    mask = mask|state; //Get the mask of the state

    initStack(&result,200);
    for(i=0;i<symbles;i++)
    {
        printf("%c ",data[i]);
    }
    printf("result\n");
    /*  Check the value from 0x0000 to 0x1111 */
    while(state>=0)
    {
        t=0;
        /* Display the origin data */
        for(i=symbles-1;i>=0;i--)
        {
            table[(int)data[symbles-i-1]]=((state&mask)>>(i))&0x00000001;
            printf("%d ",table[(int)data[symbles-i-1]]);
        }
        while(testString[t])
        {
            switch(testString[t])
            {
                /*
                 * If we find a '|' we need to pop the top two data and get their disjunction value
                 * then push it back
                */
                case'|': pop(&result,&sign_temp[0]);
                         pop(&result,&sign_temp[1]);
                         push(&result,sign_temp[0]|sign_temp[1]);
                         break;
                /* deal with the conjunction value */
                case'&': pop(&result,&sign_temp[0]);
                         pop(&result,&sign_temp[1]);
                         push(&result,sign_temp[0]&sign_temp[1]);
                         break;
                /* get the negation value*/
                case'!': pop(&result,&sign_temp[0]);
                         push(&result,!sign_temp[0]);
                         break;
                /* push the symble's value into the stack */
                default: push(&result,table[(int)testString[t]]);
                         break;
            }
            t++;
        }
        /* Get the final value from the top */
        pop(&result,&sign_temp[0]);
        printf("%3d\n",sign_temp[0]);
        state--;
    }
    stackRelease(&result);
}

/*  Change the input into postfix expression a for input,b for output */
int topostfix(char a[],char b[])
{
    int i=0,k=0;
    int flag=0;
    int symbleNum=0;
    char sign_temp;
    Mystack sign;
    Mystack symble;
    /* A stack for the sign | & ! */
    initStack(&sign,200);
    /* A stack for the symble a-z */
    initStack(&symble,200);

    /* Set symbles priority level the larger the higher */
    table['|'] = 1;
    table['&'] = 2;
    table['!'] = 3;

    while(a[i])
    {
        if(!(a[i]=='('||a[i]==')'||a[i]=='|'||a[i]=='&'||a[i]=='!'||(a[i]>='a'&&a[i]<='z')||(a[i]>='A'&&a[i]<='Z')))
        {
            printf("\nThere is an illeagle character at %d\n",i);
            return -1;
        }
        switch(a[i])
        {
            case'(':flag++;
                    push(&sign,a[i]);
                    break;
            /* find a right bracket pop all the data until meet a left bracket */
            case')':if(flag>0)
                    {
                        flag--;
                        pop(&sign,&sign_temp);
                        printf("%c",sign_temp);
                        b[k++]=sign_temp;
                        //strcat(b,sign_temp);
                        while(getTop(&sign)!='(')//所有符号出栈 直到碰到'('
                        {
                            pop(&sign,&sign_temp);
                            if(sign_temp!='(')
                            {
                                printf("%c",sign_temp);
                                b[k++]=sign_temp;
                            }

                        }
                        while(getTop(&sign)!='|'&&getTop(&sign)!=-1)//所有符号出栈 直到碰到最低优先级的符号'|'
                        {
                            pop(&sign,&sign_temp);
                            if(sign_temp!='(')
                            {
                                printf("%c",sign_temp);
                                b[k++]=sign_temp;
                            }
                        }
                    }
                    else
                    {
                        printf("\nMissing a \'(\' or the bracket is not matching\n");
                        return -1;
                    }
                    break;
            /* Compare the stack top value and the current value if the top is bigger then pop it*/
            case'|':if(table[(int)getTop(&sign)]>table[(int)a[i]])
                    {
                        pop(&sign,&sign_temp);
                        printf("%c",sign_temp);
                        b[k++]=sign_temp;
                        push(&sign,a[i]);
                    }
                    else
                    {
                        push(&sign,a[i]);
                    }
                    break;
            case'&':if(table[(int)getTop(&sign)]>table[(int)a[i]])
                    {
                        pop(&sign,&sign_temp);
                        printf("%c",sign_temp);
                        b[k++]=sign_temp;
                        push(&sign,a[i]);
                    }
                    else
                    {
                        push(&sign,a[i]);
                    }
                    break;
            case'!':push(&sign,a[i]);
                    //printf("%c",a[i]);
                    break;
            default:printf("%c",a[i]);
                    if(table[(int)a[i]]==0)
                    {
                       table[(int)a[i]] = 1;
                       //symbleNum|=a[i]-'a';   //记录出现的字符
                       data[symbleNum++] = a[i];
                    }
                    b[k++]=a[i];
                    push(&symble,a[i]);
                    break;
        }
        i++;
    }
    while(getTop(&sign)!=-1)//所有符号出栈 没有符号了
    {

        pop(&sign,&sign_temp);
        if(sign_temp!='(')
        {
            printf("%c",sign_temp);
            b[k++]=sign_temp;
        }
    }
    if(flag>0)
    {
        printf("\nMissing some ')'!\n");
        return -1;
    }
    b[k] = '\0';
    printf("\n");
    stackRelease(&sign);
    stackRelease(&symble);
    return symbleNum;
}




