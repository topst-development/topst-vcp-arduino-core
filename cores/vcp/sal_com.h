// SPDX-License-Identifier: Apache-2.0

/*
***************************************************************************************************
*
*   FileName : sal_com.h
*
*   Copyright (c) Telechips Inc.
*
*   Description :
*
*
***************************************************************************************************
*/

/* MISRA C:2012 - 4.10 */
#if !defined(SAL_COMMON_HEADER)
#define SAL_COMMON_HEADER

/*
***************************************************************************************************
*                                             [INCLUDE FILES]
***************************************************************************************************
*/

/*
***************************************************************************************************
*                                             [DEFINITIONS]
***************************************************************************************************
*/

/*
 * Primitive Type, AUTOSAR type, MISRA C:2012 - 4.6
 */
typedef char                            int8;       /*        -128 .. +127            */
typedef signed char                     sint8;      /*        -128 .. +127            */
typedef unsigned char                   uint8;      /*           0 .. 255             */
typedef short                           int16;      /*      -32768 .. +32767          */
typedef signed short                    sint16;     /*      -32768 .. +32767          */
typedef unsigned short                  uint16;     /*           0 .. 65535           */
typedef long                            int32;      /* -2147483648 .. +2147483647     */
typedef signed long                     sint32;     /* -2147483648 .. +2147483647     */
typedef unsigned long                   uint32;     /*           0 .. 4294967295      */
typedef long long                       int64;
typedef signed long long                sint64;
typedef unsigned long long              uint64;     /*       0..18446744073709551615  */

typedef int                             int32a;     /* -2147483648 .. +2147483647     */
typedef signed int                      sint32a;    /* -2147483648 .. +2147483647     */
typedef unsigned int                    uint32a;    /*           0 .. 4294967295      */

typedef uint32                          uintptr;
typedef sint32                          sintptr;

typedef uint32                          SALSize;

/*
 * Primitive Type, AUTOSAR type, MISRA C:2012 - 4.6
 */
#include <stdint.h>

typedef uint32_t                          SALSize;

/* MISRA C:2012-11.8, The macro NULL shall be the only permitted form of integer null pointer constant */
#ifndef NULL
#define NULL                            (0)
#endif

#ifndef NULL_PTR
#define NULL_PTR                        NULL //hsj((void *)0)
#endif

#ifndef FALSE
#define FALSE                           (0U)
#endif

#ifndef TRUE
#define TRUE                            (1U)
#endif

#define SALDisabled                     (FALSE)
#define SALEnabled                      (TRUE)

/*
 * Address Type
 */
typedef uint32_t                          SALAddr;

typedef volatile uint32_t                 SALReg32;
typedef volatile uint64_t                 SALReg64;

#define SAL_WriteReg(v, a)              (*((volatile uint32_t *)(a)) = (uint32_t)(v))
#define SAL_ReadReg(a)                  (*(volatile uint32_t *)(a))

/*
 * Handles
 */
typedef uint32_t                          SALFileHandle;
typedef uint32_t                          SALSearchHandle;
typedef uint32_t                          SALSockHandle;

/*
 * Specific Values
 */
#define SAL_MAX_QUEUE                   (32)
#define SAL_MAX_TASK                    (32)
#define SAL_MAX_SEMA                    (32)
#define SAL_MAX_EVENT                   (32)

#define SAL_MAX_INT_VAL                 (2147483647L)  /* MAX INT32 */
#define SAL_MAX_UINT_VAL                (4294967295UL) // MAX UINT32

#define SAL_ArraySize(x)                (sizeof(x)/sizeof((x)[0]))

#define SAL_OS_TIMER_ID                 (0UL)     /* HW Timer Resource for OS sheduling */

#define SAL_MEM_FUNC_IMPL      /* In case of using os memory library ex OS_MemCopy(), OS_MemSet()..etc   */
#define SAL_STRING_FUN_IMPL    /* In case of  using os string library. XXX_StrCopy(), XXX_Strlen()...etc */


