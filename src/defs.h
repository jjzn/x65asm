#ifndef __defs_h
#define __defs_h

#ifdef DEBUG
    #define debug(...) fprintf(stderr, "DEBUG: " __VA_ARGS__)
#else
    #define debug(...)
#endif /* DEBUG */

#endif /* __defs_h */
