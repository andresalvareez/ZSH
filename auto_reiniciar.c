#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/file.h>

#define LOCK_FILE_PATH "/Desktop/cosas utiles/scripts_zshr/mi_programa.lock"

int is_program_running();

int main() {
    if (is_program_running()) {
        printf("El programa ya está en ejecución.\n");
        return 0;
    }
    printf("Programa ejecutandose");

    time_t start_time, current_time;
    double elapsed_time;

    //system("clear");
    // Obtiene la hora de inicio
    start_time = time(NULL);

    while (1) {
        // Obtiene la hora actual
        current_time = time(NULL);
        printf("\nTiempo transcurrido: %f\n", difftime(current_time, start_time));
        // Calcula el tiempo transcurrido en segundos
        elapsed_time = difftime(current_time, start_time);
        // Verifica si han pasado más de 2 días (172800 segundos)
        
        if (elapsed_time >= 172800) {
            printf("Reiniciando...\n");
            // Ejecuta el script "reiniciar.sh"
            // system("zsh ~/desktop/cosas\ utiles/scripts_zshr/reiniciar.sh");
            system("automator Library/Services/reiniciar.workflow");
            break;
        }
        // Espera 1 hora antes de verificar nuevamente
        sleep(3600);
    }

    return 0;
}

int is_program_running() {
    char lock_file_path[256];
    const char *home_dir = getenv("HOME");
    snprintf(lock_file_path, sizeof(lock_file_path), "%s%s", home_dir, LOCK_FILE_PATH);

    int lock_file = open(lock_file_path, O_RDWR | O_CREAT, 0644);

    // Intenta obtener un bloqueo exclusivo en el archivo
    int result = flock(lock_file, LOCK_EX | LOCK_NB);

    if (result == -1) {
        // No se pudo obtener un bloqueo exclusivo, otra instancia está en ejecución
        close(lock_file);
        return 1;
    }

    // Se obtuvo un bloqueo exclusivo, por lo que esta es la única instancia en ejecución
    return 0;
}
