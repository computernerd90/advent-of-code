#include <stdio.h>

int main(int argc, char** argv) {
    
    FILE* inFile = fopen(argv[1], "r");
    if(!inFile)
        return -1;

    int floor = 0;
    int c;
    while((c = fgetc(inFile)) != EOF) {
        floor += ((char) c == '(') ? 1 : ((char) c == ')') ? -1 : 0;
    }

    printf("%d\n", floor);


    return 0;
}
