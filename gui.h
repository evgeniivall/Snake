#ifndef GUI_H
#define GUI_H


#include "snake.h"
#include <iostream>
#define TAB "\t"

#ifdef _WIN32
#include <conio.h>
#include "windows.h"
#define cls() system("cls")
#endif

#ifdef __unix__
#include <termios.h>
#include <unistd.h>
#define cls() system("clear")
#endif

std::string ColoredOut(std::string text, int type, int color, int bg);
void Set_Cursor_Pos(int XPos, int YPos);
void Set_Cursor_Pos(Snake::Point_ p);

enum color
{
    BLACK_COLOR       = 30,
    RED_COLOR         = 31,
    GREEN_COLOR       = 32,
    YELLOW_COLOR      = 33,
    BLUE_COLOR        = 34,
    PURPLE_COLOR      = 35,
    LIGHT_BLUE_COLOR  = 36,
    WHITE_COLOR       = 37
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
