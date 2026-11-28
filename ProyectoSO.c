#include <ncurses.h>
#include <string.h>
#include <stdbool.h>

int main() {
    // 1. Inicializar ncurses
    initscr();
    cbreak();             // Desactiva el buffer de línea (captura teclas al instante)
    noecho();             // No muestra en pantalla las teclas presionadas
    keypad(stdscr, TRUE); // HABILITA el uso de las flechas del teclado (KEY_UP, KEY_DOWN)
    curs_set(0);          // Oculta el cursor parpadeante

    // 2. Configurar colores (si la terminal los soporta)
    if (has_colors()) {
        start_color();
        // Par 1: Texto blanco con fondo azul para la opción seleccionada
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
    }

    // Definición de las opciones del menú
    const char* opciones[] = {
        "1.- FCFS"
        "2.- SJF"
        "3.- Round-Robin"
        "4.- SRTF"
        "5.- Salir"
    };
    int total_opciones = 5;
    int seleccionada = 0; // Índice de la opción actualmente resaltada
    int tecla;

    while (true) {
        // Obtener tamaño actual de la pantalla para centrar el menú
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        
        clear(); // Limpia la pantalla en cada ciclo para redibujar

        // Título del menú centrado
        const char* titulo = "---FUNDAMENTOS DE SISTEMAS OPERATIVOS--- ";
        mvprintw(max_y / 2 - 4, (max_x - strlen(titulo)) / 2, "%s", titulo);

        // 3. Dibujar las opciones del menú
        for (int i = 0; i < total_opciones; i++) {
            int fila = (max_y / 2) - (total_opciones / 2) + i;
            int col = (max_x - strlen(opciones[i])) / 2;

            if (i == seleccionada) {
                attron(COLOR_PAIR(1) | A_BOLD); // Activa el color azul y negrita si está seleccionada
                mvprintw(fila, col, "%s", opciones[i]);
                attroff(COLOR_PAIR(1) | A_BOLD); // Desactiva el atributo inmediatamente
            } else {
                mvprintw(fila, col, "%s", opciones[i]); // Opción normal sin resaltar
            }
        }

        // Instrucción en la parte inferior
        const char* inst = "Usa las flechas (Arriba/Abajo) y presiona Enter";
        mvprintw(max_y - 2, (max_x - strlen(inst)) / 2, "%s", inst);
        
        refresh(); // Volcar los cambios a la pantalla física

        // 4. Capturar la entrada del teclado
        tecla = getch();

        switch (tecla) {
            case KEY_UP:
                seleccionada--;
                if (seleccionada < 0) {
                    seleccionada = total_opciones - 1; // Efecto carrusel (vuelve al final)
                }
                break;
            case KEY_DOWN:
                seleccionada++;
                if (seleccionada >= total_opciones) {
                    seleccionada = 0; // Efecto carrusel (vuelve al inicio)
                }
                break;
            case 10: // Código ASCII para la tecla 'Enter' (a veces '\n')
                // Acción según la opción seleccionada
                if (seleccionada == 4) { // Opción "4. Salir"
                    goto salir_programa; // Sale del bucle principal
                } else {
                    // Mostrar un mensaje temporal de la opción elegida
                    clear();
                    char msg[100];
                    sprintf(msg, "Has seleccionado: %s", opciones[seleccionada]);
                    mvprintw(max_y / 2, (max_x - strlen(msg)) / 2, "%s", msg);
                    mvprintw(max_y / 2 + 2, (max_x - 30) / 2, "Presiona cualquier tecla...");
                    refresh();
                    getch(); // Espera una tecla antes de volver al menú
                }
                break;
            default:
                break;
        }
    }

salir_programa:
    // 5. Cerrar ncurses de forma segura
    endwin();
    return 0;
}


