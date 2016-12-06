#include <iostream>
#include "snake.h"
#include <termios.h>
#include <unistd.h>
#include <thread>
void func(Snake &s, direction &current)
{
    s.Borders_Draw();
    while(true)
    {
        s.ShowScore();
        s.Set_Direction(current);
        s.collision();
        s.Eat();
        s.Show_Snake();
    }
}

void Control(direction &current)
{
    struct termios oldt,
            newt;
    while(true)
    {
        tcgetattr( STDIN_FILENO, &oldt );
        newt = oldt;
        newt.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newt );
        int key = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

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
                        if(!(current == down))
                            current = up;
                        break;
                    }
                    case 'A':
                    {
                        if(!(current == up))
                            current = down;
                        break;
                    }
                    case 'D':
                    {
                        if(!(current == right))
                            current = left;
                        break;
                    }
                    case 'C':
                    {
                        if(!(current == left))
                            current = right;
                        break;
                    }

                }
            }
        }
    }
    usleep(500);
}

int main()
{
    system("setterm -cursor off");
    Snake a;
    direction start = direction::right;
    std::thread game(func,std::ref(a), std::ref(start));
    std::thread arrows(Control, std::ref(start));
    game.join();
    arrows.join();

    return 0;
}
