#include <stdio.h>

#include <algorithm>
#include <memory>
#include <numeric>
#include <regex>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include <boost/lexical_cast.hpp>

int main(int argc, char** argv) {
    FILE* inFile = fopen(argv[1], "r");

    if(!inFile)
        return -1;

    char inLine[10000];

    std::vector<std::pair<int, int>> vStrengths = {{20,0},{60,0},{100,0},{140,0},{180,0},{220,0}};
    auto itr = std::begin(vStrengths);

    int cycle=0,x=1;
    while(fgets(inLine, sizeof(inLine), inFile) != NULL && itr != std::end(vStrengths)) {
        std::string inStr(inLine);
        printf("%s",inLine);

        std::regex noopRegex("noop");
        std::regex addxRegex("addx (\\-?)(\\d+)");

        std::smatch match;
        if(std::regex_search(inStr, match, noopRegex)) {
            if(cycle + 1 == itr->first) {
                itr->second = x;
                ++itr;
            }
            cycle++;
        }
        else if(std::regex_search(inStr, match, addxRegex)) {
            int plus = boost::lexical_cast<int>(match[2]);
            if(match[1] == "-")
                plus *= -1;
            if(cycle + 2 > itr->first) {
                itr->second = x;
                itr++;
            }
            else if(cycle + 2 == itr->first) {
                itr++;
            }
            x += plus;
            cycle += 2;
        }
    }

    printf("%d\n", std::accumulate(std::begin(vStrengths),std::end(vStrengths),0,
            [] (int lhs, std::pair<int, int> rhs) {
                return lhs += rhs.first*rhs.second;
            }));

    return 0;
}
