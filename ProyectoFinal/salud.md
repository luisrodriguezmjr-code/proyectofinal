
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
    printf("🌱 MOTIVACION DEL DIA:\n");
    printf("   \"%s\"\n", frases[indice]);
    printf("======================================================\n\n");
}

// --- MÓDULO D: FUNCIONES DE CRONÓMETRO Y CALORÍAS ---

// 1. Configurar tiempo manual para rutina libre (máximo 5 minutos y valores positivos)
int configurarTiempoManual() {
    int minutos = 0;
    do {
        printf("\n⏱️ CONFIGURACION DE RUTINA LIBRE:\n");
        printf("Ingresa los minutos que deseas entrenar (Debe ser mayor a 0 y maximo 5 min): ");
        scanf("%d", &minutos);
        
        if (minutos <= 0 || minutos > 5) {
            printf("\n❌ Error: El tiempo debe ser un valor positivo y no puede pasar de 5 minutos. Intenta de nuevo.\n");
        }
    } while (minutos <= 0 || minutos > 5);
    
    return minutos; // Retorna los minutos configurados
}

// 2. Iniciar rutina con cronómetro (diferencia "En curso" y "Finalizado", formato MM:SS)
int inciarRutinaCronometro(int segundosTotales) {
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
    return 1; // Retorna 1 si llegó a cero por completo
}

// 3. Calcular calorías basado en el factor del nivel y los minutos
float calcularCalorias(int minutos, float factorCalorias) {
    return minutos * factorCalorias;
}

// --- PROGRAMA PRINCIPAL ---
int main() {
    float peso = 0.0;
    float alturaCm = 0.0;
    int opcionNivel = 0;
    int contadorRutinas = 0; // Contador automático de rutinas realizadas
    
    limpiarPantalla();
    printf("🌱 --- BIENVENIDO A FITLIFE APP --- 🌱\n");
    mostrarFraseMotivacional();
    
    // Módulo A: Gestión de Datos Corporales
    do {
        printf("Por favor, ingresa tu peso en kg (20 a 300): ");
        scanf("%f", &peso);
        
        printf("Por favor, ingresa tu altura en cm (50 a 250): ");
        scanf("%f", &alturaCm);
        
        if (peso < 20.0 || peso > 300.0 || alturaCm < 50.0 || alturaCm > 250.0) {
            printf("\n❌ Error: Valores ilógicos ingresados. Revisa los rangos permitidos.\n\n");
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
    printf("        📊 TU PLAN PERSONALIZADO FITLIFE              \n");
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
    printf("\n💧 RECOMENDACION DE HIDRATACION ESTANDAR:\n");
    printf("-> Beber 2 litros de agua al día.\n");
    printf("------------------------------------------------------\n");
    
    // Módulo C: Entrenamiento Personalizado (Rutina predefinida)
    int tiempoMinutosRutina = 0;
    int cantidadEjercicios = 3;
    Ejercicio rutinaAsignada[3];
    
    if (opcionNivel == 1) {
        tiempoMinutosRutina = 15;
        printf("💪 RUTINA ASIGNADA: NIVEL PRINCIPIANTE (15 min)\n\n");
        strcpy(rutinaAsignada[0].nombre, "Sentadillas libres"); 
        strcpy(rutinaAsignada[0].guia, "Baja la cadera como si te sentaras en una silla."); 
        strcpy(rutinaAsignada[0].series, "3 series x 10 rep");
        
        strcpy(rutinaAsignada[1].nombre, "Flexiones con rodillas"); 
        strcpy(rutinaAsignada[1].guia, "Apoya rodillas en el suelo y baja el pecho."); 
        strcpy(rutinaAsignada[1].series, "3 series x 8 rep");
        
        strcpy(rutinaAsignada[2].nombre, "Plancha Abdominal"); 
        strcpy(rutinaAsignada[2].guia, "Apoya antebrazos y mantén el cuerpo alineado."); 
        strcpy(rutinaAsignada[2].series, "3 series x 20 seg");
    } else if (opcionNivel == 2) {
        tiempoMinutosRutina = 25;
        printf("💪 RUTINA ASIGNADA: NIVEL NORMAL (25 min)\n\n");
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
        printf("💪 RUTINA ASIGNADA: NIVEL EXPERTO (40 min)\n\n");
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
    
    for (int i = 0; i < cantidadEjercicios; i++) {
        printf("%d. %s (%s)\n", i + 1, rutinaAsignada[i].nombre, rutinaAsignada[i].series);
        printf("   Guía: %s\n\n", rutinaAsignada[i].guia);
    }
    printf("======================================================\n");
    
    // Módulo D: Elección entre Rutina Predefinida o Rutina Libre
    int tipoEntrenamiento = 0;
    printf("¿Cómo deseas entrenar hoy?\n");
    printf("1. Usar la rutina predefinida asignada\n");
    printf("2. Configurar una rutina libre (Personalizada, máx. 5 min)\n");
    printf("Elige una opción (1-2): ");
    scanf("%d", &tipoEntrenamiento);
    
    int minutosFinales = 0;
    if (tipoEntrenamiento == 1) {
        minutosFinales = tiempoMinutosRutina;
    } else {
        minutosFinales = configurarTiempoManual();
    }
    
    char comenzar;
    printf("\n¿Deseas iniciar el cronómetro ahora? (s/n): ");
    scanf(" %c", &comenzar);
    
    if (comenzar == 's' || comenzar == 'S') {
        int segundosTotales = minutosFinales * 60;
        
        int estadoFinalizado = inciarRutinaCronometro(segundosTotales);
        
        if (estadoFinalizado == 1) {
            contadorRutinas++;
            float totalCalorias = calcularCalorias(minutosFinales, factorCalorias);
            
            printf("\n--- REPORTE DE ENTRENAMIENTO ---\n");
            printf("🔥 Calorías quemadas: %.1f kcal\n", totalCalorias);
            printf("📈 Rutinas completadas registradas: %d\n", contadorRutinas);
        }
    } else {
        printf("\n¡Plan guardado! Entrena cuando estés listo. ¡Hasta luego! 🌱\n");
    }
    
    return 0;
}

```
