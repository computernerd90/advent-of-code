#include <stdio.h>

#include <string>
#include <vector>

int main(int argc, char** argv) {
    FILE* inFile = fopen(argv[1], "r");

    if(!inFile)
        return -1;

    char inLine[50];
    int sum = 0;

    std::vector<std::string> vSacks;

    while(fscanf(inFile, "%s\n", inLine) != EOF) {
        vSacks.emplace_back(std::string(inLine));
        
        if(vSacks.size() == 3) {
            char common = '0';
            for(const char c : vSacks[0])
                if(vSacks[1].find(c) != std::string::npos
                    && vSacks[2].find(c) != std::string::npos) {
                    if(c >= 'a' && c <= 'z')
                        sum += c - 'a' + 1;
                    if(c >= 'A' && c <= 'Z')
                        sum += c - 'A' + 27;
                    break;
                }
            vSacks.clear();
        }
    }

    printf("%d\n", sum);

    return 0;
}
