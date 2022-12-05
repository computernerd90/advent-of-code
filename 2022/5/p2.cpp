#include <stdio.h>

#include <algorithm>
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
        numCrates = inStr.size() / 4;
        for(int i=0; i<numCrates; i++) {
            vStacks.push_back(std::vector<char>());
            if(inStr[4*i + 1] != ' ')
                vStacks[i].push_back(inStr[4*i + 1]);
        }
    }

    while(fgets(inLine, sizeof(inLine), inFile) != NULL) {
        std::string inStr(inLine);
        if(inStr.size() == 4*numCrates) {
            for(int i=0; i<numCrates; i++)
                if(inStr[4*i + 1] != ' ')
                   vStacks[i].push_back(inStr[4*i + 1]);
        }
        else if(inStr.size() == 1)
            for(int i=0; i<numCrates; i++) {
                vStacks[i].erase(vStacks[i].end() -1);
                std::reverse(std::begin(vStacks[i]),std::end(vStacks[i]));
            }
        else {
            int numMove,src,dest;

            sscanf(inLine, "move %d from %d to %d", &numMove, &src, &dest);

            std::copy(std::end(vStacks[src-1])-numMove, std::end(vStacks[src-1]), std::back_inserter(vStacks[dest-1]));
            vStacks[src-1].erase(vStacks[src-1].end()-numMove, vStacks[src-1].end());
        }
    }

    for(int i=0; i<numCrates; i++)
        printf("%c", *(vStacks[i].end()-1));
    printf("\n");

    return 0;
}
