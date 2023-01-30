//
//  SortedVector.h
//  Headerify
//
//  Created by Jakub Charvát on 19.03.2022.
//

#pragma once

#include <vector>


template <typename Element, typename Comparator = std::less<Element> >
class SortedVector {
public:
    using Iterator = typename std::vector<Element>::iterator;
    using ConstIterator = typename std::vector<Element>::const_iterator;

private:
    std::vector<Element> _buffer;
    const Comparator _comparator;

public:
    SortedVector(Comparator comparator = Comparator());

    Iterator operator[] (const Element & key);
    const Iterator operator[] (const Element & key) const;

    Element & operator[] (size_t index);
    const Element & operator[] (size_t index) const;

    /// @returns `true` if the element already existed in the vector, `false` otherwise
    bool insert(const Element & key);

    /// @returns `true` if the element existed and was removed, `false` if it didn't exist
    bool remove(const Element & key);
    bool remove(Iterator it);

    ConstIterator begin(void) const;
    ConstIterator end(void) const;

    static void testSortedVectorSequential(void);
    static void testSortedVectorRandom(void);
};


#include "SortedVector.cpp"
