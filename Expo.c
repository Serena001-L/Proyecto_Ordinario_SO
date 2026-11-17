/*******************************************************************************
 * UNIVERSIDAD DE LA SIERRA SUR (UNSIS)
 * LICENCIATURA EN INFORMATICA
 * MATERIA: SISTEMAS OPERATIVOS
 * 
 * ALGORITMO: Shortest Job First (SJF) No Apropiativo
 * DESCRIPCIÓN: Simulación avanzada y vistosa de la planificación de CPU 
 *              para 5 procesos con tiempos de llegada y ráfaga distintos.
 *******************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // Para simular retrasos de tiempo (efecto visual)

// Paleta de colores extendida y brillante mediante códigos de escape ANSI
#define RESET         "\033[0m"
#define NEGRILLA      "\033[1m"
#define ROJO_FUEGO    "\033[1;31m"
#define VERDE_MATRIZ  "\033[1;32m"https://www.onlinegdb.com/#
#define AMARILLO_AVIS "\033[1;33m"
#define AZUL_ELECT    "\033[1;34m"
#define MAGENTA_NEON  "\033[1;35m"
#define CIAN_CRYSTAL  "\033[1;36m"
#define BLANCO_PURA   "\033[1;37m"
#define FONDO_GRIS    "\033[44;1m" // Fondo azul para resaltar títulos

// Estructura Bloque de Control de Procesos (PCB simplificado)
struct Proceso {
    int id;                  // Identificador único (P1, P2, etc.)
    int tiempo_llegada;      // Arrival Time (AT)
    int tiempo_rafaga;       // Burst Time (BT)
    int tiempo_finalizacion; // Completion Time (CT)
    int tiempo_retorno;      // Turnaround Time (TAT)
    int tiempo_espera;       // Waiting Time (WT)
    bool completado;         // Estado del proceso en el ciclo de vida
};

// Función auxiliar para crear barras decorativas estilizadas
void imprimir_separador(char caracter, int longitud, char* color) {
    printf("%s", color);
    for(int i = 0; i < longitud; i++) {
        printf("%c", caracter);
    }
    printf("%s\n", RESET);
}

int main() {
    // Limpieza de pantalla inicial para que la presentación sea impecable
    printf("\033[H\033[2J");

    // Efecto visual de inicialización de la materia
    printf(CIAN_CRYSTAL "Iniciando Planificador CPU UNSIS-OS v2.6...\n" RESET);
    printf("[");
    for(int i = 0; i < 20; i++) {
        printf(VERDE_MATRIZ "█" RESET);
        fflush(stdout);
        usleep(40000); // Pequeña pausa de 40 milisegundos
    }
    printf("] " VERDE_MATRIZ "¡LISTO!\n\n" RESET);

    // Configuración del lote de 5 procesos con ráfagas y arribos asíncronos
    struct Proceso p[5] = {
        {1, 0, 7, 0, 0, 0, false},
        {2, 2, 4, 0, 0, 0, false},
        {3, 4, 1, 0, 0, 0, false},
        {4, 5, 4, 0, 0, 0, false},
        {5, 6, 2, 0, 0, 0, false}
    };

    int completados = 0;
    int tiempo_actual = 0;
    float suma_espera = 0, suma_retorno = 0;
    
    // Estructuras de datos dinámicas para registrar la traza del Diagrama de Gantt
    int orden_gantt[5];
    int tiempos_gantt[6]; 
    int pasos_gantt = 0;
    tiempos_gantt[0] = 0; // El tiempo arranca en el origen cero

    // CORE DEL ALGORITMO: Bucle de despacho basado en Shortest Job First
    while (completados < 5) {
        int indice_sjf = -1;
        int min_rafaga = 999999; // Centinela con valor infinito teórico

        // Fase de Selección (Filtra la cola de Listos en el 'tiempo_actual')
        for (int i = 0; i < 5; i++) {
            if (p[i].tiempo_llegada <= tiempo_actual && !p[i].completado) {
                // Condición primaria: Menor ráfaga de CPU
                if (p[i].tiempo_rafaga < min_rafaga) {
                    min_rafaga = p[i].tiempo_rafaga;
                    indice_sjf = i;
                }
                // Condición secundaria (Desempate): Criterio FCFS por orden de llegada
                else if (p[i].tiempo_rafaga == min_rafaga) {
                    if (p[i].tiempo_llegada < p[indice_sjf].tiempo_llegada) {
                        indice_sjf = i;
                    }
                }
            }
        }

        // Fase de Despacho y Ejecución (No Apropiativo)
        if (indice_sjf != -1) {
            // La CPU se bloquea por completo durante la ráfaga del proceso seleccionado
            tiempo_actual += p[indice_sjf].tiempo_rafaga;
            
            // Inyección de fórmulas métricas de Sistemas Operativos
            p[indice_sjf].tiempo_finalizacion = tiempo_actual;
            p[indice_sjf].tiempo_retorno = p[indice_sjf].tiempo_finalizacion - p[indice_sjf].tiempo_llegada;
            p[indice_sjf].tiempo_espera = p[indice_sjf].tiempo_retorno - p[indice_sjf].tiempo_rafaga;
            p[indice_sjf].completado = true;
            
            // Acumuladores para los promedios globales finales
            suma_espera += p[indice_sjf].tiempo_espera;
            suma_retorno += p[indice_sjf].tiempo_retorno;
            
            // Almacenamos el rastro histórico para pintar Gantt después
            orden_gantt[pasos_gantt] = p[indice_sjf].id;
            tiempos_gantt[pasos_gantt + 1] = tiempo_actual;
            pasos_gantt++;
            completados++;
        } else {
            // Si la cola de listos está vacía, la CPU entra en estado de Inactividad (Idle)
            tiempo_actual++;
            tiempos_gantt[0] = tiempo_actual; // Desplaza el origen si arranca en ocio
        }
    }

    // =========================================================================
    //                    RENDERIZADO DE LA INTERFAZ VISUAL
    // =========================================================================
    
    imprimir_separador('=', 74, MAGENTA_NEON);
    printf(FONDO_GRIS "          SISTEMAS OPERATIVOS: PLANIFICADOR DE PROCESOS SJF              " RESET "\n");
    imprimir_separador('=', 74, MAGENTA_NEON);
    printf("\n");

    // Impresión de la Tabla de Control con formato simétrico y limpio
    printf(AMARILLO_AVIS "+---------+------------+------------+--------------+------------+------------+\n" RESET);
    printf(AMARILLO_AVIS "| " BLANCO_PURA "Proceso" AMARILLO_AVIS " | " BLANCO_PURA "Llegada (AT)" AMARILLO_AVIS " | " BLANCO_PURA "Ráfaga (BT)" AMARILLO_AVIS " | " BLANCO_PURA "Terminado(CT)" AMARILLO_AVIS " | " BLANCO_PURA "Retorno(TAT)" AMARILLO_AVIS " | " BLANCO_PURA "Espera (WT)" AMARILLO_AVIS " |\n" RESET);
    printf(AMARILLO_AVIS "+---------+------------+------------+--------------+------------+------------+\n" RESET);
    
    for (int i = 0; i < 5; i++) {
        printf(AMARILLO_AVIS "|   " VERDE_MATRIZ "P%-5d" AMARILLO_AVIS "|      %-6d|      %-6d|       %-7d|      %-6d|      %-6d|\n" RESET, 
               p[i].id, p[i].tiempo_llegada, p[i].tiempo_rafaga, 
               p[i].tiempo_finalizacion, p[i].tiempo_retorno, p[i].tiempo_espera);
    }
    printf(AMARILLO_AVIS "+---------+------------+------------+--------------+------------+------------+\n\n" RESET);

    // Panel de Eficiencia de Rendimiento del Sistema
    printf(NEGRILLA ROJO_FUEGO "📊 MÉTRICAS DE RENDIMIENTO GLOBAL:\n" RESET);
    printf(AZUL_ELECT "  ↳ Tiempo Promedio de Espera  (μ WT) : " VERDE_MATRIZ "%.2f u.t.\n" RESET, suma_espera / 5);
    printf(AZUL_ELECT "  ↳ Tiempo Promedio de Retorno (μ TAT): " VERDE_MATRIZ "%.2f u.t.\n\n" RESET, suma_retorno / 5);

    // Renderizado Estructurado del Diagrama de Gantt
    printf(NEGRILLA CIAN_CRYSTAL "⏱️ DIAGRAMA DE GANTT (Línea de Tiempo del Procesador):\n\n" RESET);
    
    // Tapas superiores de los bloques de CPU
    printf("   ");
    for (int i = 0; i < pasos_gantt; i++) printf(CIAN_CRYSTAL "+-------" RESET);
    printf(CIAN_CRYSTAL "+\n" RESET);

    // Núcleos internos con el ID del proceso despachado
    printf("   ");
    for (int i = 0; i < pasos_gantt; i++) {
        printf(CIAN_CRYSTAL "|" RESET "  " ROJO_FUEGO "P%d" RESET "   ", orden_gantt[i]);
    }
    printf(CIAN_CRYSTAL "|\n" RESET);

    // Tapas inferiores de los bloques de CPU
    printf("   ");
    for (int i = 0; i < pasos_gantt; i++) printf(CIAN_CRYSTAL "+-------" RESET);
    printf(CIAN_CRYSTAL "+\n" RESET);

    // Escala del cronómetro o regla de tiempos de transiciones de estados
    printf("   ");
    for (int i = 0; i <= pasos_gantt; i++) {
        printf("%-8d", tiempos_gantt[i]);
    }
    printf("\n\n");
    
    imprimir_separador('=', 74, MAGENTA_NEON);
    printf(VERDE_MATRIZ "Simulación finalizada con éxito. Código de salida 0.\n" RESET);
    imprimir_separador('=', 74, MAGENTA_NEON);

    return 0;
}
