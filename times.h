#ifndef _times_
#define _times_

#include <time.h>

/* get now time  */
time_t gettime(void);

/* get runtime by auto calculate  */
/* start calculate  */
void sstart(void);
/* stop calculate and return runtime  */
time_t sstop(void);

#endif