/* MISRA C:2012-20.7
 * 4U          : 32-bit word size (in octets)
 * 8U          : Octet NBR bits
 * 4294967295U : Unsigned int Maximum value
 */
#define SAL_BitField(bit_field, bit_shift)                                       \
    ((((bit_field) >= (4U * 8U)) ? (4294967295UL)                                \
                                 : ((1u << (bit_field)) - 1UL)) << (bit_shift))

/*
 * Driver Identification
 */
typedef enum SALDriverIdTable
{
    SAL_DRVID_SAL                       = 100,
    SAL_DRVID_MPU                       = 300,
    SAL_DRVID_GIC                       = 400,
    SAL_DRVID_PEFALSH                   = 500,
    SAL_DRVID_DEFALSH                   = 600,
    SAL_DRVID_SFMC                      = 700,
    SAL_DRVID_CAN                       = 800,
    SAL_DRVID_GPSB                      = 900,
    SAL_DRVID_UART                      = 1000,
    SAL_DRVID_I2C                       = 1100,
    SAL_DRVID_PDM                       = 1200,
    SAL_DRVID_ICTC                      = 1300,
    SAL_DRVID_GDMA                      = 1400,
    SAL_DRVID_ADC                       = 1500,
    SAL_DRVID_I2S                       = 1600,
    SAL_DRVID_GMAC                      = 1700,
    SAL_DRVID_HSM                       = 1800,
    SAL_DRVID_TMR                       = 1900,
    SAL_DRVID_WDT                       = 2000,
    SAL_DRVID_CKC                       = 2100,
    SAL_DRVID_CMU                       = 2200,
    SAL_DRVID_GPIO                      = 2300,
    SAL_DRVID_PMIO                      = 2400,
    SAL_DRVID_PMU                       = 2500,
    SAL_DRVID_FMU                       = 2600,
    SAL_DRVID_RTC                       = 2700,
    SAL_DRVID_STSCFG                    = 2800,
    SAL_DRVID_DSE                       = 2900,
    SAL_DRVID_SM                        = 3000,
    SAL_DRVID_FWUG                      = 3100,
    SAL_DRVID_LIN                       = 3200,

} SALDriverId_t;

/*
 * Struct Types
 */
typedef struct SALVersionInfoTable
{
    uint8_t viMajorVersion;
    uint8_t viMinorVersion;
    uint8_t viPatchVersion;
    uint8_t viReserved;

} SALMcuVersionInfo_t;

typedef struct SALTimeValue
{
    uint32_t                              tvSec;     /* seconds           */
    uint32_t                              tvUsec;    /* and microseconds  */

} SALTimeValue_t;

/*
 * File open mode
 */
typedef enum SALFileMode
{
    SAL_FILE_READ                       = 1,  /**< Read                      */
    SAL_FILE_WRITE                      = 2,  /**< Write                     */
    SAL_FILE_READWRITE                  = 3,  /**< Read and Write            */
    SAL_FILE_CREATE                     = 4   /**< Create                    */

} SALFileMode_t;

/*
 * File seek mode
 */
typedef enum SALFileSeekOrigin
{
    SAL_SEEK_BEGIN                      = 0,  /**< Beginning of file         */
    SAL_SEEK_CUR                        = 1,  /**< Current position          */
    SAL_SEEK_END                        = 2   /**< End of file               */

} SALFileSeekOrigin_t;

/*
 * File Attribute
 */
#define SAL_FILE_ATTR_NORMAL            (0x00U)  /* Normal file - No read/write restrictions  */
#define SAL_FILE_ATTR_RDONLY            (0x01U)  /* Read only file                            */
#define SAL_FILE_ATTR_HIDDEN            (0x02U)  /* Hidden file                               */
#define SAL_FILE_ATTR_SYSTEM            (0x04U)  /* System file                               */
#define SAL_FILE_ATTR_SUBDIR            (0x10U)  /* Subdirectory                              */
#define SAL_FILE_ATTR_ARCH              (0x20U)  /* Archive file                              */

