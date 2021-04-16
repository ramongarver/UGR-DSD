#
# Autogenerated by Thrift Compiler (0.13.0)
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#
#  options string: py
#

from thrift.Thrift import TType, TMessageType, TFrozenDict, TException, TApplicationException
from thrift.protocol.TProtocol import TProtocolException
from thrift.TRecursive import fix_spec

import sys

from thrift.transport import TTransport
all_structs = []


class Operation(object):
    SUMAR = 1
    RESTAR = 2
    MULTIPLICAR = 3
    DIVIDIR = 4
    POTENCIA = 5
    RAIZ = 6

    _VALUES_TO_NAMES = {
        1: "SUMAR",
        2: "RESTAR",
        3: "MULTIPLICAR",
        4: "DIVIDIR",
        5: "POTENCIA",
        6: "RAIZ",
    }

    _NAMES_TO_VALUES = {
        "SUMAR": 1,
        "RESTAR": 2,
        "MULTIPLICAR": 3,
        "DIVIDIR": 4,
        "POTENCIA": 5,
        "RAIZ": 6,
    }


class Power(object):
    """
    Attributes:
     - base
     - exponente

    """


    def __init__(self, base=None, exponente=None,):
        self.base = base
        self.exponente = exponente

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, [self.__class__, self.thrift_spec])
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.I32:
                    self.base = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.I32:
                    self.exponente = iprot.readI32()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, [self.__class__, self.thrift_spec]))
            return
        oprot.writeStructBegin('Power')
        if self.base is not None:
            oprot.writeFieldBegin('base', TType.I32, 1)
            oprot.writeI32(self.base)
            oprot.writeFieldEnd()
        if self.exponente is not None:
            oprot.writeFieldBegin('exponente', TType.I32, 2)
            oprot.writeI32(self.exponente)
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        if self.base is None:
            raise TProtocolException(message='Required field base is unset!')
        if self.exponente is None:
            raise TProtocolException(message='Required field exponente is unset!')
        return

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)


class Calculo(object):
    """
    Attributes:
     - num1
     - num2
     - operation
     - result

    """


    def __init__(self, num1=None, num2=None, operation=None, result=float(0),):
        self.num1 = num1
        self.num2 = num2
        self.operation = operation
        self.result = result

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, [self.__class__, self.thrift_spec])
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.I32:
                    self.num1 = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.I32:
                    self.num2 = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 3:
                if ftype == TType.I32:
                    self.operation = iprot.readI32()
                else:
                    iprot.skip(ftype)
            elif fid == 4:
                if ftype == TType.DOUBLE:
                    self.result = iprot.readDouble()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, [self.__class__, self.thrift_spec]))
            return
        oprot.writeStructBegin('Calculo')
        if self.num1 is not None:
            oprot.writeFieldBegin('num1', TType.I32, 1)
            oprot.writeI32(self.num1)
            oprot.writeFieldEnd()
        if self.num2 is not None:
            oprot.writeFieldBegin('num2', TType.I32, 2)
            oprot.writeI32(self.num2)
            oprot.writeFieldEnd()
        if self.operation is not None:
            oprot.writeFieldBegin('operation', TType.I32, 3)
            oprot.writeI32(self.operation)
            oprot.writeFieldEnd()
        if self.result is not None:
            oprot.writeFieldBegin('result', TType.DOUBLE, 4)
            oprot.writeDouble(self.result)
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        if self.num1 is None:
            raise TProtocolException(message='Required field num1 is unset!')
        if self.operation is None:
            raise TProtocolException(message='Required field operation is unset!')
        if self.result is None:
            raise TProtocolException(message='Required field result is unset!')
        return

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)


