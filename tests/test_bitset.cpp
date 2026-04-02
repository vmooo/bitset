#include "../include/bitset.h"
#include <gtest/gtest.h>

TEST(BitsetTests, DefaultConstructor) {
    const vmo::Bitset bitset;
    ASSERT_TRUE(bitset.size() == 0);
}

TEST(BitsetTests, Constructor) {
    const vmo::Bitset bitset(100);
    ASSERT_TRUE(bitset.size() == 100);
}

TEST(BitsetTests, SetAndTest1) {
    vmo::Bitset bitset(100);
    bitset.set(0);
    ASSERT_TRUE(bitset.test(0) == true);
}

TEST(BitsetTests, SetAndTest2) {
    vmo::Bitset bitset(100);
    bitset.set(99);
    ASSERT_TRUE(bitset.test(99) == true);
}

TEST(BitsetTests, SetAndTest3) {
    vmo::Bitset bitset(100);
    bitset.set(150);
    ASSERT_TRUE(bitset.test(150) == true);
}

TEST(BitsetTests, SetAndTest4) {
    vmo::Bitset bitset(300);
    bitset.set(300);
    ASSERT_TRUE(bitset.test(300) == true);
}

TEST(BitsetTests, SetAndTest5) {
    vmo::Bitset bitset(1);
    bitset.set(0);
    ASSERT_TRUE(bitset[0] == true);
}

TEST(BitsetTests, SetAndTestOutside) {
    const vmo::Bitset bitset(1);
    ASSERT_TRUE(bitset[10] == false);
}

TEST(BitsetTests, CopyConstructorSize) {
    vmo::Bitset bitset(10);
    vmo::Bitset copy(bitset);
    ASSERT_TRUE(copy.size() == 10);
}

TEST(BitsetTests, CopyConstructorContent) {
    vmo::Bitset bitset(10);
    bitset.set(0);
    bitset.set(9);
    const vmo::Bitset copy(bitset);
    for (int i = 0; i < bitset.size(); ++i) {
        ASSERT_TRUE(copy[i] == bitset[i]);
    }
}

TEST(BitsetTests, MoveConstructor1) {
    vmo::Bitset bitset(10);
    vmo::Bitset move(std::move(bitset));
    ASSERT_TRUE(bitset.size() == 0);
}

TEST(BitsetTests, MoveConstructor2) {
    vmo::Bitset bitset(10);
    bitset.set(9);
    bitset.set(0);
    bitset.set(20);
    const vmo::Bitset move(std::move(bitset));
    for (int i = 0; i < bitset.size(); ++i) {
        ASSERT_TRUE(bitset[i] == move[i]);
    }
}

TEST(BitsetTests, CopyAssignmentOperator) {
    vmo::Bitset bitset(10);
    bitset.set(9);
    bitset.set(0);
    bitset.set(20);
    const vmo::Bitset copy = bitset;
    for (int i = 0; i < bitset.size(); ++i) {
        ASSERT_TRUE(copy[i] == bitset[i]);
    }
}

TEST(BitsetTests, MoveAssignmentOperator1) {
    vmo::Bitset bitset(10);
    vmo::Bitset move = std::move(bitset);
    ASSERT_TRUE(bitset.size() == 0);
}

TEST(BitsetTests, MoveAssignmentOperator2) {
    vmo::Bitset bitset(10);
    bitset.set(9);
    bitset.set(0);
    bitset.set(20);
    const vmo::Bitset move = std::move(bitset);
    for (int i = 0; i < bitset.size(); ++i) {
        ASSERT_TRUE(bitset[i] == move[i]);
    }
}

TEST(BitsetTests, union_with1) {
    vmo::Bitset bitset(3);
    bitset.set(0);
    vmo::Bitset bitset2(3);
    bitset2.set(1);
    bitset2.set(2);

    vmo::Bitset _union(bitset.union_with(bitset2));
    for (int i = 0; i < 3; ++i) {
        ASSERT_TRUE(_union[i] == true);
    }
}

