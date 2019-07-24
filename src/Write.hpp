//--------------------------------------------------------------------------------------------------
// Name:        nCurses UI Library
// File:        Write.hpp
// Description: An abstact base class used by Window class
// Notes:
// Author:      Joseph Lyons
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
