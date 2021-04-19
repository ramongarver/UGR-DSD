import glob
import sys

import math

from calculadora import Calculadora
from calculadora.ttypes import Power, Operation, Calculo, Point, InvalidOperation

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

import logging

logging.basicConfig(level=logging.DEBUG)


class CalculadoraHandler:
    def __init__(self):
        self.log = {}

    def ping(self):
        print("me han hecho ping()")

    def suma(self, n1, n2):
        print("sumando", n1, "con", n2)
        return n1 + n2

    def resta(self, n1, n2):
        print("restando", n1, "con", n2)
        return n1 - n2

    def multiplicacion(self, n1, n2):
        print("multiplicando", n1, "con", n2)
        return n1 * n2

    def division(self, n1, n2):
        if n2 == 0:
            raise InvalidOperation("InvalidOperation: No se puede dividir entre 0")
        print("dividiendo", n1, "entre", n2)
        return int(n1 / n2)

    def potencia(self, p):
        if p.base == 0 and p.exponente == 0:
            raise InvalidOperation("InvalidOperation: No se puede resolver la operación 0 elevado a 0 (indeterminación)")
        return pow(p.base, p.exponente)

    def raizCuadrada(self, num):
        if num < 0:
            raise InvalidOperation("InvalidOperation: No se puede resolver una raíz negativa")
        return math.sqrt(num)

    def resolverCalculos(self, calculos):
        for calculo in calculos:
            if calculo.operation == Operation.SUMAR:
                calculo.result = self.suma(calculo.num1, calculo.num2)
            elif calculo.operation == Operation.RESTAR:
                calculo.result = self.resta(calculo.num1, calculo.num2)
            elif calculo.operation == Operation.MULTIPLICAR:
                calculo.result = self.multiplicacion(calculo.num1, calculo.num2)
            elif calculo.operation == Operation.DIVIDIR:
                calculo.result = self.division(calculo.num1, calculo.num2)
            elif calculo.operation == Operation.POTENCIA:
                calculo.result = self.potencia(Power(calculo.num1, calculo.num2))
            elif calculo.operation == Operation.RAIZ:
                calculo.result = self.raizCuadrada(calculo.num1)
        return calculos

    def transladar(self, p, x, y, z):
        result = Point(0.0, 0.0, 0.0)
        result.x = p.x + x
        result.y = p.y + y
        result.z = p.z + z
        return result

    def escalar(self, p, x, y, z):
        result = Point(0.0, 0.0, 0.0)
        result.x = p.x * x
        result.y = p.y * y
        result.z = p.z * z
        return result

    def sumarVectores(self, v1, v2):
        if len(v1) != len(v2):
            raise InvalidOperation("InvalidOperation: No se pueden sumar vectores con distinto tamaño")
        print(v1, "+", v2)
        return [round(x,4) for x in [self.suma(a, b) for a, b in zip(v1, v2)]]

    def restarVectores(self, v1, v2):
        if len(v1) != len(v2):
            raise InvalidOperation("InvalidOperation: No se pueden restar vectores con distinto tamaño")
        print(v1, "-", v2)
        return [round(x,4) for x in [self.resta(a, b) for a, b in zip(v1, v2)]]

    def multiplicarVectores(self, v1, v2):
        if len(v1) != len(v2):
            raise InvalidOperation("InvalidOperation: No se pueden multiplicar vectores con distinto tamaño")
        print(v1, "x", v2)
        return [round(x,4) for x in [self.multiplicacion(a, b) for a, b in zip(v1, v2)]]

    def dividirVectores(self, v1, v2):
        if len(v1) != len(v2):
            raise InvalidOperation("InvalidOperation: No se pueden dividir vectores con distinto tamaño")
        print(v1, "/", v2)
        return [round(x,4) for x in [self.division(a, b) for a, b in zip(v1, v2)]]

    def sumarMatrices(self, m1, m2):
        if len(m1) != len(m2):
            raise InvalidOperation("InvalidOperation: No se pueden sumar matrices de distintas dimensiones")
        else:
            for i in range(len(m1)):
                if len(m1[i]) != len(m2[i]):
                    raise InvalidOperation("InvalidOperation: No se pueden sumar matrices de distintas dimensiones")

        result = [[] for i in range(len(m1))]
        for i in range(len(m1)):
            result[i] = [round(x,4) for x in [self.suma(a, b) for a, b in zip(m1[i], m2[i])]]
        return result

    def restarMatrices(self, m1, m2):
        if len(m1) != len(m2):
            raise InvalidOperation("InvalidOperation: No se pueden sumar matrices de distintas dimensiones")
        else:
            for i in range(len(m1)):
                if len(m1[i]) != len(m2[i]):
                    raise InvalidOperation("InvalidOperation: No se pueden restar matrices de distintas dimensiones")

        result = [[] for i in range(len(m1))]
        for i in range(len(m1)):
            result[i] = [round(x,4) for x in [self.resta(a, b) for a, b in zip(m1[i], m2[i])]]
        return result

    def multiplicarMatrices(self, m1, m2):
        for i in range(len(m1)):
            if len(m1[i]) != len(m2):
                raise InvalidOperation("InvalidOperation: No se pueden multiplicar matrices con dimensiones "
                                       "diferentes a M1(m,n) x M2(n,t)")

        result = [[[] for j in range(len(m2[0]))] for i in range(len(m1))]
        for i in range(len(m1)):
            for j in range(len(m2[0])):
                result[i][j] = 0
                for k in range(len(m2)):
                    result[i][j] += round(m1[i][k] * m2[k][j], 4)
        return result

    def cifrar(self, password):
        result = ""
        for char in password:
            result += chr(ord(char)-30)
        return result

    def descifrar(self, password):
        result = ""
        for char in password:
            result += chr(ord(char)+30)
        return result

if __name__ == "__main__":
    handler = CalculadoraHandler()
    processor = Calculadora.Processor(handler)
    transport = TSocket.TServerSocket(host="127.0.0.1", port=9090)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()

    server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

    print("Iniciando servidor...")
    server.serve()
    print("Fin")
