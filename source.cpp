#include <iostream>
#include "snake.h"
#include <termios.h>
#include <unistd.h>
#include <thread>


#define UP      'A'
#define DOWN    'B'
#define RIGHT   'C'
#define LEFT    'D'
#define ENTER   '\n'

#define ESC 27


void Game(Snake &s, direction &current, bool &game)
{
    s.Borders_Draw();
    while(!game)
    {
        if(current != enter)
        {
            s.Set_Direction(current);
            s.ShowScore();
            s.Move();
            s.Show_Snake();
            s.Eat();
            s.Collision(game);
        }
        else
        {
            s.Pause();
        }
    }

}

void Control(direction &current, bool &game)
{
    bool pause = false;
    int key;
    struct termios oldt,
            newt;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    direction previous;

    while(!game)
    {
        if(!pause)
        {
            previous = current;
            key = getchar();
        }


        if((char)key == ENTER)
        {
            pause = true;
            current = enter;
            std::cout.flush();
            key = getchar();
            continue;
        }



        if (key == ESC)
        {
            key = getchar();
            if (key == '[')
            {
                key = getchar();
                switch (key)
                {
                    case UP:
                    {
                        if(!(previous == down))
                        {
                            current = up;
                            pause = false;
                        }
                        else
                        {
                            key = ESC;
                        }
                        break;
                    }
                    case DOWN:
                    {
                        if(!(previous == up))
                        {
                            current = down;
                            pause = false;
                        }
                        else
                        {
                            key = ESC;
                        }
                        break;
                    }
                    case LEFT:
                    {
                        if(!(previous == right))
                        {
                           current = left;
                           pause = false;
                        }
                        else
                        {
                            key = ESC;
                        }
                        break;
                    }
                    case RIGHT:
                    {
                        if(!(previous == left))
                        {
                           current = right;
                           pause = false;
                        }
                        else
                        {
                            key = ESC;
                        }
                        break;
                    }
                }
            }
        }
        std::cout.flush();
        usleep(100000);

    }
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
}

void StartGame(bool &gameEnd)
{
    Snake a;

    direction start = direction::right;
    std::thread gameThread(Game,std::ref(a), std::ref(start), std::ref(gameEnd));
    std::thread controlThread(Control, std::ref(start), std::ref(gameEnd));
    gameThread.join();
    controlThread.join();
    std::cout.flush();
}



int main()
{
    system("setterm -cursor off");
    bool gameEnd = false;
    while(!gameEnd)
    {
        StartGame(gameEnd);
        gameEnd = true; //Menu function
    }
    std::cout << "End";

    return 0;
}
