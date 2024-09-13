#ifndef VULTOOLSH
#define VULTOOLSH

#include <stdbool.h>
#include <stdint.h>

typedef const char * VcpStr;

/// téglalap
typedef struct VtlRect {
   int32_t top, left;
   uint32_t width, height;
} * VtlRect;

/// stream read or write error
#define VTL_STREAMERR -15001

/// custom read or write operation
typedef uint32_t (* VtlStreamOp)( void * stream, void * mem, uint32_t size );

/// fread as VtlStreamOp
uint32_t vtl_fread( void * stream, void * mem, uint32_t size );
/// fread as VtlStreamOp, can read less than full block
uint32_t vtl_fread_part( void * stream, void * mem, uint32_t size );
/// fwrite as VtlStreamOp
uint32_t vtl_fwrite( void * stream, void * mem, uint32_t size );
/// write a complete block
bool vtl_write_block( void * stream, VtlStreamOp write, void * mem, uint32_t size );
/// read a complete block
bool vtl_read_block( void * stream, VtlStreamOp read, void * mem, uint32_t size );
/// skip reading bytes
bool vtl_read_skip( void * stream, VtlStreamOp read, uint32_t size );

/// write line to std error
void vtl_ewrite( VcpStr s );
/// write line to std error and die
void vtl_die( VcpStr s );

/// string to natural number
bool vtl_nat( VcpStr s, uint32_t * nat );
/// concatenate strings (uses one static buffer)
VcpStr vtl_cat( VcpStr a, VcpStr b );
/// same strings (NULL proof)
bool vtl_same( VcpStr a, VcpStr b );

/// átfedő területek
bool vtl_rect_overlap( VtlRect a, VtlRect b );

/// write to stderr msec passed since last call
void vtl_ewrite_stamp();

/// choose cpu as graphical card
int vtl_physical_cpu( void * p );

#endif // VULTOOLSH

