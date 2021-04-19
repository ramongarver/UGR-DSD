$:.push('gen-rb')

require 'thrift'
require 'vectores'
require 'vectores_types'
require 'matrix'

class VectoresHandler
  def initialize()
    @log = {}
  end

  def ping()
    puts "ping()"
  end

  def sumarVectores(v1, v2)
    if v1.size() != v2.size()
      raise InvalidOperation.new("InvalidOperation: No se pueden sumar vectores con distinto tamaño")
    end
    vec1 = Vector[*v1]
    vec2 = Vector[*v2]
    result = vec1 + vec2
    return *result.round(4)
  end

  def restarVectores(v1, v2)
    if v1.size() != v2.size()
      raise InvalidOperation.new("InvalidOperation: No se pueden restar vectores con distinto tamaño")
    end
    vec1 = Vector[*v1]
    vec2 = Vector[*v2]
    result = vec1 - vec2
    return *result.round(4)
  end

  def multiplicarVectores(v1, v2)
    if v1.size() != v2.size()
      raise InvalidOperation.new("InvalidOperation: No se pueden multiplicar vectores con distinto tamaño")
    end
    result = []
    for i in 0..(v1.size()-1)
      result[i] = (v1[i] * v2[i]).round(4)
    end
    return result
  end

  def dividirVectores(v1, v2)
    if v1.size() != v2.size()
      raise InvalidOperation.new("InvalidOperation: No se pueden dividir vectores con distinto tamaño")
    end
    result = []
    for i in 0..(v1.size()-1)
      if v2[i] == 0.0
        raise InvalidOperation.new("InvalidOperation: No se puede dividir entre 0")
      end
      result[i] = (v1[i] / v2[i]).round(4)
    end
    return result
  end
end

handler = VectoresHandler.new()
processor = Vectores::Processor.new(handler)
transport = Thrift::ServerSocket.new(9092)
transportFactory = Thrift::BufferedTransportFactory.new()
server = Thrift::SimpleServer.new(processor, transport, transportFactory)

puts "Iniciando servidor..."
server.serve()
puts "Fin."
