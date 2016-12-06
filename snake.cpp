#include "snake.h"
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <time.h>

void Snake::Set_Direction(direction d)
{
    currentDirection_ = d;
}

std::string output(std::string text, int type, int color, int bg)
{
    bool par = 0;
    std::string str = "\x1b[";
    if(color != 0)
    {
        str += std::to_string(color);
        par = 1;
    }
    if(type != 0)
    {
        if(par != 0)
            str += ";";
        str += std::to_string(type);
        par = 1;
    }
    if(bg != 0)
    {
        if(par != 0)
            str += ";";
        str += std::to_string(bg);
    }
    str = str + "m" + text + "\x1b[0m";

    return str;
}

void SetCursorPos(int XPos, int YPos)
{
    printf("\033[%d;%dH", YPos+1, XPos+1);
}

Snake::Snake()
{
    for(int i = 0; i < 40; i++)
        x_[i] = 0;
    for(int i = 0; i < 40; i++)
        y_[i] = 0;
    x_[0] = 2;
    y_[0] = 1;
    xMax_ = 40;
    yMax_ = 20;
    xMin_ = 2;
    yMin_ = 2;
    lenght_ = 2;
    score_ = 0;
    currentDirection_ = right;
    GenerateFood();
}

void Snake::positionSwap()
{
    for(int i = lenght_ + 1; i > 0; i--)
    {
        x_[i] = x_[i-1];
        y_[i] = y_[i-1];

    }
}
void Snake::Borders_Draw()
{
    SetCursorPos(0,0);
    for(int i = xMin_-2; i < xMax_+ 4; i++)
        std::cout << output(" ", 0, 0, 47);
    SetCursorPos(xMin_-2,yMax_+1);
    for(int i = xMin_-2; i < xMax_ + 4; i++)
        std::cout << output(" ", 0, 0, 47);
    for(int i = yMin_-1; i < yMax_+1; i++)
    {
        SetCursorPos(xMin_-2, i);
        std::cout << output("  ", 0, 0, 47);
    }
    for(int i = yMin_-1; i < yMax_+1; i++)
    {
        SetCursorPos(xMax_+ 2, i);
        std::cout << output("  ", 0, 0, 47);
    }


}

void Snake::GenerateFood()
{
     foodX_ = 1 + rand() % xMax_;
     foodY_ = 1 + rand() % yMax_;

     for(int i = 0; i < lenght_; i++)
     {
         if(((x_[i] == foodX_) && (y_[i] == foodY_)) || (foodX_ % 2 != 0))
         {
             GenerateFood();
             break;
         }
     }

}

void Snake::collision()
{
    for(int i = 1; i < lenght_; i++)
    {
        if((x_[i] == x_[0]) && (y_[i] == y_[0]))
        {
            sleep(3);

        }
    }
}

void Snake::Eat()
{
    if((x_[0] == foodX_) && (y_[0] == foodY_))
    {
        lenght_++;
        score_++;
        GenerateFood();
    }
}

void Snake::ShowScore()
{
    SetCursorPos(xMax_+5, 1);
    std::cout << "Score: " << score_;
}

void Snake::Show_Snake()
{
    SetCursorPos(foodX_, foodY_);
    std::cout << output("  ", 0, 0, 44);

    SetCursorPos(x_[lenght_], y_[lenght_]);
    std::cout << "  ";
    SetCursorPos(x_[1], y_[1]);
    std::cout << output("  ", 0, 0, 47);
    SetCursorPos(x_[0], y_[0]);
    std::cout << output("  ", 0, 0, 40);

    positionSwap();
    switch (currentDirection_)
    {
    case right:
    {
        if(x_[0] < xMax_)
            x_[0] = x_[1]+2;
        else
            x_[0] = xMin_;
        break;
    }
    case left:
    {
        if(x_[0] > xMin_)
            x_[0] = x_[1]-2;
        else
            x_[0] = xMax_;
        break;
    }
    case up:
    {
        if(y_[0] < yMax_)
            y_[0] = y_[1]+1;
        else
            y_[0] = yMin_-1;
        break;
    }
    case down:
    {
        if(y_[0] > yMin_-1)
            y_[0] = y_[1]-1;
        else
            y_[0] = yMax_;
        break;
    }

    }
    std::cout.flush();
    usleep(110000);

}
