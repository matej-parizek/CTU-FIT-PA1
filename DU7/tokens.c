#include <stdlib.h>
#include <stdio.h>

/*TREE*/
typedef struct Tree
{
    int score1, score2, level;
    char name;
    struct Tree* parent;
    struct Tree* first;
    struct Tree* second;
    struct Tree* third;
    struct Tree* fourth;   
}Tree_t;

Tree_t* newTree(int score1,int score2, Tree_t* parent, int level, char name)
{
    Tree_t* newNode=(Tree_t*)malloc(sizeof(Tree_t));
    newNode->score1=score1;
    newNode->score2=score2;
    newNode->level=level;
    newNode->name=name;
    newNode->first=NULL;
    newNode->second=NULL;
    newNode->third=NULL;
    newNode->fourth=NULL;
    newNode->parent=parent;
    return newNode;
}

void clearTree(Tree_t* tree)
{
    if(tree!=NULL)
    {
        clearTree(tree->first);
        clearTree(tree->second);
        clearTree(tree->third);
        clearTree(tree->fourth);
        free(tree);
    }
    return;
}
void printTree(Tree_t* tree, int max)
{
    if(tree!=NULL)
    {
        printTree(tree->first, max);
        printTree(tree->second, max);
        printTree(tree->third, max);
        printTree(tree->fourth, max);
        if(max==tree->level)
            printf("data:%d/%d %c\n",tree->score1, tree->score2, tree->name);
    }
}

void maxLevel(Tree_t* tree, int *max)
{
    if(tree!=NULL)
    {
        maxLevel(tree->first, max);
        maxLevel(tree->second, max);
        maxLevel(tree->third, max);
        maxLevel(tree->fourth, max);
        if(tree->level>*max)
            *max=tree->level;
    }
    return;
}

void search(Tree_t* tree, int player, Tree_t** tmp, int level)
{
    if(tree!=NULL)
    {
        search(tree->first, player, tmp, level);
        search(tree->second, player, tmp, level);
        search(tree->third, player, tmp, level);
        search(tree->fourth, player,tmp, level);

            if(player==1)
            {
                if(tree->score1 > (*tmp)->score1 )
                {
                    *tmp=tree;
                }
            }
            if(player==2)
            {
                if(tree->score2 > (*tmp)->score2)
                {
                    *tmp=tree;
                }
            }
    }
    return;
}

char research(Tree_t* tree)
{
    char c='\0';
    while (tree->parent!=NULL)
    {
        c=tree->name;
        tree=tree->parent;
    }
    return c ;
}
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
    if(s1!= 'N' && s1!= 'W' && s1!= 'E' && s1!= 'S' && s2!='{' && r!=2)
        return 0;
    int number;
    int counter=0;
    while ((r=scanf(" %d",&number))!=EOF)
    {   
        if(counter>31 || r==0)
            return 0;
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
        counter++;
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
    printf("\n");
}


/*HIGHEST NUMBER IN TOKENS*/
char max(Node_t* north, Node_t* south, Node_t* west, Node_t* east)
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

