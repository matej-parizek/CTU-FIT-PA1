#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/********LowerCase********************************************************/
char *lowerString(char *buffer)
{
    for(long int i=0; i<(long int)strlen(buffer); i++)
    {
        buffer[i]=tolower(buffer[i]);
    }
    return buffer;
}



/***********************LINKEDLIST*****************************************/
/*Linked list for products*/
typedef struct Products
{
    char protuct[201];
    char lowerProduct[201];
    int data;
    struct Products* next;
}Products_t;
/**Add product to LinkedList*/
void newProduct(Products_t** products,char *product)
{
    Products_t* temp=(Products_t*)malloc(sizeof(Products_t));
    strcpy(temp->protuct,product);
    strcpy(temp->lowerProduct,lowerString(product));
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



/*************QUOTE FROM LINKED LIST***************************************/
/*linked list for quote*/
typedef struct Node
{
    int regals;
    Products_t* products;
    struct Node* next;
}Node_t;
/*quote*/
typedef struct Quote
{
    Node_t *first;
    Node_t *last;
}Quote_t;
/**Node of linked list*/
Node_t* newNode(int regal)
{
    Node_t* node=(Node_t *)malloc(sizeof(Node_t));
    node->regals=regal;
    node->products=NULL;
    node->next=NULL;
    return node;
}

/**Creat Quote*/
Quote_t* creatQuote()
{
    Quote_t* quote=(Quote_t*)malloc(sizeof(Quote_t));
    quote->first=NULL;
    quote->last=NULL;
    return quote;
}

/**Create new node of quote */
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

void addSort(Quote_t* quote, int regal, char* product)
{
    Node_t* node=newNode(regal);
    //prazdna fronta
    if(!quote->last)
    {
        quote->first=quote->last=node;
        newProduct(&quote->first->products,product);
        return;
    }
    //pokud uz regal na zacatku existuje tak nic neprobehne
    if(quote->first->regals==regal)
    {    
        newProduct(&quote->first->products,product);
        free(node);
        return;
    }
    //pridani na zacatek
    if(quote->first->regals > regal)
    {
        node->next=quote->first;
        quote->first=node;
        newProduct(&quote->first->products,product);
        return;
    }

    //sort
    Quote_t temp=*quote;
    while (temp.first->next!=NULL && temp.first->next->regals<regal)
    {
        temp.first=temp.first->next;
    }    
    if(temp.first->next!=NULL)
    {
        //pokud je u prostred vynech
        if (temp.first->next->regals==regal)
        {
            newProduct(&temp.first->next->products,product);
            free(node);
            return;
        }
        node->next=temp.first->next;
    }
    temp.first->next=node;
    newProduct(&temp.first->next->products,product);
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



/******Print to file****************************************************/
void printfLinkedList(Products_t* products, int regal,int* position)
{
    while (products!=NULL)
    {
        printf("%d. %s -> #%d\n",*position,products->protuct,regal);
        Products_t *temp=products->next;
        free(products);
        *position+=1;
        products=temp;
    }
    
}
void printfQuote(Quote_t * quote)
{
    if(quote->first==NULL)
    {
        free(quote);
        return;
    }
    int position =0;
    while (quote->first!=NULL)
    {
        Node_t* temp = quote->first->next;
        printfLinkedList(quote->first->products,quote->first->regals,&position) ;
        free(quote->first);
        quote->first=temp;
    }
    free(quote);
}


/**************searching but not ideal worst idea*********************/
int searchLinkedList(Products_t products,const char *name)
{
    Products_t *temp=&products;
    while (temp!=NULL)
    {
        if(strstr(temp->lowerProduct,name)!=NULL)
        {
            printf("%s\n",temp->lowerProduct);
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}
int searchQuote(Quote_t quote, char *name)
{
    int count=0;
    char lowerName[201];
    strcpy(lowerName,name);
    lowerString(lowerName);
    while (quote.first!=NULL)
    {
        if(searchLinkedList(*quote.first->products,lowerName))
        {
            return count;
        }
        quote.first=quote.first->next;
        count++;
    }
    return -1;
}



/**********REGALS*********************************/
/**Get products in regal*/
int readRegals(Quote_t** quote, FILE *file){
    char buffer[201];
    int past=-1;
    char enter[2]; enter[0]='\n';enter[1]='\0';

    while (fgets(buffer,200,file))
    {
        if(buffer[0]=='\n')
            break;
        //osetrit;
        if(buffer[0]=='#')
        {
            strcpy(buffer,buffer+1);
            past+=1;
            if(past != atoi(buffer))    //wrong input
                return 1;
            add(*quote,atoi(buffer));
            continue;
        }
        int p = strcspn(buffer,enter);
        if(p!=0)
            buffer[p]='\0';
        newProduct(&(*quote)->last->products,buffer);
    }    
    return 0;
}

/**ragals compare with list*/
void commodity(Quote_t* quote,FILE *file)
{
    char buffer[201];
    Quote_t* list=creatQuote();
    
    while(fgets(buffer,200,file))
    {

        if(buffer[0]=='\n')
        {
            printfQuote(list);
            printf("-----------------\n ");
            commodity(quote,file);
            return;
        } 
        //pozistion in regal and product in regal;
        int s=searchQuote(*quote,buffer);
        if(s==-1)
            continue;
        addSort(list,s,buffer);
    }
    printfQuote(list);
    return;
}


/*****************************main******************************/
/** @return 100 cannot open the file
 *  @return 101 cannot read name of file
 */
int main(int argc,char *argv[])
{
    char * filename1=argv[1];
    char * filename2=argv[2];

    if(filename1==NULL || filename2==NULL)
     {
        fprintf(stderr,"Nezadan nazev souboru!");
        return 101;
    }

    FILE *file1 = fopen(filename1, "r");
    FILE *file2 = fopen(filename2, "w");

    if(!file1 || !file2)
    {
        fprintf(stderr,"Neotevrel se soubor");
        return 100;
    }
    
    Quote_t* quote=creatQuote();
    //read file
    readRegals(&quote,file1);
    //commodity(quote,file1);
    //printf("%s\n",quote->first->products->protuct);

    fclose(file1);
    fclose(file2);

    printfQuote(quote);
    //free all memory
    //clearQuote(quote);
    return 0;
}