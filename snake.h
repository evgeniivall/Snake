#ifndef SNAKE_H
#define SNAKE_H

#include <math.h>
#include <time.h>
#include <thread>
#include <unistd.h>

#ifdef _WIN32
#define usleep(x) Sleep((x)/1000)
#endif

enum direction {RIGHT, LEFT, UP, DOWN, PAUSE};


class Snake
{
    struct Point_;
public:
    Snake();
    void Show_Snake();
    void Set_Direction(direction d);
    void Eat();
    void GenerateFood();
    void Borders_Draw();
    void Collision(bool &b);
    void ShowScore();
    void Move();
    void Pause();

    friend void Set_Cursor_Pos(Point_ p);

    void Resize();
    ~Snake();
private:
    void positionSwap();

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
};


#endif // SNAKE_H