/*
 * Queue options, MISRA C:2012-7.3
 */
typedef enum SALBlockingOption
{
    SAL_OPT_BLOCKING                    = 0x00000000UL,
    SAL_OPT_NON_BLOCKING                = 0x00008000UL

} SALBlockingOption_t;

/*
 * Event options
 */
typedef enum SALEventOption
{
    SAL_EVENT_OPT_FLAG_SET              = 0x00000000UL,  /**< Initial state signaled                            */
    SAL_EVENT_OPT_CLR_ALL               = 0x00000001UL,  /**< Initial state nonsignaled                         */
    SAL_EVENT_OPT_CLR_ANY               = 0x00000002UL,  /**< Wait for ANY of the bits specified to be CLR      */
    SAL_EVENT_OPT_SET_ALL               = 0x00000004UL,  /**< Wait for ALL    the bits specified to be SET      */
    SAL_EVENT_OPT_SET_ANY               = 0x00000008UL,  /**< Wait for ANY of the bits specified to be SET      */
    SAL_EVENT_OPT_CONSUME               = 0x00000100UL,  /**< Consume the flags if condition(s) satisfied       */

} SALEventOption_t;

/*
 * Task Priority Setting
 */
typedef enum SALTaskPriority
{
    SAL_PRIO_ARDUINO_APP                   = 1,  /**< TOST APP task                        */
    SAL_PRIO_APP_CFG                    = 2,  /**< APP TASK START task                  */
    SAL_PRIO_POWER_MANAGER              = 3,  /**< Power Manager APP task               */
    SAL_PRIO_IPC_CONTROL                = 3,  /**< IPC Control task                     */
    SAL_PRIO_SYSTEM_MON                 = 4,  /**< System Monitoring APP task           */
    SAL_PRIO_CAN_DEMO                   = 4,  /**< CAN DEMO APP task                    */
    SAL_PRIO_AUDIO_TEST                 = 5,  /**< Audio Test APP task                  */
    SAL_PRIO_VSDR_MONITOR               = 5,  /**< Vehicle Signal DEMO APP task         */
    SAL_PRIO_SPILED_DEMO                = 6,  /**< SPILED Demo Task                     */
    SAL_PRIO_IPC_PARSER                 = 6,  /**< IPC Parser task                      */
    SAL_PRIO_KEY_APP                    = 6,  /**< KEY APP task                         */
    SAL_PRIO_UART_TEST                  = 6,  /**< Uart Test APP task                   */
    SAL_PRIO_LIN_TEST                   = 6,  /**< Lin Test APP task                    */
    SAL_PRIO_ETH_TASK                   = 6,  /**< Ethernet TX/RX task                  */
    SAL_PRIO_CONSOLE_DEMO               = 6,  /**< Console DEMO APP task                */
    SAL_PRIO_NVM_MAMAGER                = 8,  /**< NVM Manager APP task                 */
    SAL_PRIO_CONSOLE                    = 10, /**< Console task                         */
    SAL_PRIO_LOWEST                     = 12, /**< APP TASK START task                  */

} SALTaskPriority_t;


/*
 * Return Codes
 */
typedef enum SALRetCode
{
    SAL_RET_SUCCESS                     = 0,
    SAL_RET_FAILED                      = 1

} SALRetCode_t;

/*
 * Error Codes
 */
