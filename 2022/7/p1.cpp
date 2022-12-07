#include <stdio.h>

#include <algorithm>
#include <set>
#include <string>
#include <vector>

struct Node {
    std::string name;
    std::vector<std::pair<std::string, int>> vFiles;
    std::vector<std::shared_ptr<Node>> vNodes;
    std::weak_ptr<Node> parent;
};

int main(int argc, char** argv) {
    FILE* inFile = fopen(argv[1], "r");

    if(!inFile)
        return -1;

    char inLine[10000];

    std::shared_ptr<Node> root = std::make_shared<Node>();
    root->name = "/";
    std::weak_ptr<Node> pCurrentNode = root;
    fgets(inLine, sizeof(inLine), inFile);
    bool lsMode = false;
    while(fgets(inLine, sizeof(inLine), inFile) != NULL) {
        std::string inStr(inLine);

        if(inStr[0] == '$') {
            lsMode = false;
            if(inStr.substr(2, 2) == "cd") {
                if(inStr.substr(5, 2) == "..") {
                    currentNode = currentNode->parent;
                }
                else {
                    char dirName[100];
                    sscanf(inLine, "$ cd %s\n", dirName);
                    std::string strDir(dirName);
                    currentNode = 
                }
            }
            else if(inStr.substr(2, 2) == "ls") {
                lsMode = true;
            }
        }
        else {
            if(inStr.substr(0,3) == "dir") {
                char dirName[100];
                sscanf(inLine, "dir %s\n", dirName);


            }
        }
        
    }

    return 0;
}
