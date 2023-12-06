#include <stdio.h>

#include <regex>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <fmt/core.h>

int main(int argc, char** argv) {
    FILE* fInput = NULL;
    if(argc > 1)
        fInput = fopen(argv[1], "r");
    if(fInput == NULL)
        return 0;

    char line[300];
    std::string strLine;

    fgets(line, sizeof(line), fInput);
    strLine = std::string(line).substr(7);
    strLine.erase(strLine.size()-1);

    fmt::print("{}\n",strLine);

    for(int i=0; i<2; i++)
        fgets(line, sizeof(line), fInput);

    std::regex regNums("(\\d+) (\\d+) (\\d+)");
    std::smatch matchNums;

    while(fgets(line, sizeof(line), fInput)) {
        strLine = std::string(line);
        strLine.erase(strLine.size()-1);
        if(strLine.empty())
            break;
        bool found = std::regex_search(strLine, matchNums, regNums);
        BOOST_ASSERT(found);
        fmt::print("{}, {}, {}\n", matchNums[1].str(), matchNums[2].str(), matchNums[3].str());
    }

    return 0;
}
