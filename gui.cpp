#include "gui.h"
#include "snake.h"

#ifdef __APPLE__
#define __unix__
#endif

#ifdef __unix__

void Set_Cursor_Pos(Snake::Point_ p)
{
    std::cout.flush();
    printf("\033[%d;%dH", p.y_ + 1, p.x_ + 1);
}

void Set_Cursor_Pos(int XPos, int YPos)
{
    std::cout.flush();
    printf("\033[%d;%dH", YPos + 1, XPos + 1);
}
#endif // __unix__

#ifdef _WIN32

void Set_Cursor_Pos(Snake::Point_ point)
{
    COORD p = { (point.x_), (point.y_) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void Set_Cursor_Pos(int XPos, int YPos)
{
    COORD p = { XPos, YPos };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

#endif // _WIN32

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

void GUI::Set_Mode(emphasizing_mode inputMode, color setColor)
{
    if(inputMode == bg_emphasizing)
    {
        bgColor_ = setColor;
        textColor_ = 0;
    }
    else
    {
        textColor_ = setColor;
        bgColor_ = 0;
    }
}

int GUI::Show()
{
    Display();
    return position_;
}

void GUI::Display()
{
    if(enter_)
        return;
    Set_Cursor_Pos(13, 5);
    std::cout  << ColoredOut(Header_, 1,WHITE_COLOR, LIGHT_BLUE_COLOR) << std::endl << std::endl;

    for (int i = 0; i < optionsAmount_; i++)
    {
        if(i == position_)
        {
            Set_Cursor_Pos(12, (7 + i));
            std::cout  << ColoredOut(strArray_[i], 0, textColor_, bgColor_);
        }
        else
        {
            Set_Cursor_Pos(12, (7 + i));
            std::cout  << ColoredOut(strArray_[i], 0, 0, LIGHT_BLUE_COLOR);
        }
        std::cout << std::endl;
    }
    Navigator();
    Display();

}


#ifdef __unix__
void GUI::Navigator()
{
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
}
#endif
#ifdef _WIN32
void GUI::Navigator()
{
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
}
#endif


