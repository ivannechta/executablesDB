#ifndef NDIMARRAY_H_INCLUDED
#define NDIMARRAY_H_INCLUDED

#include <iostream>
#include <math.h>

using namespace std;
struct EntropyNode{
    int *name; // chain of commands (n-dim)
    int count;
    struct EntropyNode*L,*R;
};

class NdimArray{ //Stores array in a tree
private:
    int dim;
    //float *A;
    int TotalSum;
    int arraySize;

    double log2(double x){
        return log(x)/log(2);
    }
    EntropyNode *Root;int treeCount;

    int cmp(int *a,int *b){
        for (int i=0;i<dim;i++){
            if (a[i]>b[i]) return 1;
            if (a[i]<b[i]) return -1;
        }
        return 0;
    }
    void mov(int *a,int *b){
        for (int i=0;i<dim;i++){
                a[i]=b[i];
        }
    }

public:
    void add(int *cmd){
        if (Root==NULL){
            Root=new EntropyNode; Root->name=new int[dim];
            mov(Root->name,cmd);
            Root->count=1;
            TotalSum++;
            Root->L=Root->R=NULL;
        }else{
            EntropyNode **tmp=&Root;
            int cmpResult;
            while(1){
                if (*tmp==NULL){
                    *tmp=new EntropyNode; (*tmp)->name=new int[dim];
                    mov((*tmp)->name,cmd);
                    (*tmp)->count=1;
                    (*tmp)->L=(*tmp)->R=NULL;
                    treeCount++;
                    TotalSum++;
                    return ;
                }

                cmpResult=cmp((*tmp)->name,cmd);
                if (cmpResult==0){
                    (*tmp)->count++;
                    TotalSum++;
                    return;
                }

                if (cmpResult>0){
                    tmp=&((*tmp)->L);
                }else{
                    tmp=&((*tmp)->R);
                }
            }
        }
    }

    void vivod(EntropyNode *t){
        if (t==NULL) return;
        vivod(t->L);
        printf("%d\n",t->count);
        vivod(t->R);
    }

    NdimArray(int _size,int n){
        dim = n;
        //arraySize=pow(len,n);
        TotalSum=0;
        treeCount=0;
        Root=NULL;
    }
    void deleteTree(EntropyNode *t){
        if (t!=NULL){
            deleteTree(t->L);
            deleteTree(t->R);
            delete t->name;
            delete t;
        }
    }

    ~NdimArray(){
        deleteTree(Root);
    }

    void getEntropy(EntropyNode *t,float *H){
        float p;
        if (t==NULL) return;
        getEntropy(t->L,H);

        p=1.0*t->count/TotalSum;
        if (p!=0) *H=*H+p*log2(p);

        getEntropy(t->R,H);
    }

    float CalcEntropy(){
        float H=0;
        //vivod(Root);
        if (TotalSum==0) return 0;
        getEntropy(Root,&H);
        return -H;
    }
    void getDispersion(EntropyNode *t,double *D){
        double M=1.0/treeCount;
        double p,tmp;

        if (t==NULL) return;
        getDispersion(t->L,D);


        p=1.0*t->count/TotalSum;
        tmp=(M-p);
        *D=*D+tmp*tmp;

        getDispersion(t->R,D);
    }

    double CalcDispersion(){
        double D=0;
        double M=1.0/treeCount;
        if (TotalSum==0) return 0;
        getDispersion(Root,&D);

        printf("Mean=%e ",M);
        return D/(treeCount-1);
    }

    int getDim(){
        return dim;
    }
};

#endif // NDIMARRAY_H_INCLUDED
