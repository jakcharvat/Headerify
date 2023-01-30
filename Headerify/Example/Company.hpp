//
//  Company.hpp
//  Headerify
//
//  Created by Jakub Charvát on 18.03.2022.
//

#pragma once

#include <string>


struct Company {
    std::string name;
    std::string address;
    std::string id;
    unsigned int sumIncome;

    Company(const std::string & name, const std::string & address, const std::string & id, unsigned int sumIncome = 0);

    bool operator == (const Company & other) const;
    bool operator != (const Company & other) const;
};
