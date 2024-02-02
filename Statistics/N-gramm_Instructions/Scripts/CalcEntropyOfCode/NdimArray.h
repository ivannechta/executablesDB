#ifndef NDIMARRAY_H_INCLUDED
#define NDIMARRAY_H_INCLUDED

#include <iostream>
#include <math.h>

using namespace std;
struct EntropyNode{
    int *name;
    int count;
    struct EntropyNode*L,*R;
};

class NdimArray{
private:
    int len;
    int dim;
    float *A;
    float TotalSum;
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
                    //treeCount++;
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
        len = _size;
        dim = n;
        //arraySize=pow(len,n);
        TotalSum=0;
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
        float p, H=0;
        //vivod(Root);
        if (TotalSum==0) return 0;
        getEntropy(Root,&H);
        return -H;
    }

    int getDim(){
        return dim;
    }
};

#endif // NDIMARRAY_H_INCLUDED