typedef enum SALErrorCode
{
    SAL_ERR_INIT                        = 100,  /**< Initialization error for each APIs             */
    SAL_ERR_NO_SPACE                    = 101,  /**< No more space (memory, channel, etc)           */
    SAL_ERR_INVALID_PARAMETER           = 102,  /**< Invalid parameter is passed                    */
    SAL_ERR_NOT_SUPPORT                 = 103,  /**< Not supported operation or resources           */
    SAL_ERR_TIMEOUT                     = 104,  /**< Timed out while processing                     */
    SAL_ERR_INVALID_HANDLE              = 105,  /**< Invalid handle is detected                     */
    SAL_ERR_NO_DATA                     = 106,  /**< No data                                        */
    SAL_ERR_UNDEF_STATE                 = 107,  /**< Not defined state                              */
    SAL_ERR_FAIL_CREATE                 = 108,  /**< Fail to create a component(Task, event, etc)   */
    SAL_ERR_FAIL_GET_DATA               = 109,  /**< Fail to get data from a component              */
    SAL_ERR_FAIL_SEND_DATA              = 110,  /**< Fail to send data to a component               */
    SAL_ERR_FAIL_START                  = 111,  /**< Fail to start a component                      */
    SAL_ERR_FAIL_DELETE                 = 112,  /**< Fail to delete a job of a component            */
    SAL_ERR_FAIL_RELEASE                = 113,  /**< Fail to release a job of a component           */
    SAL_ERR_UNINIT_ITEM                 = 114,  /**< Uninitialized item, variable, or contents      */
    SAL_ERR_OUTOF_SIZE                  = 115,  /**< Size overflow or is lower than threshold       */
    SAL_ERR_FAIL_GET_KEY                = 116,  /**< Fail to get key or ownership                   */
    SAL_ERR_FAIL_SET_CONFIG             = 117,  /**< Fail to set configuration or status            */
    SAL_ERR_NOT_USEFUL                  = 118   /**< The status is not available                    */

} SALErrorCode_t;

/*
 * Error Information
 */
typedef struct SALErrorInfoTable
{
    SALDriverId_t                       eiDrvId;    /* Driver/Module Id */
    uint32_t                              eiApiId;    /* API func Id      */
    SALErrorCode_t                      eiErrorId;  /* Error Id         */

} SALErrorInfo_t;

/*
***************************************************************************************************
*                                         [FUNCTION PROTOTYPES Types]
***************************************************************************************************
*/
/* Task start functions type */
typedef void                            (*SALTaskFunc) (void * pArg);

/* ARM Core */
typedef SALRetCode_t                    (*SALCoreMB) (void);
typedef SALRetCode_t                    (*SALCoreRMB) (void);
typedef SALRetCode_t                    (*SALCoreWMB) (void);
typedef SALRetCode_t                    (*SALCoreCriticalEnter) (void);
typedef SALRetCode_t                    (*SALCoreCriticalExit) (void);
typedef SALRetCode_t                    (*SALCoreWaitForEvent) (void);
typedef SALRetCode_t                    (*SALCoreDiv64To32) (uint64_t * pullDividend, uint32_t uiDivisor, uint32_t * puiRem);

/* OS Runtime */
typedef SALRetCode_t                    (*SALOSInitFunctions) (void);
typedef SALRetCode_t                    (*SALOSStart) (void);

/* Memory */
typedef SALRetCode_t                    (*SALMemAlloc) (void * pMem, uint32_t uiSize);
typedef SALRetCode_t                    (*SALMemCalloc) (void * pMem, uint32_t uiNum, SALSize uiSize);
typedef SALRetCode_t                    (*SALMemFree) (void * pMem);
typedef SALRetCode_t                    (*SALMemSet) (void * pMem, uint8_t ucValue, SALSize uiSize);
typedef SALRetCode_t                    (*SALMemCopy) (void * pDest, const void * pSrc, SALSize uiSize);
typedef SALRetCode_t                    (*SALMemCmp) (const void * pMem1, const void * pMem2, SALSize uiSize, int32_t * piRetCmp);
typedef SALRetCode_t                    (*SALStrCopy) (uint8_t * pucDestString, const uint8_t * pucSrcString);
typedef SALRetCode_t                    (*SALStrCmp) (const uint8_t * puc1String, const uint8_t * puc2String, int32_t * piRetCmp);
typedef SALRetCode_t                    (*SALStrNCmp) (const uint8_t * puc1String, const uint8_t * puc2String, SALSize uiLength, int32_t * piRetCmp);
typedef SALRetCode_t                    (*SALStrLength) (const int8_t * pucString, SALSize * puiLength);

