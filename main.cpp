#include <iostream>
#include "bitset.h"

class TestBitset {
public:
    static void Run() {
        vmo::Bitset bitset(10);
        vmo::Bitset bitset_copy(bitset);

        bitset = bitset_copy;

        bitset.set(11);
        std::cout << bitset.test(15) << "\n";
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

