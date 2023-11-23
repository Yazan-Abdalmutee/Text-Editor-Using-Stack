#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node;
typedef struct node *ptr;
typedef ptr stack;

struct node
{
    ptr next;
    char statment[100];
};
void push(stack s,char st [],FILE *out);
stack create_node();
const char* pop(stack s,char last[],FILE *out);
int isempety(stack s);
void print(stack s,FILE *out);
void insert(stack s,char st [],FILE *out);
void deleate(stack l);
void save(FILE *out);
int main()
{
    printf("1. undo: this will undo (remove) that last entered statement\n");
    printf("2. redo: this will redo (i.e., re-add) that last removed statement\n");
    printf("3. print: this command will print the entire stored input text\n");
    printf("4. save: will save the text to a file called (output.txt)\n");
    printf("5. quit: will exit the program and save all results to output.txt\n\n");

    FILE *out;

    out=fopen("output.txt","w");

    char last[100]="",word[100]="";

    stack s=create_node();
    stack reAdd=create_node();

    while(1)
    {
        printf("MyCommand -> ");
        gets(word);
        printf("\n");
        fprintf(out,"\n");

        fprintf(out,"MyCommand -> %s\n",word);
        if(strlen(word)==0)
        {
            printf("u cant enter empty statement (statement should be from 1-100 chars) please try again  \n\n");
            fprintf(out,"\nu cant enter empty statement (statement should be from 1-100 chars)  please try again \n\n");

        }
        else if(strlen(word)<=100)
        {
            if(strcasecmp(word,"undo")==0)
            {

                if(isempety(s))
                {
                    fprintf(out,"\nu cant pop from empty stack\n\n");
                    printf("\nu cant pop from empty stack\n\n");

                }
                else
                {
                    //remove last entered statement
                    pop(s,last,out);
                    //add last removed statement in insert method
                    insert( reAdd, last,out);
                    fprintf(out,"\n");
                    fprintf(out,"Result ->\n\n");
                    printf("\n");
                    printf("Result ->\n\n");
                    print(s,out);
                    printf("\n");
                }
            }
            else if(strcasecmp(word,"redo")==0)
            {
                fprintf(out,"\n");
                printf("\n");

                if(last[0]=='\0')
                {

                    fprintf(out,"there is no statment deleted\n\n");
                    printf("there is no statment deleted\n\n");
                }

                else
                {

                    if(isempety(reAdd))
                    {
                        fprintf(out,"there is no statment deleated\n\n");
                        printf("there is no statment deleated\n\n");
                    }
                    else
                    {

                        fprintf(out,"Result ->\n\n");
                        printf("Result ->\n\n");
                        //re add last removed statement
                        push(s,reAdd->next->statment,out);
                        //delete the node after re add it
                        deleate(reAdd );
                        print(s,out);
                        printf("\n");

                    }

                }

            }
            else if(strcasecmp(word,"print")==0)
            {
                fprintf(out,"\n");
                printf("\n");


                print(s,out);

                printf("\n");



            }
            else if(strcasecmp(word,"save")==0)
            {
                save(out);
            }
            else if(strcasecmp(word,"quit")==0)
            {
                fprintf(out,"\n");
                fprintf(out,"     Good Bye !    ");
                printf("\n");
                printf("     ===== ! Good Bye ! =====  \n  ");
                fclose(out);
                exit(1);
            }
            else
            {
                push(s,word,out);

            }
        }
        else
        {
            printf("\n !-max size for the statement is 100 char please try again-! \n\n");
            fprintf(out,"\n !-max size for the statement is 100 char please try again-! \n\n");

        }
        memset(word,0,sizeof(word));

    }
}
//function to print the nodes in the stack in the file and in the consle
void print(stack s,FILE *out)
{
    ptr p;
    p=s->next;

    if(isempety(s))
    {
        fprintf(out,"the stack is empty\n\n");
        printf("the stack is empty\n");

    }
    else
    {
        while(p!=NULL)
        {
            fprintf(out,"%s\n",p->statment);
            printf("%s\n",p->statment);

            p=p->next;
        }
        fprintf(out,"\n");
    }

}
//function that create stack with header
stack create_node(FILE *out)
{
    stack s;
    s=(stack)malloc(sizeof(struct node));
    if(s==NULL)
    {
        fprintf(out,"THE MEMORY IS FULL\n");
        printf("THE MEMORY IS FULL\n");

    }
    s->next=NULL;
    return s;
}
//function to insert End at the stack
void push(stack s,char st [],FILE *out)
{
    stack temp;
    temp=(ptr)malloc(sizeof (struct node));
    if(temp==NULL)
    {
        fprintf(out,"THE MEMORY IS FULL\n");
        printf("THE MEMORY IS FULL\n");
    }
    strcpy( temp->statment,st);
    while(s->next!=NULL)
    {
        s=s->next;
    }
    s->next=temp;
    temp->next=NULL;


}
//method to insert the deleted nodes from stack into re Add stack
void insert(stack s,char st [],FILE *out)
{
    ptr temp;
    temp=(ptr)malloc(sizeof (struct node));
    if(temp==NULL)
    {
        fprintf(out,"THE MEMORY IS FULL\n");
        printf("THE MEMORY IS FULL\n");
    }

    strcpy( temp->statment,st);
    temp->next=s->next;
    s->next=temp;


}
//delete the node that re added
void deleate(stack l)
{
    ptr p;
    if(isempety(l))
    {
        return;

    }
    else
    {
        p=l->next;
        l->next=p->next;
        free(p);
    }

}
//remove last node that added
const char* pop(stack s,char last[],FILE *out)
{

    ptr temp;


    {
        while(s->next->next!=NULL)
        {
            s=s->next;

        }
        if(s->next->next==NULL)
        {
            temp=s->next;

            s->next=NULL;
            strcpy(last,temp->statment);

            free (temp);
        }

    }
    return last;
}
//check if the stack is empty
int isempety(stack s)
{
    return (s->next==NULL);
}
//function to save the out put and close the out put file
void save (FILE *out)
{
    fprintf(out,"\n");
    printf("\n");

    fprintf(out,"Save Done\n");
    printf("Save Done\n");
    printf("\n");
    fclose(out);

}
