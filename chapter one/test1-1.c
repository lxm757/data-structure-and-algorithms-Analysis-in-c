#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "times.h"

int main(void){
    int v_search(int [], int);
    void v_sort(int [], int);
    int N;
    for (N = 100; N <= 100000; N *= 10){
        int i, k = N / 2;
    
        /* get N random numbers  */
        int v[N];
        srand((unsigned int)time(NULL));
        for (i = 0; i < N; i++){
            v[i] = rand() % (N * 10) + 1;
            while (v_search(v, i)){
                v[i] = rand() % (N * 10) + 1;
            }
        }
    
        /* sort 100 numbers */
        sstart();
        v_sort(v, N);
    
        /* print */
        printf("%d\n", v[k-1]);
        
        printf("%d time:%ld\n", N, sstop());
    }
    return 0;
}

void v_sort(int v[], int n){
    int i, j, temp;
    for (i = 0; i < n-1; i ++){
        for (j = 0; j < n-i-1; j++){
            if (v[j] > v[j+1]){
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}

int v_search(int v[], int i){
    int j;
    for (j = 0; j < i; j++){
        if (v[j] == v[i]){
            return 1;
        }
    }
    return 0;
}

