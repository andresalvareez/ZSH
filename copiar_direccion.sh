#!/bin/bash

# Obtener la dirección de la carpeta actual
direccion=$(pwd)

# Declarar la variable vacía
frase="" # Variable que contendrá la dirección completa sin espacios
for (( i=0; i<${#direccion}; i++ )); do
    #echo ${direccion:$i:1}
    if [[ $direccion = " " ]]; # Si el caracter es un espacio,
    then
        frase+="\ " # Agregar "\ " en lugar de " "
    else
        frase+="${direccion:$i:1}" # Agregar el caracter a la variable
    fi
done

# Imprimir la variable con la dirección completa
echo $frase