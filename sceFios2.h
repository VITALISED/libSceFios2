#ifndef _SCEFIOS2_H_
#define _SCEFIOS2_H_

#include <cstdint>
#include <windows.h>

typedef int SceFiosOp;
typedef int SceFiosOverlayID;
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

typedef enum
{
    Fios_OpStorage    = 0xA0040,
    Fios_ChunkStorage = 0xA0400,
    Fios_FhStorage    = 0x8D040,
    Fios_DhStorage    = 0x470,
} FiosMemorySizes;

typedef enum
{
    SCE_FIOS_OPFLAG_IMMED              = (1 << 0),
    SCE_FIOS_OPFLAG_DONTUSECACHE       = (1 << 1),
    SCE_FIOS_OPFLAG_DONTFILLRAMCACHE   = (1 << 2),
    SCE_FIOS_OPFLAG_DONTFILLDISKCACHE  = (1 << 3),
    SCE_FIOS_OPFLAG_CACHEPERSIST       = (1 << 4),
    SCE_FIOS_OPFLAG_UNCACHEDBUFFER     = (1 << 5),
    SCE_FIOS_OPFLAG_NONDMABUFFER       = (1 << 6),
    SCE_FIOS_OPFLAG_PERSISTENTPATH     = (1 << 7),
    SCE_FIOS_OPFLAG_ALWAYSFILLRAMCACHE = (1 << 8),
    SCE_FIOS_OPFLAG_READONLYCACHE      = (1 << 9),
    SCE_FIOS_OPFLAG_REUSECACHE         = (1 << 10),
    SCE_FIOS_OPFLAG_DONTFILLCACHE      = (1 << 11),
    SCE_FIOS_OPFLAG_NOCACHE            = (1 << 12),
} SceFiosOpFlags;

typedef enum
{
    SCE_FIOS_OPEVENT_COMPLETE = 1,
    SCE_FIOS_OPEVENT_DELETE   = 2,
    SCE_FIOS_OPEVENT_START    = 3,
} SceFiosOpEvents;

typedef enum
{
    SCE_FIOS_SEEK_SET,
    SCE_FIOS_SEEK_CUR,
    SCE_FIOS_SEEK_END,
} SceFiosWhence;

typedef enum
{
    SCE_FIOS_O_READ   = (1 << 0),
    SCE_FIOS_O_RDONLY = (1 << 0),
    SCE_FIOS_O_WRITE  = (1 << 1),
    SCE_FIOS_O_WRONLY = (1 << 1),
    SCE_FIOS_O_RDWR   = (SCE_FIOS_O_READ + SCE_FIOS_O_WRITE),
    SCE_FIOS_O_APPEND = (1 << 2),
    SCE_FIOS_O_CREAT  = (1 << 3),
    SCE_FIOS_O_TRUNC  = (1 << 4),
    SCE_FIOS_O_DIRECT = (1 << 12),
} SceFiosOpenFlags;

typedef enum
{
    SCE_FIOS_OVERLAY_MAX_OVERLAYS = 64,
    SCE_FIOS_OVERLAY_POINT_MAX    = 292,
} SceFiosOverlayLimits;

typedef enum
{
    SCE_FIOS_OVERLAY_TYPE_OPAQUE,
    SCE_FIOS_OVERLAY_TYPE_TRANSLUCENT,
    SCE_FIOS_OVERLAY_TYPE_NEWER,
    SCE_FIOS_OVERLAY_TYPE_WRITABLE,
} SceFiosOverlayType;

typedef enum
{
    SCE_FIOS_IO_SCHED_DEADLINE,
    SCE_FIOS_IO_SCHED_PRIORITY,
    SCE_FIOS_IO_SCHED_FIFO,
    SCE_FIOS_IO_SCHED_MAXIMUM,
} SceFiosIOSchedulerAlgorithm;

typedef enum
{
    SCE_FIOS_IO_THREAD_COUNT_MIN = 1,
    SCE_FIOS_IO_THREAD_COUNT_MAX = 1,
} SceFiosIOThreadCount;

