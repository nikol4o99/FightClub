#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fighters.h"
#define START_HEALTH 100

FighterArray * start;

int fight(Fighter fighter1, Fighter fighter2)
{
    srand (time(NULL));
    float fH1 = START_HEALTH;
    float fH2 = START_HEALTH;
    while(fH1>0&&fH2>0){
        float damage = rand()%20;
        printf("%s hits %s with %f damage\n",fighter1.name,fighter2.name,damage);
        fH2 -= damage;
        if(fH2>0){
        damage = rand()%20;
        printf("%s hits %s with %f damage\n",fighter2.name,fighter1.name,damage);
        fH1 -= damage;
        }
    }
    if(fH1 <=0) return 2;
    else return 1;
}
FighterArray * pairing(FighterArray * begNode,FighterArray * endNode,int fightSize)
{
    int fightNum = fightSize,k = 0;
    FighterArray * newArr;
    if(fightNum%2 != 0) {
        fightNum--;
        newArr = newFighter(newArr,begNode->currentFighter);
        start = newArr;
        begNode = begNode->next;
        free(begNode->previous);
        k++;
    }
    fightNum/=2;
    for(int i=0;i<fightNum;i++){
        int fightRes = fight(begNode->currentFighter,endNode->currentFighter);
        if(fightRes == 1) {
                printf("Winner is: %s\n",begNode->currentFighter.name);
                newArr = newFighter(newArr,begNode->currentFighter);
        }
        else {
                printf("Winner is: %s\n",endNode->currentFighter.name);
                newArr = newFighter(newArr,endNode->currentFighter);
        }
        if(i==0&&k==0)start = newArr;
        endNode = endNode->previous;
        free(endNode->next);
        begNode = begNode->next;
        free(begNode->previous);
    }
    fightSize+= fightNum;
    return newArr;
}

int main()
{

    FighterArray * fighterArray = NULL;
    fighterArray = (FighterArray *) malloc(sizeof(FighterArray));
    if(fighterArray != NULL) fighterArray  = fighterLoad(fighterArray);
    FighterArray * forDumping = fighterArray;
    start = fighterArray;
    for(int i=0;i<fighterArraySize-1;i++){
        start = start->previous;
    }
    int fsize = (int)fighterArraySize;
    //printf("%s\n\n",start->currentFighter.name);
    while(fsize>=2){

        fighterArray = pairing(start,fighterArray,fsize);
        if(fsize%2==0) fsize/=2;
        else{
            fsize+=1;
            fsize/=2;
        }
        system("pause");
    }
    FILE * fp;
    fp = fopen("Champion.txt","w+");
    fprintf(fp,"CHAMION IS: %s\n",fighterArray->currentFighter.name);
    printf("CHAMION IS: %s\n",fighterArray->currentFighter.name);
    fclose(fp);
    memDump(forDumping,1);
    return 0;
}
