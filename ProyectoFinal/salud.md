
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
#endif

// Estructura para almacenar los datos de cada ejercicio
typedef struct {
    char nombre[50];
    char guia[100];
    char series[30];
} Ejercicio;

// --- FUNCIONES AUXILIARES ---

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void mostrarFraseMotivacional() {
    char frases[4][100] = {
        "¡El unico entrenamiento malo es aquel que no ocurrio!",
        "Tu cuerpo puede soportar casi cualquier cosa. ¡Convence a tu mente!",
        "No tienes que ser extremo, solo consistente.",
        "Pequenos progresos diarios dan grandes resultados."
    };
    
    srand(time(NULL));
    int indice = rand() % 4;
    
    printf("\n======================================================\n");
    printf(" MOTIVACION DEL DIA:\n");
    printf("   \"%s\"\n", frases[indice]);
    printf("======================================================\n\n");
}

// Configurar tiempo manual para rutina libre (máximo 30 minutos)
int configurarTiempoManual() {
    int minutos = 0;
    do {
        printf(" CONFIGURACION DE CRONOMETRO LIBRE:\n");
        printf("Ingresa los minutos que deseas cronometrar (Maximo 30 min): ");
        scanf("%d", &minutos);
        
        if (minutos <= 0 || minutos > 30) {
            printf("\n Error: El tiempo debe ser mayor a 0 y no pasar de 30 minutos.\n");
        }
    } while (minutos <= 0 || minutos > 30);
    
    return minutos;
}

// Cronómetro libre que ahora sí suma 1 al completarse y calcula sus calorías
int iniciarCronometroLibre(int segundosTotales) {
    int tiempoRestante = segundosTotales;
    
    printf("CRONOMETRO LIBRE EN CURSO...\n");
    printf("Presiona Ctrl+C en tu teclado si deseas salir antes.\n\n");
    
    while (tiempoRestante > 0) {
        int minutos = tiempoRestante / 60;
        int segundos = tiempoRestante % 60;
        
        printf("\rTiempo restante: %02d:%02d ", minutos, segundos);
        fflush(stdout);
        
        #ifdef _WIN32
            Sleep(1000);
        #else
            struct timespec ts = {1, 0};
            nanosleep(&ts, NULL);
        #endif
        
        tiempoRestante--;
    }
    
    printf("¡El tiempo del cronometro libre ha terminado con exito!\n");
    return 1; // Retorna 1 si llegó a cero por completo
}

// Cronómetro para rutina guiada (ejercicio por ejercicio)
int iniciarCronometroEjercicio(int segundosTotales, const char* nombreEjercicio) {
    int tiempoRestante = segundosTotales;
    
    printf(" EJERCICIO EN CURSO: %s\n", nombreEjercicio);
    printf("Presiona Ctrl+C en tu teclado si deseas forzar la salida.\n\n");
    
    while (tiempoRestante > 0) {
        int minutos = tiempoRestante / 60;
        int segundos = tiempoRestante % 60;
        
        printf("\rTiempo restante del ejercicio: %02d:%02d ", minutos, segundos);
        fflush(stdout);
        
        #ifdef _WIN32
            Sleep(1000);
        #else
            struct timespec ts = {1, 0};
            nanosleep(&ts, NULL);
        #endif
        
        tiempoRestante--;
    }
    
    printf(" ¡Ejercicio finalizado con exito!\n");
    return 1;
}

// Calcular calorías basado en el factor del nivel y los minutos
float calcularCalorias(int minutos, float factorCalorias) {
    return minutos * factorCalorias;
}

