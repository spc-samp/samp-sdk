#ifndef AMX_CELL_H_INCLUDED
    #define AMX_CELL_H_INCLUDED

    #include <stdint.h>

    // Cell size configuration
    #if !defined PAWN_CELL_SIZE
        #define PAWN_CELL_SIZE 32
    #endif

    #if PAWN_CELL_SIZE==16
        typedef uint16_t  ucell;
        typedef int16_t   cell;
    #elif PAWN_CELL_SIZE==32
        typedef uint32_t  ucell;
        typedef int32_t   cell;
    #elif PAWN_CELL_SIZE==64
        typedef uint64_t  ucell;
        typedef int64_t   cell;
    #else
        #error Unsupported cell size (PAWN_CELL_SIZE)
    #endif

    // Pointer width handling
    #if defined __64BIT__ && PAWN_CELL_SIZE < 64
        #define AMX_DONT_RELOCATE
        #define AMX_WIDE_POINTERS
    #elif defined __32BIT__ && PAWN_CELL_SIZE < 32
        #define AMX_DONT_RELOCATE
        #define AMX_WIDE_POINTERS
    #endif

    #define UNPACKEDMAX   (((ucell)1 << (sizeof(ucell)-1)*8) - 1)
    #define UNLIMITED     (~1u >> 1)

    // Character handling
    #define CHARBITS (8*sizeof(char))
    #if PAWN_CELL_SIZE==16
        #define CHARMASK (0xffffu << 8*(2-sizeof(char)))
    #elif PAWN_CELL_SIZE==32
        #define CHARMASK (0xffffffffuL << 8*(4-sizeof(char)))
    #elif PAWN_CELL_SIZE==64
        #define CHARMASK (0xffffffffffffffffuLL << 8*(8-sizeof(char)))
    #else
        #error Unsupported cell size
    #endif

    // Floating point support
    #if PAWN_CELL_SIZE==32
        #define amx_ftoc(f)   (*(cell*)&(f))
        #define amx_ctof(c)   (*(float*)&(c))
    #elif PAWN_CELL_SIZE==64
        #define amx_ftoc(f)   (*(cell*)&(f))
        #define amx_ctof(c)   (*(double*)&(c))
    #endif
#endif