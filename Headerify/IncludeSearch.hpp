//
//  IncludeSearch.hpp
//  Headerify
//
//  Created by Jakub Charvát on 24.03.2022.
//

#pragma once

#include <string>


enum class IncludeSearchResult {
    NO_INCLUDE,
    SYSTEM_INCLUDE,
    USER_INCLUDE
};


IncludeSearchResult readInclude(const std::string & line, std::string & includeFile);
