#include <stdio.h>

int main(int argc, char** argv) {
    if(argc < 2)
        return -1;

    FILE* inFile = NULL;
    
    if(fopen_s(&inFile, argv[1], "r"))
        return -1;

    int max1 = 0,max2 = 0,max3 = 0;
    int current = 0;
    int currentSum = 0;

    char buffer[20];
    while(fgets(buffer, sizeof(buffer), inFile) != NULL) {
        if(sscanf_s(buffer, "%d\n", &current) == EOF) {
            if(currentSum > max1) {
                max3 = max2;
                max2 = max1;
                max1 = currentSum;
            }
            else {
                if(currentSum > max2) {
                    max3 = max2;
                    max2 = currentSum;
                }
                else if(currentSum > max3) {
                    max3 = currentSum;
                }
            }
            currentSum = 0;
        }
        else {
            currentSum += current;
        }
    }
    if(currentSum > max1) {
        max3 = max2;
        max2 = max1;
        max1 = currentSum;
    }

    printf("%d + %d + %d = %d\n", max1, max2, max3, max1 + max2 + max3);
    return 0;
}
