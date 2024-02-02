#ifndef DBCOMMANDS_H_INCLUDED
#define DBCOMMANDS_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include "NdimArray.h"


#define MAX_COMMAND_LEN 8
#define MAX_INSTRUCTION_SIZE 50

struct Node{
    char name[7];
    int hash;
    int count;
    struct Node*L,*R;
};

class DataBase{

private:
    char **commands;
    int commandsCount;
    int tvFilter;
    NdimArray *A;

    void makeHash(Node *t,int* i){
        t->hash=*i;
        *i=*i+1;
        if (t->L!=NULL){
            makeHash(t->L,i);
        }
        if (t->R!=NULL){
            makeHash(t->R,i);
        }
    }
    int Load(char *fileName){
        FILE *f=fopen(fileName,"rt");
        if (f==NULL) {
            printf("File not found\n"); throw 2;
        }
        char cmd[MAX_INSTRUCTION_SIZE],tmp[MAX_INSTRUCTION_SIZE];
        bool endline;

        while (!feof(f)){
                fscanf(f,"%s",cmd);
                if (cmd[0]=='*'){
                    continue;
                }
                addCommand(cmd);
                endline=false;
                while(!endline&& !feof(f)){
                        fscanf(f,"%s",tmp);
                        if (tmp[0]=='+'){
                            endline=true;

                        }
                }

        }
        fclose(f);
        return makeHash();
    }
public:
    Node *Root;int treeCount;

    void addCommand(char* cmd){
        if (Root==NULL){
            Root=new Node;
            strcpy(Root->name,cmd);
            Root->count=1;
            treeCount++;
            Root->L=Root->R=NULL;
        }else{
            Node **tmp=&Root;
            int cmp;
            while(1){
                if (*tmp==NULL){
                    *tmp=new Node;
                    strcpy((*tmp)->name,cmd);
                    (*tmp)->count=1;
                    (*tmp)->L=(*tmp)->R=NULL;
                    treeCount++;
                    return ;
                }

                cmp=strcmp((*tmp)->name,cmd);
                if (cmp==0){
                    (*tmp)->count++; return;
                }

                if (cmp>0){
                    tmp=&((*tmp)->L);
                }else{
                    tmp=&((*tmp)->R);
                }
            }
        }
    }

    void vivod(Node *t){
        if (t==NULL) return;
        vivod(t->L);
        printf("%d %s %d\n",t->hash, t->name,t->count);
        vivod(t->R);
    }
    int makeHash(){
        int i=0;
        makeHash(Root,&i);
        return i;
    }
    int findCMD(char * cmd){
        Node *t=Root;
        while(t!=NULL){
            if (strcmp(t->name,cmd)==0) return t->hash;
            if (strcmp(t->name,cmd)>0) t=t->L; else t=t->R;
        }
        return -1;
    }

    void deleteTree(Node *t){
        if (t!=NULL){
            deleteTree(t->L);
            deleteTree(t->R);
            delete t;
        }
    }
    DataBase(){
        Root=NULL;
        treeCount=0;
        commandsCount=0;
        commands=NULL;
    }
    ~DataBase(){
        deleteTree(Root);
    }

    void ReadChains(int Dimension ,char *fileName){
        int differentCommandsCnt=Load(fileName);
        A=new NdimArray(differentCommandsCnt,Dimension);

        FILE *f=fopen(fileName,"rt");
        if (f==NULL) {
            printf("File not found\n"); throw 2;
        }
        char cmd[MAX_INSTRUCTION_SIZE],tmp[MAX_INSTRUCTION_SIZE];
        bool endline;

        int *indexes=new int [A->getDim()], ind_i=0;

        while (!feof(f)){
                fscanf(f,"%s",cmd);
                if (cmd[0]=='*'){ //starts new function
                    ind_i=0;
                    continue;
                }
                indexes[ind_i++]=findCMD(cmd);
                if (ind_i==A->getDim()){
                        ind_i=0;
                        A->add(indexes);
                }
                endline=false;
                while(!endline && !feof(f)){
                        fscanf(f,"%s",tmp);
                        if (tmp[0]=='+'){
                            endline=true;
                        }
                }
        }
        fclose(f);
    }

    float CalcEntropy(){
        return A->CalcEntropy();
    }
};

#endif // DBCOMMANDS_H_INCLUDED
