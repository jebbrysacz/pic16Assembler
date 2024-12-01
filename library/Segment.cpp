/*

NOTE THAT SEGMENTS ARE NOT YET IMPLEMENTED


*/

#include "Segment.hh"

// Default constructor
Segment::Segment() : data("default") {}
    
// Constructor with name
Segment::Segment(const std::string& data) : data(data) {}

// Destructor
Segment::~Segment() {}

// Member function to check if the segment matches a given string
bool Segment::segment_match(const std::string& matchString) const {
    return data == matchString;
}

// Getter for the data member
const std::string& Segment::getData() const {
    return data;
}
