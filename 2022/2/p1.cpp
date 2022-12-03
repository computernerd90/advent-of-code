#include <stdio.h>

int main(int argc, char** argv) {
    int score=0;

    FILE* inFile = fopen(argv[1], "r");

    if(!inFile)
        return -1;
    
    char player1, player2;
    while(fscanf(inFile, "%c %c\n",&player1,&player2) != EOF) {
        player2 -= 'X' - 'A';
        
        int result = 0;
        if(player1 == 'A')
            result += player2 == 'A' ? 3 : player2 == 'B' ? 6 : 0;
        if(player1 == 'B')
            result += player2 == 'B' ? 3 : player2 == 'C' ? 6 : 0;
        if(player1 == 'C')
            result += player2 == 'C' ? 3 : player2 == 'A' ? 6 : 0;
        
        score += result;

        score += player2 - 'A' + 1;
        printf("%c %c, %d points for hand, %d points for result\n", player1, player2, player2 - 'A' + 1, result);
    }

    printf("Final Score: %d\n", score);

    return 0;
}
