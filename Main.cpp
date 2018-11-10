#include <ncurses.h>
#include <unistd.h>
#include <string>
#include "Item.h"
using std::string;
#include <cstring>
#include <iostream>
using std::cout;
// #include "Item.h"

Item*** crearTablero();
bool lvlOne(char*, int, Item***);
bool lvlTwo(char*, int, Item***);
bool lvlThree(char*, int, Item***);
void finale(bool, char*);
void createGame(WINDOW*);
int main() {
    int x = 0;
    int y = 0;
    int xMax = 0;
    int yMax = 0;
    char name[20] = {""};
    int vidas = 3;
    initscr();
    echo();
    curs_set(FALSE);
    WINDOW* menuwin = newwin(8, 20, xMax / 2, yMax / 2);
    box(menuwin, 0, 0);
    getmaxyx(stdscr, yMax, xMax);
    //WINDOW* menuwin = newwin(8, 20, xMax / 2, yMax / 2); // height, width, starty, start
    box(stdscr, 0, 0); // windows, characters
    keypad(stdscr, true);
    string w = "¡Bienvenido!";
    string n = "Ingresa tu nombre: ";
    printw(w.c_str());
    printw(n.c_str());
    getstr(name); // Guardamos nombre.
    if (name != "") {
        refresh();
        wrefresh(menuwin);
        clear();
        string choices[4] = {"NIVEL I", "NIVEL II", "NIVEL III", "Salir."};
        int choice = 0;
        int HL = 0;
        int Selected = 0;
        mvwprintw(menuwin, 1, 1, "   --- MENU ---");
        while(true) {
            for (int i = 0; i < 4; i++) {
                if (i == HL) {
                    attron(A_REVERSE);
                }
                mvwprintw(menuwin,i+2, 1, choices[i].c_str());
                wattroff(menuwin,A_REVERSE);
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
            Selected = HL;
            clear();
            break;
        }
        //box(mainGame, 0, 0);
        Item*** Board = crearTablero();
        bool win = false;
        delwin(menuwin);
        switch(Selected) {
            case 0:
                createGame(stdscr);
                refresh();
                //refresh(menuwin);
                getch();
                //win = lvlOne(name, vidas, Board); // Parametro --> Name & Vidas
                // finale(win, name);
                break;
            case 1: {
                // win = lvlTwo(name, vidas, Board);
                // finale(win, name);
                break;
            case 2:
                // win = lvlThree(name, vidas, Board);
                // finale(win, name);
                break;
            case 3:
                break;
        }
    }
    }
    refresh();
    //wrefresh(menuwin);
    //delwin(menuwin);
    getch();
    // endwin();
    }
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
    /*clear();
    string n_name(name);
    int row = 0;
    int col = 0;
    getmaxyx(stdscr, row, col);
    if (win) { 
        string mesg = "¡Felicidades, " + n_name + "!";
        mvprintw(game, row/2,(col-strlen(mesg))/2,"%s",mesg);
        mesg = "¡Has completado el nivel exitosamente!";
        mvprintw(game, (row/2)+1,(col-strlen(mesg))/2,"%s",mesg);
    } else {
        string mesg = "¡Intentalo de nuevo, " + n_name + "!";
        mvprintw(game, row/2,(col-strlen(mesg))/2,"%s",mesg);
    }
    refresh();*/
}

void createGame(WINDOW* game) { 
    int maxX = 0;
    int maxY = 0;
    getmaxyx(stdscr, maxY, maxX);
    start_color();
    init_pair(1, COLOR_RED, COLOR_WHITE);
    init_pair(2, COLOR_CYAN, COLOR_WHITE);
    init_pair(3, COLOR_GREEN, COLOR_WHITE);
    init_pair(4, COLOR_MAGENTA, COLOR_WHITE);
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
}

    //attroff(COLOR_PAIR(1));
