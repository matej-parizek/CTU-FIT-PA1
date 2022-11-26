#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*Linked list for products*/
typedef struct Products
{
    char protuct[201];
    struct Products* next;
}Products_t;
/**Add product to LinkedList*/
void newProduct(Products_t** products,char *product)
{
    Products_t* temp=(Products_t*)malloc(sizeof(Products_t));
    strcpy(temp->protuct,product);
    temp->next=*products;
    *products=temp;
}

/**Clear LINKED LIST*/
void clearLinkedList(Products_t* products)
{
    while (products!=NULL)
    {
        Products_t *temp=products->next;
        free(products);
        products=temp;
    }
    
}
/******************************************************************/

/*************QUOTE FROM LINKED LIST************************/

typedef struct Node
{
    int regals;
    Products_t* products;
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
    node->products=NULL;
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

/**free memory from quote*/
void clearQuote(Quote_t * quote)
{
    if(quote->first==NULL)
    {
        free(quote);
        return;
    }
    while (quote->first!=NULL)
    {
        Node_t* temp = quote->first->next;
        clearLinkedList(quote->first->products);
        free(quote->first);
        quote->first=temp;
    }
    free(quote);
}
/************************************************************************************/

char *lowerString(char *buffer)
{
    for(long int i=0; i<(long int)strlen(buffer); i++)
    {
        buffer[i]=tolower(buffer[i]);
    }
    return buffer;
}


/**searching but not ideal worst idea*/
int searchLinkedList(Products_t* products,const char *name,char *string)
{
    Products_t *temp=products;
    while (temp!=NULL)
    {
        if(strstr(temp->protuct,name)!=NULL)
        {
            strcpy(string,temp->protuct);
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}

int searchQuote(Quote_t quote, const char *name,char *string)
{
    int count=0;
    while (quote.first!=NULL)
    {
        if(searchLinkedList(quote.first->products,name,string))
        {
            return count;
        }
        quote.first=quote.first->next;
        count++;
    }
    return -1;
}





/**Get products in regal*/
int readRegals(Quote_t** quote, FILE *file){
    char buffer[201];
    int productsCount=0;
    int regal=-1;
    while (fgets(buffer,200,file))
    {
        if(buffer[0]=='\n')
            break;
        if(buffer[0]=='#')
        {
            add(*quote,regal);
            productsCount=0;
            regal++;
            continue;
        }
        newProduct(&(*quote)->last->products,lowerString(buffer));
        productsCount++;
    }    
    return 0;
}

/**ragals compare with list*/
void commodity(Quote_t* quote,FILE *file)
{
    char buffer[201];
    while(fgets(buffer,200,file))
    {
        if(buffer[0]=='\n')
        {
            //commodity(quote,file);
            return;
        } 
        char string[200];
        //pozistion in regal and product in regal;
        int s=searchQuote(*quote,lowerString(buffer),string);
        if(s==-1)
            continue;
        printf("%d %s",s,string);         
    }
    return;
}

/** @return 100 cannot open the file
 *  @return 101 cannot read name of file
 */
int main(int argc,char *argv[])
{
    char * filename=argv[1];
    if(filename==NULL)
     {
        fprintf(stderr,"Nezadan nazev souboru!");
        return 101;
    }
    FILE *file = fopen(filename, "r");
    if(!file)
    {
        fprintf(stderr,"Neotevrel se soubor");
        return 100;
    }
    
    Quote_t* quote=creatQuote();
    //read file
    readRegals(&quote,file);   
    
    commodity(quote,file);

    fclose(file);

    //free all memory
    clearQuote(quote);
    return 0;
}