typedef enum
{
    SCE_FIOS_SCHEDULER_THREAD_COUNT_MIN     = 1,
    SCE_FIOS_SCHEDULER_THREAD_COUNT_MAX     = 3,
    SCE_FIOS_SCHEDULER_THREAD_COUNT_DEFAULT = 1,
} SceFiosSchedulerThreadCount;

typedef enum
{
    SCE_FIOS_PSARC_DEARCHIVER_MOUNT_TRANSLUCENT = 1,
} SceFiosPsarcDearchiverFlags;

typedef enum
{
    SCE_FIOS_IO_THREAD,
    SCE_FIOS_DECOMPRESSOR_THREAD,
    SCE_FIOS_CALLBACK_THREAD,
    SCE_FIOS_THREAD_TYPES,
} SceFiosThreadType;

typedef struct
{
    unsigned __int64 sizeOfContext;
    unsigned __int64 workBufferSize;
    void *pWorkBuffer;
    __int64 flags;
    __int64 reserved[3];
} SceFiosPsarcDearchiverContext;

typedef struct
{
    void *pPtr;
    unsigned __int64 length;
} SceFiosBuffer;

typedef struct
{
    unsigned __int64 sizeOfContext;
    unsigned __int64 workBufferSize;
    unsigned __int64 blockSize;
    void *pWorkBuffer;
    const char *pPath;
    __int64 flags;
    SceFiosRAMCacheCallback pCallback;
    void *pCallbackData;
    __int64 reserved;
} SceFiosRamCacheContext;

typedef struct
{
    unsigned __int32 initialized : 1;
    unsigned __int32 paramsSize : 15;
    unsigned __int32 pathMax : 16;
    unsigned int reserved1;
    unsigned int ioThreadCount;
    unsigned int threadsPerScheduler;
    unsigned __int32 extraFlag1 : 1;
    unsigned __int32 quiet : 1;
    unsigned __int32 extraFlags : 30;
    unsigned int maxChunk;
    unsigned __int8 maxDecompressorThreadCount;
    unsigned __int8 schedulerAlgorithm;
    unsigned __int8 reserved3;
    unsigned __int8 reserved4;
    __int64 reserved5;
    __int64 reserved6;
    SceFiosBuffer opStorage;
    SceFiosBuffer fhStorage;
    SceFiosBuffer dhStorage;
    SceFiosBuffer chunkStorage;
    SceFiosVprintfCallback pVprintf;
    SceFiosMemcpyCallback pMemcpy;
    void *reserved7;
    int threadPriority[3];
    int threadAffinity[3];
    int threadStackSize[3];
} SceFiosParams;

typedef struct
{
    __int64 deadline;
    SceFiosOpCallback pCallback;
    void *pCallbackContext;
    __int32 priority : 8;
    unsigned __int32 opflags : 24;
    unsigned int userTag;
    void *userPtr;
    void *pReserved;
} SceFiosOpAttr;

typedef struct
{
    unsigned __int32 openFlags : 16;
    unsigned __int32 opFlags : 16;
    unsigned int reserved;
    SceFiosBuffer buffer;
} SceFiosOpenParams;

typedef struct
{
    SceFiosSize fileSize;
    unsigned int statFlags;
    unsigned __int16 nameLength;
    unsigned __int16 fullPathLength;
    unsigned __int16 offsetToName;
    unsigned __int16 reserved[3];
    char fullPath[1024];
} SceFiosDirEntry;

typedef struct
{
    unsigned __int8 type;
    unsigned __int8 order;
    unsigned __int8 reserved[10];
    int id;
    char dst[292];
    char src[292];
} SceFiosOverlay;

typedef struct
{
    SceFiosSize fileSize;
    SceFiosDate accessDate;
    SceFiosDate modificationDate;
    SceFiosDate creationDate;
    unsigned int statFlags;
    unsigned int reserved;
    __int64 uid;
    __int64 gid;
    __int64 dev;
    __int64 ino;
    __int64 mode;
} SceFiosStat;

