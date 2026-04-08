cmake_minimum_required(VERSION 3.25)
project(myUtils VERSION 1.0.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(CMakeFunctions)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(SRC_ROOT "${CMAKE_CURRENT_LIST_DIR}/src")

file(GLOB_RECURSE SRC_CPP CONFIGURE_DEPENDS
  "${SRC_ROOT}/*.cpp"
)

list(FILTER SRC_CPP EXCLUDE REGEX ".*/_EXCLUDE_.*")
list(FILTER SRC_CPP EXCLUDE REGEX ".*/_ArchiveAndDeprecated/.*")

add_library(myUtils ${SRC_CPP})

# Build-tree include root (adjust if your compilation needs something else)
target_include_directories(myUtils PUBLIC
  $<BUILD_INTERFACE:${SRC_ROOT}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Install headers (*.hpp) flat into <prefix>/include/
file(GLOB_RECURSE SRC_HPP CONFIGURE_DEPENDS
  "${SRC_ROOT}/*.hpp"
)
list(FILTER SRC_HPP EXCLUDE REGEX ".*/_EXCLUDE_.*")

set(MYUTILS_INCLUDE_DIRS "${SRC_ROOT}")
foreach(hdr IN LISTS SRC_HPP)
  get_filename_component(dir "${hdr}" DIRECTORY)
  list(APPEND MYUTILS_INCLUDE_DIRS "${dir}")
endforeach()
list(REMOVE_DUPLICATES MYUTILS_INCLUDE_DIRS)

target_include_directories(myUtils PUBLIC
  $<BUILD_INTERFACE:${MYUTILS_INCLUDE_DIRS}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# SFML
if(EXISTS "${SRC_ROOT}/Vis") # i.e. not marked as _EXCLUDE
  list(PREPEND CMAKE_PREFIX_PATH "${SFML_ROOT}")
  find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window System)

  target_link_libraries(myUtils PUBLIC
    SFML::Graphics
    SFML::Window
    SFML::System
  )
  
  # Bake in the default location you want downstream projects to use.
  # Prefer the prefix you already pass in.
  set(MYUTILS_BAKED_SFML_ROOT "${SFML_ROOT}")
endif()

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/myUtilsConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/myUtilsConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myUtils
)


# Install the library
install(TARGETS myUtils
  EXPORT myUtilsTargets
)
install(EXPORT myUtilsTargets
  FILE myUtilsTargets.cmake
  NAMESPACE myUtils::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myUtils
)
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/myUtilsConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/myUtilsConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myUtils
)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/myUtilsConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/myUtilsConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/myUtilsConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myUtils
)
install(FILES ${SRC_HPP} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


# Create test executable
set(TEST_ROOT "${CMAKE_CURRENT_LIST_DIR}/test")
file(GLOB_RECURSE TEST_CPP CONFIGURE_DEPENDS
  "${TEST_ROOT}/*.cpp"
)
add_executable(test ${TEST_CPP})
target_link_libraries(test myUtils)
