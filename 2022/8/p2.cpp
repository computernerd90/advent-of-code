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

    int score = 0;

    for(int i=1,iSize=vTrees.size()-1; i < iSize; i++) {
        for(int j=1,jSize=vTrees[i].size()-1; j < jSize; j++) {
            int up=0,down=0,left=0,right=0;
            for(int k=j-1; k>=0; k--) {
                left++;
                if(vTrees[i][k] >= vTrees[i][j])
                    break;
            }

            for(int k=j+1; k<vTrees[i].size(); k++) {
                right++;
                if(vTrees[i][k] >= vTrees[i][j]) 
                    break;
            }

            for(int k=i-1; k>=0; k--) {
                up++;
                if(vTrees[k][j] >= vTrees[i][j]) 
                    break;
            }

            for(int k=i+1; k<vTrees.size(); k++) {
                down++;
                if(vTrees[k][j] >= vTrees[i][j]) 
                    break;
            }

            score = score > up*down*left*right ? score : up*down*left*right;
        }
    }

    printf("score = %d\n", score);

    return 0;
}
