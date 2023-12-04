#include <stdio.h>

#include <string>
#include <utility>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <fmt/core.h>

bool isDigit(char inChar) {
    return inChar >= '0' && inChar <= '9';
}

void printCandidates(std::vector<std::tuple<int,int,int>>& v) { 
    for(auto itr = v.begin(), itrEnd = v.end(); itr != itrEnd; ++itr)
        fmt::print("Gear in row {}, column {}.\n", std::get<0>(*itr), std::get<1>(*itr));
}

void removeDups(std::vector<std::tuple<int,int,int>>& v) {
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = std::remove(it+1, end, *it);
/*        end = std::remove_if(it + 1, end, [it](auto rhs) {
            return std::get<0>(*it) == std::get<0>(rhs)
            && std::get<1>(*it) == std::get<1>(rhs)
            && std::get<2>(*it) == std::get<2>(rhs);
            });*/
    }
 
    v.erase(end, v.end());
}

int main(int argc, char** argv) {
    FILE* fInput = fopen(argv[1], "r");

    char line[300];

    std::vector<std::string> vTable;
    std::vector<std::tuple<int,int,int>> vNums;
    std::vector<std::tuple<int,int>> vGears;

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
            if(vTable[i][j] == '*') {
                vGears.emplace_back(std::make_tuple(i,j));
            }
        }
    }

    int sum=0;

    for(size_t i=0, iSize=vGears.size(); i<iSize; i++) {
        fmt::print("Gear in row {}, column {}.\n", std::get<0>(vGears[i]), std::get<1>(vGears[i]));

        size_t startRow=std::get<0>(vGears[i]), endRow=std::get<0>(vGears[i]);
        if(startRow != 0)
            startRow -= 1;
        if(endRow != vTable.size()-1)
            endRow += 1;

        size_t startCol=std::get<1>(vGears[i]),endCol=std::get<1>(vGears[i]);
        if(startCol != 0)
            startCol -= 1;
        if(endCol != vTable[0].size()-1)
            endCol += 1;

        std::vector<std::tuple<int,int,int>> vCandidates;
        for(size_t j=startRow,jSize=endRow+1; j<jSize; j++) {
            for(size_t k=startCol,kSize=endCol+1; k<kSize; k++) {
                if(isDigit(vTable[j][k])) {
                    auto itrNum = std::find_if(std::begin(vNums), std::end(vNums), [j,k] (std::tuple<int,int,int> num) {
                        return std::get<0>(num) == j && (std::get<1>(num) <= k && std::get<2>(num) >= k);
                    });
                    vCandidates.emplace_back(*itrNum);
                }
            }
        }
 
        removeDups(vCandidates);
        if(vCandidates.size() > 1)
            sum += boost::lexical_cast<int>(std::string(vTable[std::get<0>(vCandidates[0])],
                        std::get<1>(vCandidates[0]),
                        std::get<2>(vCandidates[0]) - std::get<1>(vCandidates[0]) + 1))
                * boost::lexical_cast<int>(std::string(vTable[std::get<0>(vCandidates[1])],
                        std::get<1>(vCandidates[1]),
                        std::get<2>(vCandidates[1]) - std::get<1>(vCandidates[1]) + 1));
    }

    fmt::print("Sum is {}.\n", sum);
    return 0;
}
