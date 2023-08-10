#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t      strlen( const char * );
int         strcmp( const char *, const char *  );
void        strcat( char *dest, const char *src );
void        strcpy( char *dest, const char *src );



#ifdef __cplusplus
}
#endif