/* File / Directory */
typedef SALRetCode_t                    (*SALFileOpenA) (SALFileHandle * puiFile, int8_t * pcFilename, SALFileMode_t uiMode);
typedef SALRetCode_t                    (*SALFileOpenW) (SALFileHandle * puiFile, int8_t * puhwFilename, SALFileMode_t uiMode);
typedef SALRetCode_t                    (*SALFileClose) (SALFileHandle uiFile);
typedef SALRetCode_t                    (*SALFileRead) (SALFileHandle uiFile, void * pBuf, uint32_t uiBytesToRead);
typedef SALRetCode_t                    (*SALFileWrite) (SALFileHandle uiFile, void * pBuf, uint32_t uiBytesToWrite);
typedef SALRetCode_t                    (*SALFileSeek) (SALFileHandle uiFile, uint32_t uiOffset, SALFileSeekOrigin_t uiOrigin);
typedef SALRetCode_t                    (*SALFileSize) (SALFileHandle uiFile);
typedef SALRetCode_t                    (*SALFileFreeDiskSpace) (int8_t * pcRootPathName);
typedef SALRetCode_t                    (*SALFileRemoveA) (int8_t * pcFilename );
typedef SALRetCode_t                    (*SALFileRemoveW) (int8_t * puhwFilename );
typedef SALRetCode_t                    (*SALFileRename) (int8_t * pcOldName, int8_t *pcNewName);
typedef SALRetCode_t                    (*SALFileGetAttribute) (int8_t * pcFilename, uint32_t * puiAttribute);
typedef SALRetCode_t                    (*SALDirMake) (int8_t * pcDirname);
typedef SALRetCode_t                    (*SALDirRemove) (int8_t * pcDirname);
typedef SALRetCode_t                    (*SALFindClose) (SALSearchHandle uiHandle);
typedef SALRetCode_t                    (*SALFileSizeEx) (SALFileHandle uiFile, uint32_t * puiSizeHigh, uint32_t * puiSizeLow);
typedef SALRetCode_t                    (*SALFileFreeDiskSpaceEx) (int8_t * pcRootPathName, SALSize * puiSizeHigh, SALSize * puiSizeLow);

/* Data Structure - Queue */
typedef SALRetCode_t                    (*SALQueueCreate) (uint32_t * puiId, const uint8_t * pucName, uint32_t uiDepth, SALSize uiDataSize);
typedef SALRetCode_t                    (*SALQueueDelete) (uint32_t uiId);
typedef SALRetCode_t                    (*SALQueueGet) (uint32_t uiId, void * pData, uint32_t * puiSizeCopied, uint32_t iTimeout, SALBlockingOption_t  ulOptions);
typedef SALRetCode_t                    (*SALQueuePut) (uint32_t uiId, void * pData, SALSize uiSize, int32_t iTimeout, SALBlockingOption_t  ulOptions);

/* Event */
typedef SALRetCode_t                    (*SALEventCreate) (uint32_t * puiId, const uint8_t * pucName, uint32_t uiInitialValue);
typedef SALRetCode_t                    (*SALEventDelete) (uint32_t uiId);
typedef SALRetCode_t                    (*SALEventSet) (uint32_t uiId, uint32_t uiEvent, SALEventOption_t ulOptions);
typedef SALRetCode_t                    (*SALEventGet) (uint32_t uiId, uint32_t uiEvent, uint32_t iTimeout, uint32_t uiOptions, uint32_t * puiFlags);

/* Mutex */
typedef SALRetCode_t                    (*SALMutexCreate) ( void );
typedef SALRetCode_t                    (*SALMutexDelete) (uint32_t uiId);
typedef SALRetCode_t                    (*SALMutexLock) (uint32_t uiId, uint32_t uiTimeoutmsec);
typedef SALRetCode_t                    (*SALMutexUnlock) (uint32_t uiId);

