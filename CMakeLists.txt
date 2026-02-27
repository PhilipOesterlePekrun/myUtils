cmake_minimum_required(VERSION 3.25)
project(myUtils)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(CMakeFunctions)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)

create_target_from_dir(Core "Core/")

create_target_from_dir(Db "Db/")

create_target_from_dir(NumMethods "NumMethods/")
create_target_from_dir(Vis "Vis/")

# Add the library
add_library(myUtils INTERFACE)
target_link_libraries(myUtils INTERFACE Core Db NumMethods Vis)

# Top level mu.hpp
target_include_directories(myUtils INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_sources(myUtils INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/mu.hpp>
)

# Install library target
install(TARGETS myUtils
    EXPORT myUtilsTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install all .hpp files from src/ EXCEPT myUtils.hpp into include/myUtils/
install(DIRECTORY src/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/myUtils
        FILES_MATCHING PATTERN "*.hpp"
                       PATTERN "myUtils.hpp" EXCLUDE)

# Install myUtils.hpp to include/ directly
install(FILES src/myUtils.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export target info for downstream usage
install(EXPORT myUtilsTargets
    FILE myUtilsTargets.cmake
    NAMESPACE myUtils::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myUtils
)

# --- Self-include ---
#include_directories(
#  "src"
#  "src/Db"
#)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/myUtilsConfig.cmake"
"
include(\"\${CMAKE_CURRENT_LIST_DIR}/myUtilsTargets.cmake\")
")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/myUtilsConfig.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myUtils
)

# Create test executable
add_executable(test
  test/Test_Main.cpp
  test/Test1.cpp
  )
target_link_libraries(test myUtils)
