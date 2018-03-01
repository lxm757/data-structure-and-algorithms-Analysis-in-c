#include <stdio.h>
#include <time.h>
#include <sys/time.h>

static time_t stime;
static struct timeval sval;

///* get time  */
//int main(void){
//    sstart();
//    for (int i=0; i < 10; i ++){
//        putchar('a'+i);
//    }
//    putchar('\n');
//    printf("%ld\n", sstop());
//    return 0;
//}

/* get now time  */
time_t gettime(void){
    struct timeval start;
    gettimeofday(&start, NULL);
    return start.tv_usec +
        start.tv_sec * 1000000;
}

/* auto calculate  */
/* start  */
void sstart(void){
    gettimeofday(&sval, NULL);
    stime = sval.tv_usec + 
        sval.tv_sec * 1000000;
    //printf("\tsstart:%ld\n", stime);
}

/* end  */
time_t sstop(void){
    gettimeofday(&sval, NULL);
    time_t t = sval.tv_usec +
        sval.tv_sec * 1000000;
    //printf("\tsstop:%ld\n", t);
    return t - stime;
}
