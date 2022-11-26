#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @return 100 from main, cant open file */

/*Linked list for products*/
typedef struct Products
{
    char protuct[201];
    struct Products* next;
}Products_t;

void newProduct(Products_t * products,char *product)
{
    Products_t* temp=(Products_t*)malloc(sizeof(Products_t));
    strcpy(temp->protuct,product);
    temp->next=NULL;
    products->next=temp;
}
/******************************************************************/

/*************QUOTE FROM LINKED LIST************************/

typedef struct Node
{
    int regals;
    char **protucts;
    struct Node* next;
}Node_t;

typedef struct Quote
{
    Node_t *first;
    Node_t *last;
}Quote_t;

/**
 * Node of linked list
*/
Node_t* newNode(int regal)
{
    Node_t* node=(Node_t *)malloc(sizeof(Node_t));
    node->regals=regal;
    node->next=NULL;
    return node;
}

/**
 * Creat Quote
 * using in main()
*/
Quote_t* creatQuote()
{
    Quote_t* quote=(Quote_t*)malloc(sizeof(Quote_t));
    quote->first=NULL;
    quote->last=NULL;
    return quote;
}

/**
 * Create new node of quote 
*/
void add(Quote_t* quote, int regal)
{
    Node_t* node = newNode(regal);
    if(!quote->last)
    {
        quote->first = quote->last= node;
        return;
    }
    quote->last->next=node;
    quote->last=node;
    return;
}


/************************************************************************************/










int readFile(Quote_t** quote, FILE *file){
    char buffer[201];
    int productsCount=0;
    int regal=-1;
    while (fgets(buffer,200,file))
    {
        if(buffer[0]=='\n')
            break;
        if(buffer[0]=='#')
        {
            //add(*quote,regal);
            productsCount=0;
            regal++;
            continue;
        }
        printf("%d %s",regal,buffer);
        productsCount++;
    }
    return 0;
}

void clearQuote(Quote_t * quote)
{
    while (quote->first->next!=NULL)
    {
        Node_t* temp = quote->first->next;
        free(quote->first);
        quote->first=temp;
    }
    free(quote->first);
    free(quote);
}

int main(int argc,char *argv[])
{
    char * filename=argv[1];
    FILE *file = fopen(filename, "r");
    if(!file)
    {
        fprintf(stderr,"Neotevrel se soubor");
        return 100;
    }
    Quote_t* quote=creatQuote();
    //read file
    readFile(&quote,file);

    fclose(file);

    //free all memory
    clearQuote(quote);
    
    return 0;
}