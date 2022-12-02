#include <stdlib.h>
#include <stdio.h>

/*LINKED LIST*/
typedef struct Node
{
    int data;
    struct Node *next;
}Node_t;

/*LINKED LIST FUNCTION*/
void append(Node_t** tokens, int data)  //Add data on the last 
{
    Node_t* newNode=(Node_t*)malloc(sizeof(Node_t));
    newNode->data=data;
    newNode->next=NULL;
    if(*tokens==NULL)
    {
        *tokens=newNode;
        return;
    }    
    Node_t *temp=*tokens;
    while (temp->next !=NULL)
        temp=temp->next;
    temp->next=newNode;
    return;
}
int pop(Node_t** token, int *data)  //Take off the data from first
{
    if(*token==NULL)
        return 0;
    Node_t* temp=*token;
    *data=(*token)->data;
    (*token)=(*token)->next;
    free(temp);
    return 1;
}
void push(Node_t** token,int data)  //Add data on the first
{
    Node_t* temp=(Node_t*)malloc(sizeof(Node_t));
    temp->next=*token;
    temp->data=data;
    *token=temp;

}
void clear(Node_t* token)   //Clear memory from LL
{
    if(token==NULL)
        return;
    while (token!=NULL)
    {
        Node_t* tmp=token->next;
        free(token);
        token=tmp;
    }
    return;
}
void clearAll(Node_t* north, Node_t* south, Node_t* west, Node_t* east)
{
    clear(north);
    clear(south);
    clear(east);
    clear(west);
}
/*PREPARE FOR GAME*/
int control(char *read, char c)
{
    int i=0;
    while (read[i]!='\0')
    {
        if(read[i]==c)
            return 1;
        i++;
    }
    read[i]=c;
    read[i+1]='\0';
    return 0;
}
int input(Node_t** north,Node_t** south,Node_t** west,Node_t** east, char *used)    //Read inputs and check if all is right
{
    char s1;
    char s2;
    int r=scanf(" %c: %c", &s1, &s2);
    if (control(used,s1))
        return 0;
    if(s1!= 'N' && s1!= 'W' && s1!= 'E' && s1!= 'S' && s2!='{')
        return 0;
    int number;
    while ((r=scanf(" %d",&number)))
    {
        if(s1=='N')
            append(north,number);
        if(s1=='S')
            append(south,number);
        if(s1=='W')
            append(west,number);
        if(s1=='E')
            append(east,number);
        char c;
        c='\0';        
        while(scanf(" %c",&c)!=EOF)
        {
             if(c!=',' && c!= '}')
            {
                return 0;
            }
            if(c=='}' || c==',' )
                break;
        }
        if(c=='}')
            break;
    }
    return 1;
}

void print(Node_t *token)
{
    while (token!=NULL)
    {
        printf("%d ",token->data);
        token=token->next;
    }
}


/*HIGHEST NUMBER IN TOKENS*/
char highestToken(Node_t* north, Node_t* south, Node_t* west, Node_t* east)
{
    int max=0;
    char c='\0';
    if(north!=NULL)
    {
        max=north->data;
        c='N';
    }
    else if(south!=NULL)
    {
        max=south->data;
        c='S';
    }
    else if(west!=NULL)
    {
        max=west->data;
        c='W';
    }
    else if(east!=NULL)
    {
        max=east->data;
        c='E';  
    }
    if(south!=NULL)
        if(max < (*south).data)
        {
            max=(*south).data;
            c='S';
        }
    if(west!=NULL)
        if(max<(*west).data)
        {
            max=(*west).data;
            c='W';
        }
    if(east!=NULL)
        if(max < (*east).data)
        {
            max=(*east).data;
            c='E';
        }
    return c;
}
/*PLAY*/

int score(Node_t** north, Node_t** south, Node_t** west, Node_t** east, int *number,
    int *countNorth, int *coutWest, int *countEast, int *coutSouth, char *c, int *pozition)
{
    *number=0;
    *c= highestToken(*north, *south, *west, *east); //funkce která vybírá co vyhodit
    if(*c=='N')
    {
        *countNorth+=1;
        *pozition=*countNorth;
        return pop(north, number);
    }
    if(*c=='S')
    {
        *coutSouth+=1;
        *pozition=*coutSouth;
        return pop(south, number);
    }
    if(*c=='W')
    {
        *coutWest+=1;
        *pozition=*coutWest;
        return pop(west, number);
    }
    if(*c=='E')
    {
        *countEast+=1;
        *pozition=*countEast;
        return pop(east, number);
    }
    if(*c=='\0')
        return 0;
    return 0;
}

void play(Node_t** north, Node_t** south, Node_t** west, Node_t** east, int *score1, int *score2, int player,
int *countNorth, int *coutWest, int *countEast, int *coutSouth)
{
    char c='\0';
    int number;
    int pozition=0;
    if(player==1)
    {
        int r = score(north,south,west,east,&number, countNorth, coutWest, countEast, coutSouth, &c,&pozition);
        if(r!=0)
        {
            *score1+=number;
            printf("A: %c[%d] (%d)\n", c, pozition,number);
            play(north,south,west,east,score1,score2,2, countNorth, coutWest, countEast, coutSouth);
        }
    }
    if(player==2)
    {

        int r = score(north,south,west,east,&number,countNorth, coutWest, countEast, coutSouth, &c,&pozition);
        if(r!=0)
        {
            *score2+=number;
            printf("B: %c[%d] (%d)\n", c, pozition,number);
            play(north,south,west,east,score1,score2,1,countNorth, coutWest, countEast, coutSouth);
        }
    }
    return;
}

int main()
{
    Node_t* north=NULL;
    Node_t* south=NULL;
    Node_t* west=NULL;
    Node_t* east=NULL;
    char read[5]; read[0]='\0';
    if(input(&north,&south, &west, &east,read) == 0)
    {
        printf("Nespravny vstup.\n");
        clearAll( north, south, west, east);
        return 0;
    }
    if(input(&north,&south, &west, &east,read)==0)
    {
        printf("Nespravny vstup.\n");
        clearAll( north, south, west, east);
        return 0;
    }
    if(input(&north,&south, &west, &east,read) == 0)
    {
        printf("Nespravny vstup.\n");
        clearAll( north, south, west, east);
        return 0;
    }
    if(input(&north,&south, &west, &east,read) == 0)
    {
        printf("Nespravny vstup.\n");
        clearAll( north, south, west, east);
        return 0;
    }
    int countNorth=-1, coutWest=-1, countEast=-1, coutSouth=-1;
    int score1=0, score2=0;

    /*Game*/

    play(&north,&south,&west,&east,&score1,&score2,1,&countNorth, &coutWest, &countEast, &coutSouth);

    printf("Celkem A/B: %d/%d\n",score1,score2);

    clearAll( north, south, west, east);
    return 0;
}