class Point(object):
    """
    Attributes:
     - x
     - y
     - z

    """


    def __init__(self, x=None, y=None, z=None,):
        self.x = x
        self.y = y
        self.z = z

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, [self.__class__, self.thrift_spec])
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.DOUBLE:
                    self.x = iprot.readDouble()
                else:
                    iprot.skip(ftype)
            elif fid == 2:
                if ftype == TType.DOUBLE:
                    self.y = iprot.readDouble()
                else:
                    iprot.skip(ftype)
            elif fid == 3:
                if ftype == TType.DOUBLE:
                    self.z = iprot.readDouble()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, [self.__class__, self.thrift_spec]))
            return
        oprot.writeStructBegin('Point')
        if self.x is not None:
            oprot.writeFieldBegin('x', TType.DOUBLE, 1)
            oprot.writeDouble(self.x)
            oprot.writeFieldEnd()
        if self.y is not None:
            oprot.writeFieldBegin('y', TType.DOUBLE, 2)
            oprot.writeDouble(self.y)
            oprot.writeFieldEnd()
        if self.z is not None:
            oprot.writeFieldBegin('z', TType.DOUBLE, 3)
            oprot.writeDouble(self.z)
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        if self.x is None:
            raise TProtocolException(message='Required field x is unset!')
        if self.y is None:
            raise TProtocolException(message='Required field y is unset!')
        if self.z is None:
            raise TProtocolException(message='Required field z is unset!')
        return

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)


class InvalidOperation(TException):
    """
    Attributes:
     - why

    """


    def __init__(self, why=None,):
        self.why = why

    def read(self, iprot):
        if iprot._fast_decode is not None and isinstance(iprot.trans, TTransport.CReadableTransport) and self.thrift_spec is not None:
            iprot._fast_decode(self, iprot, [self.__class__, self.thrift_spec])
            return
        iprot.readStructBegin()
        while True:
            (fname, ftype, fid) = iprot.readFieldBegin()
            if ftype == TType.STOP:
                break
            if fid == 1:
                if ftype == TType.STRING:
                    self.why = iprot.readString().decode('utf-8') if sys.version_info[0] == 2 else iprot.readString()
                else:
                    iprot.skip(ftype)
            else:
                iprot.skip(ftype)
            iprot.readFieldEnd()
        iprot.readStructEnd()

    def write(self, oprot):
        if oprot._fast_encode is not None and self.thrift_spec is not None:
            oprot.trans.write(oprot._fast_encode(self, [self.__class__, self.thrift_spec]))
            return
        oprot.writeStructBegin('InvalidOperation')
        if self.why is not None:
            oprot.writeFieldBegin('why', TType.STRING, 1)
            oprot.writeString(self.why.encode('utf-8') if sys.version_info[0] == 2 else self.why)
            oprot.writeFieldEnd()
        oprot.writeFieldStop()
        oprot.writeStructEnd()

    def validate(self):
        return

    def __str__(self):
        return repr(self)

    def __repr__(self):
        L = ['%s=%r' % (key, value)
             for key, value in self.__dict__.items()]
        return '%s(%s)' % (self.__class__.__name__, ', '.join(L))

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.__dict__ == other.__dict__

    def __ne__(self, other):
        return not (self == other)
all_structs.append(Power)
Power.thrift_spec = (
    None,  # 0
    (1, TType.I32, 'base', None, None, ),  # 1
    (2, TType.I32, 'exponente', None, None, ),  # 2
)
all_structs.append(Calculo)
Calculo.thrift_spec = (
    None,  # 0
    (1, TType.I32, 'num1', None, None, ),  # 1
    (2, TType.I32, 'num2', None, None, ),  # 2
    (3, TType.I32, 'operation', None, None, ),  # 3
    (4, TType.DOUBLE, 'result', None, float(0), ),  # 4
)
all_structs.append(Point)
Point.thrift_spec = (
    None,  # 0
    (1, TType.DOUBLE, 'x', None, None, ),  # 1
    (2, TType.DOUBLE, 'y', None, None, ),  # 2
    (3, TType.DOUBLE, 'z', None, None, ),  # 3
)
all_structs.append(InvalidOperation)
InvalidOperation.thrift_spec = (
    None,  # 0
    (1, TType.STRING, 'why', 'UTF8', None, ),  # 1
)
fix_spec(all_structs)
del all_structs
