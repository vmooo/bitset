//
// Created by Михолап Иван on 25.03.26.
//

#ifndef BITSET_BITSET_H
#define BITSET_BITSET_H

#include <iterator>
#include <stdexcept>

namespace vmo {
    class Bitset {
    public:
        using value_type = bool;
        using reference = value_type &;
        using const_reference = const value_type &;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        class Iterator {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using pointer = value_type *;
            using reference = value_type &;

        private:
            pointer ptr{};

        public:

            explicit Iterator(pointer);

            reference operator*() const;
            pointer operator->() const;

            Iterator& operator++();
            Iterator operator++(int);
            Iterator& operator--();
            Iterator operator--(int);

            bool operator==(const Iterator &) const;
            bool operator!=(const Iterator &) const;


            bool operator<(const Iterator &) const;
            bool operator>(const Iterator &) const;
            bool operator<=(const Iterator &) const;
            bool operator>=(const Iterator &) const;

            Iterator operator+(difference_type) const;
            Iterator operator-(difference_type) const;
            Iterator& operator+=(difference_type);
            Iterator& operator-=(difference_type);

            reference operator[](difference_type) const;

            friend ptrdiff_t operator-(const Iterator &, const Iterator &);
        };

    private:
        value_type *data{};
        size_type _size{};
        size_type capacity{};

    public:
        Bitset();
        ~Bitset();

        explicit Bitset(size_type);

        Bitset(const Bitset &);
        Bitset(Bitset &&) noexcept ;

        void set(size_type);
        bool test(size_type) const;
        bool operator[](size_type) const;

        Bitset union_with(const Bitset &) const;
        Bitset intersection_with(const Bitset &) const;
        bool is_subset(const Bitset &) const;

        size_type size() const;
        bool empty() const;
        void clear();
    };
} // vmo

#endif //BITSET_BITSET_H