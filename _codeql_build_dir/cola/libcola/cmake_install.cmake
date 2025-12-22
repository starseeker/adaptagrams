# Install script for directory: /home/runner/work/adaptagrams/adaptagrams/cola/libcola

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/runner/work/adaptagrams/adaptagrams/_codeql_build_dir/libcola.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libcola" TYPE FILE FILES
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/box.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/cc_clustercontainmentconstraints.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/cc_nonoverlapconstraints.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/cluster.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/cola_log.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/cola.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/commondefs.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/compound_constraints.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/conjugate_gradient.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/connected_components.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/convex_hull.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/exceptions.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/gradient_projection.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/output_svg.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/pseudorandom.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/shapepair.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/shortest_paths.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/sparse_matrix.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/straightener.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/unused.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcola.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcola.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcola.so"
         RPATH "/usr/local/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/runner/work/adaptagrams/adaptagrams/_codeql_build_dir/libcola.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcola.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcola.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcola.so"
         OLD_RPATH "/home/runner/work/adaptagrams/adaptagrams/_codeql_build_dir:"
         NEW_RPATH "/usr/local/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcola.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libcola" TYPE FILE FILES
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/box.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/cc_clustercontainmentconstraints.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/cc_nonoverlapconstraints.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/cluster.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/cola_log.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/cola.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/commondefs.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/compound_constraints.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/conjugate_gradient.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/connected_components.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/convex_hull.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/exceptions.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/gradient_projection.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/output_svg.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/pseudorandom.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/shapepair.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/shortest_paths.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/sparse_matrix.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/straightener.h"
    "/home/runner/work/adaptagrams/adaptagrams/cola/libcola/unused.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/runner/work/adaptagrams/adaptagrams/_codeql_build_dir/cola/libcola/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
