#!/bin/sh -e
# ejecutar = Macro para compilación y ejecución del programa ejemplo servidor en una sola máquina Unix de nombre localhost.

echo "Lanzando el servidor..."
echo
java -cp . -Djava.rmi.server.codebase=file:./ -Djava.rmi.server.hostname=localhost -Djava.security.policy=server.policy Servidor 5