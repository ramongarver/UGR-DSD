#
# Autogenerated by Thrift Compiler (0.13.0)
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#

require 'thrift'
require 'cifrador_types'

module Cifrador
  class Client
    include ::Thrift::Client

    def ping()
      send_ping()
      recv_ping()
    end

    def send_ping()
      send_message('ping', Ping_args)
    end

    def recv_ping()
      result = receive_message(Ping_result)
      return
    end

    def cifrar(password)
      send_cifrar(password)
      return recv_cifrar()
    end

    def send_cifrar(password)
      send_message('cifrar', Cifrar_args, :password => password)
    end

    def recv_cifrar()
      result = receive_message(Cifrar_result)
      return result.success unless result.success.nil?
      raise ::Thrift::ApplicationException.new(::Thrift::ApplicationException::MISSING_RESULT, 'cifrar failed: unknown result')
    end

    def descifrar(password)
      send_descifrar(password)
      return recv_descifrar()
    end

    def send_descifrar(password)
      send_message('descifrar', Descifrar_args, :password => password)
    end

    def recv_descifrar()
      result = receive_message(Descifrar_result)
      return result.success unless result.success.nil?
      raise ::Thrift::ApplicationException.new(::Thrift::ApplicationException::MISSING_RESULT, 'descifrar failed: unknown result')
    end

  end

  class Processor
    include ::Thrift::Processor

    def process_ping(seqid, iprot, oprot)
      args = read_args(iprot, Ping_args)
      result = Ping_result.new()
      @handler.ping()
      write_result(result, oprot, 'ping', seqid)
    end

    def process_cifrar(seqid, iprot, oprot)
      args = read_args(iprot, Cifrar_args)
      result = Cifrar_result.new()
      result.success = @handler.cifrar(args.password)
      write_result(result, oprot, 'cifrar', seqid)
    end

    def process_descifrar(seqid, iprot, oprot)
      args = read_args(iprot, Descifrar_args)
      result = Descifrar_result.new()
      result.success = @handler.descifrar(args.password)
      write_result(result, oprot, 'descifrar', seqid)
    end

  end

  # HELPER FUNCTIONS AND STRUCTURES

  class Ping_args
    include ::Thrift::Struct, ::Thrift::Struct_Union

    FIELDS = {

    }

    def struct_fields; FIELDS; end

    def validate
    end

    ::Thrift::Struct.generate_accessors self
  end

  class Ping_result
    include ::Thrift::Struct, ::Thrift::Struct_Union

    FIELDS = {

    }

    def struct_fields; FIELDS; end

    def validate
    end

    ::Thrift::Struct.generate_accessors self
  end

  class Cifrar_args
    include ::Thrift::Struct, ::Thrift::Struct_Union
    PASSWORD = 1

    FIELDS = {
      PASSWORD => {:type => ::Thrift::Types::STRING, :name => 'password'}
    }

    def struct_fields; FIELDS; end

    def validate
    end

    ::Thrift::Struct.generate_accessors self
  end

  class Cifrar_result
    include ::Thrift::Struct, ::Thrift::Struct_Union
    SUCCESS = 0

    FIELDS = {
      SUCCESS => {:type => ::Thrift::Types::STRING, :name => 'success'}
    }

    def struct_fields; FIELDS; end

    def validate
    end

    ::Thrift::Struct.generate_accessors self
  end

  class Descifrar_args
    include ::Thrift::Struct, ::Thrift::Struct_Union
    PASSWORD = 2

    FIELDS = {
      PASSWORD => {:type => ::Thrift::Types::STRING, :name => 'password'}
    }

    def struct_fields; FIELDS; end

    def validate
    end

    ::Thrift::Struct.generate_accessors self
  end

  class Descifrar_result
    include ::Thrift::Struct, ::Thrift::Struct_Union
    SUCCESS = 0

    FIELDS = {
      SUCCESS => {:type => ::Thrift::Types::STRING, :name => 'success'}
    }

    def struct_fields; FIELDS; end

    def validate
    end

    ::Thrift::Struct.generate_accessors self
  end

end

