#include <algorithm>
#include <numeric>
#include <vector>

#include <cstdio>

int main(int argc, char** argv) {
    if(argc < 2)
        return -1;

    FILE* inFile = NULL;
    
    if(fopen_s(&inFile, argv[1], "r"))
        return -1;

    std::vector<int> sums;
    int current = 0, currentSum = 0;

    char buffer[20];
    while(fgets(buffer, sizeof(buffer), inFile) != NULL) {
        if(sscanf_s(buffer, "%d\n", &current) == EOF) {
            sums.push_back(currentSum);
            currentSum = 0;
        }
        else {
            currentSum += current;
        }
    }

    if(sums.size() > 2) {
        std::sort(std::begin(sums), std::end(sums));

        printf("%d + %d + %d = %d\n", *(std::end(sums)-1), *(std::end(sums)-2), *(std::end(sums)-3),
                std::accumulate(std::end(sums)-3, std::end(sums), 0));
    }
    return 0;
}