/* Semaphore */
typedef SALRetCode_t                    (*SALSemaphoreCreate) (uint32_t * puiId, const uint8_t * pucName, uint32_t uiInitialValue, SALBlockingOption_t ulOptions);
typedef SALRetCode_t                    (*SALSemaphoreDelete) (uint32_t uiId);
typedef SALRetCode_t                    (*SALSemaphoreRelease) (uint32_t uiId);
typedef SALRetCode_t                    (*SALSemaphoreWait) (uint32_t uiId, int32_t iTimeout, SALBlockingOption_t ulOptions);

/* Task */
typedef SALRetCode_t                    (*SALTaskCreate) (uint32_t * puiTaskId, const uint8_t * pucTaskName, SALTaskFunc fnTask, uint32_t * puiStackPtr, uint32_t uiStackSize, SALTaskPriority_t uiPriority, void * pTaskParam);
typedef SALRetCode_t                    (*SALTaskDelete) (uint32_t uiTaskId);
typedef SALRetCode_t                    (*SALTaskCurrent) (uint32_t * puiTaskId);
typedef SALRetCode_t                    (*SALTaskSleep) (uint32_t uiMilliSec);

/* Socket */
typedef SALSockHandle                   (*SALNetSocket) (uint32_t iType);
typedef SALRetCode_t                    (*SALNetClose) (SALSockHandle uiSock);
typedef SALRetCode_t                    (*SALNetConnect) (SALSockHandle uiSock, int8_t * pucAddr, uint16_t uhwPort, uint32_t uiTimeout);
typedef SALRetCode_t                    (*SALNetBind) (SALSockHandle uiSock, uint16_t uhwPort);
typedef SALRetCode_t                    (*SALNetSendTo) (SALSockHandle uiSock, int8_t * pcBuf, uint32_t uiLen, int8_t * pcAddr, uint16_t uhwPort);
typedef SALRetCode_t                    (*SALNetSend) (SALSockHandle uiSock, int8_t * pcBuf, uint32_t uiLen );
typedef SALRetCode_t                    (*SALNetRecvFrom) (SALSockHandle uiSock, int8_t * pcBuf, uint32_t uiLen, SALAddr * puiAddr, uint16_t * puhwPort, uint32_t uiTimeout);
typedef SALRetCode_t                    (*SALNetRecv) (SALSockHandle uiSock, int8_t * pcBuf, uint32_t uiLen, uint32_t uiTimeout);

/* Debugging */
typedef SALRetCode_t                    (*SALReportError) (SALDriverId_t uiDriverId, uint32_t uiApiId, uint32_t uiErrorCode, const int8_t * pucEtc);
typedef SALRetCode_t                    (*SALGetCurrentError) (SALErrorInfo_t * psInfo);

/* Etc */
/* Time */
typedef SALRetCode_t                    (*SALGetTickCount) (uint32_t * puiTickCount);
typedef SALRetCode_t                    (*SALHandleTick) ( void );
typedef SALRetCode_t                    (*SALGetVersion) (SALMcuVersionInfo_t * psVersion);
typedef SALRetCode_t                    (*SALGetSystemTickCount) (uint64_t * pullSysTickCount);
typedef SALRetCode_t                    (*SALIncreaseSystemTick) (uint64_t * pullSysTickCount);

/*
***************************************************************************************************
*                                             [DEFINITIONS of TCSAL Functions]
***************************************************************************************************
*/
/* ARM Core */
typedef struct SALCoreTable
{
    SALCoreMB                           fnCoreMB;
    SALCoreRMB                          fnCoreRMB;
    SALCoreWMB                          fnCoreWMB;
    SALCoreCriticalEnter                fnCoreCriticalEnter;
    SALCoreCriticalExit                 fnCoreCriticalExit;
    SALCoreWaitForEvent                 fnCoreWaitForEvent;
    SALCoreDiv64To32                    fnCoreDiv64To32;

} SALCoreFunc_t;

/* OS Runtime */
typedef struct SALOSRunTable
{
    SALOSInitFunctions                  fnOsInitFuncs;
    SALOSStart                          fnOsStart;

} SALOSRunFunc_t;

