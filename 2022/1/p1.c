#include <stdio.h>

int main(int argc, char** argv) {
    if(argc < 2)
        return -1;

    FILE* inFile = NULL;
    
    if(fopen_s(&inFile, argv[1], "r"))
        return -1;

    int max = 0;
    int current = 0;
    int currentSum = 0;

    char buffer[20];
    while(fgets(buffer, sizeof(buffer), inFile) != NULL) {
        if(sscanf_s(buffer, "%d\n", &current) == EOF) {
            if(currentSum > max)
                max = currentSum;
            currentSum = 0;
        }
        else {
            currentSum += current;
        }
    }

    printf("%d\n", currentSum > max ? currentSum : max);
    return 0;
}
