#ifndef _SCEFIOS2_H_
#define _SCEFIOS2_H_

#include <cstdint>
#include <windows.h>

typedef __int64 SceFiosSize;
typedef __int64 SceFiosTime;
typedef int SceFiosDH;

struct FIOS2HANDLE
{
    int mFH;
};

#ifdef __cplusplus
extern "C" {
#endif

    uintptr_t extern sceFiosIOFilterCache;

    SceFiosSize extern sceFiosFHGetSize(SceFiosSize lFH);
    __int64 extern sceFiosIOFilterAdd(__int64 unk1);

#ifdef __cplusplus
}
#endif

#endif //_SCEFIOS2_H_