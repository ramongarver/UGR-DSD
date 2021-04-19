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

class Conexion:
    def __init__(self, host, port):
        self.host = host
        self.port = port

    def conectar(self):
        self.transport = TSocket.TSocket(self.host, self.port)
        self.transport = TTransport.TBufferedTransport(self.transport)
        self.protocol = TBinaryProtocol.TBinaryProtocol(self.transport)
        client = Calculadora.Client(self.protocol)
        self.transport.open()
        return client

    def desconectar(self):
        self.transport.close()


class CalculadoraHandler:
    def __init__(self):
        self.log = {}

    def ping(self):
        print("me han hecho ping()")

    def suma(self, n1, n2):
        conexion = Conexion("localhost", 9091)
        client = conexion.conectar()
        result = client.suma(n1, n2)
        conexion.desconectar()
        return result

    def resta(self, n1, n2):
        conexion = Conexion("localhost", 9091)
        client = conexion.conectar()
        result = client.resta(n1, n2)
        conexion.desconectar()
        return result

    def multiplicacion(self, n1, n2):
        conexion = Conexion("localhost", 9091)
        client = conexion.conectar()
        result = client.multiplicacion(n1, n2)
        conexion.desconectar()
        return result

    def division(self, n1, n2):
        conexion = Conexion("localhost", 9091)
        client = conexion.conectar()
        result = client.division(n1, n2)
        conexion.desconectar()
        return result

    def potencia(self, p):
        conexion = Conexion("localhost", 9091)
        client = conexion.conectar()
        result = client.potencia(p)
        conexion.desconectar()
        return result

    def raizCuadrada(self, num):
        conexion = Conexion("localhost", 9091)
        client = conexion.conectar()
        result = client.raizCuadrada(num)
        conexion.desconectar()
        return result

    def resolverCalculos(self, calculos):
        conexion = Conexion("localhost", 9091)
        client = conexion.conectar()
        result = client.resolverCalculos(calculos)
        conexion.desconectar()
        return result

    def transladar(self, p, x, y, z):
        conexion = Conexion("localhost", 9091)
        client = conexion.conectar()
        result = client.transladar(p, x, y, z)
        conexion.desconectar()
        return result

    def escalar(self, p, x, y, z):
        conexion = Conexion("localhost", 9091)
        client = conexion.conectar()
        result = client.escalar(p, x, y, z)
        conexion.desconectar()
        return result

    def sumarVectores(self, v1, v2):
        conexion = Conexion("localhost", 9092)
        client = conexion.conectar()
        result = client.sumarVectores(v1, v2)
        conexion.desconectar()
        return result

    def restarVectores(self, v1, v2):
        conexion = Conexion("localhost", 9092)
        client = conexion.conectar()
        result = client.restarVectores(v1, v2)
        conexion.desconectar()
        return result

    def multiplicarVectores(self, v1, v2):
        conexion = Conexion("localhost", 9092)
        client = conexion.conectar()
        result = client.multiplicarVectores(v1, v2)
        conexion.desconectar()
        return result

    def dividirVectores(self, v1, v2):
        conexion = Conexion("localhost", 9092)
        client = conexion.conectar()
        result = client.dividirVectores(v1, v2)
        conexion.desconectar()
        return result

    def sumarMatrices(self, m1, m2):
        conexion = Conexion("localhost", 9093)
        client = conexion.conectar()
        result = client.sumarMatrices(m1, m2)
        conexion.desconectar()
        return result

    def restarMatrices(self, m1, m2):
        conexion = Conexion("localhost", 9093)
        client = conexion.conectar()
        result = client.restarMatrices(m1, m2)
        conexion.desconectar()
        return result

    def multiplicarMatrices(self, m1, m2):
        conexion = Conexion("localhost", 9093)
        client = conexion.conectar()
        result = client.multiplicarMatrices(m1, m2)
        conexion.desconectar()
        return result

    def cifrar(self, password):
        conexion = Conexion("localhost", 9094)
        client = conexion.conectar()
        result = client.cifrar(password)
        conexion.desconectar()
        return result

    def descifrar(self, password):
        conexion = Conexion("localhost", 9094)
        client = conexion.conectar()
        result = client.descifrar(password)
        conexion.desconectar()
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
