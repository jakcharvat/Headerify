//
//  SortedVector.cpp
//  Headerify
//
//  Created by Jakub Charvát on 18.03.2022.
//

#include "CVATRegister.hpp"


template <typename Element, typename Comparator>
SortedVector<Element, Comparator>::SortedVector(Comparator comparator):
_comparator(comparator) { }


//MARK: - Subscripts
template <typename Element, typename Comparator>
inline typename SortedVector<Element, Comparator>::Iterator
SortedVector<Element, Comparator>::operator[](const Element & key) {
    return lower_bound(_buffer.begin(), _buffer.end(), key, _comparator);
}


template <typename Element, typename Comparator>
inline const typename SortedVector<Element, Comparator>::Iterator
SortedVector<Element, Comparator>::operator[](const Element & key) const {
    return const_cast<SortedVector<Element, Comparator> *>(this)->operator[](key);
}


template <typename Element, typename Comparator>
inline Element &
SortedVector<Element, Comparator>::operator[](size_t index) {
    return _buffer[index];
}


template <typename Element, typename Comparator>
inline const Element &
SortedVector<Element, Comparator>::operator[](size_t index) const {
    return const_cast<SortedVector *>(this)[index];
}


//MARK: - Insert
template <typename Element, typename Comparator>
bool
SortedVector<Element, Comparator>::insert(const Element & key) {
    bool exists = false;

    Iterator it = (*this)[key];
    if (it != _buffer.end() && *it == key) exists = true;
    _buffer.insert(it, key);

    return exists;
}


//MARK: - Remove
template <typename Element, typename Comparator>
bool
SortedVector<Element, Comparator>::remove(const Element & key) {
    Iterator it = (*this)[key];
    if (*it != key) return false;
    _buffer.erase(it);
    return true;
}


template <typename Element, typename Comparator>
bool
SortedVector<Element, Comparator>::remove(Iterator it) {
    _buffer.erase(it);
    return true;
}


//MARK: - Iterators
template <typename Element, typename Comparator>
inline typename SortedVector<Element, Comparator>::ConstIterator
SortedVector<Element, Comparator>::begin() const {
    return _buffer.begin();
}


template <typename Element, typename Comparator>
inline typename SortedVector<Element, Comparator>::ConstIterator
SortedVector<Element, Comparator>::end() const {
    return _buffer.end();
}


//MARK: - Tests
template <typename Element, typename Comparator>
void
SortedVector<Element, Comparator>::testSortedVectorSequential() {
    SortedVector<int> sv;

    assert(!sv.insert(7));
    assert(!sv.insert(3));
    assert(!sv.insert(6));
    assert(!sv.insert(2));
    assert(!sv.insert(1));
    assert(!sv.insert(9));
    assert(!sv.insert(4));
    assert(!sv.insert(5));
    assert(!sv.insert(0));
    assert(!sv.insert(8));

    int last = -1;
    for (int el : sv) {
        assert(el > last);
        last = el;
    }
}


template <typename Element, typename Comparator>
void
SortedVector<Element, Comparator>::testSortedVectorRandom() {
    for (int i = 0; i < 1000; ++i) {
        SortedVector<int> v;
        for (int i = 0; i < 1000; ++i) {
            v.insert(rand() % 100);
        }

        int last = -1;
        for (int el : v) {
            assert(el >= last);
            last = el;
        }
    }
}


