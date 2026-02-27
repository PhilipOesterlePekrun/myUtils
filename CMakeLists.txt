cmake_minimum_required(VERSION 3.25)
project(myUtils)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(CMakeFunctions)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)

create_target_from_dir(Core "src/Core/")

create_target_from_dir(Db "src/Db/")

create_target_from_dir(NumMethods "src/NumMethods/")
create_target_from_dir(Vis "src/Vis/")

# Add the library
add_library(myUtils INTERFACE)
target_link_libraries(myUtils INTERFACE Core Db NumMethods Vis)

target_include_directories(myUtils INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>          # <Core/...> in-tree
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>            # <myUtils/...> after install
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/myUtils
  FILES_MATCHING PATTERN "*.hpp"
)

install(TARGETS myUtils Core Db NumMethods Vis
  EXPORT myUtilsTargets
)

install(EXPORT myUtilsTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myUtils
)

include(CMakePackageConfigHelpers)

install(EXPORT myUtilsTargets
  NAMESPACE myUtils::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myUtils
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/myUtilsConfigVersion.cmake"
  VERSION 0.1.0
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/myUtilsConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/myUtilsConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myUtils
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/myUtilsConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/myUtilsConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myUtils
)

# Create test executable
add_executable(test
  test/Test_Main.cpp
  test/Test1.cpp
  )
target_link_libraries(test myUtils)
