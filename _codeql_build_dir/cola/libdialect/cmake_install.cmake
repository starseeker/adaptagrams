# Install script for directory: /home/runner/work/adaptagrams/adaptagrams/cola/libdialect

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/runner/work/adaptagrams/adaptagrams/_codeql_build_dir/libdialect.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libdialect" TYPE FILE FILES
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/aca.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/chains.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/commontypes.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/constraints.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/expansion.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/faces.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/graphs.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/hola.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/io.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/libdialect.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/logging.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/nearalign.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/nodeconfig.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/opts.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/ortho.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/peeling.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/planarise.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/quadaction.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/routing.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/treeplacement.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/trees.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/util.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdialect.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdialect.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdialect.so"
         RPATH "/usr/local/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/runner/work/adaptagrams/adaptagrams/_codeql_build_dir/libdialect.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdialect.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdialect.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdialect.so"
         OLD_RPATH "/home/runner/work/adaptagrams/adaptagrams/_codeql_build_dir:"
         NEW_RPATH "/usr/local/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdialect.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libdialect" TYPE FILE FILES
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/aca.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/chains.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/commontypes.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/constraints.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/expansion.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/faces.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/graphs.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/hola.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/io.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/libdialect.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/logging.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/nearalign.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/nodeconfig.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/opts.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/ortho.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/peeling.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/planarise.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/quadaction.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/routing.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/treeplacement.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/trees.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libdialect/util.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/runner/work/adaptagrams/adaptagrams/_codeql_build_dir/cola/libdialect/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
