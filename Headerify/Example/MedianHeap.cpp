//
//  MedianHeap.cpp
//  Headerify
//
//  Created by Jakub Charvát on 18.03.2022.
//


template <typename Element>
void
MedianHeap<Element>::_balance() {
    while (_left.size() > _right.size() + 1) {
        Element el = _left.extract();
        _right.insert(el);
    }

    while (_right.size() > _left.size()) {
        Element el = _right.extract();
        _left.insert(el);
    }
}


//MARK: - Insert
template <typename Element>
void
MedianHeap<Element>::insert(const Element & value) {
    if (_left.size() == 0) {
        _left.insert(value);
        return;
    }

    if (value < _left.top()) {
        _left.insert(value);
    } else {
        _right.insert(value);
    }

    _balance();
}


//MARK: - Size
template <typename Element>
size_t
MedianHeap<Element>::size() const {
    return _left.size() + _right.size();
}


//MARK: - Median
template <typename Element>
const Element &
MedianHeap<Element>::median() const {
    static const Element zero = Element();
    if (_left.size() == 0) return zero;

    if (_left.size() == _right.size()) return _right.top();
    return _left.top();
}


//MARK: - Tests
template <typename Element>
void
MedianHeap<Element>::testMedianHeapSequential() {
    MedianHeap<unsigned int> medians;
    assert(medians.size() == 0);
    assert(medians.median() == 0);

    for (unsigned int i = 0; i < 1000; ++i) {
        medians.insert(i);
        assert(medians.size() == i + 1);
        assert(medians.median() == (1 + i) / 2);
    }
}


template <typename Element>
void
MedianHeap<Element>::testMedianHeapRandom() {
    for (int i = 0; i < 1000; ++i) {
        MedianHeap<unsigned int> medians;
        std::vector<unsigned int> values;
        for (int j = 0; j < 1000; ++j) {
            unsigned int value = rand() % 1000;
            medians.insert(value);
            values.push_back(value);

            sort(values.begin(), values.end());
            assert(medians.median() == values[values.size() / 2]);
        }
    }
}


