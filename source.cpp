#include "snake.h"
#include "gui.h"


#ifdef __unix__
#define CURSOR_HIDE system("setterm -cursor off")
#endif

#ifdef WIN32_
#define CURSOR_HIDE ShowConsoleCursor(false)
#endif

void Game(Snake &s, direction &current, bool &game)
{
    s.Borders_Draw();
    while(!game)
    {
        if(current != enter)
        {
            s.ShowScore();
            s.Set_Direction(current);
            s.Move();
            s.Collision(game);
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

void Control(direction &current, bool &game_end)
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

    while(!game_end)
    {
        if(!pause)
        {
            previous = current;
            key = getchar();
        }
        if(game_end)
        {
            tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
            return;
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
#endif

#ifdef _WIN32

#define UP      72
#define DOWN    80
#define RIGHT   77
#define LEFT    75
#define ENTER   13

void Control(direction &current, bool &game_end)
{
	direction previous;
	bool pause = false;
    int key;
    while(!game_end)
    {
		key = _getch();
        if(!pause)
        {
            previous = current;
        }
            switch (key)
            {
                case ENTER:
                {
                    pause = true;
                    current = enter;
                    
                    break;
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
    Snake obj;
    direction start = direction::right;
    std::thread gameThread(Game,std::ref(obj), std::ref(start), std::ref(gameEnd));
    std::thread controlThread(Control, std::ref(start), std::ref(gameEnd));
    gameThread.join();
    controlThread.join();
    std::cout.flush();
}


bool Menu()
{
    std::string options[2] = {"   New Game   ", "     Exit     "};
    GUI menu(2, options, "GAME OVER",bg_emphasizing, red);
    return menu.Show();
}

#ifdef _WIN32
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
#endif
int main()
{
    cls();
    CURSOR_HIDE;
    bool gameEnd = false;
    while(!gameEnd)
    {
        StartGame(gameEnd);
        gameEnd = Menu(); //Menu function
    }

    return 0;
}
