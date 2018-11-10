#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "Item.h"
#include <iostream>
using std::string;
using namespace std;

Item*** crearTablero();
void lvlOne(char*, int, Item***, WINDOW*);
bool lvlTwo(char*, int, Item***, WINDOW*);
bool lvlThree(char*, int, Item***, WINDOW*);
void finale(bool, char*, WINDOW*);
void imprimir(Item*** x);
void createGame(WINDOW*);
void createBarrita(WINDOW*, int, int, int);
void moveBarrita(WINDOW*, int, int, int);
void createBall(WINDOW*, int, int, int);

int main() {
    int x = 0;
    int y = 0;
    int xMax = 0;
    int yMax = 0;
    char name[20] = {""};
    int vidas = 3;
    initscr();
    noecho();
    curs_set(FALSE);
    WINDOW* menuwin = newwin(8, 20, xMax / 2, yMax / 2); // height, width, starty, start
    box(menuwin, 0, 0); // windows, characters
    keypad(menuwin, true);
    start_color();
    string w = "¡Bienvenido! ";
    string n = "Ingresa tu nombre: ";
    printw(w.c_str());
    printw(n.c_str());
    echo();
    getstr(name); // Guardamos nombre.
    noecho();
    if (name != "") {
        clear();
        refresh();
        wrefresh(menuwin);
        clear();
        string choices[4] = {"NIVEL I", "NIVEL II", "NIVEL III", "Salir."};
        int choice = 0;
        int HL = 0;
        int S = 0;
        mvwprintw(menuwin, 1, 1, "   --- MENU ---");
        while(true) {
            for (int i = 0; i < 4; i++) {
                if (i == HL) {
                    wattron(menuwin, A_REVERSE);
                }
                mvwprintw(menuwin, i+2, 1, choices[i].c_str());
                wattroff(menuwin, A_REVERSE);
            }
            choice = wgetch(menuwin);
        // Pantallita del juego.
            switch(choice) {
            case KEY_UP:
                HL--;
                if (HL < 0) {
                    HL = 0;
                }
                break;
            case KEY_DOWN:
                HL++;
                if (HL > 3) {
                    HL == 3;
                }
                break;
            default:
                break;
        }
        if (choice == 10) {
            S = HL;
            break;
        }
    }
        // WINDOW* mainGame = newwin(10, 10, 0, 0);
        Item*** Board = crearTablero();
        bool win = false;
        switch(S) {
            case 0:
                while (!win) {
                    createGame(stdscr);
                    lvlOne(name, vidas, Board, stdscr);
                    clear();
                }
                //finale(win, name, stdscr);
                break;
            case 1:
                createGame(stdscr);
                win = lvlTwo(name, vidas, Board, stdscr);
                finale(win, name, stdscr);
                getch();
                break;
            case 2:
                createGame(stdscr);
                win = lvlThree(name, vidas, Board, stdscr);
                finale(win, name, stdscr);
                getch();
                break;
            case 3:
                break;
        }
    }
    refresh();
    wrefresh(menuwin);
    delwin(menuwin);
    endwin();
}

Item*** crearTablero() {
    Item*** Board = new Item**[10];
    for (int i = 0; i < 10; i++) {
        Board[i] = new Item*[10];
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            Board[i][j] = NULL;
        }
    }
    return Board;
}

void finale(bool win, char* name, WINDOW* game) {
    clear();
    string n_name(name);
    start_color();
     int row = 0;
     int col = 0;
     getmaxyx(game, row, col);
     if (win) { 
         init_pair(6, COLOR_GREEN, COLOR_BLACK);
         attron(COLOR_PAIR(6));
         string mesg = "          ¡Felicidades, " + n_name + "!";
         mvwprintw(game,row/2,(col-20)/2,mesg.c_str());
         attroff(COLOR_PAIR(6));
         mesg = "¡Has completado el nivel exitosamente!";
         mvwprintw(game,(row/2)+1,(col-20)/2,mesg.c_str());
    } else {
         init_pair(7, COLOR_RED, COLOR_BLACK);
         attron(COLOR_PAIR(7));
         string mesg = "¡Intentalo de nuevo, " + n_name + "!";
         mvwprintw(game,row/2,(col-20)/2,"%s",mesg.c_str());
         attroff(COLOR_PAIR(7));
     }
     refresh();
}

