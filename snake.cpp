#include "snake.h"
#include <iostream>
#include <unistd.h>
#include <math.h>
#include <time.h>

#define head 0

void SetCursorPos(Snake::Point_ p)
{
    std::cout.flush();
    printf("\033[%d;%dH", p.y_ + 1, p.x_ + 1);
}
void SetCursorPos(int XPos, int YPos)
{
    std::cout.flush();
    printf("\033[%d;%dH", YPos + 1, XPos + 1);
}


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



Snake::Snake() : max_({38, 19}), min_({0, 1})
{
    //max_ = {38, 19};
    //max_.x_ = 38;
    //max_.y_ = 19;
    //min_ = {0, 1};
    //min_.x_ = 0;
    //min_.y_ = 1;

    lenght_ = 10;
    score_ = 0;
    currentDirection_ = right;
    loos_ = false;

    snake_ = new Point_[lenght_ + 1];
    for(unsigned i = 0; i < lenght_ + 1; i++)
    {
        //snake_[i] = {0, 0};
        snake_[i].x_ = 0;
        snake_[i].y_ = 0;
    }
    srand(time(0));
    do
    {
        snake_[head].x_= rand() % max_.x_ + 2;
        snake_[head].y_= rand() % max_.y_ + 1;
    }
    while(snake_[head].x_ % 2);

    GenerateFood();

}


Snake::~Snake()
{
    delete [] snake_;
}

void Snake::Resize()
{
    Point_ *temp = new Point_[lenght_ + 1];

    for(unsigned i = 0; i < lenght_; i++)
    {
        temp[i] = snake_[i];
    }

    delete []snake_;
    snake_ = temp;

}



void Snake::Borders_Draw()
{
    SetCursorPos(0,0);
    //
    for(int j = min_.x_; j < max_.x_ + 2; j++)
    {
       std::cout << output(" ", 0, 0, 44);
    }
    //
    std::cout << std::endl;
    for(int i = min_.y_; i < max_.y_+ 1; i++)
    {
        for(int j = min_.x_; j < max_.x_ + 2; j++)
        {
            std::cout << output(" ", 0, 0, 46 );
        }
       std::cout << std::endl;
    }


}

void Snake::GenerateFood()
{
     food_.x_ = rand() % max_.x_ + 2;
     food_.y_ = rand() % max_.y_ + 1;

     for(unsigned i = 0; i < lenght_ + 1; i++)
     {
         if((food_ == snake_[i]) || (food_.x_ % 2 != 0))
         {
             GenerateFood();
             break;
         }
     }

}

void Snake::Collision(bool &b)
{
    for(unsigned i = 1; i < lenght_; i++)
    {
        if(snake_[i] == snake_[head])
        {
            b = true;
            for(int t = 0; t < 5; t++)
            {
                for(unsigned i = 1; i < lenght_ + 1; i++)
                {
                    SetCursorPos(snake_[i]);
                    std::cout << output("  ", 0, 0, 47 );
                }
                SetCursorPos(snake_[head + 1]);
                std::cout << output("  ", 0, 0, 40 );
                std::cout.flush();
                usleep(100000);

                for(unsigned i = 0; i < lenght_ + 1; i++)
                {
                    SetCursorPos(snake_[i]);
                    std::cout << output("  ", 0, 0, 46 );
                }
                std::cout.flush();
                usleep(100000);


            }
            SetCursorPos(food_);
            std::cout << output("  ", 0, 0, 46 );


        }
    }
}

void Snake::Eat()
{
    if(snake_[head] == food_)
    {
        lenght_++;
        Resize();
        score_++;
        GenerateFood();
    }
}

void Snake::ShowScore()
{
    SetCursorPos(0,0);
    for(int j = min_.x_; j < max_.x_ + 2; j++)
    {
       std::cout << output(" ", 0, 0, 44);
    }
    SetCursorPos(16,0);
    std::cout << output("Score: ", 0, 0, 44)
              << output(std::to_string(score_), 0, 0, 44);

}
void Snake::Pause()
{
    SetCursorPos(33, 0);
    std::cout << output("Paused", 0, 0, 44);

}

void Snake::positionSwap()
{
    for(int i = lenght_; i > 0; i--)
    {
        snake_[i].x_ = snake_[i-1].x_;
        snake_[i].y_ = snake_[i-1].y_;
    }
}

void Snake::Move()
{
    positionSwap();
    switch (currentDirection_)
    {
        case right:
        {
            if(snake_[head].x_ < max_.x_)
                snake_[head].x_ = snake_[head + 1].x_ + 2;
            else
                snake_[head].x_ = min_.x_;
            break;
        }
        case left:
        {
            if(snake_[head].x_ > min_.x_)
                snake_[head].x_ = snake_[head + 1].x_ - 2;
            else
                snake_[head].x_ = max_.x_;
            break;
        }
        case down:
        {
            if(snake_[head].y_ < max_.y_)
                snake_[head].y_ = snake_[head + 1].y_ + 1;
            else
                snake_[head].y_ = min_.y_;
            break;
        }
        case up:
        {
            if(snake_[head].y_ > min_.y_)
                snake_[head].y_ = snake_[head + 1].y_ - 1;
            else
                snake_[head].y_ = max_.y_;
            break;
        }

    }
}

void Snake::Show_Snake()
{
    SetCursorPos(food_);
    std::cout << output("  ", 0, 0, 41);

    SetCursorPos(snake_[lenght_]);
    std::cout << output("  ", 0, 0, 46 );

    SetCursorPos(snake_[head + 1]);
    std::cout << output("  ", 0, 0, 47);

    SetCursorPos(snake_[head]);
    std::cout << output("  ", 0, 0, 40);


    std::cout.flush();
    usleep(100000);

}
