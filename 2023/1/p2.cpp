#include <stdio.h>

#include <regex>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <fmt/core.h>

int wordToDigit(const std::string& strNum) {
    if(strNum == "one")
        return 1;
    if(strNum == "two")
        return 2;
    if(strNum == "three")
        return 3;
    if(strNum == "four")
        return 4;
    if(strNum == "five")
        return 5;
    if(strNum == "six")
        return 6;
    if(strNum == "seven")
        return 7;
    if(strNum == "eight")
        return 8;
    if(strNum == "nine")
        return 9;
    return 0;
}

int main(int argc, char** argv) {
    FILE* fInput = fopen(argv[1],"r");

    char line[300];

    int firstDigit,secondDigit;

    int result = 0;
    while(fgets(line, sizeof(line), fInput)) {
        firstDigit = -1;
        secondDigit = -1;
        std::string strLine(line);
    
        std::regex regLine("(one)|(two)|(three)|(four)|(five)|(six)|(seven)|(eight)|(nine)|[1-9]");

        std::sregex_iterator itr(strLine.begin(), strLine.end(), regLine);
        std::sregex_iterator end;

        while(itr != end) {
            int i;
            try {
                i = boost::lexical_cast<int>(itr->str());
            }
            catch(boost::bad_lexical_cast&) {
                i = wordToDigit(itr->str());
            }
            itr++;
            if(firstDigit == -1)
                firstDigit = i;
            else
                secondDigit = i;
        }

        if(secondDigit == -1)
            secondDigit = firstDigit;

        result += 10*firstDigit + secondDigit;
    }

    fmt::print("Result is {}.\n", result);

    return 0;
}
