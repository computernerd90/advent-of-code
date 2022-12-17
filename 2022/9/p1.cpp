#include <stdio.h>

#include <cmath>

#include <string>
#include <tuple>
#include <utility>
#include <vector>

int main(int argc, char** argv) {
    FILE* inFile = fopen(argv[1], "r");

    if(!inFile)
        return -1;

    char inLine[10];

    std::vector<std::pair<char, int>> vMoves;

    while(fgets(inLine, sizeof(inLine), inFile) != NULL) {
        char direction;
        int steps;
        
        sscanf(inLine, "%c %d\n", &direction, &steps);

        vMoves.emplace_back(std::make_pair(direction, steps));
    }

    int minX=0,minY=0,maxX=0,maxY=0;
    int x=0,y=0;
    for(auto itr = vMoves.begin(), itrEnd = vMoves.end(); itr != itrEnd; ++itr) {
        switch(itr->first) {
            case 'U':
                y += itr->second;
                break;
            case 'D':
                y -= itr->second;
                break;
            case 'L':
                x -= itr->second;
                break;
            case 'R':
                x += itr->second;
                break;
            default:
                printf("Not supposed to be here.\n");
                break;
        }
        if(x < minX)
            minX = x;
        else if(x > maxX)
            maxX = x;

        if(y < minY)
            minY = y;
        else if(y > maxY)
            maxY = y;
    }

    std::vector<std::vector<char>> vvGrid;
    for(int i=0; i<(maxY-minY+1); i++)
        vvGrid.emplace_back(std::vector<char>(maxX-minX+1,'.'));
    x = -minX;
    y = -minY;
    int headX=x, headY=y, tailX=x, tailY=y;
    vvGrid[tailY][tailX] = '#';

    printf("minX=%d,maxX=%d,minY=%d,maxY=%d\n", minX, maxX, minY, maxY);
    for(int i=0,iSize=vMoves.size(); i<iSize; i++) {
        for(int j=0,jSize=vMoves[i].second; j<jSize; j++) {
            /*for(int k=0; k<(maxY-minY+1); k++) {
                for(int l=0; l<(maxX-minX+1); l++) {
                    char c = '.';
                    if(l == tailX && k == tailY)
                        c = 'T';
                    if(l == headX && k == headY)
                        c = 'H';
                    printf("%c",c);
                }
                printf("\n");
            }
            printf("\n");*/
            printf("headX=%d,headY=%d,tailX=%d,tailY=%d\n", headX, headY, tailX, tailY);
            if(vMoves[i].first == 'U') {
                headY++;
            }
            else if(vMoves[i].first == 'D') {
                headY--;
            }
            else if(vMoves[i].first == 'L') {
                headX--;
            }
            else if(vMoves[i].first == 'R') {
                headX++;
            }
            if(std::abs(headX - tailX) == 2) {
                if(headX > tailX)
                    tailX++;
                else
                    tailX--;
                if(headY != tailY)
                    tailY = headY;
            }
            else if(std::abs(headY - tailY) == 2) {
                if(headY > tailY)
                    tailY++;
                else
                    tailY--;
                if(headX != tailX)
                    tailX = headX;
            }
            vvGrid[tailY][tailX] = '#';
        }
    }

    int count = 0;
    for(auto row: vvGrid)
        for(auto c: row)
            if(c == '#')
                count++;

    printf("Count = %d\n", count);
    return 0;
}
