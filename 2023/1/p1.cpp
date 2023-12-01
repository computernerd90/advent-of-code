#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fInput = fopen(argv[1],"r");

    char line[300];

    int result = 0;
    int firstDigit,secondDigit;

    while(fgets(line, sizeof(line), fInput)) {
        firstDigit = -1;
        secondDigit = -1;
        for(int i=0, iSize=sizeof(line); i < iSize; i++) {

            printf("char is %c, integer value shifted down 48 is %d.\n", line[i], line[i]-48);

            line[i] -= 48;
            if(line[i] >= 0 && line[i] <= 8) {
                if(firstDigit == -1) {
                    firstDigit = line[i];
                }
                else {
                    secondDigit = line[i];
                }
            }
        }

        if(secondDigit == -1) {
            secondDigit = firstDigit;
        }

        printf("Number is %d%d\n", firstDigit,secondDigit);

        result += 10*firstDigit + secondDigit;
    }

    printf("Answer: %d\n", result);

    return 0;
}
