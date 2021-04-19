$:.push('gen-rb')

require 'thrift'
require 'cifrador'

class CifradorHandler
  def initialize()
    @log = {}
  end

  def ping()
    puts "ping()"
  end

  def cifrar(password)
    puts "Contraseña cifrada"
    result = ""
    password.each_char do |char|
      result += ((char.ord)-30).chr
    end
    return result
  end

  def descifrar(password)
    puts "Contraseña descifrada"
    result = ""
    password.each_char do |char|
      result += ((char.ord)+30).chr
    end
    return result
  end
end

handler = CifradorHandler.new()
processor = Cifrador::Processor.new(handler)
transport = Thrift::ServerSocket.new(9094)
transportFactory = Thrift::BufferedTransportFactory.new()
server = Thrift::SimpleServer.new(processor, transport, transportFactory)

puts "Iniciando servidor..."
server.serve()
puts "Fin."
