//
//  IncludeSearch.cpp
//  Headerify
//
//  Created by Jakub Charvát on 24.03.2022.
//

#include "IncludeSearch.hpp"


template <size_t size>
constexpr inline size_t
constStrlen(const char (& str)[size]) {
    return size - 1;
}


template <size_t size>
bool match(const char *& str, const char (& search)[size]) {
    if (strncmp(str, search, constStrlen(search))) return false;
    str += constStrlen(search);
    return true;
}


bool match(const char *& str, char search) {
    if (*str != search) return false;
    ++str;
    return true;
}


void skipWhiteSpace(const char *& str) {
    while (*str && isspace(*str)) ++str;
}


IncludeSearchResult readInclude(const std::string & line, std::string & includeFile) {
    const char * str = line.c_str();

    skipWhiteSpace(str);
    if (!(*str)) return IncludeSearchResult::NO_INCLUDE;

    if (!match(str, '#')) return IncludeSearchResult::NO_INCLUDE;
    skipWhiteSpace(str);
    if (!match(str, "include")) return IncludeSearchResult::NO_INCLUDE;
    skipWhiteSpace(str);

    char includeStart = *str;
    if (includeStart != '<' && includeStart != '"') return IncludeSearchResult::NO_INCLUDE;
    ++str;
    char includeEnd = includeStart == '"' ? '"' : '>';

    const char * includeFileBegin = str;
    while (*str && *str != includeEnd) ++str;
    if (!(*str)) return IncludeSearchResult::NO_INCLUDE;

    size_t len = str - includeFileBegin;
    includeFile = std::string(includeFileBegin, len);

    return includeStart == '<' ? IncludeSearchResult::SYSTEM_INCLUDE : IncludeSearchResult::USER_INCLUDE;
}
