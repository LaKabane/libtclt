# Copyright (c) 2012 Antoine Marandon <ntnrmrndn AT gmail DOT com>

# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.

# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.


require 'rubygems'
require 'ffi'

module Rtclt
  class Peer
    attr_accessor :name
    attr_accessor :key
    attr_accessor :ip
  end

  def Rtclt.test
    Tclt::tclt_init
    puts Tclt::tclt_get_version
    Tclt::tclt_destroy
    test = Tclt::Peer.new
    test[:name] = FFI::MemoryPointer.from_string "Name..."
    test[:key] = FFI::MemoryPointer.from_string "key :)"
    test[:ip] = FFI::MemoryPointer.from_string "127.0.0.1"
    puts test[:ip].read_string
    puts Tclt::tclt_add_peer(test).read_string
    Rtclt::set_callback_add_peer do |peer|
      puts peer.name
    end
    Rtclt::_add_peer_callback test, 'lol'
  end

  def Rtclt.init
    Tclt::tclt_init
    Tclt::tclt_set_callback_command Tclt::ADD_PEER_CMD, Rtclt::_add_peer_callback
    Tclt::tclt_set_callback_command Tclt::DELETE_PEER_CMD, Rtclt::_del_peer_callback
    Tclt::tclt_set_callback_command Tclt::EDIT_PEER_CMD, Rtclt::_edit_peer_callback
    Tclt::tclt_set_callback_command Tclt::ADD_LOG_CMD, Rtclt::_add_log_callback
  end

  def Rtclt.destroy
    Tclt::tclt_destroy
  end

  def Rtclt.get_version
    return Tclt::tclt_get_version
  end

  def Rtclt.set_callback_add_peer(&callback)
    if callback.respond_to?("call")
      @@callback_add_peer = callback;
    else
      puts "ERROR: callback is not callable"
    end
  end

  def Rtclt.set_callback_del_peer(&callback)
    if callback.respond_to?("call")
      @@callback_del_peer = callback;
    else
      puts "ERROR: callback is not callable"
    end
  end

  def Rtclt.set_callback_edit_peer(&callback)
 if callback.respond_to?("call")
      @@callback_edit_peer = callback;
    else
      puts "ERROR: callback is not callable"
    end
  end

  def Rtclt.set_callback_add_log(&callback)
    if callback.respond_to?("call")
      @@callback_add_log = callback;
    else
      puts "ERROR: callback is not callable"
    end
  end

  def Rtclt.delete_peer(peer)
    return Tclt::tclt_delte_peer(peer.key).read_string
  end

  def Rtclt.parse(data)
    return Tclt::tclt_dispatch_command(data, 0)
  end

# -- Private stuff -- not intended to be accessed from the outside

  module Tclt
    extend FFI::Library
    ffi_lib 'tclt'

    ADD_PEER_CMD = "AddContact"
    DELETE_PEER_CMD = "DeleteContact"
    EDIT_PEER_CMD = "EditContact"
    ADD_LOG_CMD = "AddLog"

    attach_function :tclt_init, [], :void
    attach_function :tclt_destroy, [], :void
    attach_function :tclt_get_version, [], :int
    callback :tclt_callback_command_type, [:pointer, :pointer], :int
    attach_function :tclt_set_callback_command, [:string, :tclt_callback_command_type], :int
    attach_function :tclt_get_callback_command, [], :pointer

    #peer related
    class Peer < FFI::Struct
      layout  :name, :pointer,
      :key, :pointer,
      :ip, :pointer
    end
    attach_function :tclt_add_peer, [:pointer], :pointer
    attach_function :tclt_add_list_of_peers, [:pointer, :uint], :pointer
    attach_function :tclt_add_connection, [], :pointer
    attach_function :tclt_add_tunnel, [], :void

    attach_function :tclt_delete_connection, [], :void
    attach_function :tclt_stop_tunnel, [], :void
    attach_function :tclt_delete_peer, [:string], :pointer
    attach_function :tclt_clear_peers, [], :void

    attach_function :tclt_edit_peer, [], :void

    #Group related
    attach_function :tclt_create_group, [], :void
    attach_function :tclt_destroy_group, [], :void
    attach_function :tclt_add_peer_to_group, [], :void
    attach_function :tclt_clear_group, [], :void

    #Administration related
    attach_function :tclt_edit_config, [], :void
    attach_function :tclt_add_public_key, [], :void
    attach_function :tclt_add_key_for_peer, [], :void
    attach_function :tclt_add_key_for_client, [], :void
    #attach_function :tclt_add_log, [:string], :pointer for tNETacle core

    #Parsing
    attach_function :tclt_dispatch_command, [:string, :pointer], :int
  end

  @@callback_add_peer = nil
  @@callback_del_peer = nil
  @@callback_edit_peer = nil
  @@callback_add_log = nil

  def Rtclt._add_peer_callback(peer, internal)
    if !@@callback_add_peer.nil?
      @@callback_add_peer.call Rtclt::_Tclt_peer_to_Rtclt peer
    end
  end

  def Rtclt._edit_peer_callback(external, internal)
    if !@@callback_add_log.nil?
      @@callback_edit_peer.call external.read_string
    end
  end

  def Rtclt._del_peer_callback(peer, internal)
    if !@@callback_del_peer.nil?
      @@callback_del_peer.call Rtclt::_Tclt_peer_to_Rtclt peer
    end
  end

  def Rtclt._edit_peer_callback(peer, internal)
    if !@@callback_edit_peer.nil?
      @@callback_edit_peer.call Rtclt::_Tclt_peer_to_Rtclt peer
    end
  end

  def Rtclt._Tclt_peer_to_Rtclt(peer)
    rPeer = Rtclt::Peer.new
    rPeer.name = peer[:name].read_string
    rPeer.key = peer[:key].read_string
    rPeer.ip = peer[:ip].read_string
    return rPeer
  end

end
Rtclt::test
