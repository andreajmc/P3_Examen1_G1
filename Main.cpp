#include <ncurses.h>
#include <unistd.h>
#include <string>i
using std::string;
// #include "Item.h"

Item*** crearTablero();
bool lvlOne(char*, int, Item***);
bool lvlTwo(char*, int, Item***);
bool lvlThree(char*, int, Item***);
void finale(bool, char*);

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
    WINDOW* menuwin = newwin(8, 20, xMax / 2, yMax / 2); // height, width, starty, start
    box(menuwin, 0, 0); // windows, characters
    keypad(menuwin, true);
    string w = "¡Bienvenido!";
    string n = "Ingresa tu nombre: ";
    printw(w.c_str());
    printw(n.c_str());
    getstr(name); // Guardamos nombre.
    if (name != "") {
        clear();
        refresh();
        wrefresh(menuwin);
        clear();
        string choices[4] = {"NIVEL I", "NIVEL II", "NIVEL III", "Salir."};
        int choice = 0;
        int HL = 0;
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
            break;
        }
    }
        WINDOW* mainGame = newwin(10, 10, 0, 0);
        Item*** Board = crearTablero();
        bool win = false;
        switch(HL) {
            case 0:
                win = lvlOne(name, vidas, Board); // Parametro --> Name & Vidas
                finale(win, name);
                break;
            case 1:
                win = lvlTwo(name, vidas, Board);
                finale(win, name);
                break;
            case 2:
                win = lvlThree(name, vidas, Board);
                finale(win, name);
                break;
            case 3:
                break;
        }
    }
    refresh();
    wrefresh(menuwin);
    delwin(menuwin);
    getch();
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

void finale(bool win, char* name) {
    clear();
    if (win) {
        
    } else {

    }
}

