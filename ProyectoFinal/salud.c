
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

// Función para limpiar la pantalla según el sistema operativo
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Función para mostrar una frase motivacional aleatoria
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
    printf("🌱 MOTIVACION DEL DIA:\n");
    printf("   \"%s\"\n", frases[indice]);
    printf("======================================================\n\n");
}

// Función para ejecutar el cronómetro y retornar el estado (1 si finalizó, 0 si se canceló)
int ejecutarCronometro(int segundosTotales) {
    int tiempoRestante = segundosTotales;
    
    printf("\n⏱️ ESTADO: En curso...\n");
    printf("Presiona Ctrl+C en tu teclado si deseas forzar la salida.\n\n");
    
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
    
    printf("\n\n🎉 ESTADO: Finalizado con exito.\n");
    return 1; // Retorna 1 indicando que llegó a cero por completo
}

int main() {
    float peso = 0.0;
    float alturaCm = 0.0;
    int opcionNivel = 0;
    int contadorRutinas = 0; // Contador de rutinas realizadas
    
    limpiarPantalla();
    printf("🌱 --- BIENVENIDO A FITLIFE APP --- 🌱\n");
    
    mostrarFraseMotivacional();
    
    // MÓDULO A: Validación estricta con rangos lógicos
    do {
        printf("Por favor, ingresa tu peso en kg (20 a 300): ");
        scanf("%f", &peso);
        
        printf("Por favor, ingresa tu altura en cm (50 a 250): ");
        scanf("%f", &alturaCm);
        
        if (peso < 20.0 || peso > 300.0 || alturaCm < 50.0 || alturaCm > 250.0) {
            printf("\n❌ Error: Valores ilógicos ingresados. Revisa los rangos permitidos (Peso: 20-300kg, Altura: 50-250cm).\n\n");
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
    
    limpiarPantalla();
    printf("======================================================\n");
    printf("        📊 TU PLAN PERSONALIZADO FITLIFE              \n");
    printf("======================================================\n");
    printf("Tu IMC calculado es: %.1f\n\n", imc);
    
    // MÓDULO B: Plan Nutricional e Hidratación Estándar
    printf("🥗 PLAN NUTRICIONAL SUGERIDO:\n");
    if (imc < 21.5) {
        printf("->💡 PLAN DE VOLUMEN (Enfoque: Subir masa muscular magra)\n");
        printf("   • Desayuno: Batido de leche entera, platano, avena y mantequilla de mani.\n");
        printf("   • Almuerzo: Carne de res o pollo, arroz blanco y pure de camote.\n");
        printf("   • Cena: Pescado o pollo con papas al horno y aguacate.\n");
    } else {
        printf("->💡 PLAN DE RECOMPOSICION (Enfoque: Bajar grasa y crear musculo)\n");
        printf("   • Desayuno: Tortilla de claras de huevo con espinacas y avena en agua.\n");
        printf("   • Almuerzo: Pechuga de pollo a la plancha, arroz integral y ensalada verde.\n");
        printf("   • Cena: Filete de pescado al horno con brocoli al vapor.\n");
    }
    printf("\n💧 RECOMENDACION DE HIDRATACION ESTANDAR:\n");
    printf("-> Beber 2 litros de agua al dia (Recomendacion obligatoria).\n");
    printf("------------------------------------------------------\n");
    
    int tiempoMinutos = 0;
    int cantidadEjercicios = 3;
    Ejercicio rutinaAsignada[3];
    float factorCalorias = 0.0;
    
    // MÓDULO C: Asignación de rutinas según nivel
    if (opcionNivel == 1) {
        tiempoMinutos = 15;
        factorCalorias = 5.0;
        printf("💪 TU RUTINA ASIGNADA: NIVEL PRINCIPIANTE (Tiempo: 15 min)\n\n");
        
        strcpy(rutinaAsignada[0].nombre, "Sentadillas libres");
        strcpy(rutinaAsignada[0].guia, "Baja la cadera como si te sentaras en una silla.");
        strcpy(rutinaAsignada[0].series, "3 series x 10 rep");
        
        strcpy(rutinaAsignada[1].nombre, "Flexiones con rodillas");
        strcpy(rutinaAsignada[1].guia, "Apoya rodillas en el suelo y baja el pecho de forma controlada.");
        strcpy(rutinaAsignada[1].series, "3 series x 8 rep");
        
        strcpy(rutinaAsignada[2].nombre, "Plancha Abdominal");
        strcpy(rutinaAsignada[2].guia, "Apoya antebrazos y mantén el cuerpo alineado como una tabla.");
        strcpy(rutinaAsignada[2].series, "3 series x 20 seg");
        
    } else if (opcionNivel == 2) {
        tiempoMinutos = 25;
        factorCalorias = 7.5;
        printf("💪 TU RUTINA ASIGNADA: NIVEL NORMAL (Tiempo: 25 min)\n\n");
        
        strcpy(rutinaAsignada[0].nombre, "Sentadillas con salto");
        strcpy(rutinaAsignada[0].guia, "Haz una sentadilla clásica y sube con un salto explosivo.");
        strcpy(rutinaAsignada[0].series, "4 series x 12 rep");
        
        strcpy(rutinaAsignada[1].nombre, "Flexiones de pecho estándar");
        strcpy(rutinaAsignada[1].guia, "Cuerpo estirado, baja el pecho rozando el suelo.");
        strcpy(rutinaAsignada[1].series, "4 series x 12 rep");
        
        strcpy(rutinaAsignada[2].nombre, "Zancadas / Lunges");
        strcpy(rutinaAsignada[2].guia, "Da un paso adelante bajando la rodilla trasera casi al suelo.");
        strcpy(rutinaAsignada[2].series, "4 series x 10 por pierna");
        
    } else {
        tiempoMinutos = 40;
        factorCalorias = 10.0;
        printf("💪 TU RUTINA ASIGNADA: NIVEL EXPERTO (Tiempo: 40 min)\n\n");
        
        strcpy(rutinaAsignada[0].nombre, "Burpees");
        strcpy(rutinaAsignada[0].guia, "Haz una flexión, encoge piernas rápido y termina con salto.");
        strcpy(rutinaAsignada[0].series, "4 series x 15 rep");
        
        strcpy(rutinaAsignada[1].nombre, "Flexiones diamante");
        strcpy(rutinaAsignada[1].guia, "Junta tus manos formando un diamante para enfocar tríceps.");
        strcpy(rutinaAsignada[1].series, "4 series x 12 rep");
        
        strcpy(rutinaAsignada[2].nombre, "Sentadillas búlgaras");
        strcpy(rutinaAsignada[2].guia, "Apoya un pie atrás en una silla y baja con una sola pierna.");
        strcpy(rutinaAsignada[2].series, "4 series x 12 por pierna");
    }
    
    for (int i = 0; i < cantidadEjercicios; i++) {
        printf("%d. %s (%s)\n", i + 1, rutinaAsignada[i].nombre, rutinaAsignada[i].series);
        printf("   Como hacer: %s\n\n", rutinaAsignada[i].guia);
    }
    printf("======================================================\n");
    
    // Módulo D: Cronómetro, calorías y contador
    char comenzar;
    printf("¿Deseas comenzar la rutina y arrancar el cronometro ahora? (s/n): ");
    scanf(" %c", &comenzar);
    
    if (comenzar == 's' || comenzar == 'S') {
        int tiempoSegundos = tiempoMinutos * 60;
        
        // Ejecuta el cronómetro y evalúa si finalizó por completo
        int estadoFinalizado = ejecutarCronometro(tiempoSegundos);
        
        if (estadoFinalizado == 1) {
            // Sumar 1 al contador de rutinas realizadas
            contadorRutinas++;
            
            // Cálculo de calorías (kcal/min * tiempo total en minutos)
            float totalCalorias = factorCalorias * tiempoMinutos;
            
            printf("\n--- REPORTE DE ENTRENAMIENTO ---\n");
            printf("🔥 Calorías quemadas: %.1f kcal\n", totalCalorias);
            printf("📈 Rutinas completadas registradas: %d\n", contadorRutinas);
        }
    } else {
        printf("\n¡Plan guardado! No olvides entrenar más tarde. ¡Hasta luego! 🌱\n");
    }
    
    return 0;
}

```
