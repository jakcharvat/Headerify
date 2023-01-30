//
//  Heap.cpp
//  Headerify
//
//  Created by Jakub Charvát on 18.03.2022.
//


template <typename Element, typename Comparator>
Heap<Element, Comparator>::Heap(Comparator comparator):
_comparator(comparator) { }


//MARK: - Traversal
template <typename Element, typename Comparator>
inline size_t
Heap<Element, Comparator>::_parent(size_t child) const {
    return (child - 1) / 2;
}


template <typename Element, typename Comparator>
inline size_t
Heap<Element, Comparator>::_leftChild(size_t parent) const {
    return 2*parent + 1;
}


template <typename Element, typename Comparator>
inline size_t
Heap<Element, Comparator>::_rightChild(size_t parent) const {
    return _leftChild(parent) + 1;
}


template <typename Element, typename Comparator>
inline size_t
Heap<Element, Comparator>::_topChild(size_t parent) const {
    if (_rightChild(parent) >= _buffer.size()) return _leftChild(parent);

    return _comparator(_buffer[_leftChild(parent)], _buffer[_rightChild(parent)])
        ? _leftChild(parent)
        : _rightChild(parent);
}


//MARK: - Sift
template <typename Element, typename Comparator>
void
Heap<Element, Comparator>::_siftUp() {
    if (_buffer.size() <= 1) return;

    size_t currIdx = _buffer.size() - 1;
    size_t parent = _parent(currIdx);

    while (currIdx && !_comparator(_buffer[parent], _buffer[currIdx])) {
        std::swap(_buffer[parent], _buffer[currIdx]);
        currIdx = parent;
        parent = _parent(currIdx);
    }
}


template <typename Element, typename Comparator>
void
Heap<Element, Comparator>::_siftDown() {
    size_t currIdx = 0;
    size_t topChild = _topChild(currIdx);

    while (topChild < _buffer.size() && !_comparator(_buffer[currIdx], _buffer[topChild])) {
        std::swap(_buffer[currIdx], _buffer[topChild]);
        currIdx = topChild;
        topChild = _topChild(currIdx);
    }
}


//MARK: - Push
template <typename Element, typename Comparator>
void
Heap<Element, Comparator>::insert(const Element & value) {
    _buffer.push_back(value);
    _siftUp();
}


//MARK: - Top
template <typename Element, typename Comparator>
const Element &
Heap<Element, Comparator>::top() const {
    return _buffer[0];
}


//MARK: - Extract
template <typename Element, typename Comparator>
Element
Heap<Element, Comparator>::extract() {
    Element value = _buffer[0];
    std::swap(_buffer.front(), _buffer.back());
    _buffer.pop_back();
    _siftDown();
    return value;
}


//MARK: - Size
template <typename Element, typename Comparator>
inline size_t
Heap<Element, Comparator>::size() const {
    return _buffer.size();
}


//MARK: - Tests
template <typename Element, typename Comparator>
void
Heap<Element, Comparator>::testMinHeapSequential() {
    MinHeap<unsigned int> minHeap;
    for (unsigned int i = 10; i > 0; --i) {
        minHeap.insert(i);
    }

    for (unsigned int i = 1; i <= 10; ++i) {
        assert(minHeap.top() == i);
        assert(minHeap.extract() == i);
    }

    assert(minHeap.size() == 0);
}


template <typename Element, typename Comparator>
void
Heap<Element, Comparator>::testMinHeapRandom() {
    for (unsigned int i = 0; i < 100; ++i) {
        std::vector<unsigned int> nums;
        MinHeap<unsigned int> minHeap;

        for (unsigned int j = 0; j < 1000; ++j) {
            unsigned int num = rand() % 100;
            minHeap.insert(num);
            nums.push_back(num);
        }

        sort(nums.begin(), nums.end(), std::less<unsigned int>());

        for (unsigned int i = 0; i < 100; ++i) {
            assert(minHeap.top() == nums[i]);
            assert(minHeap.extract() == nums[i]);
        }
    }
}


template <typename Element, typename Comparator>
void
Heap<Element, Comparator>::testMaxHeapSequential() {
    MaxHeap<unsigned int> maxHeap;
    for (unsigned int i = 10; i > 0; --i) {
        maxHeap.insert(i);
    }

    for (unsigned int i = 10; i > 0; --i) {
        assert(maxHeap.top() == i);
        assert(maxHeap.extract() == i);
    }

    assert(maxHeap.size() == 0);
}


template <typename Element, typename Comparator>
void
Heap<Element, Comparator>::testMaxHeapRandom() {
    for (unsigned int i = 0; i < 100; ++i) {
        std::vector<unsigned int> nums;
        MaxHeap<unsigned int> maxHeap;

        for (unsigned int j = 0; j < 1000; ++j) {
            unsigned int num = rand() % 100;
            maxHeap.insert(num);
            nums.push_back(num);
        }

        sort(nums.begin(), nums.end(), std::greater<unsigned int>());

        for (int i = 0; i < 100; ++i) {
            assert(maxHeap.top() == nums[i]);
            assert(maxHeap.extract() == nums[i]);
        }
    }
}
