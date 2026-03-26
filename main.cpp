#include <cassert>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "include/bitset.h"

class TestBitset {
public:
    static void Run() {

        using std::size_t;
        using std::cout;

        vmo::Bitset bitset(10);
        vmo::Bitset bitset_copy(bitset);

        bitset.set(3);

        for (std::size_t i = 0; i < bitset.size(); ++i) {
            std::cout << bitset[i];
        }

        std::cout << '\n';

        for (auto it = bitset.begin(); it != bitset.end(); ++it) {
            std::cout << *it;
        }

        std::cout << '\n';

        bitset_copy.set(3);
        bitset_copy.set(20);

        std::for_each(bitset_copy.begin(), bitset_copy.end(), [](const int& value) {
            std::cout << value;
        });

        std::cout << '\n';

        vmo::Bitset new_bitset(std::move(bitset));
        //std::cout << bitset[0];
        for (const auto& value : new_bitset) {
            std::cout << value;
        }

        std::cout << '\n' << "union_with:\n";
        const vmo::Bitset bitset_union = bitset_copy.union_with(new_bitset);
        for (const auto& value : bitset_union) {
            std::cout << value;
        }

        assert(static_cast<bool>(std::cout) == true && "std::cout is dead");
    }
};

int main() {

    try {
       TestBitset::Run();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