void createGame(WINDOW* game) {
     int maxX = 0;
     int maxY = 0;
     getmaxyx(stdscr, maxY, maxX);
     start_color();
     init_pair(1, COLOR_RED, COLOR_RED);
     init_pair(2, COLOR_CYAN, COLOR_CYAN);
     init_pair(3, COLOR_GREEN, COLOR_GREEN);
     init_pair(4, COLOR_MAGENTA, COLOR_MAGENTA);
     init_pair(8, COLOR_WHITE, COLOR_BLACK);
     init_pair(9, COLOR_BLACK, COLOR_BLACK);
     attron(COLOR_PAIR(1));
     for (int j = 0; j < maxX; j++) {
        for (int i = 0; i < 3; i++) {
             attron(COLOR_PAIR(1));
             mvwaddch(game,i, j, ACS_BOARD);
         }
     }
     attroff(COLOR_PAIR(1));
 
     for (int j = 0; j < maxX; j++) {
         for (int i = 3; i < 6; i++) {
              attron(COLOR_PAIR(2));
              mvwaddch(game,i, j, ACS_BOARD);
         }
     }
     attroff(COLOR_PAIR(2));
 
     for (int j = 0; j < maxX; j++) {
        for (int i = 6; i < 9; i++) {
              attron(COLOR_PAIR(3));
	      mvwaddch(game,i, j, ACS_BOARD);
          }
     }
     attroff(COLOR_PAIR(3));
 
     for (int j = 0; j < maxX; j++) {
        for (int i = 9; i < 12; i++) {
              attron(COLOR_PAIR(4));
              mvwaddch(game,i, j, ACS_BOARD);
          }
     }
     attroff(COLOR_PAIR(4));
     char lifes[10] = "Vidas:   ";
     //char score[10] = "Score:   ";
     lifes[7] = '3';
     for (int i = 0; i < maxX; i++) {
         if (i < 8) {
            attron(COLOR_PAIR(8)); 
            mvwaddch(game, maxY-1, i, lifes[i]);
            attroff(COLOR_PAIR(8));
         } else if (i < 30 && i > 15) {
            attron(COLOR_PAIR(8));
            //mvwaddch(game, maxY-1, i, score[i]);
            attroff(COLOR_PAIR(8));
         } else {
             attron(COLOR_PAIR(9));
             mvwaddch(game, maxY-1, i, ACS_BOARD);
             attroff(COLOR_PAIR(9));
         }
         //mvwaddch(game, i, maxY, A
     }
}

void lvlOne(char* name, int vidas, Item*** Board, WINDOW* game) {
    int maxX = 0;
    int maxY = 0;
    getmaxyx(game, maxY, maxX);
    int right = maxX/2-6;
    int left = maxX/2+6;
    while(1) {
    createBarrita(game,right, left, maxY);
    createBall(game, right, left, maxY);
        if (getch() == 'A' || getch() == 'a') {
            --right;
            moveBarrita(game,right,left, 1);
        } else if (getch() == 'D' || getch() == 'd') {
            ++left;
            moveBarrita(game,right,left, 2);
        }
    }
        refresh();
}

bool lvlTwo(char* name, int vidas, Item*** Board, WINDOW* game) {
    int maxX = 0;
    int maxY = 0;
    getmaxyx(game, maxY, maxX);
    int right = maxX/2-4;
    int left = maxX/2+4;
    createBarrita(game,right, left, maxY);
    createBall(game, right, left, maxY);
    getch();
    return false;
}

bool lvlThree(char* name, int vidas, Item*** Board, WINDOW* game) {
    int maxX = 0;
    int maxY = 0;
    getmaxyx(game, maxY, maxX);
    int right = maxX/2-2;
    int left = maxX/2+2;

    getmaxyx(game, maxY, maxX);
    createBarrita(game,right, left, maxY);
    createBall(game, right, left, maxY);
    getch();
    return true;
}

void createBarrita(WINDOW* game, int right, int left, int maxY) { 
     start_color();
     init_pair(5, COLOR_WHITE, COLOR_WHITE);
     move(maxY-2, 0);
     clrtoeol();
     for(int j = right; j < left; j++) {
        for (int i = maxY-2; i < maxY-1; i++) {
            attron(COLOR_PAIR(5));
            mvwaddch(game,i, j, ACS_BOARD);
      }
     }
      attroff(COLOR_PAIR(5));
      wrefresh(game);
}

void moveBarrita(WINDOW* game, int right, int left, int flag) {
    noecho();
    int maxX = 0;
    int maxY = 0;
    getmaxyx(game,maxY, maxX);
    if (flag == 1) {
        if (right < 0) {
            right = 0;
        }
        createBarrita(game, right-1, left-1, maxY);
    } else if (flag == 2) {
        if (left > maxX) {
            left = maxX;
        }
        createBarrita(game, right+1, left+1, maxY);
    }
    wrefresh(game);
}
    
void createBall(WINDOW* game, int right, int left, int maxY) {
    start_color();
    init_pair(10, COLOR_RED, COLOR_RED);
    attron(COLOR_PAIR(10));
    mvwaddch(game, maxY-3, right+3, ACS_BLOCK);
    mvwaddch(game, maxY-3, right+4, ACS_BLOCK);
    attroff(COLOR_PAIR(10));
}
