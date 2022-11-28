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
    char regalProduct[201];
    struct Products* next;
}Products_t;
/**Add product to LinkedList*/
void newProduct(Products_t** products,char *product, const char *regalProd)
{
    Products_t* temp=(Products_t*)malloc(sizeof(Products_t));
    Products_t* last=*products;
    strcpy(temp->protuct,product);
    strcpy(temp->regalProduct,regalProd);
    strcpy(temp->lowerProduct,lowerString(product));
    temp->next=NULL;
    if(*products==NULL)
    {
        *products=temp;
        return;
    }
    while (last->next!=NULL)
    {
        last=last->next;
    }
    last->next=temp;
    return;
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

void addSort(Quote_t* quote, int regal, char* product,char *name)
{
    Node_t* node=newNode(regal);
    //prazdna fronta
    if(!quote->last)
    {
        quote->first=quote->last=node;
        newProduct(&quote->first->products,product,name);
        return;
    }
    //pokud uz regal na zacatku existuje tak nic neprobehne
    if(quote->first->regals==regal)
    {    
        newProduct(&quote->first->products,product,name);
        free(node);
        return;
    }
    //pridani na zacatek
    if(quote->first->regals > regal)
    {
        node->next=quote->first;
        quote->first=node;
        newProduct(&quote->first->products,product,name);
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
            newProduct(&temp.first->next->products,product,name);
            free(node);
            return;
        }
        node->next=temp.first->next;
    }
    temp.first->next=node;
    newProduct(&temp.first->next->products,product,name);
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
        if(regal!=-1)
            printf(" %d. %s -> #%d %s\n",*position,products->protuct,regal,products->regalProduct);
        else
            printf(" %d. %s -> %s\n",*position,products->protuct,products->regalProduct);
        Products_t *temp=products->next;
        free(products);
        *position+=1;
        products=temp;
    }
    
}
void printfQuote(Quote_t * quote, Products_t* noList)
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
    printfLinkedList(noList,-1,&position);
}


/**************searching but not ideal worst idea*********************/
char *searchLinkedList(Products_t products,const char *name)
{
    Products_t *temp=&products;
    while (temp!=NULL)
    {   
        if(strstr(temp->lowerProduct,name)!=NULL)
        {
            return temp->protuct;
        }
        temp=temp->next;
    }
    return NULL;
}
int searchQuote(Quote_t* list, Quote_t quote, char *name)
{
    char temp[201];temp[0]='\0';
    int regal=0;  int minRegal=__INT32_MAX__;
    char help[201]; strcpy(help,name);
    int lenName=(int)strlen(name);
    lowerString(help);
    while (quote.first!=NULL)
    {
        int lenMax=0;
        char *buffer=searchLinkedList(*quote.first->products, help);
        if(buffer!=NULL)
        {
            int len=(int)strlen(buffer);
            if(lenMax<len)
            {                
                strcpy(temp,buffer);
                regal=quote.first->regals;
                lenMax=len;
                if(lenName==lenMax)
                {
                    break;
                }
            }
        }
        quote.first=quote.first->next;
    }
    if(temp[0]!='\0')
    {
        addSort(list,regal,name,temp);
        return 1;
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
        newProduct(&(*quote)->last->products,buffer,buffer);
    }    
    return 0;
}

/**ragals compare with list*/
void commodity(Quote_t* quote,FILE *file)
{
    char buffer[201];
    Quote_t* list=creatQuote();
    Products_t *notList=NULL;
    printf("Optimalizovany seznam:\n");
    while(fgets(buffer,200,file))
    {
        char enter[2]; enter[0]='\n';enter[1]='\0';
        int p = strcspn(buffer,enter);
        if(p!=0)
            buffer[p]='\0';

        if(buffer[0]=='\n')
        {
            printfQuote(list,notList);
            commodity(quote,file);
            return;
        } 

        //pozistion in regal and product in regal;
        int s=searchQuote(list, *quote,buffer);
        if(s==-1)
        {
            newProduct(&notList,buffer,"N/A");
            continue;
        }
    }
    printfQuote(list,notList);
    return;
}


/*****************************main******************************/
/** @return 100 cannot open the file
 *  @return 101 cannot read name of file
 */
int main(int argc,char *argv[])
{
    char * filename1=argv[1];

    if(filename1==NULL)
     {
        fprintf(stderr,"Nezadan nazev souboru!");
        return 101;
    }

    FILE *file1 = fopen(filename1, "r");

    if(!file1)
    {
        fprintf(stderr,"Neotevrel se soubor");
        return 100;
    }
    
    Quote_t* quote=creatQuote();
    //read file
    readRegals(&quote,file1);
    commodity(quote,file1);
    fclose(file1);

    //free all memory
    clearQuote(quote);
    return 0;
}