typedef struct
{
    SceFiosHandle mFH;
} FIOS2HANDLE;

typedef union {
    SceFiosRamCacheContext sceFiosIOFilterCache;
    SceFiosPsarcDearchiverContext sceFiosIOFilterPsarcDearchiver;
} SceFiosFilterContext;

#ifndef FIOS_TYPES_ONLY

#ifdef __cplusplus
extern "C"
{
#endif

    SceFiosRamCacheContext *WINAPI sceFiosIOFilterCache;
    SceFiosPsarcDearchiverContext *WINAPI sceFiosIOFilterPsarcDearchiver;

    SceFiosSize WINAPI sceFiosFHGetSize(SceFiosHandle lFH);
    __int64 WINAPI sceFiosIOFilterAdd(int unk1, uintptr_t lpIOFilter, SceFiosFilterContext *lpRamCacheContext);
    void WINAPI sceFiosInitialize(SceFiosParams lParams);
    __int64 WINAPI sceFiosIsValidHandle(int lFH);
    SceFiosSize WINAPI sceFiosFileGetSizeSync(SceFiosOpAttr lAttr, const char *lpacFilename);
    __int64 WINAPI sceFiosCachePrefetchFileSync(SceFiosOpAttr lAttr, const char *lpacFilename);
    __int64 WINAPI sceFiosExistsSync(SceFiosOpAttr lAttr, const char *lpacFilename);
    __int64 WINAPI sceFiosFileRead(
        SceFiosOpAttr lAttr, const char *lpacFilename, void *lpData, SceFiosSize liSize, SceFiosOffset liOffset);
    __int64 WINAPI sceFiosArchiveMountSync(
        SceFiosOpAttr lAttr, __int64 unk1, __int64 unk2, const char *lpMountPoint, __int64 unk3[2], __int64 unk4);
    SceFiosSize WINAPI sceFiosArchiveGetMountBufferSizeSync(__int64 unk1, const char *lpacFilename, __int64 unk2);
    __int64 WINAPI
    sceFiosFileReadSync(__int64 unk1, const char *lpacFilename, void *lpData, __int64 unk2, SceFiosOffset liOffset);
    __int64 WINAPI sceFiosOpGetError(__int64 unk1);
    __int64 WINAPI sceFiosOpDelete(__int64 unk1);
    __int64 WINAPI sceFiosOpWait(__int64 unk1);
    __int64 WINAPI sceFiosDHCloseSync(__int64 unk1, unsigned int unk2);
    __int64 WINAPI sceFiosDHReadSync(__int64 unk1, unsigned int unk2);
    __int64 WINAPI sceFiosDHOpenSync(__int64 unk1, unsigned int unk2, const char *lpacArchiveRoot, void *lpData);
    __int64 WINAPI sceFiosDHOpen(__int64 unk1, unsigned int unk2, const char *lpacArchiveRoot, void *lpData);
    __int64 WINAPI sceFiosOpGetActualCount(unsigned int unk1);
    const char *WINAPI sceFiosFHGetPath(SceFiosHandle lFH);
    __int64 WINAPI sceFiosFHTell(SceFiosHandle lFH);
    __int64 WINAPI sceFiosFHSeek(SceFiosHandle lFH, __int64 lpStart, __int64 lpEnd);
    __int64 WINAPI sceFiosFHCloseSync(__int64 unk1, SceFiosHandle lFh);
    __int64 WINAPI sceFiosFHWriteSync(__int64 unk1, SceFiosHandle lFh, void *lpData, __int64 liSize);
    // footnote for liSize: in cTkFileSystem::Read it's calculated as (liNumElements * liSize) then passed to fios.
    __int64 WINAPI sceFiosFHReadSync(__int64 unk1, SceFiosHandle lFh, void *lpData, __int64 liSize);
    __int64 WINAPI sceFiosFHOpenSync(__int64 unk1, SceFiosHandle lFh, const char *lpacFilename, __int64 unk2);

#ifdef __cplusplus
}
#endif

#endif // FIOS_TYPES_ONLY

#endif //_SCEFIOS2_H_