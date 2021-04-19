import glob
import sys

from calculadora import Calculadora
from calculadora.ttypes import Power, Operation, Calculo, Point, InvalidOperation

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

# Imprimir una matriz
def print_matrix(m):
    for i in range(len(m)):
        for j in m[i]:
            print(j, end = ' ')
        print()

# Transformar una operación a su carácter
def operation_to_char(operation):
    if operation == Operation.SUMAR:
        operation = "+"
    elif operation == Operation.RESTAR:
        operation = "-"
    elif operation == Operation.MULTIPLICAR:
        operation = "x"
    elif operation == Operation.DIVIDIR:
        operation = "/"
    elif operation == Operation.POTENCIA:
        operation = "^"
    elif operation == Operation.RAIZ:
        operation = "sqrt"
    return operation

# Imprimir calculo
def print_calculo(calculo):
    if calculo.operation != 6:
        print(calculo.num1, operation_to_char(calculo.operation), calculo.num2, "=", calculo.result)
    else:
        print(operation_to_char(calculo.operation) + "(" + str(calculo.num1) + ") =", calculo.result)

# Imprimir una lista de cálculos
def print_calculos(calculos):
    for calculo in calculos:
        print_calculo(calculo)

def main():

    # Comprobación del número de argumentos
    if len(sys.argv) < 4:
        print("usage:", sys.argv[0], "server_host first_operand operator [second_operand]\n")
        exit(1)

    operator = sys.argv[3]
    # Comprobación de los operadores binarios
    if len(sys.argv) == 5 and operator != '+' and operator != '-' and operator != 'x' and operator != '/' and operator != '^':
        print("usage:", sys.argv[0], "server_host first_operand operator [second_operand]\n")
        exit(1)

    # Comprobación del operador unario
    if len(sys.argv) == 4 and operator != 'r':
        print("usage:", sys.argv[0], "server_host first_operand operator [second_operand]\n")
        exit(1)

    host = sys.argv[1]
    # Make socket
    transport = TSocket.TSocket(host, 9090)

    # Buffering is critical. Raw sockets are very slow
    transport = TTransport.TBufferedTransport(transport)

    # Wrap in a protocol
    protocol = TBinaryProtocol.TBinaryProtocol(transport)

    # Create a client to use the protocol encoder
    client = Calculadora.Client(protocol)

    # Connect
    transport.open()

    # Check connection with server
    print("ping()\n")
    client.ping()


    # Operaciones básicas
    num1 = int(sys.argv[2])
    num2 = 0
    if len(sys.argv) == 5:
        num2 = int(sys.argv[4])
    p = Power(num1, num2)

    if operator == '+':
        suma = client.suma(num1, num2)
        print(str(num1) + " + " + str(num2) + " = " + str(suma))
    elif operator == '-':
        resta = client.resta(num1, num2)
        print(str(num1) + " - " + str(num2) + " = " + str(resta))
    elif operator == 'x':
        multiplicacion = client.multiplicacion(num1, num2)
        print(str(num1) + " x " + str(num2) + " = " + str(multiplicacion))
    elif operator == '/':
        try:
            division = client.division(num1, num2)
            print(str(num1) + " / " + str(num2) + " = " + str(division))
        except InvalidOperation as e:
            print(e.why)
    elif operator == '^':
        try:
            potencia = client.potencia(p)
            print(str(p.base) + " ^ " + str(p.exponente) + " = " + str(potencia))
        except InvalidOperation as e:
            print(e.why)
    elif operator == 'r':
        try:
            raiz = client.raizCuadrada(num1)
            print("sqrt(" + (str(num1)) + ") = " + str(raiz))
        except InvalidOperation as e:
            print(e.why)
    else:
        print("Operación no reconocida")
        exit(1)

    print()
    # ---------------------------------------------------------------------- #


    # Operaciones sobre estructura de operandos y operadores
    calculos = [Calculo(3, 2, Operation.SUMAR),
                Calculo(2, 0, Operation.RESTAR),
                Calculo(4, 5, Operation.MULTIPLICAR),
                Calculo(5, 2, Operation.DIVIDIR),
                Calculo(4, 4, Operation.POTENCIA),
                Calculo(2, 0, Operation.RAIZ)]
    calculos = client.resolverCalculos(calculos)

    print_calculos(calculos)

    print()
    # ---------------------------------------------------------------------- #


    # Operaciones geométricas (transformaciones geométricas)
    p = Point(1.0, 2.5, 3.0)
    print("Punto inicial:", p)

    ptransladado = client.transladar(p, 3.0, -3.5, 0.8)
    print("Punto transladado:", ptransladado)

    pescalado = client.escalar(p, 1.5, 0.75, 1.25)
    print("Punto escalado:", pescalado)

    print()
    # ---------------------------------------------------------------------- #



    # Operaciones con vectores
    v1 = [2.1, 3.3, 3.5, 5.4, 3.5, 7.2]
    print("Vector 1 (A)")
    print(v1)

    v2 = [2.4, 3.3, 3.2, 3.0, 0.3, 7.0]
    print("Vector 2 (B)")
    print(v2)

    try:
        vsuma = client.sumarVectores(v1, v2)
        print("Vector suma (A+B)")
        print(vsuma)
    except InvalidOperation as e:
        print(e.why)

    try:
        vresta = client.restarVectores(v1, v2)
        print("Vector resta (A-B)")
        print(vresta)
    except InvalidOperation as e:
        print(e.why)

    try:
        vmultiplicacion = client.multiplicarVectores(v1, v2)
        print("Vector multiplicación (AxB)")
        print(vmultiplicacion)
    except InvalidOperation as e:
        print(e.why)

    try:
        vdivision = client.dividirVectores(v1, v2)
        print("Vector división (A/B)")
        print(vdivision)
    except InvalidOperation as e:
        print(e.why)

    print()
    # ---------------------------------------------------------------------- #


    # Operaciones con matrices
    m1 = [[1.5, 0.5, 2.2], [1.75, 0.25, 0.4], [1.3, 0.7, 1.5]]
    print("Matriz 1 (A)")
    print_matrix(m1)

    m2 = [[3.2, 4.5, 4.5], [3.4, 5.6, 1.0], [3.4, 9.6, 0.0]]
    print("Matriz 2 (B)")
    print_matrix(m2)

    try:
        msuma = client.sumarMatrices(m1, m2)
        print("Matriz suma (A+B)")
        print_matrix(msuma)
    except InvalidOperation as e:
        print(e.why)

    try:
        mresta = client.restarMatrices(m1, m2)
        print("Matriz resta (A-B)")
        print_matrix(mresta)
    except InvalidOperation as e:
        print(e.why)

    try:
        mmultiplicacion = client.multiplicarMatrices(m1, m2)
        print("Matriz multiplicación (AxB)")
        print_matrix(mmultiplicacion)
    except InvalidOperation as e:
        print(e.why)

    m3 = [[1.5], [1.75], [1.25]]
    print("Matriz 3 (C) (no cuadrada)")
    print_matrix(m3)

    m4 = [[2.0, 0.5]]
    print("Matriz 4 (D) (no cuadrada)")
    print_matrix(m4)

    try:
        mmultiplicacionnc = client.multiplicarMatrices(m3, m4)
        print("Matriz multiplicación (CxD) (no cuadrada)")
        print_matrix(mmultiplicacionnc)
    except InvalidOperation as e:
        print(e.why)

    print()
    # ---------------------------------------------------------------------- #


    # Operaciones de cifrado y descifrado
    password = "abretesesamo"
    encryptedPassword = client.cifrar(password)
    desencryptedPassword = client.descifrar(encryptedPassword)


    print("Contraseña sin cifrar:", password)
    print("Contraseña cifrada:", encryptedPassword)
    print("Contraseña descifrada:", desencryptedPassword)
    # ---------------------------------------------------------------------- #


    # Disconnect
    transport.close()


if __name__ == "__main__":
    main()
