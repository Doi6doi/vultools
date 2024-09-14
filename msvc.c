#include "vultools.h"
#include <windows.h>
#include <stdio.h>

void vtl_ewrite_stamp( VcpStr msg ) {
   static DWORD last = 0;
   DWORD curr = GetTickCount();
   if ( last )
      fprintf( stderr, "%s: %ld\n", msg, curr-last );
   last = curr;
}
