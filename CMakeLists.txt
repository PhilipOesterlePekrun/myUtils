cmake_minimum_required(VERSION 3.25)
project(myUtils)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set default install prefix if not provided by the user
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # Set install prefix next to the build directory
    get_filename_component(_default_prefix "${CMAKE_BINARY_DIR}/../install" ABSOLUTE)
    set(CMAKE_INSTALL_PREFIX "${_default_prefix}" CACHE PATH "Install path prefix" FORCE)
endif()


# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)


# Sources (optional for now)
file(GLOB_RECURSE myUtils_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp"
)

# Add the library
add_library(myUtils ${myUtils_SOURCES})

# Include directory (public headers live in src/)
target_include_directories(myUtils PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)


# Create executable for testing/demo
add_executable(myUtils_Test test/Test_Main.cpp)
target_link_libraries(myUtils_Test PRIVATE myUtils)

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


# Only if installing with tests (not necessary usually)
#install(DIRECTORY test/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/myUtils/test
#        FILES_MATCHING PATTERN "*.hpp")


# Export target info for downstream usage
install(EXPORT myUtilsTargets
    FILE myUtilsTargets.cmake
    NAMESPACE myUtils::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/myUtils
)
