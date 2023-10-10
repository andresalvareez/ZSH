#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>

#define LOCK_FILE_PATH "/Desktop/cosas utiles/scripts_zshr/mi_programa.lock" // Ruta absoluta del archivo lock 
#define CLAVE_LOCK 0002 // Clave de el bloqueo exclusivo del archivo lock
#define RUTA_ICONO "~/Desktop/cosas\ utiles/iconos/Brave.icns" // Ruta absoluta de el icono que se quiere usar
#define RUTA_APP "/Applications/Brave\ Browser.app/Contents/Resources" // Ruta absoluta de la app que se quiere ejecutar

//** Prototipado de las funciones **//

int is_program_running();

int main()
{
    if (is_program_running())
    {
        printf("El programa ya está en ejecución.\n");
        return 0;
    }
    printf("Programa ejecutandose");
    
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