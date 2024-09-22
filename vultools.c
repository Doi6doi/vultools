#include "vultools.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vulkan/vulkan.h>


char * vtBuf = NULL;
uint32_t vtBufSize = 0;

void * vtl_realloc( void * old, size_t size ) {
   void * p = realloc( old, size );
   if ( 0 < size && ! p )
      vtl_die( "Out of memory" );
   return p;
}

bool vtl_nat( VcpStr s, uint32_t * i ) {
   *i = 0;
   VcpStr t = s;
   while ( *t ) {
      if ( '0' <= *t && *t <= '9' )
         *i = *i * 10 + *t - '0';
      else
         return false;
      ++t;
   }
   return t != s;
}

void vtl_grow( uint32_t size ) {
   if ( size <= vtBufSize ) return;
   vtBuf = vtl_realloc( vtBuf, size );
   vtBufSize = size;
}

VcpStr vtl_cat( VcpStr a, VcpStr b ) {
   uint32_t la = strlen( a );
   uint32_t lb = strlen( b );
   vtl_grow( la+lb+1 );
   vtBuf[0] = 0;
   strcat( vtBuf, a );
   strcat( vtBuf, b );
   return vtBuf;
}

bool vtl_same( VcpStr a, VcpStr b ) {
   if ( !a ) return !b;
   if ( !b ) return false;
   return 0 == strcmp( a, b );
}

uint32_t vtl_fread( void * stream, void * mem, uint32_t size ) {
   return size * fread( mem, size, 1, stream );
}

uint32_t vtl_fread_part( void * stream, void * mem, uint32_t size ) {
   return fread( mem, 1, size, stream );
}

uint32_t vtl_fwrite( void * stream, void * mem, uint32_t size ) {
   return size * fwrite( mem, size, 1, stream );
}

void vtl_die( VcpStr s ) {
   vtl_ewrite( s );
   exit(1);
}

bool vtl_read_block( void * stream, VtlStreamOp read, void * mem, uint32_t size ) {
   char * p = mem;
   while ( 0 < size ) {
      uint32_t n = read( stream, mem, size );
      if ( 0 == n ) return false;
      p += n;
      size -=n;
   }
   return true;
}

bool vtl_read_skip( void * stream, VtlStreamOp read, uint32_t size ) {
   static char buf[512];
   while ( 0 < size ) {
      uint32_t n = size <= 512 ? size : 512;
      n = read( stream, buf, n );
      if ( 0 == n ) return false;
      size -=n;
   }
   return true;
}

bool vtl_write_block( void * stream, VtlStreamOp write, void * mem, uint32_t size ) {
   char * p = mem;
   while ( 0 < size ) {
      uint32_t n = write( stream, mem, size );
      if ( 0 == n ) return false;
      p += n;
      size -= n;
   }
   return true;
}


void vtl_ewrite( VcpStr s ) {
   fprintf( stderr, "%s\n", s );
}


static int vtl_physical_type_cpu( VkPhysicalDeviceType pdt ) {
   switch ( pdt ) {
      case VK_PHYSICAL_DEVICE_TYPE_CPU: return 2;
      case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: return 1;
      default: return 0;
   }
}

int vtl_physical_cpu( void * p ) {
   VkPhysicalDevice pd = *(VkPhysicalDevice *)p;
   VkPhysicalDeviceProperties pdp;
   vkGetPhysicalDeviceProperties( pd, &pdp );
   return vtl_physical_type_cpu( pdp.deviceType );
}


/// átfedő intervallumok
static bool vtl_iv_overlap( int32_t a, uint32_t al, int32_t b, uint32_t bl ) {
   return (a <= b && b < a+al)
      || (b <= a && a < b+bl);
}

/// átfedő téglalapok
bool vtl_rect_overlap( VtlRect a, VtlRect b ) {
   return vtl_iv_overlap( a->left, a->width, b->left, b->width )
      && vtl_iv_overlap( a->top, a->height, b->top, b->height );
}
     


