#include <stdio.h>

#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <regex>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

struct Monkey {
    std::vector<int> vItems;
    std::binary_function<int,int,int> oper;
    int divisibleBy,trueMonkey,falseMonkey;
};

int whichStep(std::string strLine, const std::vector<std::regex>& vRegexes, std::smatch& match) {
    auto itr = std::find_if(std::begin(vRegexes), std::end(vRegexes), [&] (const std::regex& theRegex) {
            return std::regex_search(strLine, match, theRegex);
        });
    if(itr != std::end(vRegexes))
        return std::distance(std::begin(vRegexes),itr);
    else
        return -1;
}

int main(int argc, char** argv) {
    FILE* inFile = fopen(argv[1], "r");

    if(!inFile)
        return -1;

    char inLine[10000];
    
    std::vector<Monkey> vMonkeys;

    Monkey theMonkey;

    std::vector<std::regex> vRegexes{
        std::regex("Monkey (\\d+):"),
        std::regex("Starting items:"),
        std::regex("Operation: new = old (.) (\\w+)"),
        std::regex("Test: divisible by (\\d+)"),
        std::regex("If true: throw to monkey (\\d+)"),
        std::regex("If false: throw to monkey (\\d+)")
    };

    while(fgets(inLine, sizeof(inLine), inFile) != NULL) {
        std::string inStr(inLine);
        printf("%s",inLine);
        
        std::smatch match;
        
        switch(whichStep(inStr,vRegexes,match)) {
            // Monkey x:
            case 0: {
                printf("Found step 1.\n");
                } break;
            // Starting items: ...
            case 1: {
                printf("Found step 2.\n");
                theMonkey = {};
                std::vector<std::string> vTemp;
                boost::split(vTemp, inStr.substr(17), boost::is_any_of(","));
               
                for(auto i: vTemp) {
                    boost::trim(i);
                    int theInt;
                    if(boost::conversion::try_lexical_convert<int>(i,theInt))
                        theMonkey.vItems.emplace_back(theInt);
                }

                } break;
            // Operation: new = old ...
            case 2: {
                printf("Found step 3.\n");
                    for(auto i : match)
                        printf("%s ", i.str().c_str());
                    printf("\n");
                } break;
            // Test: divisible by ...
            case 3: {
                printf("Found step 4.\n");
                
                } break;
            // If true: throw to monkey y
            case 4: {
                printf("Found step 5.\n");
                } break;
            // If false: throw to monkey z
            case 5: {
                printf("Found step 6.\n");
                } break;
            // Swallow up the newlines/other cases here.
            default: {
                } break;
        }
    }

    return 0;
}
