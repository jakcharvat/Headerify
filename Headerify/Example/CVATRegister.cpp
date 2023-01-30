//
//  CVATRegister.cpp
//  Headerify
//
//  Created by Jakub Charvát on 18.03.2022.
//

#include "CVATRegister.hpp"

using namespace std::string_literals;

bool
CVATRegister::_idComparison(const Company * a, const Company * b) {
    return a->id < b->id;
}


bool
CVATRegister::_nameAddressComparison( const Company * a, const Company * b) {
    int nameComp = strcasecmp(a->name.c_str(), b->name.c_str());
    if (nameComp) return nameComp < 0;
    return strcasecmp(a->address.c_str(), b->address.c_str()) < 0;
}

//MARK: - Ctor and Dtor
CVATRegister::CVATRegister():
_ids(CVATRegister::_idComparison),
_namesAddresses(CVATRegister::_nameAddressComparison) { }


CVATRegister::~CVATRegister() {
    for (auto company : _ids) {
        delete company;
    }
}


//MARK: New Company
bool
CVATRegister::newCompany(const std::string & name, const std::string & addr, const std::string & taxID) {
    Company * company = new Company(name, addr, taxID);

    auto itId = _ids[company];
    if (itId != _ids.end()) {
        if (**itId == *company) {
            delete company;
            return false;
        }
    }

    auto itNameAddress = _namesAddresses[company];
    if (itNameAddress != _namesAddresses.end()) {
        if (**itNameAddress == *company) {
            delete company;
            return false;
        }
    }

    _ids.insert(company);
    _namesAddresses.insert(company);

    return true;
}


//MARK: Cancel Company
bool
CVATRegister::cancelCompany(const std::string & name, const std::string & addr) {
    Company company(name, addr, ""s);
    auto it = _namesAddresses[&company];

    if (it == _namesAddresses.end() || **it != company) return false;
    _ids.remove(*it);

    delete *it;
    _namesAddresses.remove(it);
    return true;
}

bool
CVATRegister::cancelCompany(const std::string & taxID) {
    Company company(""s, ""s, taxID);
    auto it = _ids[&company];

    if (it == _ids.end() || **it != company) return false;
    _namesAddresses.remove(*it);

    delete *it;
    _ids.remove(it);
    return true;
}


//MARK: Invoice
bool
CVATRegister::invoice(const std::string & name, const std::string & addr, unsigned int amount) {
    if (amount < 0) return false;

    Company company(name, addr, ""s);
    auto it = _namesAddresses[&company];

    if (it == _namesAddresses.end() || **it != company) return false;
    (*it)->sumIncome += amount;
    _invoices.insert(amount);

    return true;
}

bool
CVATRegister::invoice(const std::string & taxID, unsigned int amount) {
    if (amount < 0) return false;

    Company company(""s, ""s, taxID);
    auto it = _ids[&company];

    if (it == _ids.end() || **it != company) return false;
    (*it)->sumIncome += amount;
    _invoices.insert(amount);

    return true;
}


//MARK: Audit
bool
CVATRegister::audit(const std::string & name, const std::string & addr, unsigned int & sumIncome) const {
    Company company(name, addr, ""s);
    auto it = _namesAddresses[&company];

    if (it == _namesAddresses.end() || **it != company) return false;
    sumIncome = (*it)->sumIncome;

    return true;
}

bool
CVATRegister::audit(const std::string & taxID, unsigned int & sumIncome) const {
    Company company(""s, ""s, taxID);
    auto it = _ids[&company];

    if (it == _ids.end() || **it != company) return false;
    sumIncome = (*it)->sumIncome;

    return true;
}


//MARK: Traversal
bool
CVATRegister::firstCompany(std::string & name, std::string & addr) const {
    auto it = _namesAddresses.begin();
    if (it == _namesAddresses.end()) return false;

    name = (*it)->name;
    addr = (*it)->address;

    return true;
}

bool
CVATRegister::nextCompany(std::string & name, std::string & addr) const {
    Company company(name, addr, ""s);
    auto it = _namesAddresses[&company];

    if (it == _namesAddresses.end() || **it != company) return false;
    auto next = it + 1;
    if (next == _namesAddresses.end()) return false;

    name = (*next)->name;
    addr = (*next)->address;
    return true;
}


//MARK: Median
unsigned int
CVATRegister::medianInvoice() const {
    return _invoices.median();
}
