#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

#define BOARD_X 10
#define BOARD_Y 10
#define WIN_LENGTH 20
#define DIFFICULTY 120

typedef struct
{
    int x, y;
} Point;

Point snake[BOARD_X * BOARD_Y];
Point head = {4, 4};
Point apple;

int snake_length = 1;
int dx = 1, dy = 0;
int game = 1;
int exit_game = 0;

char *chares[4] = {" .", " O", " X", " 8"};
char *message = "";

void gen_food()
{
    int valid = 0;
    while (!valid)
    {
        apple.x = rand() % BOARD_X;
        apple.y = rand() % BOARD_Y;
        valid = 1;
        for (int i = 0; i < snake_length; i++)
        {
            if (snake[i].x == apple.x && snake[i].y == apple.y)
            {
                valid = 0;
                break;
            }
        }
    }
}

void draw_board()
{
    clear();
    mvprintw(0, 0, "Snake length: %d\n", snake_length);
    for (int y = 0; y < BOARD_Y; y++)
    {
        for (int x = 0; x < BOARD_X; x++)
        {
            int draw = 0;
            if (x == apple.x && y == apple.y)
                draw = 2;
            for (int i = 0; i < snake_length; i++)
            {
                if (snake[i].x == x && snake[i].y == y)
                {
                    draw = i == 0 ? 3 : 1;
                }
            }
            printw("%s", chares[draw]);
        }
        printw("\n");
    }
    refresh();
}

void def()
{
    message = "Lose";
    game = 0;
}

void won()
{
    message = "Win";
    game = 0;
}

void update_snake()
{
    head.x += dx;
    head.y += dy;

    if (head.x < 0 || head.x >= BOARD_X || head.y < 0 || head.y >= BOARD_Y)
    {
        def();
        return;
    }

    for (int i = 0; i < snake_length; i++)
    {
        if (snake[i].x == head.x && snake[i].y == head.y)
        {
            def();
            return;
        }
    }

    for (int i = snake_length; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }
    snake[0] = head;

    if (head.x == apple.x && head.y == apple.y)
    {
        snake_length++;
        if (snake_length >= WIN_LENGTH)
        {
            won();
        }
        gen_food();
    }
}

void process_input()
{
    int ch = getch();
    switch (ch)
    {
    case 'w':
        dx = 0;
        dy = -1;
        break;
    case 's':
        dx = 0;
        dy = 1;
        break;
    case 'a':
        dx = -1;
        dy = 0;
        break;
    case 'd':
        dx = 1;
        dy = 0;
        break;
    case 'x':
        exit_game = 1;
        break;
    }
}

void init_game()
{
    head.x = 4;
    head.y = 4;
    snake_length = 1;
    snake[0] = head;
    dx = 1;
    dy = 0;
    gen_food();
}

int main()
{
    srand(time(NULL));
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    timeout(DIFFICULTY);
    keypad(stdscr, TRUE);

    while (!exit_game)
    {
        clear();
        mvprintw(0, 0, "Press Enter to start, x to exit");
        int ch = getch();
        if (ch == '\n')
        {
            init_game();
            game = 1;
            while (game && !exit_game)
            {
                process_input();
                update_snake();
                draw_board();
                usleep(DIFFICULTY * 1000);
            }
            mvprintw(BOARD_Y + 2, 0, "%s\nPress Enter to play again", message);
            while ((ch = getch()) != '\n')
            {
            }
        }
        else if (ch == 'x')
        {
            break;
        }
    }

    endwin();
    return 0;
}
