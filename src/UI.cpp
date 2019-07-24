//--------------------------------------------------------------------------------------------------
// Name:        nCurses UI Library
// File:        UI.cpp
// Description: A user interface class that dynamically creates Windows and offers the user a
//              handful of Window functionality, such as writing and clearing.
// Notes:
// Author:      Joseph Lyons
//--------------------------------------------------------------------------------------------------

#include "UI.hpp"

//--------------------------------------------------------------------------------------------------
// Private: Ensures window is a valid choice
//--------------------------------------------------------------------------------------------------
bool UI::window_is_valid (const unsigned int& window_number)
{
    return window_number < window_vector.size();
}

//--------------------------------------------------------------------------------------------------
// Private: Prints an error stating the window is invalid
//--------------------------------------------------------------------------------------------------
void UI::print_error()
{
    write_to_all_windows ("Invalid Window Requested", true);
}

//--------------------------------------------------------------------------------------------------
// Public: Constructor - Sets up nCurses
//--------------------------------------------------------------------------------------------------
UI::UI()
{
    // start nCurses
    initscr();
    refresh();

    // Set noecho so that input isn't automatically inserted into a window by nCurses when wgetch()
    // is called from within a Window.  We have our own custom input method, live_input(), that
    // inserts the text received from wgetch() into the correct window.
    noecho();

    new_window = NULL;
}

//--------------------------------------------------------------------------------------------------
// Public: Destructor - Closes down nCurses
//--------------------------------------------------------------------------------------------------
UI::~UI()
{
    // Delete windows
    for (int i = 0; i < window_vector.size(); i++)
        delete window_vector[i];

    // End nCurses
    endwin();
}

//--------------------------------------------------------------------------------------------------
// Public: Instantiates new window
//--------------------------------------------------------------------------------------------------
void UI::make_new_window (const unsigned int& x, const unsigned int& y,
                          const unsigned int& width, const unsigned int& height,
                          const std::string& window_title, const bool& is_center_print_window)
{
    new_window = new (std::nothrow) Window (x, y, width, height, window_title,
                                            is_center_print_window);

    if (new_window == NULL)
        exit (0);

    window_vector.push_back (new_window);
    new_window = NULL;
}

//--------------------------------------------------------------------------------------------------
// Public: Allows the user to write the screen via keyboard in real-time.  The char that is written
//         is returned so that the calling function may use it for whatever it may need.
//--------------------------------------------------------------------------------------------------
char UI::live_input (const unsigned int& window_number, const bool& newline)
{
    if (window_is_valid (window_number))
        return window_vector[window_number]->live_input (newline);

    print_error();

    return 0;
}

//--------------------------------------------------------------------------------------------------
// Public: Prints a line to a window as long as the window is wide using the divider_symbol
//--------------------------------------------------------------------------------------------------
void UI::print_window_divider (const unsigned int& window_number, const char& divider_symbol)
{
    if (window_is_valid (window_number))
        window_vector[window_number]->print_divider (divider_symbol);

    else
        print_error();
}

//--------------------------------------------------------------------------------------------------
// Public: Writes to specified window at default location.
//--------------------------------------------------------------------------------------------------
void UI::write_to_window (const unsigned int& window_number, const std::string& text,
                          const bool& newline)
{
    if (window_is_valid (window_number))
        window_vector[window_number]->write (text, newline);

    else
        print_error();
}

//--------------------------------------------------------------------------------------------------
// Public: Write an integer within window
//--------------------------------------------------------------------------------------------------
void UI::write_to_window (const unsigned int& window_number, const int& int_number,
                          const bool& newline)
{
    window_vector[window_number]->write (int_number, newline);
}

//--------------------------------------------------------------------------------------------------
// Public: Write a float within window
//--------------------------------------------------------------------------------------------------
void UI::write_to_window (const unsigned int& window_number, const float& float_number,
                          const bool& newline)
{
    window_vector[window_number]->write (float_number, newline);
}

//--------------------------------------------------------------------------------------------------
// Public: Write a double within window
//--------------------------------------------------------------------------------------------------
void UI::write_to_window (const unsigned int& window_number, const double& double_number,
                          const bool& newline)
{
    window_vector[window_number]->write (double_number, newline);
}

//--------------------------------------------------------------------------------------------------
// Public: Write a char within window
//--------------------------------------------------------------------------------------------------
void UI::write_to_window (const unsigned int& window_number, const char& character,
                          const bool& newline)
{
    window_vector[window_number]->write (character, newline);
}

//--------------------------------------------------------------------------------------------------
// Public: allows printing to all windows in the UI object
//--------------------------------------------------------------------------------------------------
void UI::write_to_all_windows (const std::string& text, const bool& newline)
{
    for (int i = 0; i < window_vector.size(); i++)
        write_to_window (i, text, true);
}

//--------------------------------------------------------------------------------------------------
// Public: Empty specified window
//--------------------------------------------------------------------------------------------------
void UI::clear_window (const unsigned int& window_number)
{
    window_vector[window_number]->clear_window();
}

//--------------------------------------------------------------------------------------------------
// Public: Empty all windows
//--------------------------------------------------------------------------------------------------
void UI::clear_all_windows()
{
    for (int i = 0; i < window_vector.size(); i++)
        clear_window (i);
}

//--------------------------------------------------------------------------------------------------
// Public: returns the height number of windows that the UI is managing.
//--------------------------------------------------------------------------------------------------
unsigned long int UI::get_number_of_windows()
{
    return window_vector.size();
}

//--------------------------------------------------------------------------------------------------
// Public: returns the width (columns) of the internal window specified.  It returns -1 if the user
//         didn't specify a window that is valid.
//--------------------------------------------------------------------------------------------------
unsigned int UI::get_window_width (const unsigned int& window_number)
{
    if (window_is_valid (window_number))
        return window_vector[window_number]->get_width();

    print_error();

    return -1;
}

//--------------------------------------------------------------------------------------------------
// Public: returns the height (columns) of the internal window specified.  It returns -1 if the user
//         didn't specify a window that is valid.
//--------------------------------------------------------------------------------------------------
unsigned int UI::get_window_height (const unsigned int& window_number)
{
    if (window_is_valid (window_number))
        return window_vector[window_number]->get_height();

    print_error();

    return -1;
}
