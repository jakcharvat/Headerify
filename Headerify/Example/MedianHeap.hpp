//
//  MedianHeap.hpp
//  Headerify
//
//  Created by Jakub Charvát on 18.03.2022.
//

#pragma once

#include "Heap.hpp"


template <typename Element>
class MedianHeap {
private:
    MaxHeap<Element> _left;
    MinHeap<Element> _right;

    void _balance(void);

public:
    void insert(const Element & value);
    const Element & median(void) const;
    size_t size(void) const;

    static void testMedianHeapSequential(void);
    static void testMedianHeapRandom(void);
};


#include "MedianHeap.cpp"
