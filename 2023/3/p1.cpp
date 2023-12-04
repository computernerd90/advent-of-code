#include <stdio.h>

#include <string>
#include <utility>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <fmt/core.h>

bool isDigit(char inChar) {
    return inChar >= '0' && inChar <= '9';
}

int main(int argc, char** argv) {
    FILE* fInput = fopen(argv[1], "r");

    char line[300];

    std::vector<std::string> vTable;
    std::vector<std::tuple<int,int,int>> vNums;

    while(fgets(line,sizeof(line),fInput)) {
        std::string strLine(line);
        strLine.erase(strLine.end()-1);
        fmt::print("{}\n", strLine);
        vTable.emplace_back(strLine);
    }

    fmt::print("\n");

    for(size_t i=0, iSize=vTable.size(); i<iSize; i++) {
        for(size_t j=0,jSize=vTable[i].size(); j<jSize; j++) {
            int start = j;
            while(isDigit(vTable[i][j]) && j<jSize) {
                j++;
            }
            int end = j - 1;
            if(j != start) {
                vNums.emplace_back(std::make_tuple(i,start,end));
            }
        }
    }

    int sum=0;

    for(size_t i=0, iSize=vNums.size(); i<iSize; i++) {
        fmt::print("Num in row {}, from column {} to {}.\n", std::get<0>(vNums[i]), std::get<1>(vNums[i]), std::get<2>(vNums[i]));

        size_t startRow=std::get<0>(vNums[i]), endRow=std::get<0>(vNums[i]);
        if(startRow != 0)
            startRow -= 1;
        if(endRow != vTable.size()-1)
            endRow += 1;

        size_t startCol=std::get<1>(vNums[i]),endCol=std::get<2>(vNums[i]);
        if(startCol != 0)
            startCol -= 1;
        if(endCol != vTable[0].size()-1)
            endCol += 1;
        bool invalidNum = true;
        for(size_t j=startRow,jSize=endRow+1; j<jSize; j++) {
            for(size_t k=startCol,kSize=endCol+1; k<kSize; k++) {
                if(vTable[j][k] != '.' && !isDigit(vTable[j][k])) {
                    invalidNum = false;
                    j = jSize;
                    k = kSize;
                    break;
                }
            }
        }
        if(!invalidNum) {
            std::string strNum(vTable[std::get<0>(vNums[i])], std::get<1>(vNums[i]), std::get<2>(vNums[i])-std::get<1>(vNums[i])+1);
            fmt::print("Valid num: {}\n", strNum);
            sum += boost::lexical_cast<int>(strNum);
        }
    }

    fmt::print("Sum is {}.\n", sum);
    return 0;
}
