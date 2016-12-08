#ifndef SNAKE_H
#define SNAKE_H



enum direction {right, left, up, down, enter};

class Snake
{
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

    void Resize();
    ~Snake();
    bool loos_;

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

    void SetCursorPos(Point_ p);
    void SetCursorPos(int XPos, int YPos);

    unsigned lenght_;
    direction currentDirection_;
    int score_;
};

#endif // SNAKE_H
