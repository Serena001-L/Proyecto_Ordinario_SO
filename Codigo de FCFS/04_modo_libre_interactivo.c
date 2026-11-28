#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int rafaga;
    int espera;
} Proceso;

int main() {
    int n;
    printf("=== SIMULADOR FCFS: MODO LIBRE ===\n");
    printf("Ingresa el numero de procesos que quieres simular: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;
    getchar(); // Limpiar el salto de linea del buffer

    Proceso *p = (Proceso *)malloc(n * sizeof(Proceso));
    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Ingresa el tiempo de rafaga (CPU) para P%d (en ms): ", p[i].id);
        if (scanf("%d", &p[i].rafaga) != 1) return 1;
        getchar(); // Limpiar el buffer
    }

    float total_espera = 0;
    int tiempo_actual = 0;
    
    printf("\n--- INICIANDO SIMULACION INTERACTIVA ---\n");
    for (int i = 0; i < n; i++) {
        printf("\n[Presiona Enter para cargar a P%d a la CPU]", p[i].id);
        getchar();
        
        p[i].espera = tiempo_actual;
        printf("> [Tiempo %d ms] P%d obtiene la CPU.\n", tiempo_actual, p[i].id);
        printf("> Ejecutando P%d por %d ms...\n", p[i].id, p[i].rafaga);
        
        tiempo_actual += p[i].rafaga;
        total_espera += p[i].espera;
        
        printf("> [Tiempo %d ms] P%d termina. (Tiempo de espera: %d ms)\n", tiempo_actual, p[i].id, p[i].espera);
    }

    printf("\n--------------------------------------------------\n");
    printf("RESUMEN FINAL:\n");
    printf("Tiempo de espera promedio: %.2f ms\n", total_espera / n);
    printf("--------------------------------------------------\n");
    
    free(p);
    return 0;
}
