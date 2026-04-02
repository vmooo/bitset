#include "../include/bitset.h"

#include <algorithm>
#include <cassert>
#include <iostream>

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

    inline void Bitset::change_index(const size_type index) const {
        assert(index < capacity);
        assert(index < _size);
        data.get()[index] ^= 1;
    }

    // PUBLIC METHODS

    Bitset::Bitset() : capacity(1) {
        data = std::make_unique<value_type[]>(capacity);
    }

    Bitset::~Bitset() = default;

    Bitset::Bitset(const size_type _size) : _size(_size), capacity(_size + 1) {
        data = std::make_unique<value_type[]>(capacity);
    }

    Bitset::Bitset(const Bitset & other) {
        capacity = other.capacity;
        _size = other._size;
        data = std::make_unique<value_type[]>(capacity);

        for (int i = 0; i < _size; ++i) {
            assert(other.data.get() != nullptr && "pointer other.data is null");
            data.get()[i] = other.data.get()[i];
        }
    }

    Bitset::Bitset(Bitset && other) noexcept {
        capacity = other.capacity;
        _size = other._size;
        data = std::move(other.data);
        other.capacity = 0;
        other._size = 0;
    }

    Bitset& Bitset::operator=(const Bitset & other) {
        if (this != &other) {
            capacity = other.capacity;
            _size = other._size;
            data = std::make_unique<value_type[]>(other.capacity);

            for (int i = 0; i < _size; ++i) {
                assert(other.data != nullptr && "pointer other.data is null");
                data.get()[i] = other.data.get()[i];
            }
        }
        return *this;
    }

    Bitset& Bitset::operator=(Bitset && other) noexcept {
        if (this != &other) {
            capacity = other.capacity;
            _size = other._size;
            data = std::move(other.data);
        }
        return *this;
    }

    void Bitset::set(const size_type index) {
        assert(data.get() != nullptr);

        if (index < _size) {
        }
        else if (index < capacity) {
            _size = index + 1;
        }
        else {
            const size_type multiplied_capacity = capacity_multiplier * capacity;
            const size_type new_capacity = (index < multiplied_capacity ? multiplied_capacity : index + 1);

            auto new_data = std::make_unique<value_type[]>(new_capacity);
            for (int i = 0; i < _size; ++i) {
                new_data.get()[i] = data.get()[i];
            }

            data = std::move(new_data);

            _size = index + 1;
            capacity = new_capacity;
        }
        change_index(index);
    }

    bool Bitset::test(const size_type index) const {
        assert(data != nullptr);

        if (index < capacity) {
            return data.get()[index];
        }
        return false;
    }

    bool Bitset::operator[](const size_type index) const {
        assert(data.get() != nullptr);
        return test(index);
    }

    Bitset Bitset::union_with(const Bitset &other) const {
        size_type new_size = _size;
        size_type min_size = other._size;
        if (_size < other._size) {
           std::swap(new_size, min_size);
        }
        Bitset result(new_size);

        for (size_type i = 0; i < min_size; ++i) {
            result.data[i] = data[i] | other.data[i];
        }
        if (new_size == _size) {
            for (size_type i = min_size; i < new_size; ++i) {
                result.data[i] = data[i];
            }
        }
        else {
            for (size_type i = min_size; i < new_size; ++i) {
                result.data[i] = other.data[i];
            }
        }
        return result;
    }

    size_type Bitset::size() const {
        return _size;
    }

    bool Bitset::empty() const {
        return _size == 0;
    }

    Bitset::Iterator Bitset::begin() const {
        return Iterator(data.get());
    }

    Bitset::Iterator Bitset::end() const {
        return Iterator(data.get() + _size);
    }

} // vmo
