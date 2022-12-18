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

    std::vector<std::string> vScreen(6, std::string(40,'.'));
    auto itr = std::begin(vScreen);

    int cycle=0,x=1;
    
    while(fgets(inLine, sizeof(inLine), inFile) != NULL && itr != std::end(vScreen)) {
        std::string inStr(inLine);
        printf("%s",inLine);

        std::regex noopRegex("noop");
        std::regex addxRegex("addx (\\-?)(\\d+)");

        std::smatch match;
        if(std::regex_search(inStr, match, noopRegex)) {
            if(std::abs(cycle-x) <= 1) {
                itr->at(cycle) = '#';
            }
            cycle = (cycle+1)%itr->size();
            if(cycle == 0)
                ++itr;
        }
        else if(std::regex_search(inStr, match, addxRegex)) {
            int plus = boost::lexical_cast<int>(match[2]);
            if(match[1] == "-")
                plus *= -1;
            for(int i=0; i<2 && itr != std::end(vScreen); i++) {
                if(std::abs(cycle-x) <= 1)
                    itr->at(cycle) = '#';
                cycle = (cycle+1)%itr->size();
                if(cycle == 0)
                    ++itr;
            }
            x += plus;
        }
    }

    for(auto r : vScreen)
        printf("%s\n", r.c_str());

    return 0;
}
