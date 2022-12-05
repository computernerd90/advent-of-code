#include <stdio.h>

int main(int argc, char** argv) {
    FILE* inFile = fopen(argv[1], "r");

    if(!inFile)
        return -1;

    int l1,h1,l2,h2;
    int num = 0;
    while(fscanf(inFile, "%d-%d,%d-%d", &l1, &h1, &l2, &h2) != EOF) {
        if((l1 >= l2 && h1 <= h2) || (l1 <= l2 && h1 >= h2))
            num++;
    }

    printf("%d\n", num);

    return 0;
}
