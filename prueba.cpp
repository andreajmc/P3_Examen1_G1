#include <ncurses.h>
#include <unistd.h>

int main() {

    initscr();
    int maxX = 0;
    int maxY = 0;
    getmaxyx(stdscr, maxY, maxX); 
    start_color();
     init_pair(1, COLOR_RED, COLOR_BLACK);
     attron(COLOR_PAIR(1));
     for (int j = 0; j < maxX; j++) {
         for (int i = 0; i < 3; i++) {
             attron(COLOR_PAIR(1));
             mvwaddch(stdscr,i, j, ACS_BOARD);
         }
     }
     getch();
     endwin();
}

