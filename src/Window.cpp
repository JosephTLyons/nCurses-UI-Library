//--------------------------------------------------------------------------------------------------
// Name:        nCurses UI Library
// File:        Window.cpp
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
// Author:      Joseph Lyons
//--------------------------------------------------------------------------------------------------

#include <iostream>
#include "Window.hpp"

//--------------------------------------------------------------------------------------------------
// Private: Write definition provides the required definition for the private virtual pure function
//          of the Write base class that this Window class inherits.  The Write base class then has
//          public write methods that utilize this definition of how to write.  These public write
//          functions of the Write class are what are actually called on the Window objects in order
//          to write to them.
//--------------------------------------------------------------------------------------------------
void Window::write_definition (const std::string& text, const bool& newline)
{
    if (is_center_print_window)
        wprintw (ncurse_text_ptr, get_centered_text (text).c_str());
    else
        wprintw (ncurse_text_ptr, text.c_str());

    if (newline)
        wprintw (ncurse_text_ptr, "\n");

    wrefresh (ncurse_text_ptr); // Refresh the text window
}

//--------------------------------------------------------------------------------------------------
// Private: Pads a string with the correct amount of spaces to center it within this window.
// Notes:   If a string has more characters than the width of the window, centering will be skipped
//          and the original string will be returned.
//--------------------------------------------------------------------------------------------------
std::string Window::get_centered_text (const std::string& text)
{
    int spaces_left = getmaxx (ncurse_text_ptr) - (int) text.length();

    if (spaces_left <= 0)
        return text;

    return std::string (spaces_left / 2, ' ') + text;
}

//--------------------------------------------------------------------------------------------------
// Public: Constructor - Intializes and draws both the text window and the border window.  Based on
//         the user's settings, the constructor will either display the window title or not and give
//         the user the option to have text centered or left aligned text.  If a title isn't used,
//         the text window takes this space and uses it as a printable region.
//--------------------------------------------------------------------------------------------------
Window::Window (const unsigned int& x, const unsigned int& y,
                const unsigned int& width, const unsigned int& height,
                const std::string& window_title, const bool& is_center_print_window_input)
    : is_center_print_window (is_center_print_window_input)
{
    // Create inner invisible window for the text

    // If a window title is wanted, we need to adjust the inner text window down a line to allow
    // for it, if we don't want a title, go ahead and use the space where the title would be as
    // printable space for the text window
    const bool has_window_title = window_title.length() > 0;

    unsigned int adjustment = 0;

    if (has_window_title)
        adjustment = 1;

    ncurse_text_ptr = newwin (height - adjustment - 2, width - 2, y + adjustment + 1, x + 1);

    scrollok (ncurse_text_ptr, TRUE);

    // Create outer border of window
    ncurse_border_ptr = newwin (height, width, y, x);
    box (ncurse_border_ptr, 0, 0);

    // Print centered window title if requested
    if (has_window_title)
        mvwprintw (ncurse_border_ptr, 1, 1, get_centered_text (window_title).c_str());

    wrefresh (ncurse_border_ptr);
}

//--------------------------------------------------------------------------------------------------
// Public: Destructor
//--------------------------------------------------------------------------------------------------
Window::~Window()
{

}

//--------------------------------------------------------------------------------------------------
// Public: Allows the user to write the screen via keyboard in real-time.  The char that is written
//         is returned so that the calling function may use it for whatever it may need.
// Note:   Live input does not currently support center-aligned text.  Please use left-aligned until
//         this is implemented.  Currently, the application will terminate if you try to call
//         live_input() on a center print window.  This will be removed if this feature is added in
//         the future.
//--------------------------------------------------------------------------------------------------
char Window::live_input (const bool& newline)
{
    assert(! is_center_print_window);

    char input = wgetch (ncurse_text_ptr);
    flushinp(); // Does this need to be here for this library?
    write (input, newline);
    return input;
}

//--------------------------------------------------------------------------------------------------
// Public: Prints a line as long as the window is wide using the divider_symbol
//--------------------------------------------------------------------------------------------------
void Window::print_divider (const char& divider_symbol)
{
    write (std::string (get_width(), divider_symbol), false);
}

//--------------------------------------------------------------------------------------------------
// Public: Empty all text from within window
//--------------------------------------------------------------------------------------------------
void Window::clear_window()
{
    wclear (ncurse_text_ptr);
    wrefresh (ncurse_text_ptr);
}

//--------------------------------------------------------------------------------------------------
// Public: Returns the width (columns) of the internal window
//--------------------------------------------------------------------------------------------------
unsigned int Window::get_width()
{
    return getmaxx (ncurse_text_ptr);
}

//--------------------------------------------------------------------------------------------------
// Public: Returns the height (lines) of the internal window
//--------------------------------------------------------------------------------------------------
unsigned int Window::get_height()
{
    return getmaxy (ncurse_text_ptr);
}
