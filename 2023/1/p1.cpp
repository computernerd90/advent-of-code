#include <stdio.h>

int main(int argc, char** argv) {
    FILE* fInput = fopen(argv[1],"r");

    char line[300];

    int result = 0;
    int firstDigit,secondDigit;

    while(fgets(line, sizeof(line), fInput)) {
        firstDigit = -1;
        secondDigit = -1;
        for(int i=0; line[i] != '\n'; i++) {
            if(line[i] == ' ' || line[i] == '\n')
                continue;
            line[i] -= 48;
            if(line[i] >= 0 && line[i] <= 9) {
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

        printf("%d%d\n", firstDigit, secondDigit);

        result += 10*firstDigit + secondDigit;
    }

    printf("Answer: %d\n", result);

    return 0;
}
