#include "snake.h"

#include "gui.h"




void Game(Snake &s, direction &current, bool &game)
{
    s.Borders_Draw();
    while(!game)
    {
        if(current != enter)
        {
            s.Set_Direction(current);
            s.Move();
            s.Collision(game);
            s.ShowScore();
            if(!game)
            {
                s.Show_Snake();
            s.Eat();
            }


        }
        else
        {
            s.Pause();
        }
    }

}
#ifdef __unix__

#define UP      'A'
#define DOWN    'B'
#define RIGHT   'C'
#define LEFT    'D'
#define ENTER   '\n'
#define ESC      27

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
        //if(game)
        //{
        //    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
        //    return;
        //}

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

            //if(game)
            //{
            //    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
            //    return;
            //}
            key = getchar();

            if (key == '[')
            {
          //      if(game)
            //    {
              //      tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
                //    return;
                //}
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
#endif

#ifdef _WIN32

#define UP      72
#define DOWN    80
#define RIGHT   77
#define LEFT    75
#define ENTER   13

void Control(direction &current, bool &game)
{
    bool pause = false;
    int key;
    while(!game)
    {
        if(!pause)
        {
            previous = current;
            key = getchar();
        }
            switch (key)
            {
                case ENTER:
                {
                    pause = true;
                    current = enter;
                    key = getchar();
                    continue;
                }
                case UP:
                {
                    if(!(previous == down))
                    {
                        current = up;
                        pause = false;
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
                    break;
                }
                case LEFT:
                {
                    if(!(previous == right))
                    {
                        current = left;
                        pause = false;
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
                    break;
                }
           }
          usleep(100000);
    }
}

#endif
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


bool Menu()
{
    std::string options[2] = {"   New Game   ", "     Exit     "};
    GUI G(2, options, "You are lose!",bg_emphasizing, red);
    return G.Show();
}

int main()
{
    system("setterm -cursor off");
    bool gameEnd = false;
    while(!gameEnd)
    {
        StartGame(gameEnd);
        gameEnd = Menu(); //Menu function
    }
    std::cout << "End";

    return 0;
}
