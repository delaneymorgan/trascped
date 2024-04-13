/**
 * @file main.cpp
 *
 * @brief trascped example
 *
 * @copyright Delaney & Morgan Computing
 */

#include "trascped.h"


using namespace trascped;


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
    TRACE_CHECK("fred: %d", 12345);
    throw std::exception();
}

void sub1() {
    TRACE();
    sub2();
}

int main() {
    TRACE();
    TRACE_CHECK("Start");
    try {
        sub1();
        TRACE_CHECK("no exception raised");
    }
    catch (std::exception &ex) {
        TRACE_CHECK("exception handled");
    }
    TRACE_CHECK("Done");
    return 0;
}
