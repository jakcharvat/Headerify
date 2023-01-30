//
//  main.cpp
//  Headerify
//
//  Created by Jakub Charvát on 18.03.2022.
//

#include <iostream>
#include <fstream>

#include "IncludeSearch.hpp"


int main(int argc, const char * argv[]) {
    std::ifstream ifs("Example/main.cpp");

    if (!ifs.good()) {
        std::cerr << "Cannot open main file" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        std::string include;
        auto res = readInclude(line, include);

        if (res == IncludeSearchResult::NO_INCLUDE) continue;

        if (res == IncludeSearchResult::SYSTEM_INCLUDE) {
            std::cout << "SYSTEM INCLUDE ";
        } else {
            std::cout << "USER   INCLUDE ";
        }

        std::cout << include << std::endl;
    }
}
