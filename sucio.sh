#!/bin/bash

# Obtenemos la fecha y hora actual
timestamp=$(date +%Y-%m-%d_%H-%M-%S)

# Le pedimos al usuario que introduzca la extensión deseada
echo "Introduce la extensión del archivo:"
read -r extension

# Creamos el nombre del archivo con el formato que has especificado
nombre_archivo="sucio_$(basename "$PWD")_${timestamp}.${extension}"

# Definimos la ruta completa del archivo
ruta_archivo="$HOME/desktop/notas/$nombre_archivo"

# Creamos el archivo vacío con la extensión especificada en la ruta indicada
touch "$ruta_archivo"

# Abrimos el archivo en el editor de texto predeterminado
open "$ruta_archivo"