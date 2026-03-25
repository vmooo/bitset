//
// Created by Михолап Иван on 25.03.26.
//

#include "bitset.h"

namespace vmo {

    using value_type = Bitset::value_type;
    using reference = Bitset::reference;
    using const_reference = Bitset::const_reference;
    using size_type = Bitset::size_type;
    using difference_type = Bitset::difference_type;

    using iterator_category = Bitset::Iterator::iterator_category;
    using pointer = Bitset::Iterator::pointer;
    using reference = Bitset::reference;

    // BITSET::ITERATOR

    Bitset::Iterator::Iterator(pointer _ptr) : ptr(_ptr) {}

    reference Bitset::Iterator::operator*() const {
        return *ptr;
    }

    pointer Bitset::Iterator::operator->() const {
        return ptr;
    }

    Bitset::Iterator& Bitset::Iterator::operator++() {
        ++ptr;
        return *this;
    }

    Bitset::Iterator Bitset::Iterator::operator++(int) {
        Bitset::Iterator tmp = *this;
        ++ptr;
        return tmp;
    }

    Bitset::Iterator& Bitset::Iterator::operator--() {
        --ptr;
        return *this;
    }

    Bitset::Iterator Bitset::Iterator::operator--(int) {
        Bitset::Iterator tmp = *this;
        ++ptr;
        return tmp;
    }

    bool Bitset::Iterator::operator==(const Bitset::Iterator & other) const {
        return ptr == other.ptr;
    }

    bool Bitset::Iterator::operator!=(const Bitset::Iterator & other) const {
        return ptr != other.ptr;
    }

    bool Bitset::Iterator::operator<(const Bitset::Iterator & other) const {
        return ptr < other.ptr;
    }

    bool Bitset::Iterator::operator<=(const Bitset::Iterator & other) const {
        return ptr <= other.ptr;
    }

    bool Bitset::Iterator::operator>(const Bitset::Iterator & other) const {
        return ptr > other.ptr;
    }

    bool Bitset::Iterator::operator>=(const Bitset::Iterator & other) const {
        return ptr >= other.ptr;
    }

    Bitset::Iterator Bitset::Iterator::operator+(const difference_type n) const {
        return Bitset::Iterator(ptr + n);
    }

    Bitset::Iterator Bitset::Iterator::operator-(const difference_type n) const {
        return Bitset::Iterator(ptr - n);
    }

    Bitset::Iterator& Bitset::Iterator::operator+=(const difference_type n) {
        ptr += n;
        return *this;
    }

    Bitset::Iterator& Bitset::Iterator::operator-=(const difference_type n) {
        ptr -= n;
        return *this;
    }

    reference Bitset::Iterator::operator[](const difference_type n) const {
        return ptr[n];
    }

    ptrdiff_t operator-(const Bitset::Iterator& first, const Bitset::Iterator& second) {
        return first.ptr - second.ptr;
    }

    // BITSET

    Bitset::Bitset() : capacity(1), _size(0) {
        data = new value_type[capacity];
    }

    Bitset::~Bitset() {
        delete [] data;
    }


} // vmo
