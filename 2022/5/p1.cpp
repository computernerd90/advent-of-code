#include <stdio.h>

#include <string>
#include <vector>

int main(int argc, char** argv) {
    FILE* inFile = fopen(argv[1], "r");

    if(!inFile)
        return -1;

    char inLine[100];

    int numCrates = 0;
    std::vector<std::vector<char>> vStacks;

    if(fgets(inLine, sizeof(inLine), inFile) != NULL) {
        std::string inStr(inLine);
        numCrates = inStr.size() / 3;
        for(int i=0; i<numCrates; i++) {
            vStacks.push_back(std::vector<char>());
            vStacks[i].push_back(inStr[3*i + 1]);
        }
    }

    while(fgets(inLine, sizeof(inLine), inFile) != NULL) {
        std::string inStr(inLine);
        if(inStr.size() == 3*numCrates) {
            for(int i=0; i<numCrates; i++)
                vStacks[i].push_back(inStr[3*i + 1]);
        }
    }

    for(int i=0; i<numCrates; i++) {
        for(int j=0,stackSize=vStacks[i].size(); j<stackSize; j++)
            printf("%c ", vStacks[i][j]);
        printf("\n");
    }

    return 0;
}
