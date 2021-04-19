### Versión 1

Cliente/Servidor simple.

- Cliente: cliente.py
- Servidor: servidor.py

Posee toda la funcionalidad completa.

Ejecución:

`python3 gen-py/servidor.py`

`python3 gen-py/cliente.py localhost 4 + 2`

### Versión 2

Cliente/Servidor complejo.

- Cliente: cliente.py
- Servidor/Cliente: servidor_intermedio.py
- Servidor: servidor_operaciones.rb
- Servidor: servidor_vectores.rb
- Servidor: servidor_matrices.rb
- Servidor: servidor_cifrador.rb

Ejecución:

`python3 gen-py/servidor_intermedio.py`

`ruby gen-rb/servidor_operaciones.rb`

`ruby gen-rb/servidor_vectores.rb`

`ruby gen-rb/servidor_matrices.rb`

`ruby gen-rb/servidor_cifrador.rb`

`python3 gen-py/cliente.py localhost 4 + 2`



#### Versiones utilizadas

Apache Thrift -  0.13.0

Python - 3.8.5

Ruby - 2.7.0