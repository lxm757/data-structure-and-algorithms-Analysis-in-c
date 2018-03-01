#include <stdio.h>
#include <string.h>

int main(void){
    char str[100];
    char _filename[] = "test003";
    FILE *fp = fopen(_filename, "r");
    /* fgets: change EOF to \n  */
    fgets(str, 100, fp);
    //printf("%s", str);
    int i, j, tmp;
    if ((tmp = strncmp(str, "#include", 8)) == 0){
        for (i = 8; str[i] == ' ' || str[i] == '\t'; i++);
        //printf("%d\n", i);
        for (j = 0; (str[j] = str[i]) != '\n'; i++, j++);
        str[j] = '\0';
        printf("%s\n", str);
    }
    //printf("%d\n", tmp);
    return 0;
}
