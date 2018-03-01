#include <stdio.h>

int main(void){
    void PrintReal(double, int);
    PrintReal(123.456, 3);
    return 0;
}

/*   */
void PrintDigit(int N){
    putchar('0' + N);
}

int IntPart(double N){
    return (int)N;
}

double DecPart(double N){
    return N - (int)N;
}

double RoundUp(double N, int DecPlaces){
    int i;
    double AmountToAdd = 0.5;
    for (i = 0; i < DecPlaces; i ++){
        AmountToAdd /= 10;
    }
    return N + AmountToAdd;
}

void PrintFractionPart(double FractionPart, int DecPlaces){
    int i, Adigit;
    for (i = 0; i < DecPlaces; i++){
        FractionPart *= 10;
        Adigit = IntPart(FractionPart);
        PrintDigit(Adigit);
        FractionPart = DecPart(FractionPart);
    }
}

void PrintOut(int IntegerPart){
    if (IntegerPart / 10){
        PrintOut(IntegerPart / 10);
    }
    putchar('0' + IntegerPart % 10);
}

void PrintReal(double N, int DecPlaces){
    int IntegerPart;
    double FractionPart;
    if (N < 0){
        putchar('-');
        N = -N;
    }
    N = RoundUp(N, DecPlaces);
    IntegerPart = IntPart(N);
    FractionPart = DecPart(N);
    PrintOut(IntegerPart);
    if (DecPlaces > 0){
        putchar('.');
    }
    PrintFractionPart(FractionPart, DecPlaces);
    putchar('\n');
}
