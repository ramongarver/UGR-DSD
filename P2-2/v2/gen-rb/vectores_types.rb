#
# Autogenerated by Thrift Compiler (0.13.0)
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#

require 'thrift'

class InvalidOperation < ::Thrift::Exception; end

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

