#ifndef SNAKE_H
#define SNAKE_H

enum direction {right, left, up, down};

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
    void collision();
    void ShowScore();


private:
    int x_[30];
    int y_[30];

    int foodX_;
    int foodY_;
    int xMax_;
    int yMax_;
    int xMin_;
    int yMin_;
    unsigned lenght_;
    direction currentDirection_;
    int score_;



};

#endif // SNAKE_H
