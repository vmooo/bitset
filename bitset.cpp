//
// Created by Михолап Иван on 25.03.26.
//

#include "bitset.h"
#include <cassert>

namespace vmo {

    using value_type = Bitset::value_type;
    using reference = Bitset::reference;
    using const_reference = Bitset::const_reference;
    using size_type = Bitset::size_type;
    using difference_type = Bitset::difference_type;

    using iterator_category = Bitset::Iterator::iterator_category;
    using pointer = Bitset::pointer;
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

    difference_type operator-(const Bitset::Iterator& first, const Bitset::Iterator& second) {
        return first.ptr - second.ptr;
    }

    // BITSET

    // PRIVATE MEMBERS

    inline void Bitset::reallocate(const size_type new_capacity) {
        const auto new_data = new value_type[new_capacity];
        for (int i = 0; i < _size; ++i) {
            assert(new_data != nullptr && "pointer other.data is null");
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }

    inline void Bitset::change_index(const size_type index) {
        assert(index < capacity);
        assert(index < _size);
        data[index] ^= 1;
    }

    // PUBLIC METHODS

    Bitset::Bitset() : capacity(1) {
        data = new value_type[capacity];
    }

    Bitset::~Bitset() {
        delete [] data;
    }

    Bitset::Bitset(const size_type _size) : _size(_size), capacity(_size) {
        data = new value_type[capacity];
    }

    Bitset::Bitset(const Bitset & other) {
        capacity = other.capacity;
        _size = other._size;
        data = new value_type[other.capacity];

        for (int i = 0; i < _size; ++i) {
            assert(other.data != nullptr && "pointer other.data is null");
            data[i] = other.data[i];
        }
    }

    Bitset::Bitset(Bitset && other) noexcept {
        capacity = other.capacity;
        _size = other._size;
        data = other.data;
        other.data = nullptr;
    }

    Bitset& Bitset::operator=(const Bitset & other) {
        if (this != &other) {
            capacity = other.capacity;
            _size = other._size;
            data = new value_type[other.capacity];

            for (int i = 0; i < _size; ++i) {
                assert(other.data != nullptr && "pointer other.data is null");
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Bitset& Bitset::operator=(Bitset && other) noexcept {
        if (this != &other) {
            capacity = other.capacity;
            _size = other._size;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    void Bitset::set(const size_type index) {
        assert(data != nullptr);

        if (index < _size) {
        }
        else if (index < capacity) {
            _size = index + 1;
        }
        else {
            const size_type multiplied_capacity = 2 * capacity;
            const size_type new_capacity = (index < multiplied_capacity ? multiplied_capacity : index + 1);
            reallocate(new_capacity);

            _size = index + 1;
            capacity = new_capacity;
        }
        change_index(index);
    }

    bool Bitset::test(const size_type index) const {
        assert(data != nullptr);

        if (index < capacity) {
            return data[index];
        }
        return false;
    }

    bool Bitset::operator[](const size_type index) const {
        assert(data != nullptr);
        return test(index);
    }

    size_type Bitset::size() const {
        return _size;
    }

    Bitset::Iterator Bitset::begin() const {
        return Iterator(data);
    }

    Bitset::Iterator Bitset::end() const {
        return Iterator(data + _size);
    }

} // vmo
