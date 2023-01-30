//
//  Heap.hpp
//  Headerify
//
//  Created by Jakub Charvát on 18.03.2022.
//

#pragma once

#include <vector>


template <typename Element, typename Comparator>
class Heap {
private:
    std::vector<Element> _buffer;
    const Comparator _comparator;

    size_t _parent(size_t child) const;
    size_t _leftChild(size_t parent) const;
    size_t _rightChild(size_t parent) const;
    size_t _topChild(size_t parent) const;

    void _siftUp(void);
    void _siftDown(void);

public:
    Heap(Comparator comparator = Comparator());
    void insert(const Element & value);
    const Element & top(void) const;
    Element extract(void);
    size_t size(void) const;

    static void testMinHeapSequential(void);
    static void testMinHeapRandom(void);
    static void testMaxHeapSequential(void);
    static void testMaxHeapRandom(void);
};

template <typename Element>
using MinHeap = Heap<unsigned int, std::less<Element> >;

template <typename Element>
using MaxHeap = Heap<unsigned int, std::greater<Element> >;


#include "Heap.cpp"
