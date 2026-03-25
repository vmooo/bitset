#include <iostream>
#include "bitset.h"

class TestBitset {
public:
    void Run() {

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

