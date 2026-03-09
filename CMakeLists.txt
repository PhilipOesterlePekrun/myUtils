cmake_minimum_required(VERSION 3.25)
project(myUtils)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(CMakeFunctions)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)

set(SRC_ROOT "${CMAKE_CURRENT_LIST_DIR}/src")
message(STATUS "SRC_ROOT=${SRC_ROOT}")
if(NOT IS_DIRECTORY "${SRC_ROOT}")
  message(FATAL_ERROR "SRC_ROOT does not exist: '${SRC_ROOT}'")
endif()

file(GLOB_RECURSE MYUTILS_CPP CONFIGURE_DEPENDS
  "${SRC_ROOT}/*.cpp"
)

list(FILTER MYUTILS_CPP EXCLUDE REGEX ".*/_EXCLUDE_.*")
list(FILTER MYUTILS_CPP EXCLUDE REGEX ".*/_ArchiveAndDeprecated/.*")

add_library(myUtils ${MYUTILS_CPP})

# Build-tree include root (adjust if your compilation needs something else)
target_include_directories(myUtils PUBLIC
  $<BUILD_INTERFACE:${SRC_ROOT}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Install headers (*.hpp) flat into <prefix>/include/
file(GLOB_RECURSE MYUTILS_HPP CONFIGURE_DEPENDS
  "${SRC_ROOT}/*.hpp"
)
list(FILTER MYUTILS_HPP EXCLUDE REGEX ".*/_EXCLUDE_.*")

set(MYUTILS_INCLUDE_DIRS "${SRC_ROOT}")
foreach(hdr IN LISTS MYUTILS_HPP)
  get_filename_component(dir "${hdr}" DIRECTORY)
  list(APPEND MYUTILS_INCLUDE_DIRS "${dir}")
endforeach()
list(REMOVE_DUPLICATES MYUTILS_INCLUDE_DIRS)

target_include_directories(myUtils PUBLIC
  $<BUILD_INTERFACE:${MYUTILS_INCLUDE_DIRS}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


# SFML
if(SFML_ROOT)
  list(PREPEND CMAKE_PREFIX_PATH "${SFML_ROOT}")

  find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window System)

  target_link_libraries(myUtils PUBLIC
    SFML::Graphics
    SFML::Window
    SFML::System
  )
endif()


# Install the library
install(TARGETS myUtils EXPORT myUtilsTargets)
install(EXPORT myUtilsTargets DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myUtils)
install(FILES ${MYUTILS_HPP} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


# Create test executable
add_executable(test
  test/Test_Main.cpp
  test/Test1.cpp
  )
target_link_libraries(test myUtils)