/* Memory */
typedef struct SALMemTable
{
    SALMemAlloc                         fnMemAlloc;
    SALMemCalloc                        fnMemCalloc;
    SALMemFree                          fnMemFree;
    SALMemSet                           fnMemSet;
    SALMemCopy                          fnMemCopy;
    SALMemCmp                           fnMemCmp;
    SALStrCopy                          fnStrCopy;
    SALStrCmp                           fnStrCmp;
    SALStrNCmp                          fnStrNCmp;
    SALStrLength                        fnStrLength;

} SALMemFunc_t;

/* File / Directory */
typedef struct SALFileTable
{
    SALFindClose                        fnFindClose;
    SALFileFreeDiskSpace                fnFileFreeDiskSpace;
    SALFileOpenA                        fnFileOpenA;
    SALFileRead                         fnFileRead;
    SALFileRemoveA                      fnFileRemoveA;
    SALFileSeek                         fnFileSeek;
    SALFileSize                         fnFileSize;
    SALFileWrite                        fnFileWrite;
    SALFileRename                       fnFileRename;
    SALFileGetAttribute                 fnFileGetAttribute;
    SALDirMake                          fnDirMake;
    SALDirRemove                        fnDirRemove;
    SALFileClose                        fnFileClose;
    SALFileSizeEx                       fnFileSizeEx;
    SALFileFreeDiskSpaceEx              fnFileFreeDiskSpaceEx;
    SALFileOpenW                        fnFileOpenW;
    SALFileRemoveW                      fnFileRemoveW;

} SALFileFunc_t;

typedef struct SALDataStructureTable
{
    SALQueueCreate                      fnQueueCreate;
    SALQueueDelete                      fnQueueDelete;
    SALQueueGet                         fnQueueGet;
    SALQueuePut                         fnQueuePut;

} SALDataStructFunc_t;

/* Synchronization Object */
typedef struct SALSyncObjectTable
{
    /* Event */
    SALEventCreate                      fnEventCreate;
    SALEventDelete                      fnEventDelete;
    SALEventSet                         fnEventSet;
    SALEventGet                         fnEventGet;

    /* Mutex */
    SALMutexCreate                      fnMutexCreate;
    SALMutexDelete                      fnMutexDelete;
    SALMutexLock                        fnMutexLock;
    SALMutexUnlock                      fnMutexUnlock;

    /* Semaphore */
    SALSemaphoreCreate                  fnSemaphoreCreate;
    SALSemaphoreDelete                  fnSemaphoreDelete;
    SALSemaphoreRelease                 fnSemaphoreRelease;
    SALSemaphoreWait                    fnSemaphoreWait;

} SALSyncObjectFunc_t;

/* Task */
typedef struct SALTaskTable
{
    SALTaskCreate                       fnTaskCreate;
    SALTaskCurrent                      fnTaskCurrent;
    SALTaskDelete                       fnTaskDelete;
    SALTaskSleep                        fnTaskSleep;

} SALTaskFunc_t;

/* Socket */
typedef struct SALSocketTable
{
    SALNetSocket                        fnNetSocket;
    SALNetClose                         fnNetClose;
    SALNetConnect                       fnNetConnect;
    SALNetBind                          fnNetBind;
    SALNetSendTo                        fnNetSendTo;
    SALNetSend                          fnNetSend;
    SALNetRecvFrom                      fnNetRecvFrom;
    SALNetRecv                          fnNetRecv;

} SALSocketFunc_t;

/* Debug */
typedef struct SALTraceTable
{
    SALReportError                      fnReportError;
    SALGetCurrentError                  fnGetCurrentError;

} SALTraceFunc_t;

/* Etc */
typedef struct SALEtcTable
{
    SALGetTickCount                     fnGetTickCount;
    SALHandleTick                       fnHandleTick;
    SALGetVersion                       fnGetVersion;
    SALGetSystemTickCount               fnGetSystemTickCount;
    SALIncreaseSystemTick               fnIncreaseSystemTick;

} SALEtcFunc_t;

#endif // SAL_COMMON_HEADER

