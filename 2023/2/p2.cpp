#include <stdio.h>

#include <regex>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <fmt/core.h>

int main(int argc, char** argv) {
    FILE* fInput = fopen(argv[1],"r");

    char line[300];
    
    std::regex regGameID("Game (\\d+)\\:"); 
    std::regex regBlueCount("(\\d+)\\s+blue");
    std::regex regRedCount("(\\d+)\\s+red");
    std::regex regGreenCount("(\\d+)\\s+green");

    int iIDSum = 0;

    const int iRED_CUBE_MAX = 12;
    const int iBLUE_CUBE_MAX = 14;
    const int iGREEN_CUBE_MAX = 13;

    fmt::print("Red: {}, Blue: {}, Green: {}\n", iRED_CUBE_MAX, iBLUE_CUBE_MAX, iGREEN_CUBE_MAX);

    while(fgets(line, sizeof(line), fInput)) {
        std::string strLine(line);

        boost::char_separator commaSep(";");
        boost::tokenizer tokGames(strLine, commaSep);

        int redCubes=0;
        int blueCubes=0;
        int greenCubes=0;

        for(auto itr = tokGames.begin(), itrEnd = tokGames.end(); itr != itrEnd; ++itr) {
            fmt::print("{}\n", *itr);
            
            std::smatch theMatch;
            if(std::regex_search(*itr, theMatch, regBlueCount)) {
                int blueCount = boost::lexical_cast<int>(theMatch[1].str());
                if(blueCount > blueCubes)
                    blueCubes = blueCount;
            }
            if(std::regex_search(*itr, theMatch, regRedCount)) {
                int redCount = boost::lexical_cast<int>(theMatch[1].str());
                if(redCount > redCubes)
                    redCubes = redCount;
            }
            if(std::regex_search(*itr, theMatch, regGreenCount)) {
                int greenCount = boost::lexical_cast<int>(theMatch[1].str());
                if(greenCount > greenCubes)
                    greenCubes = greenCount;
            }
        }

        fmt::print("Max blue: {}, red: {}, green: {}.\n", blueCubes, redCubes, greenCubes);
        iIDSum += blueCubes*redCubes*greenCubes;
    }

    fmt::print("ID sum is {}.\n", iIDSum);

    return 0;
}
