//--------------------------------------------------------------------------------------------------
// Name:        nCurses UI Library
// File:        Write.cpp
// Description: An abstact base class used by Window class
// Notes:
// Author:      Joseph Lyons
//--------------------------------------------------------------------------------------------------

#include "Write.hpp"

//--------------------------------------------------------------------------------------------------
// Public: Calls the write_definition that the derived class must implement
//--------------------------------------------------------------------------------------------------
void Write::write (const std::string& text, const bool& newline)
{
    write_definition (text, newline);
}

//--------------------------------------------------------------------------------------------------
// Public: Write an integer calling the write_definition that the derived class must implement
//--------------------------------------------------------------------------------------------------
void Write::write (const int& int_number, const bool& newline)
{
    write_definition (std::to_string (int_number), newline);
}

//--------------------------------------------------------------------------------------------------
// Public: Write a float calling the write_definition that the derived class must implement
//--------------------------------------------------------------------------------------------------
void Write::write (const float& float_number, const bool& newline)
{
    write_definition (std::to_string (float_number), newline);
}

//--------------------------------------------------------------------------------------------------
// Public: Write a double calling the write_definition that the derived class must implement
//--------------------------------------------------------------------------------------------------
void Write::write (const double& double_number, const bool& newline)
{
    write_definition (std::to_string (double_number), newline);
}

//--------------------------------------------------------------------------------------------------
// Public: Write a char calling the write_definition that the derived class must implement
//--------------------------------------------------------------------------------------------------
void Write::write (const char& character, const bool& newline)
{
    write_definition (std::string (1, character), newline);
}
