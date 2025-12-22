# Install script for directory: /home/runner/work/adaptagrams/adaptagrams/cola/libavoid

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/runner/work/adaptagrams/adaptagrams/_codeql_build_dir/libavoid.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libavoid" TYPE FILE FILES
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/actioninfo.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/assertions.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/connectionpin.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/connector.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/connend.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/debug.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/debughandler.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/dllexport.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/geometry.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/geomtypes.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/graph.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/hyperedge.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/hyperedgeimprover.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/hyperedgetree.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/junction.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/libavoid.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/makepath.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/mtst.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/obstacle.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/orthogonal.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/router.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/scanline.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/shape.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/timer.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/vertices.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/viscluster.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/visibility.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/vpsc.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libavoid.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libavoid.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libavoid.so"
         RPATH "/usr/local/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/runner/work/adaptagrams/adaptagrams/_codeql_build_dir/libavoid.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libavoid.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libavoid.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libavoid.so"
         OLD_RPATH "/home/runner/work/adaptagrams/adaptagrams/_codeql_build_dir:"
         NEW_RPATH "/usr/local/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libavoid.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libavoid" TYPE FILE FILES
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/actioninfo.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/assertions.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/connectionpin.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/connector.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/connend.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/debug.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/debughandler.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/dllexport.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/geometry.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/geomtypes.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/graph.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/hyperedge.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/hyperedgeimprover.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/hyperedgetree.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/junction.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/libavoid.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/makepath.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/mtst.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/obstacle.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/orthogonal.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/router.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/scanline.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/shape.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/timer.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/vertices.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/viscluster.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/visibility.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libavoid/vpsc.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/runner/work/adaptagrams/adaptagrams/_codeql_build_dir/cola/libavoid/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
