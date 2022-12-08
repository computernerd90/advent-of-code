#include <stdio.h>

#include <algorithm>
#include <memory>
#include <numeric>
#include <set>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    FILE* inFile = fopen(argv[1], "r");

    if(!inFile)
        return -1;

    char inLine[10000];

    std::vector<std::string> vTrees;

    while(fgets(inLine, sizeof(inLine), inFile) != NULL) {
        std::string inStr(inLine);
        inStr = inStr.substr(0, inStr.size()-1);

        vTrees.emplace_back(inStr);
    }

    printf("vTrees.size() == %d, vTrees[0].size() == %d\n", vTrees.size(), vTrees[0].size());
    int numTrees = 2*vTrees.size() + 2*vTrees[0].size() - 4;

    for(size_t i=1,iSize=vTrees.size()-1; i < iSize; i++) {
        for(size_t j=1,jSize=vTrees[j].size()-1; j < jSize; j++) {
            bool visible = true;
            for(size_t k=0; k<j; k++) {
                if(vTrees[i][k] >= vTrees[i][j]) {
                    visible = false;
                    break;
                }
            }

            if(visible) {
                printf("Visible tree found at (%d, %d).\n", i, j);
                numTrees++;
                continue;
            }
            visible = true;

            for(size_t k=j+1,kSize=vTrees[j].size(); k<kSize; k++) {
                if(vTrees[i][k] >= vTrees[i][j]) {
                    visible = false;
                    break;
                }
            }

            if(visible) {
                printf("Visible tree found at (%d, %d).\n", i, j);
                numTrees++;
                continue;
            }
            visible = true;

            for(size_t k=0; k<i; k++) {
                if(vTrees[k][j] >= vTrees[i][j]) {
                    visible = false;
                    break;
                }
            }

            if(visible) {
                printf("Visible tree found at (%d, %d).\n", i, j);
                numTrees++;
                continue;
            }
            visible = true;

            for(size_t k=i+1; k<vTrees.size(); k++) {
                if(vTrees[k][j] >= vTrees[i][j]) {
                    visible = false;
                    break;
                }
            }

            if(visible) {
                printf("Visible tree found at (%d, %d).\n", i, j);
                numTrees++;
            }
        }
    }

    printf("numTrees = %d\n", numTrees);

    return 0;
}
