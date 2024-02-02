#include <cstdlib>
#include <iostream>
#include <string.h>
#include "DBCommands.h"
#include "NdimArray.h"


//#define FILENAME "e:\\temp\\Entropy2\\commands_from_exe.txt"

using namespace std;
void Usage(char *s){
    printf("Usage: %s <debug.file> <Memory_len>\n", s);
    printf("Example:\n%s a.asm 12\n", s);
}
int main(int argc, char **argv)
{
    if (argc!=3){
        Usage(argv[0]);
        return -1;
    }

    DataBase *DB;
    for (int i=1;i<=atoi(argv[2]);i++){
        DB=new DataBase();
        DB->ReadChains(i, argv[1]);
        //printf("Memory=%d Entropy=%.3f\n",i,DB->CalcEntropy());
        printf("Memory=%d ",i);
        printf("Dispersion=%e\n",DB->CalcDispersion());
        delete DB;
    }


    return EXIT_SUCCESS;
}
