#ifndef AMX_MEMORY_H_INCLUDED
    #define AMX_MEMORY_H_INCLUDED

    // Alloca handling
    #if !defined HAVE_ALLOCA_H
        #if defined __GNUC__ || defined __LCC__ || defined __DMC__ || defined __ARMCC_VERSION || \
            (defined __WATCOMC__ && __WATCOMC__ >= 1200)
            #define HAVE_ALLOCA_H 1
        #endif
    #endif

    #if defined HAVE_ALLOCA_H
        #include <alloca.h>
    #elif defined __BORLANDC__
        #include <malloc.h>
    #endif

    #if defined __WIN32__ || defined _WIN32 || defined WIN32
        #if !defined alloca
        #define alloca(n)   _alloca(n)
        #endif
    #endif

    // Memory compaction margin
    #if !defined AMX_COMPACTMARGIN
        #define AMX_COMPACTMARGIN 64
    #endif
#endif