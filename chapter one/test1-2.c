#include <stdio.h>
#include <string.h>

/* set alphas  */
char v[4][4] = {
        {'t', 'h', 'i', 's'},
        {'w', 'a', 't', 's'},
        {'o', 'a', 'h', 'g'},
        {'f', 'g', 'd', 't'}
};

char _this[] = "this";
char _two[] = "two";
char _fat[] = "fat";
char _that[] = "that";
/* set words  */
char *words[4] = {
    _this, _two, _fat, _that
};


int main(void){
    void v_search(char [4][4], int, int);

    int i, j;
    for (i = 0; i < 4; i++){
        for (j = 0; j < 4; j++){
            v_search(v, i, j);
        }
    }
}

void v_search(char v[4][4], int x, int y){
    void w_search(char *);
    int i, j, p;
    char temp[5];
    /* north  */
    for (i = x, p = 0; i >= 0; i--){
        temp[p++] = v[i][y];
        temp[p] = '\0';
        w_search(temp);
    }
    /* south  */
    for (i = x, p = 0; i < 4; i++){
        temp[p++] = v[i][y];
        temp[p] = '\0';
        w_search(temp);
    }
    /* west  */
    for (j = y, p = 0; j >= 0; j--){
        temp[p++] = v[x][j];
        temp[p] = '\0';
        w_search(temp);
    }
    temp[p] = '\0';
    /* east  */
    for (j = y, p = 0; j < 4; j++){
        temp[p++] = v[x][j];
        temp[p] = '\0';
        w_search(temp);
    }
    /* northeast  */
    for (i = x, j = y, p = 0; i >= 0 && j < 4; i--, j++){
        temp[p++] = v[i][j];
        temp[p] = '\0';
        w_search(temp);
    }
    /* southeast  */
    for (i = x, j = y, p = 0; i < 4 && j < 4; i++, j++){
        temp[p++] = v[i][j];
        temp[p] = '\0';
        w_search(temp);
    }
    /* northwest  */
    for (i = x, j = y, p = 0; i >= 0 && j >= 0; i--, j--){
        temp[p++] = v[i][j];
        temp[p] = '\0';
        w_search(temp);
    }
    /* southwest  */
    for (i = x, j = y, p = 0; i < 4 && j >= 0; i++, j--){
        temp[p++] = v[i][j];
        temp[p] = '\0';
        w_search(temp);
    }
}

void w_search(char *s){
    //printf("search:%s\n", s);
    int i;
    for (i = 0; i < 4; i++){
        if (!strcmp(words[i], s)){
            printf("\tget:%s\n", s);
        }
    }
}
