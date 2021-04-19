$:.push('gen-rb')

require 'thrift'
require 'operaciones'
require 'operaciones_types'

class OperacionesHandler
  def initialize()
    @log = {}
  end

  def ping()
    puts "ping()"
  end

  def suma(n1, n2)
    puts "sumando #{n1} con #{n2}"
    return n1 + n2
  end

  def resta(n1, n2)
    puts "restando #{n1} con #{n2}"
    return n1 - n2
  end

  def multiplicacion(n1, n2)
    puts "multiplicando #{n1} con #{n2}"
    return n1 * n2
  end

  def division(n1, n2)
    if n2 == 0
      raise InvalidOperation.new("InvalidOperation: No se puede dividir entre 0")
    end
    puts "dividiendo #{n1} entre #{n2}"
    return (n1 / n2).to_i
  end

  def potencia(p)
    if p.base == 0 and p.exponente == 0
      raise InvalidOperation.new("InvalidOperation: No se puede resolver la operación 0 elevado a 0 (indeterminación)")
    end
    return p.base ** p.exponente
  end

  def raizCuadrada(num)
    if num < 0
      raise InvalidOperation.new("InvalidOperation: No se puede resolver una raíz negativa")
    end
    return Math.sqrt(num)
  end

  def resolverCalculos(calculos)
    for calculo in calculos
      if calculo.operation == Operation::SUMAR
        calculo.result = self.suma(calculo.num1, calculo.num2)
      elsif calculo.operation == Operation::RESTAR
        calculo.result = self.resta(calculo.num1, calculo.num2)
      elsif calculo.operation == Operation::MULTIPLICAR
        calculo.result = self.multiplicacion(calculo.num1, calculo.num2)
      elsif calculo.operation == Operation::DIVIDIR
        calculo.result = self.division(calculo.num1, calculo.num2)
      elsif calculo.operation == Operation::POTENCIA
        p = Power.new
        p.base = calculo.num1
        p.exponente = calculo.num2
        calculo.result = self.potencia(p)
      elsif calculo.operation == Operation::RAIZ
        calculo.result = self.raizCuadrada(calculo.num1)
      end
    end
    return calculos
  end

  def transladar(p, x, y, z)
    result = Point.new
    result.x = p.x + x
    result.y = p.y + y
    result.z = p.z + z
    return result
  end

  def escalar(p, x, y, z)
    result = Point.new
    result.x = p.x * x
    result.y = p.y * y
    result.z = p.z * z
    return result
  end
end

handler = OperacionesHandler.new()
processor = Operaciones::Processor.new(handler)
transport = Thrift::ServerSocket.new(9091)
transportFactory = Thrift::BufferedTransportFactory.new()
server = Thrift::SimpleServer.new(processor, transport, transportFactory)

puts "Iniciando servidor..."
server.serve()
puts "Fin."