TEST(BitsetTests, union_with2) {
    vmo::Bitset bitset(3);
    vmo::Bitset bitset2(3);
    vmo::Bitset _union(bitset.union_with(bitset2));
    for (int i = 0; i < 3; ++i) {
        ASSERT_TRUE(_union[i] == false);
    }
}

TEST(BitsetTests, union_with3) {
    vmo::Bitset bitset(3);
    vmo::Bitset bitset2(4);
    vmo::Bitset _union(bitset.union_with(bitset2));
    ASSERT_TRUE(_union.size() == 4);
}

TEST(BitsetTests, union_with4) {
    vmo::Bitset bitset;
    vmo::Bitset bitset2(3);
    vmo::Bitset _union(bitset.union_with(bitset2));
    ASSERT_TRUE(_union.size() == 3);
}

TEST(BitsetTests, union_with5) {
    vmo::Bitset bitset;
    vmo::Bitset bitset2(3);
    bitset2.set(2);
    bitset2.set(1);
    bitset2.set(0);
    vmo::Bitset _union(bitset.union_with(bitset2));
    for (int i = 0; i < 3; ++i) {
        ASSERT_TRUE(_union[i] == true);
    }
}

TEST(BitsetTests, isEmpty) {
    vmo::Bitset bitset;
    ASSERT_TRUE(bitset.empty() == true);
}

TEST(BitsetTests, isNotEmpty) {
    vmo::Bitset bitset(1);
    ASSERT_TRUE(bitset.empty() == false);
}

TEST(BitsetTests, intersectionWith1) {
    vmo::Bitset bitset(3);
    vmo::Bitset bitset2(4);
    vmo::Bitset intersection(bitset.intersection_with(bitset2));
    ASSERT_TRUE(intersection.size() == 3);
}

TEST(BitsetTests, intersectionWith2) {
    vmo::Bitset bitset(3);
    bitset.set(0);
    bitset.set(1);
    bitset.set(2);
    vmo::Bitset bitset2 = bitset;
    vmo::Bitset intersection(bitset.intersection_with(bitset2));
    for (int i = 0; i < 3; ++i) {
        ASSERT_TRUE(intersection[i] == true);
    }
}

TEST(BitsetTests, isSubset1) {
    vmo::Bitset bitset(10);
    vmo::Bitset bitset2(3);
    ASSERT_TRUE(bitset.is_subset(bitset2) == true);
}

TEST(BitsetTests, isSubset2) {
    vmo::Bitset bitset(10);
    vmo::Bitset bitset2(3);
    bitset.set(2);
    bitset2.set(2);
    ASSERT_TRUE(bitset.is_subset(bitset2) == true);
}

TEST(BitsetTests, isSubset3) {
    vmo::Bitset bitset(10);
    vmo::Bitset bitset2(3);
    bitset.set(2);
    ASSERT_TRUE(bitset.is_subset(bitset2) == false);
}

TEST(BitsetTests, clear) {
    vmo::Bitset bitset(10);
    bitset.clear();
    ASSERT_TRUE(bitset.empty() == true);
}

// Bitset::Iterator tests

TEST(BitsetIteratorTests, rangeBasedLoop1) {
    vmo::Bitset bitset(10);
    for (auto a : bitset) {
        ASSERT_TRUE(a == false);
    }
}

TEST(BitsetIteratorTests, rangeBasedLoop2) {
    vmo::Bitset bitset(3);
    bitset.set(0);
    bitset.set(1);
    bitset.set(2);
    for (auto a : bitset) {
        ASSERT_TRUE(a == true);
    }
}

TEST(BitsetIteratorTests, forEach1) {
    vmo::Bitset bitset(10);
    std::for_each(bitset.begin(), bitset.end(), [&](auto a) {
        ASSERT_TRUE(a == false);
    });
}

TEST(BitsetIteratorTests, forEach2) {
    vmo::Bitset bitset(3);
    bitset.set(0);
    bitset.set(1);
    bitset.set(2);
    std::for_each(bitset.begin(), bitset.end(), [&](auto a) {
        ASSERT_TRUE(a == true);
    });
}