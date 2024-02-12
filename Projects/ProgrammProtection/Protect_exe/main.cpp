#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

using namespace std;
#define N 10

int A[N];
void zap(){
    for (int i=0;i<N;i++){
        A[i]=rand()%100;
    }

}
void vivod(){
    for (int i=0;i<N;i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}
void sort(){
    bool flag=true;
    int tmp;

    while (flag){
        flag=false;
        for (int i=0;i<N-1;i++){
            if (A[i]>A[i+1]){
                    flag=true;
                    tmp=A[i];
                    A[i]=A[i+1];
                    A[i+1]=tmp;
            }
        }
    }
}
void laba(){
    zap();
    vivod();
    sort();
    vivod();
}


int main()
{
    HINSTANCE hModule=NULL;
    hModule=LoadLibrary("protect.dll");
    if (hModule!=NULL)
	{
		::FreeLibrary(hModule);
	}
	else {
            cout << "Error in load protect.dll" << endl;
            exit(1);
    }

    laba();
    return 0;
}
