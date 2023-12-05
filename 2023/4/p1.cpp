#include <stdio.h>

#include <algorithm>
#include <regex>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <fmt/core.h>

int main(int argc, char** argv) {
    FILE* fInput = fopen(argv[1], "r");    
    
    char line[300];

    std::vector<std::string> vCards;

    while(fgets(line,sizeof(line),fInput)) {
        std::string strLine(line);
        strLine.erase(strLine.size()-1);

        vCards.emplace_back(strLine);
    }

    std::regex regLine("Card +(\\d+)\\: (.*) \\| (.*)");
    std::smatch matches;

    int sum=0;

    for(auto itr = vCards.begin(), itrEnd = vCards.end(); itr != itrEnd; ++itr) {
        fmt::print("{}\n", *itr);

        std::regex_search(*itr, matches, regLine);

        std::vector<std::string> v1;
        std::vector<int> vWinningNums,vNums;
        boost::algorithm::split(v1, matches[2].str(), boost::algorithm::is_space());

        for(size_t i=0, iSize=v1.size(); i<iSize; i++)
            if(!boost::algorithm::trim_copy(v1[i]).empty())
                vWinningNums.push_back(boost::lexical_cast<int>(boost::algorithm::trim_copy(v1[i])));

        boost::algorithm::split(v1, matches[3].str(), boost::algorithm::is_space());

        for(size_t i=0, iSize=v1.size(); i<iSize; i++)
            if(!boost::algorithm::trim_copy(v1[i]).empty())
                vNums.push_back(boost::lexical_cast<int>(boost::algorithm::trim_copy(v1[i])));

        auto winningNumsBegin=std::begin(vWinningNums);
        auto winningNumsEnd=std::end(vWinningNums);

        int exponent=-1;
        int winningNums = 0;

        fmt::print("Winning nums: ");
        for(auto itr=vWinningNums.begin(), itrEnd=vWinningNums.end(); itr != itrEnd; ++itr)
            fmt::print("{}, ", *itr);
        fmt::print("\n");

        fmt::print("Actual nums: ");
        for(auto itr=vNums.begin(), itrEnd=vNums.end(); itr != itrEnd; ++itr)
            fmt::print("{}, ", *itr);
        fmt::print("\n");
        
        for(auto itr=vNums.begin(), itrEnd=vNums.end(); itr != itrEnd; ++itr) {
            if(std::find(winningNumsBegin, winningNumsEnd, *itr) != winningNumsEnd) {
                exponent++;
                winningNums++;
            }
        }
        
        if(exponent >= 0) {
            sum += pow(2, exponent);
        }



        fmt::print("Winning nums: {}, Sum so far: {}\n", winningNums, sum);

        fmt::print("\n");
    }

    fmt::print("Sum total: {}\n", sum);

    return 0;
}
