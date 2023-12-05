#include <stdio.h>

#include <algorithm>
#include <regex>
#include <string>
#include <tuple>
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

    std::vector<std::tuple<int, std::vector<int>, int>> vScores;

    for(size_t i=0, iSize=vCards.size(); i<iSize; i++)
        vScores.emplace_back(std::make_tuple(i,std::vector<int>(),0));

    for(size_t i=0, iSize=vCards.size(); i < iSize; i++) {
        fmt::print("{}\n", vCards[i]);

        std::regex_search(vCards[i], matches, regLine);

        std::vector<std::string> v1;
        std::vector<int> vWinningNums,vNums;
        boost::algorithm::split(v1, matches[2].str(), boost::algorithm::is_space());

        for(size_t j=0, jSize=v1.size(); j<jSize; j++)
            if(!boost::algorithm::trim_copy(v1[j]).empty())
                vWinningNums.push_back(boost::lexical_cast<int>(boost::algorithm::trim_copy(v1[j])));

        boost::algorithm::split(v1, matches[3].str(), boost::algorithm::is_space());

        for(size_t j=0, jSize=v1.size(); j<jSize; j++)
            if(!boost::algorithm::trim_copy(v1[j]).empty())
                vNums.push_back(boost::lexical_cast<int>(boost::algorithm::trim_copy(v1[j])));

        auto winningNumsBegin = std::begin(vWinningNums);
        auto winningNumsEnd = std::end(vWinningNums);

        int winningNums=0;
        for(auto itr=vNums.begin(), itrEnd=vNums.end(); itr != itrEnd; ++itr) 
            if(std::find(winningNumsBegin, winningNumsEnd, *itr) != winningNumsEnd)
                winningNums++;

        if(winningNums > 0)
            for(int j=0; j<winningNums; j++)
                std::get<1>(vScores[i]).emplace_back(i+j);
    }

    for(size_t i=0, iSize=vScores.size(); i < iSize; i++) {
        for(size_t j=0, jSize=std::get<1>(vScores[i]).size(); j<jSize; j++) {
            if(std::get<1>(vScores[i])[j] < iSize)
                std::get<2>(vScores[std::get<1>(vScores[i])[j]]) += std::get<2>(vScores[i]) + 1;
        }
        if(std::get<1>(vScores[i]).size() != 0)
            sum += std::get<2>(vScores[i])+1;
    }

    fmt::print("Sum total: {}\n", sum);

    return 0;
}
