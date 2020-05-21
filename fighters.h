#ifndef FIGHTERS_H
#define FIGHTERS_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define NAME_SIZE 20


static size_t fighterArraySize;

typedef struct Fighters
{
    char name[NAME_SIZE];
} Fighter;
typedef struct plinkedList
{
    Fighter currentFighter;
    struct plinkedList * previous;
    struct plinkedList * next;
} FighterArray;

FighterArray * newFighter(FighterArray * node,Fighter fighter)
{
    FighterArray * newNode = NULL;
    newNode = (FighterArray *) malloc(sizeof(FighterArray));
    if(newNode!=NULL)
    {
    node -> next = newNode;
    newNode -> previous = node;
    newNode -> currentFighter = fighter;
    newNode -> next = NULL;
    fighterArraySize++;
    }
    else newNode = newFighter(node,fighter);
    return newNode;
}
FighterArray * fighterLoad(FighterArray * fightersLoaded)
{
    FILE * fp;
    char path[] = "Fighters.txt";
    fp = fopen(path,"r+");
    FighterArray * first = fightersLoaded;
    size_t fileSize;
    fscanf(fp,"%d\n",&fileSize);
//printf("%d",fileSize);
    for(int i = 0 ; i < fileSize ; i++)
    {
        char name[NAME_SIZE];
        Fighter new_Fighter;
        fscanf(fp," %s/n",name);
        //printf("%s\n",name);
        strcpy(new_Fighter.name,name);
        fightersLoaded = newFighter(fightersLoaded,new_Fighter);
    }
    fclose(fp);
    return fightersLoaded;
}
void memDump(FighterArray * arr,size_t arrSize){
    for(int i = 0;i<arrSize;i++){
        arr = arr -> previous;
        free(arr->next);
    }
}

#endif // FIGHTERS_H
