//
//  CVATRegister.hpp
//  Headerify
//
//  Created by Jakub Charvát on 18.03.2022.
//

#pragma once

#include <string>
#include <vector>

#include "Company.hpp"
#include "MedianHeap.hpp"
#include "SortedVector.hpp"


class CVATRegister {
private:
    using CompanyComparison = std::function<bool(const Company *, const Company *)>;
    using Companies = SortedVector<Company *, CompanyComparison>;

    friend void testSortedVectorSequential();
    friend void testSortedVectorRandom();

    static bool _idComparison(const Company * a, const Company * b);
    static bool _nameAddressComparison(const Company * a, const Company * b);

    std::vector<Company> _companies;
    Companies _ids;
    Companies _namesAddresses;
    MedianHeap<unsigned int> _invoices;


public:
    CVATRegister(void);
    ~CVATRegister(void);
    bool newCompany     (const std::string & name,   const std::string & addr,    const std::string & taxID     );
    bool cancelCompany  (const std::string & name,   const std::string & addr                                   );
    bool cancelCompany  (const std::string & taxID                                                              );
    bool invoice        (const std::string & taxID,  unsigned int amount                                        );
    bool invoice        (const std::string & name,   const std::string & addr,    unsigned int amount           );
    bool audit          (const std::string & name,   const std::string & addr,    unsigned int & sumIncome) const;
    bool audit          (const std::string & taxID,  unsigned int & sumIncome                             ) const;
    bool firstCompany   (std::string & name,         std::string & addr                                   ) const;
    bool nextCompany    (std::string & name,         std::string & addr                                   ) const;
    unsigned int medianInvoice(void) const;
};
