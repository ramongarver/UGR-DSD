#
# Autogenerated by Thrift Compiler (0.13.0)
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#

require 'thrift'

module Operation
  SUMAR = 1
  RESTAR = 2
  MULTIPLICAR = 3
  DIVIDIR = 4
  POTENCIA = 5
  RAIZ = 6
  VALUE_MAP = {1 => "SUMAR", 2 => "RESTAR", 3 => "MULTIPLICAR", 4 => "DIVIDIR", 5 => "POTENCIA", 6 => "RAIZ"}
  VALID_VALUES = Set.new([SUMAR, RESTAR, MULTIPLICAR, DIVIDIR, POTENCIA, RAIZ]).freeze
end

class Power; end

class Calculo; end

class Point; end

class InvalidOperation < ::Thrift::Exception; end

class Power
  include ::Thrift::Struct, ::Thrift::Struct_Union
  BASE = 1
  EXPONENTE = 2

  FIELDS = {
    BASE => {:type => ::Thrift::Types::I32, :name => 'base'},
    EXPONENTE => {:type => ::Thrift::Types::I32, :name => 'exponente'}
  }

  def struct_fields; FIELDS; end

  def validate
    raise ::Thrift::ProtocolException.new(::Thrift::ProtocolException::UNKNOWN, 'Required field base is unset!') unless @base
    raise ::Thrift::ProtocolException.new(::Thrift::ProtocolException::UNKNOWN, 'Required field exponente is unset!') unless @exponente
  end

  ::Thrift::Struct.generate_accessors self
end

class Calculo
  include ::Thrift::Struct, ::Thrift::Struct_Union
  NUM1 = 1
  NUM2 = 2
  OPERATION = 3
  RESULT = 4

  FIELDS = {
    NUM1 => {:type => ::Thrift::Types::I32, :name => 'num1'},
    NUM2 => {:type => ::Thrift::Types::I32, :name => 'num2', :optional => true},
    OPERATION => {:type => ::Thrift::Types::I32, :name => 'operation', :enum_class => ::Operation},
    RESULT => {:type => ::Thrift::Types::DOUBLE, :name => 'result', :default => 0}
  }

  def struct_fields; FIELDS; end

  def validate
    raise ::Thrift::ProtocolException.new(::Thrift::ProtocolException::UNKNOWN, 'Required field num1 is unset!') unless @num1
    raise ::Thrift::ProtocolException.new(::Thrift::ProtocolException::UNKNOWN, 'Required field operation is unset!') unless @operation
    raise ::Thrift::ProtocolException.new(::Thrift::ProtocolException::UNKNOWN, 'Required field result is unset!') unless @result
    unless @operation.nil? || ::Operation::VALID_VALUES.include?(@operation)
      raise ::Thrift::ProtocolException.new(::Thrift::ProtocolException::UNKNOWN, 'Invalid value of field operation!')
    end
  end

  ::Thrift::Struct.generate_accessors self
end

class Point
  include ::Thrift::Struct, ::Thrift::Struct_Union
  X = 1
  Y = 2
  Z = 3

  FIELDS = {
    X => {:type => ::Thrift::Types::DOUBLE, :name => 'x'},
    Y => {:type => ::Thrift::Types::DOUBLE, :name => 'y'},
    Z => {:type => ::Thrift::Types::DOUBLE, :name => 'z'}
  }

  def struct_fields; FIELDS; end

  def validate
    raise ::Thrift::ProtocolException.new(::Thrift::ProtocolException::UNKNOWN, 'Required field x is unset!') unless @x
    raise ::Thrift::ProtocolException.new(::Thrift::ProtocolException::UNKNOWN, 'Required field y is unset!') unless @y
    raise ::Thrift::ProtocolException.new(::Thrift::ProtocolException::UNKNOWN, 'Required field z is unset!') unless @z
  end

  ::Thrift::Struct.generate_accessors self
end

class InvalidOperation < ::Thrift::Exception
  include ::Thrift::Struct, ::Thrift::Struct_Union
  def initialize(message=nil)
    super()
    self.why = message
  end

  def message; why end

  WHY = 1

  FIELDS = {
    WHY => {:type => ::Thrift::Types::STRING, :name => 'why'}
  }

  def struct_fields; FIELDS; end

  def validate
  end

  ::Thrift::Struct.generate_accessors self
end