// --- PROGRAMA PRINCIPAL ---
int main() {
    float peso = 0.0;
    float alturaCm = 0.0;
    int opcionNivel = 0;
    int contadorRutinas = 0;
    int opcionMenuPrincipal = 0;
    
    limpiarPantalla();
    printf("--- BIENVENIDO A FITLIFE APP --- \n");
    mostrarFraseMotivacional();
    
    // Módulo A: Gestión de Datos Corporales
    do {
        printf("Por favor, ingresa tu peso en kg (20 a 300): ");
        scanf("%f", &peso);
        
        printf("Por favor, ingresa tu altura en cm (50 a 250): ");
        scanf("%f", &alturaCm);
        
        if (peso < 20.0 || peso > 300.0 || alturaCm < 50.0 || alturaCm > 250.0) {
            printf(" Error: Valores ilógicos ingresados. Revisa los rangos permitidos.\n\n");
        }
    } while (peso < 20.0 || peso > 300.0 || alturaCm < 50.0 || alturaCm > 250.0);
    
    float alturaM = alturaCm / 100.0;
    float imc = peso / (alturaM * alturaM);
    
    printf("\nSELECCIONA TU NIVEL DE DIFICULTAD:\n");
    printf("1. Principiante (Factor: 5.0 kcal/min)\n");
    printf("2. Normal (Factor: 7.5 kcal/min)\n");
    printf("3. Experto (Factor: 10.0 kcal/min)\n");
    
    do {
        printf("Elige una opcion (1-3): ");
        scanf("%d", &opcionNivel);
    } while (opcionNivel < 1 || opcionNivel > 3);
    
    float factorCalorias = 0.0;
    if (opcionNivel == 1) factorCalorias = 5.0;
    else if (opcionNivel == 2) factorCalorias = 7.5;
    else factorCalorias = 10.0;
    
    limpiarPantalla();
    printf("======================================================\n");
    printf("         TU PLAN PERSONALIZADO FITLIFE              \n");
    printf("======================================================\n");
    printf("Tu IMC calculado es: %.1f\n\n", imc);
    
    // Módulo B: Nutrición Predictiva e Hidratación
    printf("🥗 PLAN NUTRICIONAL SUGERIDO:\n");
    if (imc < 21.5) {
        printf("->💡 PLAN DE VOLUMEN (Enfoque: Subir masa muscular magra)\n");
        printf("   • Desayuno: Batido de leche entera, plátano, avena y mantequilla de maní.\n");
        printf("   • Almuerzo: Carne de res o pollo, arroz blanco y puré de camote.\n");
        printf("   • Cena: Pescado o pollo con papas al horno y aguacate.\n");
    } else {
        printf("->💡 PLAN DE RECOMPOSICION (Enfoque: Bajar grasa y crear músculo)\n");
        printf("   • Desayuno: Tortilla de claras de huevo con espinacas y avena en agua.\n");
        printf("   • Almuerzo: Pechuga de pollo a la plancha, arroz integral y ensalada verde.\n");
        printf("   • Cena: Filete de pescado al horno con brócoli al vapor.\n");
    }
    printf(" RECOMENDACION DE HIDRATACION ESTANDAR:\n");
    printf("-> Beber 2 litros de agua al día.\n");
    printf("------------------------------------------------------\n");
    
    // Definición de rutinas usando Arrays de Estructuras por nivel
    int cantidadEjercicios = 3;
    Ejercicio rutinaAsignada[3];
    int tiempoMinutosRutina = 0;

    if (opcionNivel == 1) {
        tiempoMinutosRutina = 15;
        strcpy(rutinaAsignada[0].nombre, "Sentadillas libres"); 
        strcpy(rutinaAsignada[0].guia, "Baja la cadera como si te sentaras en una silla."); 
        strcpy(rutinaAsignada[0].series, "3 series x 10 rep");
        
        strcpy(rutinaAsignada[1].nombre, "Flexiones con rodillas"); 
        strcpy(rutinaAsignada[1].guia, "Apoya rodillas en el suelo y baja el pecho."); 
        strcpy(rutinaAsignada[1].series, "3 series x 8 rep");
        
        strcpy(rutinaAsignada[2].nombre, "Plancha Abdominal"); 
        strcpy(rutinaAsignada[2].guia, "Apoya antebrazos y manten el cuerpo alineado."); 
        strcpy(rutinaAsignada[2].series, "3 series x 20 seg");
    } else if (opcionNivel == 2) {
        tiempoMinutosRutina = 25;
        strcpy(rutinaAsignada[0].nombre, "Sentadillas con salto"); 
        strcpy(rutinaAsignada[0].guia, "Haz una sentadilla clásica y salta."); 
        strcpy(rutinaAsignada[0].series, "4 series x 12 rep");
        
        strcpy(rutinaAsignada[1].nombre, "Flexiones de pecho"); 
        strcpy(rutinaAsignada[1].guia, "Cuerpo estirado, baja el pecho al suelo."); 
        strcpy(rutinaAsignada[1].series, "4 series x 12 rep");
        
        strcpy(rutinaAsignada[2].nombre, "Zancadas / Lunges"); 
        strcpy(rutinaAsignada[2].guia, "Da un paso adelante bajando la rodilla."); 
        strcpy(rutinaAsignada[2].series, "4 series x 10 por pierna");
    } else {
        tiempoMinutosRutina = 40;
        strcpy(rutinaAsignada[0].nombre, "Burpees"); 
        strcpy(rutinaAsignada[0].guia, "Flexión, encoge piernas y salto explosivo."); 
        strcpy(rutinaAsignada[0].series, "4 series x 15 rep");
        
        strcpy(rutinaAsignada[1].nombre, "Flexiones diamante"); 
        strcpy(rutinaAsignada[1].guia, "Manos juntas para tríceps."); 
        strcpy(rutinaAsignada[1].series, "4 series x 12 rep");
        
        strcpy(rutinaAsignada[2].nombre, "Sentadillas bulgaras"); 
        strcpy(rutinaAsignada[2].guia, "Un pie atras en una silla y baja."); 
        strcpy(rutinaAsignada[2].series, "4 series x 12 por pierna");
    }

    // Bucle principal para mantenerse en la aplicación hasta que se decida salir
    do {
        printf("\n======================================================\n");
        printf(" RUTINA ASIGNADA PARA TU NIVEL (%d min totales)\n\n", tiempoMinutosRutina);
        for (int i = 0; i < cantidadEjercicios; i++) {
            printf("%d. %s (%s)\n", i + 1, rutinaAsignada[i].nombre, rutinaAsignada[i].series);
            printf("   Guia: %s\n\n", rutinaAsignada[i].guia);
        }
        printf("======================================================\n");
        
        int tipoEntrenamiento = 0;
        printf("¿Cómo deseas entrenar hoy?\n");
        printf("1. Usar la rutina predefinida asignada\n");
        printf("2. Usar cronómetro libre independiente (Máx. 30 min)\n");
        printf("Elige una opción (1-2): ");
        scanf("%d", &tipoEntrenamiento);
        
        if (tipoEntrenamiento == 1) {
            char comenzar;
            printf("\n¿Deseas iniciar la rutina predefinida ahora? (s/n): ");
            scanf(" %c", &comenzar);
            
            if (comenzar == 's' || comenzar == 'S') {
                int minutosPorEjercicio = tiempoMinutosRutina / cantidadEjercicios;
                if (minutosPorEjercicio < 1) minutosPorEjercicio = 1; 
                int segundosPorEjercicio = minutosPorEjercicio * 60;
                
                int rutinaCompletaExitosa = 1;

                for (int i = 0; i < cantidadEjercicios; i++) {
                    printf("\n--------------------------------------------------\n");
                    printf("Iniciando ejercicio %d de %d:\n", i + 1, cantidadEjercicios);
                    printf("• %s (%s)\n", rutinaAsignada[i].nombre, rutinaAsignada[i].series);
                    printf("• Guia: %s\n", rutinaAsignada[i].guia);
                    
                    int resultado = iniciarCronometroEjercicio(segundosPorEjercicio, rutinaAsignada[i].nombre);
                    
                    if (resultado != 1) {
                        rutinaCompletaExitosa = 0;
                        break;
                    }
                }
                
                if (rutinaCompletaExitosa == 1) {
                    contadorRutinas++;
                    float totalCalorias = calcularCalorias(tiempoMinutosRutina, factorCalorias);
                    
                    printf("--- REPORTE DE ENTRENAMIENTO ---\n");
                    printf(" Calorias quemadas: %.1f kcal\n", totalCalorias);
                    printf(" Rutinas completadas registradas en total: %d\n", contadorRutinas);
                }
            } else {
                printf("\n¡Plan guardado para luego!\n");
            }
        } else {
            // Opción 2: Cronómetro libre independiente que también suma al contador y calcula calorías
            int minutosLibres = configurarTiempoManual();
            char comenzarLibre;
            printf("\n¿Deseas iniciar el cronómetro libre ahora? (s/n): ");
            scanf(" %c", &comenzarLibre);
            
            if (comenzarLibre == 's' || comenzarLibre == 'S') {
                int estadoLibre = iniciarCronometroLibre(minutosLibres * 60);
                
                if (estadoLibre == 1) {
                    contadorRutinas++;
                    float totalCaloriasLibre = calcularCalorias(minutosLibres, factorCalorias);
                    
                    printf("\n--- REPORTE DE CRONOMETRO LIBRE ---\n");
                    printf(" Calorias quemadas: %.1f kcal\n", totalCaloriasLibre);
                    printf(" Rutinas completadas registradas en total: %d\n", contadorRutinas);
                }
            } else {
                printf("\nCronómetro libre cancelado.\n");
            }
        }
        
        // Menú de control para continuar o salir
        printf("\n======================================================\n");
        printf("¿Qué deseas hacer ahora?\n");
        printf("1. Realizar otra actividad (Continuar en la app)\n");
        printf("2. Salir del programa\n");
        printf("Elige una opción (1-2): ");
        scanf("%d", &opcionMenuPrincipal);
        
    } while (opcionMenuPrincipal == 1);
    
    // Reporte final al salir del programa frente al objetivo base (mínimo 1 rutina completada)
    printf("\n======================================================\n");
    printf(" REPORTE FINAL DE LA JORNADA:\n");
    printf("• Rutinas completadas: %d\n", contadorRutinas);
    if (contadorRutinas >= 1) {
        printf(" ¡Objetivo cumplido! Has completado al menos una sesión de entrenamiento hoy. ¡Excelente trabajo, hatsu!\n");
    } else {
        printf(" No registraste ninguna sesión completa de entrenamiento hoy. ¡Ánimo para la próxima, hatsu!\n");
    }
    printf("======================================================\n");
    printf("¡Gracias por usar FitLife App! ¡Hasta luego!\n");
    
    return 0;
}
```