void forest(Tree_t* tree,Node_t** north, Node_t** south, Node_t** west, Node_t** east, int level, int player)               
{
    int number;

    if(north !=NULL && south!=NULL && west!=NULL && south!=NULL)
    {
        if(player==1)
        {
            if(pop(north,&number))
            {
                tree->first=newTree(tree->score1+number,tree->score2,tree,level,'N');
                forest(tree->first,north,south,west,east,level+1,2);
                push(north,number);
            }
            if(pop(south,&number))
            {
                tree->fourth=newTree(tree->score1+number,tree->score2,tree,level,'S');
                forest(tree->fourth,north,south,west,east,level+1,2);
                push(south,number);
            }
            if(pop(west,&number))
            {
                tree->third=newTree(tree->score1+number,tree->score2,tree,level,'W');
                forest(tree->third,north,south,west,east,level+1,2);
                push(west,number);
            }
            if(pop(east,&number))
            {
                tree->second=newTree(tree->score1+number,tree->score2,tree,level,'E');
                forest(tree->second,north,south,west,east,level+1,2);
                push(east,number);
            }
        }
        if(player==2)
        {
            if(pop(north,&number))
            {
                tree->first=newTree(tree->score1,tree->score2+number,tree,level,'N');
                forest(tree->first,north,south,west,east,level+1,1);
                push(north,number);
            }
            if(pop(south,&number))
            {
                tree->fourth=newTree(tree->score1,tree->score2+number,tree,level,'S');
                forest(tree->fourth,north,south,west,east,level+1,1);
                push(south,number);
            }
            if(pop(west,&number))
            {
                tree->third=newTree(tree->score1,tree->score2+number,tree,level,'W');
                forest(tree->third,north,south,west,east,level+1,1);
                push(west,number);
            }
            if(pop(east,&number))
            {
                tree->second=newTree(tree->score1,tree->score2+number,tree,level,'E');
                forest(tree->second,north,south,west,east,level+1,1);
                push(east,number);
            }
        }
        
    }   
}


char best(Node_t** north, Node_t** south, Node_t** west, Node_t** east, int score1, int score2, int player)
{

    Tree_t* tree=newTree(score1,score2,NULL,-1,'\0');
    forest(tree,north,south,west,east,0,player);
    int maxLvl=0;
    maxLevel(tree,&maxLvl);
    Tree_t* tmp=tree;
    search(tree, player ,&tmp, maxLvl);
    printf("%d /%d\n", tmp->score1, tmp->score2);
    //printTree(tree, maxLvl);
    char c= research(tmp);
    clearTree(tree);
    return c;
}

/*PLAY*/

int score(Node_t** north, Node_t** south, Node_t** west, Node_t** east, int *number,int *countNorth, int *coutWest,
int *countEast, int *coutSouth, char *c, int *pozition, int player, int score1, int score2) 
{
    *number=0;
    *c= best(north,south,west,east,score1,score2, player);  //funkce která vybírá co vyhodit
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
        int r = score(north,south,west,east,&number, countNorth, coutWest, countEast, coutSouth,
                        &c,&pozition, player, *score1, *score2);
        if(r!=0)
        {
            *score1+=number;
            printf("A: %c[%d] (%d)\n", c, pozition,number);
           // printf("------score1 %d/ score2 %d\n"  ,*score1,*score2);
            play(north,south,west,east,score1,score2,2, countNorth, coutWest, countEast, coutSouth);
        }
    }
    if(player==2)
    {

        int r = score(north,south,west,east,&number,countNorth, coutWest, countEast, coutSouth, 
                        &c,&pozition, player, *score1, *score2);
        if(r!=0)
        {
            *score2+=number;
            printf("B: %c[%d] (%d)\n", c, pozition,number);
            //printf("------score1 %d/ score2 %d\n"  ,*score1,*score2);
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
    printf("Zetony:\n");
    if(input(&north,&south, &west, &east,read) == 0)
    {
        printf("Nespravny vstup.\n");
        printf("%s\n",read);
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
    if(input(&north,&south, &west, &east,read) == 0 || north==NULL || south==NULL || east==NULL || west==NULL)
    {
        printf("Nespravny vstup.\n");
        clearAll( north, south, west, east);
        return 0;
    }
    int countNorth=-1, coutWest=-1, countEast=-1, coutSouth=-1;
    int score1=0, score2=0;

    /*Game*/
    play(&north,&south,&west,&east,&score1,&score2,1,&countNorth, &coutWest, &countEast, &coutSouth);
    //best(&north,& south, &west, &east,0,0,1);

    //zkouska stromu
    printf("Celkem A/B: %d/%d\n",score1,score2);
    clearAll( north, south, west, east);
    return 0;
}
