#ifndef GUI_H
#define GUI_H



#include <iostream>
#define TAB "\t"

#ifdef _WIN32
#include <conio.h>
#define cls() system("cls")
#endif

#ifdef __unix__
#include <termios.h>
#include <unistd.h>
#define cls() system("clear")
#endif

std::string ColoredOut(std::string text, int type, int color, int bg);

enum color
{
    black       = 30,
    red         = 31,
    green       = 32,
    yellow      = 33,
    blue        = 34,
    purple      = 35,
    light_blue  = 36,
    white       = 37
};
enum emphasizing_mode
{
    bg_emphasizing,
    text_emphasizing
};

class GUI
{

public:
    int Show();
    GUI();
    GUI(int size, std::string* names, std::string head, emphasizing_mode mode, color emp_color);
    //std::string ColoredOut(std::string text, int type, int color, int bg);

    ~GUI()
    {
        delete [] strArray_;
    }

private:
    void Set_Mode(emphasizing_mode inputMode, color color);
    std::string *strArray_;

    int optionsAmount_;
    std::string Header_;
    int textColor_;
    int bgColor_;

    bool enter_;
    int position_;

    void Display();
    void Navigator();
};


#endif // GUI_H
