#include "gui.h"
#include <iostream>
#include "snake.h"
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

GUI::GUI(int size, std::string* names, std::string head, emphasizing_mode mode, color emp_color)
{
    optionsAmount_ = size;
    strArray_ = new std::string[optionsAmount_];
    for(int i = 0; i < optionsAmount_; i++)
    {
        strArray_[i] = names[i];
    }
    position_ = 0;
    Header_ = head;
    Set_Mode(mode, emp_color);

    enter_ = false;
}
void GUI::Set_Mode(emphasizing_mode inputMode, color col)
{
    if(inputMode == bg_emphasizing)
    {
        bgColor_ = col + 10;
        textColor_ = 0;
    }
    else
    {
        textColor_ = col;
        bgColor_ = 0;
    }
}

std::string GUI::ColoredOut(std::string text, int type, int color, int bg)
{
    bool flag = false;
    std::string str = "\x1b[";
    if(color != 0)
    {
        str += std::to_string(color);
        flag = true;
    }
    if(type != 0)
    {
        if(flag)
            str += ";";
        str += std::to_string(type);
        flag = true;
    }
    if(bg != 0)
    {
        if(flag)
            str += ";";
        str += std::to_string(bg);
    }
    str = str + "m" + text + "\x1b[0m";

    return str;
}

//void GUI::Show()
int GUI::Show()
{
    Display();
    return position_;
}

void GUI::Display()
{
    //cls();
    if(enter_)
        return;
    SetCursorPos(13, 5);
    std::cout  << ColoredOut(Header_,1,white,46) << std::endl << std::endl;

    for (int i = 0; i < optionsAmount_; i++)
    {
        if(i == position_)
        {
            SetCursorPos(12, (7 + i));
            std::cout  << ColoredOut(strArray_[i], 0, textColor_, bgColor_);
        }
        else
        {
            SetCursorPos(12, (7 + i));
            std::cout  << ColoredOut(strArray_[i], 0, 0, 46);
        }
        std::cout << std::endl;
    }
    Navigator();
    Display();

}

void GUI::Navigator()
{
#ifdef __unix__

    struct termios oldt,
        newt;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    int key = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

    if((char)key == '\n')
        enter_ = true;
    if (key == 27)
    {
        key = getchar();
        if (key == '[')
        {
            key = getchar();
            switch (key)
            {
                case 'B':
                {
                    if (position_ + 1 < optionsAmount_)
                        ++position_;
                    else
                        position_ = 0;
                    break;
                }
                case 'A':
                {
                    if (position_ - 1 >= 0)
                        --position_;
                    else
                        position_ = optionsAmount_ - 1;
                    break;
                }

            }
        }
    }
#endif
#ifdef _WIN32

    int key = _getch();

        switch (key)
        {
            case 80:
            {
                if (position_ + 1 < optionsAmount_)
                    ++position_;
                else
                    position_ = 0;
                break;
            }
            case 72:
            {
                if (position_ - 1 >= 0)
                    --position_;
                else
                    position_ = optionsAmount_ - 1;
                break;
            }
            case 13:
            {
                enter_ = true;
                break;
            }

        }

#endif
}

