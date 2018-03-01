#include <stdio.h>
#include <limits.h>

int main(void){
    int i;
    long a = 2;
    for (i = 0; i < 100; i++){
        a *= 2;
        printf("%-20ld\n", a);
    }
    return 0;
}
