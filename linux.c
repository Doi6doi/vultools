

void vtl_ewrite_stamp( VcpStr msg ) {
   static uint64_t last = 0;
   struct timespec ts;
   clock_gettime(CLOCK_MONOTONIC, &ts);
   uint64_t curr = (uint64_t)(ts.tv_nsec / 1000000) 
      + ((uint64_t)ts.tv_sec * 1000ull);
   if ( last )
      fprintf( stderr, "%s: %ld\n", msg, curr-last );
   last = curr;
}
