#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>
#include <stdint.h>
typedef unsigned char uchar;
struct keyFile{
    void* startAddr;
    uint32_t size;
    uchar *data; //reserved
};

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

void DLL_EXPORT SomeFunction(const LPCSTR sometext);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
