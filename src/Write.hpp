//--------------------------------------------------------------------------------------------------
// Project:     Ultima 2.0
// File:        Write.hpp
// Description: An abstact base class used by both the Window class and the File_Out class
// Notes:
// Authors:     Joseph Lyons, Shaun Whitfield
// Class:       CSCI-C 435: Operating Systems (Spring 2019)
//--------------------------------------------------------------------------------------------------

#ifndef Write_hpp
#define Write_hpp

#include <iostream>

class Write
{
private:
    // Must be implemented by any derived class, all the public write functions depend on it
    virtual void write_definition (const std::string& text, const bool& newline) = 0;

public:
    // All public overloaded write() methods should either directly call write_definition()
    // or call other overloaded versions of write() that directly call write_definition()
    void write (const std::string& text, const bool& newline);
    void write (const int& int_number, const bool& newline);
    void write (const float& float_number, const bool& newline);
    void write (const double& double_number, const bool& newline);
    void write (const char& character, const bool& newline);
};

#endif /* Write_hpp */
