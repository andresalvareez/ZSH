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
else
    # Recorriendo la dirección letra por letra
    for ((i = 0; i < ${#direccion}; i++)); do
        # Imprimiendo cada letra
        echo ${direccion:$i:1}
    done
fi
