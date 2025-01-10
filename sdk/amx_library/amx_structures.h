#ifndef AMX_STRUCTURES_H_INCLUDED
    #define AMX_STRUCTURES_H_INCLUDED

    #include "amx_cell.h"
    #include "amx_alignment.h"
    #include "amx_calling.h"

    struct tagAMX;
    typedef cell (AMX_NATIVE_CALL *AMX_NATIVE)(struct tagAMX *amx, const cell *params);
    typedef int (AMXAPI *AMX_CALLBACK)(struct tagAMX *amx, cell index, cell *result, const cell *params);
    typedef int (AMXAPI *AMX_DEBUG)(struct tagAMX *amx);
    typedef int (AMXAPI *AMX_IDLE)(struct tagAMX *amx, int AMXAPI Exec(struct tagAMX *, cell *, int));

    #if !defined _FAR
        #define _FAR
    #endif

    typedef struct tagAMX_NATIVE_INFO {
        const char _FAR *name;
        AMX_NATIVE func       PACKED;
    } AMX_NATIVE_INFO;

    #if !defined AMX_USERNUM
        #define AMX_USERNUM     4
    #endif
    #define sEXPMAX         19
    #ifndef sNAMEMAX
        #define sNAMEMAX      31
    #endif

    typedef struct tagAMX_FUNCSTUB {
        ucell address         PACKED;
        char name[sEXPMAX+1];
    } AMX_FUNCSTUB;

    typedef struct tagFUNCSTUBNT {
        ucell address         PACKED;
        uint32_t nameofs      PACKED;
    } AMX_FUNCSTUBNT;

    typedef struct tagFUNCPART {
        ucell address         PACKED;
    } AMX_FUNCPART;

    typedef struct tagFUNCWIDE {
        uintptr_t address     PACKED;
    } AMX_FUNCWIDE;

    typedef struct tagAMX {
        unsigned char _FAR *base PACKED;
        unsigned char _FAR *data PACKED;
        AMX_CALLBACK callback PACKED;
        AMX_DEBUG debug       PACKED;
        cell cip              PACKED;
        cell frm              PACKED;
        cell hea              PACKED;
        cell hlw              PACKED;
        cell stk              PACKED;
        cell stp              PACKED;
        int flags             PACKED;
        
        #if AMX_USERNUM > 0
            long usertags[AMX_USERNUM] PACKED;
            void _FAR *userdata[AMX_USERNUM] PACKED;
        #endif
        
        int error             PACKED;
        int paramcount;
        cell pri              PACKED;
        cell alt              PACKED;
        cell reset_stk        PACKED;
        cell reset_hea        PACKED;
        cell sysreq_d         PACKED;
        
        #if defined JIT
            int reloc_size      PACKED;
            long code_size      PACKED;
        #endif
    } AMX;

    typedef struct tagAMX_HEADER {
        int32_t size          PACKED;
        uint16_t magic        PACKED;
        char    file_version;
        char    amx_version;
        int16_t flags         PACKED;
        int16_t defsize       PACKED;
        int32_t cod           PACKED;
        int32_t dat           PACKED;
        int32_t hea           PACKED;
        int32_t stp           PACKED;
        int32_t cip           PACKED;
        int32_t publics       PACKED;
        int32_t natives       PACKED;
        int32_t libraries     PACKED;
        int32_t pubvars       PACKED;
        int32_t tags          PACKED;
        int32_t nametable     PACKED;
    } AMX_HEADER;
#endif