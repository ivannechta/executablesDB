#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
bool isError;

void readKey(FILE *f, keyFile *key){

    fread(&key->startAddr, 4, 1, f);
    fread(&key->size, 4, 1, f);
    DWORD old;
    VirtualProtect(key->startAddr, key->size, PAGE_EXECUTE_READWRITE, &old);
    fread(key->startAddr, key->size, 1, f);
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
keyFile *key=new keyFile;
FILE *f;

    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            isError=false;
            f=fopen("key.ini","rb");
            if (f==NULL){
                    isError = true;
                    MessageBoxA(0, "File with key (key.ini) was not found!", "Protection Error", MB_OK | MB_ICONERROR);
                return FALSE;
            }
            readKey(f,key);
            break;
        case DLL_PROCESS_DETACH:
            if (key!=NULL){
                //delete key->data;
                delete key;
            }
            break;
    }
    fclose(f);
    return TRUE; // succesful
}
