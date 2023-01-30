//
//  Company.cpp
//  Headerify
//
//  Created by Jakub Charvát on 18.03.2022.
//

#include "Company.hpp"


Company::Company(const std::string & name, const std::string & address, const std::string & id, unsigned int sumIncome):
name(name),
address(address),
id(id),
sumIncome(sumIncome) { }


bool
Company::operator==(const Company & other) const {
    if (id == other.id) return true;
    return !strcasecmp(name.c_str(), other.name.c_str())
        && !strcasecmp(address.c_str(), other.address.c_str());
}


bool
Company::operator!=(const Company & other) const {
    return ! operator == (other);
}
