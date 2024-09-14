#ifndef VULTOOLSARCHH
#define VULTOOLSARCHH


#if defined(_WIN32) || defined(_WIN64)

#include <winsock2.h>

#define VT_L16(x) x
#define VT_L32(x) x

#elif 

#elif defined(__linux__) || defined(__CYGWIN__)

#include <endian.h>

#define VTL_16(x) htole16(x)
#define VTL_32(x) htole32(x)

#endif


#endif // VULTOOLSARCHH
