#ifndef _SCEFIOS2_H_
#define _SCEFIOS2_H_

#include <cstdint>
#include <windows.h>

typedef __int64 SceFiosSize;
typedef __int64 SceFiosTime;
typedef int SceFiosDH;
typedef int SceFiosFH;
typedef __int64 SceFiosOffset;
typedef void *(*SceFiosMemcpyCallback)(void *, const void *, unsigned __int64);
typedef __int64 SceFiosTimeInterval;
typedef unsigned __int64 SceFiosDate;
typedef unsigned __int8 SceFiosOpEvent;
typedef bool (*SceFiosRAMCacheCallback)(void *, int, const char *, void *);
typedef int (*SceFiosOpCallback)(void *, int, unsigned __int8, int);
typedef int SceFiosHandle;
typedef void (*SceFiosIOFilterCallback)();
typedef int (*SceFiosVprintfCallback)(const char *, char *);

enum FiosMemorySizes
{
    Fios_OpStorage = 0xA0040,
    Fios_ChunkStorage = 0xA0400,
    Fios_FhStorage = 0x8D040,
    Fios_DhStorage = 0x470,
};

enum SceFiosOpFlags
{
    SCE_FIOS_OPFLAG_IMMED = (1 << 0),
    SCE_FIOS_OPFLAG_DONTUSECACHE = (1 << 1),
    SCE_FIOS_OPFLAG_DONTFILLRAMCACHE = (1 << 2),
    SCE_FIOS_OPFLAG_DONTFILLDISKCACHE = (1 << 3),
    SCE_FIOS_OPFLAG_CACHEPERSIST = (1 << 4),
    SCE_FIOS_OPFLAG_UNCACHEDBUFFER = (1 << 5),
    SCE_FIOS_OPFLAG_NONDMABUFFER = (1 << 6),
    SCE_FIOS_OPFLAG_PERSISTENTPATH = (1 << 7),
    SCE_FIOS_OPFLAG_ALWAYSFILLRAMCACHE = (1 << 8),
    SCE_FIOS_OPFLAG_READONLYCACHE = (1 << 9),
    SCE_FIOS_OPFLAG_REUSECACHE = (1 << 10),
    SCE_FIOS_OPFLAG_DONTFILLCACHE = (1 << 11),
    SCE_FIOS_OPFLAG_NOCACHE = (1 << 12),
};

enum SceFiosOpEvents
{
    SCE_FIOS_OPEVENT_COMPLETE = 1,
    SCE_FIOS_OPEVENT_DELETE = 2,
    SCE_FIOS_OPEVENT_START = 3,
};

enum SceFiosWhence
{
    SCE_FIOS_SEEK_SET,
    SCE_FIOS_SEEK_CUR,
    SCE_FIOS_SEEK_END,
};

enum SceFiosOpenFlags
{
    SCE_FIOS_O_READ = (1 << 0),
    SCE_FIOS_O_RDONLY = (1 << 0),
    SCE_FIOS_O_WRITE = (1 << 1),
    SCE_FIOS_O_WRONLY = (1 << 1),
    SCE_FIOS_O_RDWR = 3,
    SCE_FIOS_O_APPEND = (1 << 2),
    SCE_FIOS_O_CREAT = (1 << 3),
    SCE_FIOS_O_TRUNC = (1 << 4),
    SCE_FIOS_O_DIRECT = (1 << 12),
};

enum SceFiosOverlayLimits
{
    SCE_FIOS_OVERLAY_MAX_OVERLAYS = 64,
    SCE_FIOS_OVERLAY_POINT_MAX = 292,
};

enum SceFiosOverlayType
{
    SCE_FIOS_OVERLAY_TYPE_OPAQUE,
    SCE_FIOS_OVERLAY_TYPE_TRANSLUCENT,
    SCE_FIOS_OVERLAY_TYPE_NEWER,
    SCE_FIOS_OVERLAY_TYPE_WRITABLE,
};

enum SceFiosIOSchedulerAlgorithm : __int32
{
    SCE_FIOS_IO_SCHED_DEADLINE,
    SCE_FIOS_IO_SCHED_PRIORITY,
    SCE_FIOS_IO_SCHED_FIFO,
    SCE_FIOS_IO_SCHED_MAXIMUM,
};

enum SceFiosIOThreadCount
{
    SCE_FIOS_IO_THREAD_COUNT_MIN = 1,
    SCE_FIOS_IO_THREAD_COUNT_MAX = 1,
};

enum SceFiosSchedulerThreadCount
{
    SCE_FIOS_SCHEDULER_THREAD_COUNT_MIN = 1,
    SCE_FIOS_SCHEDULER_THREAD_COUNT_MAX = 3,
    SCE_FIOS_SCHEDULER_THREAD_COUNT_DEFAULT = 1,
};

enum SceFiosPsarcDearchiverFlags
{
    SCE_FIOS_PSARC_DEARCHIVER_MOUNT_TRANSLUCENT = 1,
};

enum SceFiosThreadType
{
    SCE_FIOS_IO_THREAD,
    SCE_FIOS_DECOMPRESSOR_THREAD,
    SCE_FIOS_CALLBACK_THREAD,
    SCE_FIOS_THREAD_TYPES,
};

struct FIOS2HANDLE
{
    int mFH;
};

#ifdef __cplusplus
extern "C"
{
#endif

    uintptr_t extern sceFiosIOFilterCache;

    SceFiosSize extern sceFiosFHGetSize(SceFiosSize lFH);
    __int64 extern sceFiosIOFilterAdd(__int64 unk1);

#ifdef __cplusplus
}
#endif

#endif //_SCEFIOS2_H_