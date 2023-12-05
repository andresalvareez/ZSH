#include <stdio.h>
int main() {
    FILE *archivo;
    int numero, total = 0;

    // Abre el archivo en modo lectura
    archivo = fopen("texto_para_script.txt", "r");

    // Verifica si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    // Lee línea por línea hasta llegar al final del archivo
    while (fscanf(archivo, "%*[^0-9]%d", &numero) == 1) {
        // Suma el número al total
        total += numero;
        printf("Número: %d -- Total: %d\n", numero, total);
    }

    // Muestra el total
    printf("\nTotal recaudado: %d\n", total);

    // Cierra el archivo
    fclose(archivo);

    return 0;
}
