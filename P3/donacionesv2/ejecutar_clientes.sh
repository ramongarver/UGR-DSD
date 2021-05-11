#!/bin/sh -e
# ejecutar = Macro para ejecución de los programas ejemplo cliente en una sola máquina Unix de nombre localhost.

echo "Lanzando el cliente..."
echo
java -cp . -Djava.security.policy=server.policy Donador 2