#!/bin/sh -e
# ejecutar = Macro para ejecución de los programas ejemplo cliente en una sola máquina Unix de nombre localhost.

echo
echo "Lanzando el primer cliente..."
echo
java -cp . -Djava.security.policy=server.policy cliente

sleep 2

echo
echo "Lanzando el segundo cliente..."
echo
java -cp . -Djava.security.policy=server.policy cliente