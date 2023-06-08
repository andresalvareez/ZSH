#!bin/bash

direccion=$(pwd)

# Función para cambiar los espacios por "\ "
function cambiar_espacios {
    direccion=${direccion// /\\ }
}

# Verificando si hay espacios en blanco en la dirección
if [[ $direccion =~ " " ]]; then
    # Llamando a la función para cambiar los espacios
    cambiar_espacios
    echo "$direccion"
    echo "$direccion" | pbcopy
fi
