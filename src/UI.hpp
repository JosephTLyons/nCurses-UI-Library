//--------------------------------------------------------------------------------------------------
// Name:        nCurses UI Library
// File:        UI.hpp
// Description: A user interface class that dynamically creates Windows and offers the user a
//              handful of Window functionality, such as writing and clearing.
// Notes:
// Author:      Joseph Lyons
//--------------------------------------------------------------------------------------------------

#ifndef UI_hpp
#define UI_hpp

#include <iostream>
#include <vector>
#include "Window.hpp"

class UI
{
private:
    Window* new_window;
    std::vector<Window*> window_vector;

    // Private methods
    bool window_is_valid (const unsigned int& window_number);
    void print_error();

public:
    UI();
    ~UI();

    void make_new_window (const unsigned int& x, const unsigned int& y,
                          const unsigned int& width, const unsigned int& height,
                          const std::string& window_title, const bool& is_center_print_window);

    char live_input (const unsigned int& window_number, const bool& newline);

    void print_window_divider (const unsigned int& window_number, const char& divider_symbol);

    void write_to_window (const unsigned int& window_number, const std::string& text,
                          const bool& newline);
    void write_to_window (const unsigned int& window_number, const int& int_number,
                          const bool& newline);
    void write_to_window (const unsigned int& window_number, const float& float_number,
                          const bool& newline);
    void write_to_window (const unsigned int& window_number, const double& double_number,
                          const bool& newline);
    void write_to_window (const unsigned int& window_number, const char& character,
                          const bool& newline);

    void write_to_all_windows (const std::string& text, const bool& newline);

    void clear_window (const unsigned int& window_number);
    void clear_all_windows();

    unsigned long int get_number_of_windows();

    unsigned int get_window_width (const unsigned int& window_number);
    unsigned int get_window_height (const unsigned int& window_number);
};

#endif /* UI_hpp */
