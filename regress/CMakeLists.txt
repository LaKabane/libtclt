#
# Copyright (c) 2012 Florent Tribouilloy <tribou_f AT epitech DOT net>
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
# libtclt regression tests CMakeLists.txt
# =========================================


project(libtclt-regression)
cmake_minimum_required(VERSION 2.8)

set(${CMAKE_SYSTEM_NAME} True)

set(REGRESS_SOURCE_DIR ${CMAKE_SOURCE_DIR})

enable_testing()
set(TCLT tclt) 

message(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

if(UNIX)
  link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif(UNIX)
if (Windows)
  link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Debug)
endif(Windows)

set (ALL_TESTS
  tclt_get_version
  tclt_init
  tclt_destroy
#  tclt_add_connection
#  tclt_add_key_for_client
#  tclt_add_key_for_peer
#  tclt_add_list_of_peers
#  tclt_add_peer
#  tclt_add_peer_to_group
#  tclt_add_public_key
#  tclt_add_tunnel
#  tclt_clear_group
#  tclt_clear_peers
#  tclt_create_group
#  tclt_delete_connection
#  tclt_delete_peer
#  tclt_destroy
#  tclt_destroy_group
#  tclt_edit_config
#  tclt_edit_peer
#  tclt_get_versin
#  tclt_init
#  tclt_stop_tunnel
)

foreach(REGRESS_NAME ${ALL_TESTS})
    add_executable(${REGRESS_NAME} ${REGRESS_SOURCE_DIR}/regress/${REGRESS_NAME}.c)
    target_link_libraries(${REGRESS_NAME} ${TCLT})
    add_test(${REGRESS_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${REGRESS_NAME})
endforeach(REGRESS_NAME)
