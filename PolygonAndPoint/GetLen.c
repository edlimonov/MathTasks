#include <stdio.h>

int GetLen(FILE *i, FILE *o) {
    int len = 0; double n;
    while(fscanf(i, "%lf", &n) == 1) len++;

    if ((len == 0) || (len%2 != 0)){
        fprintf(o, "Недостаточно данных");
        fclose(i);
        fclose(o);
        return -1;
    }
    return (len/2);
}
