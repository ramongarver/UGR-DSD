#!/bin/sh -e
# ejecutar = Macro para ejecución de los programas ejemplo cliente en una sola máquina Unix de nombre localhost.

echo
echo "Lanzando diez hebras del primer cliente..."
echo
java -cp . -Djava.security.policy=server.policy Cliente_Ejemplo_Multi_Threaded localhost 10

sleep 2

echo
echo "Lanzando veinte hebras del segundo cliente..."
echo
java -cp . -Djava.security.policy=server.policy Cliente_Ejemplo_Multi_Threaded localhost 20