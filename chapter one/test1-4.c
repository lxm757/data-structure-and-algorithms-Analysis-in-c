#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 100

int main(void){
    void ProcessFile(const char *);
    char FileName[] = "test003";
    ProcessFile(FileName);
    return 0;
}

void ProcessFile(const char *FileName){
    FILE *fp = fopen(FileName, "r");
    if (fp == NULL){
        printf("error: can't open %s\n", FileName);
        exit(1);
    }
    char str[MAXLINE];
    int i, j;
    while (fgets(str, MAXLINE, fp) != NULL){
        if (strncmp(str, "#include", 8) == 0){
            /* skip blanks  */
            for (i = 8; str[i] == ' ' || str[i] == '\t'; i++);
            /* read filename  */
            for (j = 0; (str[j] = str[i]) != '\n'; i++, j++);
            str[j] = '\0';
            //printf("%s", str);
            ProcessFile(str);
        } else {
            fputs(str, stdout);
        }
    }
}
