/*
Autor: Andres Alvarez San Martin
Fecha de creacion: 07/06/2023
Programa que cada vez que se habre la terminal por primera vez detecta si este(el programa) se esta ejecutando y si lo esta para de ejecutarse
y si no lo esta ve cuanto tiempo lleva el ordenador encendido y si es mas de dos dias abre un script de automator para ofrecer el reiniciado
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/file.h>

#define LOCK_FILE_PATH "/Desktop/cosas utiles/scripts_zshr/mi_programa.lock" // Ruta absoluta del archivo lock 
#define CLAVE_LOCK 0001 // Clave de el bloqueo exclusivo del archivo lock
const char *command = "uptime | awk -F'( |,|:)+' '{if ($5 == \"day\" || $5 == \"days\") print $4,$6,$7; else if ($5 == \"min\" || $5 == \"mins\")print $4; else print $4,$5 }'";

//** Prototipado de las funciones **//

int is_program_running();
int totalhoras(int hours, int minutes, int days);

int main()
{
    if (is_program_running())
    {
        printf("El programa ya está en ejecución.\n");
        return 0;
    }
    printf("Programa ejecutandose");

    double days, hours, minutes;
    char input[100];

    while (1)
    {
        float totalHours = 0;

        // Aqui llamamos al conmando uptime y lo guardamos en un pipe
        FILE *pipe = popen(command, "r");
        if (!pipe) // Si no se pudo ejecutar el comando
        {
            printf("Error al ejecutar el comando.\n");
            return 1;
        }

        fgets(input, sizeof(input), pipe);                     // Asignamos a input el valor que devuelve el comando
        pclose(pipe);                                          // Cerramos el file pipe del comando
        sscanf(input, "%lf %lf %lf", &days, &hours, &minutes); // Guarda los valores del input en las variables

        totalHours = totalhoras(hours, minutes, days);

        if (totalHours >= 48)
        {
            printf("\nTiempo total encendido: %f h\n", totalHours);
            printf("Reiniciando...\n");
            system("automator /Users/andres/Library/Services/reiniciar.workflow"); // Llamamos a el programa de automator que runea el script "shutdown -r now" como administrador
            break;
        }
        printf("\nTiempo total encendido: %f h\n", totalHours);

        sleep(3600); // Espera 1 hora antes de verificar nuevamente
    }
    return 0;
}

// Funcion para ver si el programa ya esta runeando en otra terminal
int is_program_running()
{
    char lock_file_path[256];
    const char *home_dir = getenv("HOME");
    snprintf(lock_file_path, sizeof(lock_file_path), "%s%s", home_dir, LOCK_FILE_PATH);

    int lock_file = open(lock_file_path, O_RDWR | O_CREAT, CLAVE_LOCK);
    // Intenta obtener un bloqueo exclusivo en el archivo
    int result = flock(lock_file, LOCK_EX | LOCK_NB);

    if (result == -1)
    {
        // No se pudo obtener un bloqueo exclusivo, otra instancia está en ejecución
        close(lock_file);
        return 1;
    }
    // Se obtuvo un bloqueo exclusivo, por lo que esta es la única instancia en ejecución
    return 0;
}
// Funcon para modificar la hora total en base a cuanto tiempo lleva si es menos de un dia
int totalhoras(int hours, int minutes, int days)
{
    int totalHours = 0;
    // En estos if lo que hago es si hay solo minutos o solo horas pues lo detecto y lo guardo en la variable correspondiente
    if (hours == 0 && minutes == 0)
    {
        minutes = days;
        days = 0;
        hours = 0;
        totalHours = minutes / 60; // Calcula el tiempo total en horas
    }
    else if (minutes == 0)
    {
        minutes = hours;
        hours = days;
        days = 0;
        totalHours = (days * 24) + hours + (minutes / 60); // Calcula el tiempo total en horas
    }
    else
    {
        totalHours = (days * 24) + hours + (minutes / 60); // Calcula el tiempo total en horas
    }
    return totalHours;
}
