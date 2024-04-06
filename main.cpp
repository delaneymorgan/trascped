#include <iostream>

#include "trascped.h"


class SomeClass {
public:
    SomeClass() {
        TRACE();
    }

    ~SomeClass() {
        TRACE();
    }
};

void sub2() {
    TRACE();
    SomeClass someClass;
    throw std::exception();
}

void sub1() {
    TRACE();
    sub2();
}

int main() {
    TRACE();
    std::cout << "Start" << std::endl;
    try {
        sub1();
        std::cout << "normal" << std::endl;
    }
    catch (std::exception &ex) {
        std::cout << "exception" << std::endl;
    }
    std::cout << "Done!" << std::endl;
    return 0;
}
