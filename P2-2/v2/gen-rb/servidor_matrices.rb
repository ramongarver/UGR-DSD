$:.push('gen-rb')

require 'thrift'
require 'matrices'
require 'matrices_types'
require 'matrix'

class MatricesHandler
  def initialize()
    @log = {}
  end

  def ping()
    puts "ping()"
  end

  def sumarMatrices(m1, m2)
    if m1.size() != m2.size()
      raise InvalidOperation.new("InvalidOperation: No se pueden sumar matrices de distintas dimensiones")
    else
      for i in 0..(m1.size()-1)
        if m1[i].size() != m2[i].size()
          raise InvalidOperation.new("InvalidOperation: No se pueden sumar matrices de distintas dimensiones")
        end
      end
    end
    mat1 = Matrix[*m1]
    mat2 = Matrix[*m2]
    result = mat1 + mat2
    return *result.round(4)
  end

  def restarMatrices(m1, m2)
    if m1.size() != m2.size()
      raise InvalidOperation.new("InvalidOperation: No se pueden sumar matrices de distintas dimensiones")
    else
      for i in 0..(m1.size()-1)
        if m1[i].size() != m2[i].size()
          raise InvalidOperation.new("InvalidOperation: No se pueden restar matrices de distintas dimensiones")
        end
      end
    end
    mat1 = Matrix[*m1]
    mat2 = Matrix[*m2]
    result = mat1 - mat2
    return *result.round(4)
  end

  def multiplicarMatrices(m1, m2)
    for i in 0..(m1.size()-1)
      if m1[i].size() != m2.size()
        raise InvalidOperation.new("InvalidOperation: No se pueden multiplicar matrices con dimensiones diferentes a M1(m,n) x M2(n,t)")
      end
    end
    mat1 = Matrix[*m1]
    mat2 = Matrix[*m2]
    result = mat1 * mat2
    return *result.round(4)
  end
end

handler = MatricesHandler.new()
processor = Matrices::Processor.new(handler)
transport = Thrift::ServerSocket.new(9093)
transportFactory = Thrift::BufferedTransportFactory.new()
server = Thrift::SimpleServer.new(processor, transport, transportFactory)

puts "Iniciando servidor..."
server.serve()
puts "Fin."
