#include <ncurses.h>
#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define WIN 21

#define KEY_UP_P1 'w'
#define KEY_DOWN_P1 's'
#define KEY_UP_P2 KEY_UP
#define KEY_DOWN_P2 KEY_DOWN

#define BORDER "#"

void draw(int coord_p1, int coord_p2, int b_x, int b_y, int score_p1, int score_p2) {
    for (int y = 0; y < HEIGHT + 2; y++) {
        printw(BORDER);
        for (int x = 0; x < WIDTH + 2; x++) {
            if (y == 0 || y == HEIGHT + 1)
                printw(BORDER);
            else if (x == 0 && y >= coord_p1 - 1 && y <= coord_p1 + 1)
                mvaddch(y, 1, '|');
            else if (x == WIDTH + 1 && y >= coord_p2 - 1 && y <= coord_p2 + 1)
                mvaddch(y, WIDTH + 2, '|');
            else if (x == b_x && y == b_y)
                mvaddch(y, x + 1, 'o');
            else
                printw(" ");
        }
        printw(BORDER);
        printw("\n");
    }
    printw("\n%40d | %d", score_p1, score_p2);
}

void move_players(int *coord_p1, int *coord_p2) {
    int key = getch();

    if (key == KEY_UP_P1 && *coord_p1 > 2) --(*coord_p1);
    else if (key == KEY_DOWN_P1 && *coord_p1 < HEIGHT - 1) ++(*coord_p1);
    
    if (key == KEY_UP_P2 && *coord_p2 > 2) --(*coord_p2);
    else if (key == KEY_DOWN_P2 && *coord_p2 < HEIGHT - 1) ++(*coord_p2);
}

int main() {
    int score_p1 = 0, score_p2 = 0;
    int coord_p1 = HEIGHT / 2, coord_p2 = HEIGHT / 2;
    int b_x = (WIDTH + 2) / 2, b_y = 5;
    int nb_x = 1, nb_y = 1;
    initscr();
    curs_set(0);
    keypad (stdscr, 1);
    halfdelay(1);

    while (score_p1 < WIN && score_p2 < WIN) {
        draw(coord_p1, coord_p2, b_x, b_y, score_p1, score_p2);
        //nodelay(stdscr, 1);
        move_players(&coord_p1, &coord_p2);
        //move_ball(coord_p1, coord_p2);
        if (b_y == 1) nb_y = 1;
        if (b_y == HEIGHT) nb_y = -1;

        if (b_x == 1) {
            if (b_y >= coord_p1 - 1 && b_y <= coord_p1 + 1) {
                nb_x = 1;
                b_x += nb_x;
            } else {
                score_p2++;
                b_x = (WIDTH + 2) / 2;
                b_y = (HEIGHT + 2) / 2;
            }
        } else if (b_x == WIDTH) {
            if (b_y >= coord_p2 - 1 && b_y <= coord_p2 + 1) {
                nb_x = -1;
                b_x += nb_x;
            } else {
                score_p1++;
                b_x = (WIDTH + 2) / 2;
                b_y = (HEIGHT + 2) / 2;
            }
        } else {
            b_x += nb_x;
            b_y += nb_y;
        }
        erase();
    }
    endwin();
    score_p1 == WIN ? printf("\nпоздравляем победителя! (1 игрок)\n")
                     : printf("\nпоздравляем победителя! (2 игрок)\n");
}
