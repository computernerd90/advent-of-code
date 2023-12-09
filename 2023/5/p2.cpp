#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#include <map>
#include <regex>
#include <string>
#include <tuple>

#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <fmt/core.h>

int64_t findVal(int64_t key, const std::vector<std::tuple<int64_t,int64_t,int64_t>>& vTuples) {
    for(auto itr=vTuples.begin(), itrEnd=vTuples.end(); itr != itrEnd; ++itr) {
        int64_t srcStart = std::get<0>(*itr);
        int64_t destStart = std::get<1>(*itr);
        int64_t range = std::get<2>(*itr);

        if(destStart <= key && (destStart + range + 1) >= key)
            return srcStart + (key - destStart);
    }

    return key;
}

void parseTuples(FILE* fInput, std::vector<std::tuple<int64_t,int64_t,int64_t>>& vTuples) {
    char line[300];
    std::string strLine;
    
    std::regex regNums("(\\d+) (\\d+) (\\d+)");
    std::smatch matchNums;
    
    while(fgets(line, sizeof(line), fInput)) {
        strLine = std::string(line);
        strLine.erase(strLine.size()-1);
        if(strLine.empty())
            break;
        bool found = std::regex_search(strLine, matchNums, regNums);
        BOOST_ASSERT(found);

        vTuples.emplace_back(std::make_tuple(boost::lexical_cast<int64_t>(matchNums[1].str()),
            boost::lexical_cast<int64_t>(matchNums[2].str()),
            boost::lexical_cast<int64_t>(matchNums[3].str())));
    }
}

int main(int argc, char** argv) {
    FILE* fInput = NULL;
    if(argc > 1)
        fInput = fopen(argv[1], "r");
    if(fInput == NULL)
        return 0;

    char line[300];
    std::string strLine;

    fgets(line, sizeof(line), fInput);
    strLine = std::string(line).substr(7);
    strLine.erase(strLine.size()-1);

    for(int i=0; i<2; i++)
        fgets(line, sizeof(line), fInput);

    std::regex regSeeds("(\\d+) (\\d+)");
    std::smatch matchSeeds;
    
    auto regItrBegin = std::sregex_iterator(strLine.begin(), strLine.end(), regSeeds);
    auto regItrEnd = std::sregex_iterator();

    std::vector<std::tuple<int64_t, int64_t>> vSeedRanges;
    for(std::regex_iterator regItr=regItrBegin; regItr != regItrEnd; ++regItr) {
        int64_t start = boost::lexical_cast<int64_t>(regItr->str(1));
        int64_t range = boost::lexical_cast<int64_t>(regItr->str(2));
        vSeedRanges.emplace_back(std::make_tuple(start,range));
    }

    std::vector<std::tuple<int64_t,int64_t,int64_t>> vSeedSoil;
    std::vector<std::tuple<int64_t,int64_t,int64_t>> vSoilFert;
    std::vector<std::tuple<int64_t,int64_t,int64_t>> vFertWater;
    std::vector<std::tuple<int64_t,int64_t,int64_t>> vWaterLight;
    std::vector<std::tuple<int64_t,int64_t,int64_t>> vLightTemp;
    std::vector<std::tuple<int64_t,int64_t,int64_t>> vTempHumid;
    std::vector<std::tuple<int64_t,int64_t,int64_t>> vHumidLoc;

    parseTuples(fInput, vSeedSoil);
    fgets(line, sizeof(line), fInput);
    parseTuples(fInput, vSoilFert);
    fgets(line, sizeof(line), fInput);
    parseTuples(fInput, vFertWater);
    fgets(line, sizeof(line), fInput);
    parseTuples(fInput, vWaterLight);
    fgets(line, sizeof(line), fInput);
    parseTuples(fInput, vLightTemp);
    fgets(line, sizeof(line), fInput);
    parseTuples(fInput, vTempHumid);
    fgets(line, sizeof(line), fInput);
    parseTuples(fInput, vHumidLoc);

    int64_t loc = LLONG_MAX;
    for(auto itr=vSeedRanges.begin(), itrEnd=vSeedRanges.end(); itr != itrEnd; ++itr) {
        int64_t start=std::get<0>(*itr);
        int64_t range=std::get<1>(*itr);

        fmt::print("Start {}, range {}\n", start, range);

        for(int i=0; i<range; i++) {
            int64_t key=start+i;
            key=findVal(key,vSeedSoil);
            key=findVal(key,vSoilFert);
            key=findVal(key,vFertWater);
            key=findVal(key,vWaterLight);
            key=findVal(key,vLightTemp);
            key=findVal(key,vTempHumid);
            key=findVal(key,vHumidLoc);
            if(key < loc)
                loc = key;
        }
    }

    fmt::print("Shortest is {}.\n", loc);

    return 0;
}
