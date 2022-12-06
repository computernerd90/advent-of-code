#include <stdio.h>

#include <algorithm>
#include <set>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    FILE* inFile = fopen(argv[1], "r");

    if(!inFile)
        return -1;

    char inLine[10000];

    while(fgets(inLine, sizeof(inLine), inFile) != NULL) {
        std::string inStr(inLine);
        for(int i=0; i<inStr.size()-14; i++) {
            std::string theString(inStr.substr(i,14));

            std::set<char> theSet(std::begin(theString), std::end(theString));
            std::string newString;
            for(auto c: theSet)
                newString.append(1,c);

            if(theSet.size() == 14) {
                printf("%d\n", i+14);
                return 0;
            }
        }
    }

    return 0;
}
