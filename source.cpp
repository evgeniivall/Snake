#include "snake.h"
#include "gui.h"

#ifdef __APPLE__
#define __unix__
#endif

#ifdef __unix__
#define CURSOR_HIDE system("setterm -cursor off")
#define CURSOR_SHOW system("setterm -cursor on")
#endif



#ifdef WIN32_
#define CURSOR_HIDE ShowConsoleCursor(false)
#define CURSOR_SHOW ShowConsoleCursor(true) 
#endif

void Game(Snake &s, direction &current, bool &game)
{
    s.Borders_Draw();
    while(!game)
    {
        if(current != PAUSE)
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

#define UP_ARROW        'A'
#define DOWN_ARROW      'B'
#define RIGHT_ARROW     'C'
#define LEFT_ARROW      'D'
#define ENTER_KEY       '\n'
#define ESC             27

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

        if((char)key == ENTER_KEY)
        {
            pause = true;
            current = PAUSE;
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
                    case UP_ARROW:
                    {
                        if(!(previous == DOWN))
                        {
                            current = UP;
                            pause = false;
                        }
                        else
                        {
                            key = ESC;
                        }
                        break;
                    }
                    case DOWN_ARROW:
                    {
                        if(!(previous == UP))
                        {
                            current = DOWN;
                            pause = false;
                        }
                        else
                        {
                            key = ESC;
                        }
                        break;
                    }
                    case LEFT_ARROW:
                    {
                        if(!(previous == RIGHT))
                        {
                           current = LEFT;
                           pause = false;
                        }
                        else
                        {
                            key = ESC;
                        }
                        break;
                    }
                    case RIGHT_ARROW:
                    {
                        if(!(previous == LEFT))
                        {
                           current = RIGHT;
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

#define UP_ARROW      72
#define DOWN_ARROW    80
#define RIGHT_ARROW   77
#define LEFT_ARROW    75
#define ENTER_KEY     13

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
                case ENTER_KEY:
                {
                    pause = true;
                    current = PAUSE;
                    
                    break;
                }
                case UP_ARROW:
                {
                    if(!(previous == DOWN))
                    {
                        current = UP;
                        pause = false;
                    }
                    break;
                }
                case DOWN_ARROW:
                {
                    if(!(previous == UP))
                    {
                        current = DOWN;
                        pause = false;
                    }
                    break;
                }
                case LEFT_ARROW:
                {
                    if(!(previous == RIGHT))
                    {
                        current = LEFT;
                        pause = false;
                    }
                    break;
                }
                case RIGHT_ARROW:
                {
                    if(!(previous == LEFT))
                    {
                        current = RIGHT;
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
    direction start = direction::RIGHT;
    std::thread gameThread(Game,std::ref(obj), std::ref(start), std::ref(gameEnd));
    std::thread controlThread(Control, std::ref(start), std::ref(gameEnd));
    gameThread.join();
    controlThread.join();
    std::cout.flush();
}


bool Menu()
{
    std::string options[2] = {"   New Game   ", "     Exit     "};
    GUI menu(2, options, " GAME OVER",bg_emphasizing, RED_COLOR);
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
    CURSOR_SHOW;
    cls();

    return 0;
}
