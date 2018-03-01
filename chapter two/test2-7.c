#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "times.h"

int main(void){
    void usetest(void (*)(int), long l, long r);
    void test1(int);
    void test2(int);
    void test3(int);
    printf("- usetest3 -\n");
    usetest(test3, 10000, 640000);
    return 0;
}

void usetest(void (*test)(int),long l, long r){
    int j;
    long i, avg;
    for (i = l; i <= r; i *= 2){
        avg = 0;
        for (j = 0; j < 10; j++){
            sstart();
            test(i);
            time_t t = sstop();
            avg += t;
        }
        printf("%-10ld avg time:%ld\n", 
                i, avg / 10);
    }
}

void test1(int n){
    void printarr(int [], int);
    int RandInt(int, int);
    srand((unsigned int)time(NULL));
    int A[n];
    int i, j, tmp;
    for (i = 0; i < n; i++){
        tmp = RandInt(0, n-1);
        for (j = 0; j < i; j++){
            if (tmp == A[j]){
                tmp = RandInt(0, n-1);
                j = 0;
                j --;
            }
        }
        A[i] = tmp;
    }
    //printarr(A, n);
}

void test2(int n){
    void printarr(int [], int);
    int RandInt(int, int);
    srand((unsigned int)time(NULL));
    int used[n];
    int A[n];
    int i, tmp;
    for (i = 0; i < n; i++){
        used[i] = 0;
    }
    for (i = 0; i < n; i++){
        tmp = RandInt(0, n-1);
        while (used[tmp]){
            tmp = RandInt(0, n-1);
        }
        A[i] = tmp;
        used[tmp] = 1;
    }
    //printarr(A, n);
}

void test3(int n){
    void printarr(int [], int);
    void swap(int *, int *);
    int RandInt(int, int);
    srand((unsigned int)time(NULL));
    int A[n];
    int i;
    for (i = 0; i < n; i++){
        A[i] = i;
    }
    for (i = 0; i < n; i++){
        swap(&A[i], &A[RandInt(0, n-1)]);
    }
    //printarr(A, n);
}

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void printarr(int v[], int n){
    int i;
    for (i = 0; i < n; i++){
        if (i+1 % 10 == 0){
            putchar('\n');
        }
        printf("%d\n", v[i]);
    }
    putchar('\n');
}

int RandInt(int i, int j){
    return rand()%(j-i+1) + i;
}
