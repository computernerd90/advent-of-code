#include <stdio.h>

int main(int argc, char** argv) {
    
    FILE* inFile = fopen(argv[1], "r");
    if(!inFile)
        return -1;

    int floor = 0;
    int c, position=0;
    while((c = fgetc(inFile)) != EOF) {
        position++;
        floor += ((char) c == '(') ? 1 : ((char) c == ')') ? -1 : 0;
        if(floor == -1)
            break;
        printf("%c %d, ", c, position);
    }

    printf("\n");

    printf("%d\n", position);


    return 0;
}
