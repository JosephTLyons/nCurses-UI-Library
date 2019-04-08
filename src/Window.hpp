//--------------------------------------------------------------------------------------------------
// Project:     Ultima 2.0
// File:        Window.hpp
// Description: A Window class that uses the power of nCurses to build windows, while purposely
//              avoiding all of nCurses major downfalls.
// Notes:       This class should only be called from within the UI class, as the UI constructor
//              contains the initscr() and endwin() ncurses functions that need to be called before
//              and after the lifetime of these Window objects.  The UI constructor also calls n
//              noecho(), a function that keeps wgetch() from inserting values into the screen for
//              us during the Window class' live_input() method.
//
//              Window = an instance of this Window wrapper class
//              WINDOW = an instance of an nCurses window
//
// Authors:     Joseph Lyons, Shaun Whitfield
// Class:       CSCI-C 435: Operating Systems (Spring 2019)
//--------------------------------------------------------------------------------------------------

#ifndef Window_hpp
#define Window_hpp

#include <iostream>
#include <ncurses.h>
#include "Write.hpp"

class Window : public Write
{
private:
    WINDOW* ncurse_border_ptr;
    WINDOW* ncurse_text_ptr;
    const bool is_center_print_window;

    // Private methods
    void write_definition (const std::string& text, const bool& newline) override;
    std::string get_centered_text (const std::string& text);

public:
    Window (const unsigned int& x, const unsigned int& y,
            const unsigned int& width, const unsigned int& height,
            const std::string& window_title, const bool& is_center_print_window_input);

    ~Window();

    char live_input (const bool& newline);
    void print_divider (const char& divider_symbol);

    void clear_window();

    unsigned int get_width();
    unsigned int get_height();
};

#endif /* Window_hpp */
