#include <stdio.h>

#include <algorithm>
#include <memory>
#include <numeric>
#include <set>
#include <string>
#include <vector>

struct Node {
    std::string name;
    std::vector<std::pair<std::string, int>> vFiles;
    std::vector<std::shared_ptr<Node>> vNodes;
    std::weak_ptr<Node> parent;
};

int recurse_tree(std::shared_ptr<Node>& node, std::vector<int>& vSizes) {
    int size = std::accumulate(std::begin(node->vFiles), std::end(node->vFiles),
        0,[] (int lhs, std::pair<std::string,int> prFile) {
            return lhs + prFile.second;
        });
    if(node->vNodes.size() != 0) {
        for(auto itr = std::begin(node->vNodes), endItr = std::end(node->vNodes);
            itr != endItr; ++itr)
            size += recurse_tree(*itr, vSizes);
    }

    if(size <= 100000)
        vSizes.emplace_back(size);

    return size;
}

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

        printf("%s", inLine);
        if(inStr[0] == '$') {
            lsMode = false;
            char cmdStr[100],operStr[100];
            sscanf(inLine, "$ %s %s\n", cmdStr, operStr);
            if(std::string(cmdStr) == "cd") {
                if(std::string(operStr) == "..") {
                    pCurrentNode = (pCurrentNode.lock())->parent;
                }
                else {
                    char dirName[100];
                    sscanf(inLine, "$ cd %s\n", dirName);
                    
                    pCurrentNode = *(std::find_if(std::begin((pCurrentNode.lock())->vNodes),
                        std::end((pCurrentNode.lock())->vNodes),
                        [&] (std::shared_ptr<Node>& node) {
                            return node->name == std::string(dirName);
                        }));
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

                std::shared_ptr<Node> newNode = std::make_shared<Node>();
                newNode->name = std::string(dirName);
                newNode->parent = pCurrentNode;
                (pCurrentNode.lock())->vNodes.emplace_back(newNode);
            }
            else {
               int iSize;
               char fileName[100];
               sscanf(inLine, "%d %s\n", &iSize, fileName);
               
               (pCurrentNode.lock())->vFiles.emplace_back(std::make_pair(std::string(fileName), iSize));
            }
        } 
    }

    std::vector<int> vSizes;
    recurse_tree(root, vSizes);
    int total = std::accumulate(std::begin(vSizes), std::end(vSizes), 0);

    printf("Total: %d\n", total);
    return 0;
}
