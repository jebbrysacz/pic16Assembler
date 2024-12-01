/*

NOTE THAT SEGMENTS ARE NOT YET IMPLEMENTED


*/

#include <iostream>
#include "Segment.hh"

int main() {
    Segment segment("example_data");

    if (segment.segment_match("example_data")) {
        std::cout << "The segment matches the string." << std::endl;
    } else {
        std::cout << "The segment does not match the string." << std::endl;
    }

    std::cout << "Segment data: " << segment.getData() << std::endl;

    return 0;
}
