#include <iostream>
#include "bitset.h"

class TestBitset {
public:
    void Run() {
        vmo::Bitset bitset(10);
        vmo::Bitset bitset_copy(bitset);


    }
};

int main() {

    try {
       TestBitset().Run();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

