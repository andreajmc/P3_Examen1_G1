#include <ncurses.h>
#include <unistd.h>
#include <string>
using std::string;
int main() {
    int x = 0;
    int y = 0;
    int xMax = 0;
    int yMax = 0;
    char name[20] = {""};
    initscr();
    echo();
    curs_set(FALSE);
    WINDOW* menuwin = newwin(10, 20, xMax / 2, yMax / 2); // height, width, starty, start
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
/*
    switch(HL) {
        case 0:
            lvlOne(); // Parametro --> Name & Vidas
            break;
        case 1:
            lvlTwo();
            break;
        case 2:
            lvlThree();
            break;
        case 3:
            break;
    } */
    }
    refresh();
    wrefresh(menuwin);
    delwin(menuwin);
    getch();
    endwin();
}

