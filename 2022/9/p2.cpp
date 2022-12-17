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
    std::vector<std::pair<int,int>> vRope(10,std::make_pair(x,y));
    printf("vector is size %d.\n", vRope.size());
    int headX=x, headY=y, tailX=x, tailY=y;
    vvGrid[tailY][tailX] = '#';

    printf("minX=%d,maxX=%d,minY=%d,maxY=%d\n", minX, maxX, minY, maxY);
    for(int i=0,iSize=vMoves.size(); i<iSize; i++) {
        for(int j=0,jSize=vMoves[i].second; j<jSize; j++) {
            if(vMoves[i].first == 'U') {
                vRope[0].second++;
                headY++;
            }
            else if(vMoves[i].first == 'D') {
                vRope[0].second--;
                headY--;
            }
            else if(vMoves[i].first == 'L') {
                vRope[0].first--;
                headX--;
            }
            else if(vMoves[i].first == 'R') {
                vRope[0].first++;
                headX++;
            }
            for(int k=1,kSize=vRope.size(); k<kSize; k++) {
                if(std::abs(vRope[k-1].first - vRope[k].first) == 2) {
                    if(vRope[k-1].first > vRope[k].first)
                        vRope[k].first++;
                    else
                        vRope[k].first--;
                    if(vRope[k-1].second != vRope[k].second) {
                        if(std::abs(vRope[k-1].second - vRope[k].second) == 2) {
                            if(vRope[k-1].second > vRope[k].second)
                                vRope[k].second++;
                            else
                                vRope[k].second--;
                        }
                        else {
                            vRope[k].second = vRope[k-1].second;
                        }
                    }
                }
                if(std::abs(vRope[k-1].second - vRope[k].second) == 2) {
                    if(vRope[k-1].second > vRope[k].second)
                        vRope[k].second++;
                    else
                        vRope[k].second--;
                    if(vRope[k-1].first != vRope[k].first) {
                        if(std::abs(vRope[k-1].first - vRope[k].first) == 2) {
                            if(vRope[k-1].first > vRope[k].first)
                                vRope[k].first++;
                            else
                                vRope[k].first--;
                        }
                        else {
                            vRope[k].first = vRope[k-1].first;
                        }
                    }
                }
            }
/*            for(int k=vvGrid.size()-1; k>=0; k--) {
                for(int l=0,jSize=vvGrid[k].size(); l<jSize; l++)
                {
                    char toPrint = '.';
                    for(int m=vRope.size()-1; m>=0; m--) {
                        if(vRope[m].first == l && vRope[m].second == k)
                            toPrint = 48+m;
                    }
                    printf("%c", toPrint);
                }
                printf("\n");
            }
            printf("\n");
*/

            vvGrid[vRope[vRope.size()-1].second][vRope[vRope.size()-1].first] = '#';
        }
    }

    int count = 0;

    for(int i=vvGrid.size()-1; i>=0; i--) {
        for(int j=0,jSize=vvGrid[i].size(); j<jSize; j++) {
            printf("%c", vvGrid[i][j]);
            if(vvGrid[i][j] == '#')
                count++;
        }
        printf("\n");
    }

    printf("Count = %d\n", count);
    return 0;
}
