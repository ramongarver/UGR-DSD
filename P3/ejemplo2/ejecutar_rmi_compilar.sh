#!/bin/sh -e
# ejecutar = Macro para compilación y ejecución del ligador de RMI.

echo
echo "Lanzando el ligador de RMI..."
rmiregistry &

echo
echo "Compilando con javac..."
javac *.java