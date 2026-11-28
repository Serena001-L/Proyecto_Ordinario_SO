#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int rafaga;
    int espera;
} Proceso;

int main() {
    Proceso p[] = {{1, 3, 0}, {2, 3, 0}, {3, 24, 0}};
    int n = 3;
    float total_espera = 0;
    int tiempo_actual = 0;

    printf("=== ESCENARIO 2: PROCESOS CORTOS PRIMERO (EFICIENTE) ===\n");
    printf("Orden de llegada: P1 (3ms), P2 (3ms), P3 (24ms)\n\n");

    for (int i = 0; i < n; i++) {
        printf("[Presiona Enter para cargar el proceso P%d a la CPU]", p[i].id);
        getchar();
        
        p[i].espera = tiempo_actual;
        printf("\n> [Tiempo %d ms] P%d obtiene la CPU.\n", tiempo_actual, p[i].id);
        printf("> Ejecutando P%d por %d ms...\n", p[i].id, p[i].rafaga);
        
        tiempo_actual += p[i].rafaga;
        total_espera += p[i].espera;
        
        printf("> [Tiempo %d ms] P%d termina su ejecucion.\n", tiempo_actual, p[i].id);
        printf("> Tiempo que P%d paso esperando: %d ms\n\n", p[i].id, p[i].espera);
    }

    printf("--------------------------------------------------\n");
    printf("RESUMEN FINAL:\n");
    printf("Tiempo de espera promedio: %.2f ms\n", total_espera / n);
    printf("--------------------------------------------------\n");

    return 0;
}
