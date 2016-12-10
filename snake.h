#ifndef SNAKE_H
#define SNAKE_H

#include <math.h>
#include <time.h>
#include <thread>

#ifdef WIN32_
#define usleep(x) Sleep((x)/1000)
#endif

enum direction {right, left, up, down, enter};

class Snake
{


private:
    struct Point_
    {
        int x_;
        int y_;
        bool operator == (Point_ &p)
        {
            if((x_ == p.x_) && (y_ == p.y_))
                return true;
            else
                return false;
        }
    };
    Point_ *snake_;
    Point_ max_;
    Point_ min_;
    Point_ food_;

    int bgColor_;
    int snakeColor_;
    int headColor_;
    int panelColor_;
    int foodColor_;

    unsigned lenght_;
    direction currentDirection_;
    int score_;
public:
    Snake();
    void Show_Snake();
    void Set_Direction(direction d);
    void positionSwap();
    void Eat();
    void GenerateFood();
    void Borders_Draw();
    void Collision(bool &b);
    void ShowScore();
    void Game_End();
    void showFood();
    void Move();
    void Pause();

    friend void Set_Cursor_Pos(Point_ p);

    void Resize();
    ~Snake();
    bool loos_;
};



void Set_Cursor_Pos(int XPos, int YPos);
void Set_Cursor_Pos(Snake::Point_ p);

#endif // SNAKE_H


