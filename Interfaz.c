
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OPCIONES 6

void mostrar_menu() {
    char *opciones[NUM_OPCIONES] = {
        "Concurrencia",
        "Planificadores",
        "Gestion de archivos",
        "Gestion de memoria",
        "Dispositivos E/S",
        "Salir"
    };

    int seleccion = 0;
    int tecla;
    int alto, ancho;
    int inicio_y, inicio_x;

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
        init_pair(3, COLOR_CYAN, COLOR_BLACK);
    }

    getmaxyx(stdscr, alto, ancho);

    WINDOW *menu = newwin(16, 50,
                         (alto - 16) / 2,
                         (ancho - 50) / 2);

    box(menu, 0, 0);

    while (1) {
        werase(menu);
        box(menu, 0, 0);

        wattron(menu, COLOR_PAIR(3) | A_BOLD);
        mvwprintw(menu, 2, 13, "SISTEMA OPERATIVO");
        wattroff(menu, COLOR_PAIR(3) | A_BOLD);

        mvwprintw(menu, 3, 10, "Menu principal");
        mvwhline(menu, 4, 2, ACS_HLINE, 46);

        for (int i = 0; i < NUM_OPCIONES; i++) {
            if (i == seleccion) {
                wattron(menu, COLOR_PAIR(1) | A_BOLD);
                mvwprintw(menu, 6 + i, 10, "> %-25s",
                          opciones[i]);
                wattroff(menu, COLOR_PAIR(1) | A_BOLD);
            } else {
                wattron(menu, COLOR_PAIR(2));
                mvwprintw(menu, 6 + i, 10, "  %-25s",
                          opciones[i]);
                wattroff(menu, COLOR_PAIR(2));
            }
        }

        mvwprintw(menu, 14, 5, "Use UP/DOWN y ENTER");
        wrefresh(menu);

        tecla = wgetch(menu);

        switch (tecla) {
            case KEY_UP:
                seleccion--;
                if (seleccion < 0)
                    seleccion = NUM_OPCIONES - 1;
                break;

            case KEY_DOWN:
                seleccion++;
                if (seleccion >= NUM_OPCIONES)
                    seleccion = 0;
                break;

            case 10:
            case KEY_ENTER:
                if (seleccion == NUM_OPCIONES - 1) {
                    delwin(menu);
                    endwin();
                    return;
                }

                werase(menu);
                box(menu, 0, 0);

                mvwprintw(menu, 6, 10,
                          "Seleccionaste:");
                mvwprintw(menu, 8, 10, "%s",
                          opciones[seleccion]);
                mvwprintw(menu, 11, 8,
                          "Presiona una tecla...");
                wrefresh(menu);

                wgetch(menu);
                break;
        }
    }
}

int main() {
    mostrar_menu();
    return 0;
}
