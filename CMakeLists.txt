# libtctl CMakeLists.txt
# ========================

project(libtclt)
cmake_minimum_required(VERSION 2.8)

# CMake Configuration
# ------------------
set(CMAKE_MODULE_PATH ${CMAME_MODULE_PATH} ${CMAKE_SOURCE_DIR}/util/cmake/Modules/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(${CMAKE_SYSTEM_NAME} True)

include(${CMAKE_SOURCE_DIR}/CMakeLists.txt.local OPTIONAL)

# CMake global options
# ------------------
# None at the moment

# Global Packages search
# ------------------
find_package(Yajl REQUIRED)

# Global CPP definitions
add_definitions(-D${CMAKE_SYSTEM_NAME})

# Global include directories
# ------------------
include_directories(${CMAKE_HOME_DIRECTORY}/include)
include_directories(${YAJL_INCLUDE_DIR})

# Portable source files
# ------------------
set(SOURCES_LIST
  ${CMAKE_SOURCE_DIR}/tclt.c
  ${CMAKE_SOURCE_DIR}/json_parse.c
)

# OS families specific things
# ---------------------------
if(UNIX)
	# Unix specific include directories
	# ------------------
	include_directories(/usr/include/)

	# Unix specific definitions
	# ------------------
  	add_definitions(-DUnix)

	# Unix specific source files
	# ------------------
	set(SOURCES_LIST ${SOURCES_LIST}
	  )
endif()

if (Windows)
	# CMake windows Configuration
	# ------------------
	set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})
  	add_definitions(-DWindows)

	# Windows source files
	# ------------------
	set(HEADERS_LIST 
	  )
	set(SOURCES_LIST ${SOURCES_LIST} ${HEADERS_LIST}
	  )
endif()

# OS specific things
# ------------------
if(Linux)
        set(CMAKE_SYSTEM_INCLUDE_PATH
                ${CMAKE_SYSTEM_INCLUDE_PATH} /usr/local/include)

	# Linux specific Options
	# ------------------
        option(ENABLE_BSDCOMPAT "Enable the use of the libbsd" OFF)

	# Linux specific package search
	# ------------------
	if (ENABLE_BSDCOMPAT)
                find_package(Bsd)
	endif()

	# Linux specific definitions
	# ------------------
	add_definitions(-D_GNU_SOURCE)
	add_definitions(-DHAVE_SETRESXID)
        if (ENABLE_BSDCOMPAT AND BSD_FOUND)
		add_definitions(-DHAVE_BSD_COMPAT)
	endif()

        # Linux specifig include directories
	# ----------------------------------
	include_directories(/usr/local/include)
        if (ENABLE_BSDCOMPAT AND BSD_FOUND)
                include_directories(${BSD_INCLUDE_DIRS})
	endif()
endif()

if (OpenBSD)
        set(CMAKE_SYSTEM_INCLUDE_PATH
                ${CMAKE_SYSTEM_INCLUDE_PATH} /usr/local/include)
	include_directories(/usr/local/include)
	add_definitions(-DHAVE_SETPROCTITLE)
	add_definitions(-DHAVE_SETRESXID)
endif()

if (NetBSD)
        set(CMAKE_SYSTEM_INCLUDE_PATH
                ${CMAKE_SYSTEM_INCLUDE_PATH} /usr/pkg/include)
	include_directories(/usr/pkg/include)
	add_definitions(-DHAVE_SETPROCTITLE)
endif()

if (FreeBSD)
        set(CMAKE_SYSTEM_INCLUDE_PATH
                ${CMAKE_SYSTEM_INCLUDE_PATH} /usr/local/include)
	include_directories(/usr/local/include)
	add_definitions(-DHAVE_SETPROCTITLE)
	add_definitions(-DHAVE_SETRESXID)
endif()

if (Darwin)
	# Darwin specific include directories (macport)
	# ------------------
        set(CMAKE_SYSTEM_INCLUDE_PATH
                ${CMAKE_SYSTEM_INCLUDE_PATH} /opt/local/include)
	include_directories(/opt/local/include)

	# Darwin specific definitions
	# ------------------
endif()

# Library definitons
# ------------------
add_library(tclt SHARED
  ${SOURCES_LIST})


# Global linked libraries
# ------------------

target_link_libraries(tclt
        ${YAJL_LIBRARIES}
)

# Linux linked libraries
# ------------------------
if (ENABLE_BSDCOMPAT AND BSD_FOUND)
  target_link_libraries(tclt ${BSD_LIBRARIES})
endif()

# Windows linked libraries
# ------------------------

if (Windows)
    target_link_libraries(tclt Ws2_32.lib)
endif()

include(${CMAKE_SOURCE_DIR}/CMakeLists.txt.link.local OPTIONAL)
