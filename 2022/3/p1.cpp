#include <stdio.h>

#include <algorithm>
#include <string>

int main(int argc, char** argv) {
    FILE* inFile = fopen(argv[1], "r");

    if(!inFile)
        return -1;

    char inLine[50];
    int sum = 0;
    while(fscanf(inFile, "%s\n", inLine) != EOF) {
        std::string strLine(inLine);
        std::string str1 = strLine.substr(0,strLine.size()/2);
        std::string str2 = strLine.substr(strLine.size()/2,std::string::npos);

        for(const char c : str1)
            if(str2.find(c) != std::string::npos) {
                if(c >= 'a' && c <= 'z')
                    sum += c - 'a' + 1;
                if(c >= 'A' && c <= 'Z')
                    sum += c - 'A' + 27;
                break;
            }
    }

    printf("%d\n", sum);

    return 0;
}
