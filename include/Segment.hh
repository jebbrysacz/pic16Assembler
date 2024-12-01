/*

NOTE THAT SEGMENTS ARE NOT YET IMPLEMENTED


*/

#ifndef SEGMENT_HH
#define SEGMENT_HH

#include <string>

class Segment {
public:
    // Constructors
    Segment();
    Segment(const std::string& data);

    // Destructor
    ~Segment();

    // Member function to check if the segment matches a given string
    bool segment_match(const std::string& matchString) const;

    // Getter for the data member
    const std::string& getData() const;

private:
    std::string data;  // Data stored in the segment
};

#endif
