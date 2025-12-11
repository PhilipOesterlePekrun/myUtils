function(commentBlock)
    # This function intentionally does nothing.
    # It ignores all arguments passed to it.
endfunction()

function(createTargetFromDir TARGET_NAME DIR_PATH)
    # 1. Resolve the absolute path of the directory
    get_filename_component(FULL_DIR_PATH "${DIR_PATH}" ABSOLUTE)

    # 2. Collect all source and header files
    # Note: We use GLOB here for convenience, but if you add files later, 
    # you may need to re-run CMake manually.
    file(GLOB ALL_SOURCES "${FULL_DIR_PATH}/*.cpp" "${FULL_DIR_PATH}/*.c")
    file(GLOB ALL_HEADERS "${FULL_DIR_PATH}/*.hpp" "${FULL_DIR_PATH}/*.h")

    set(SOURCES "")
    foreach(file ${ALL_SRC_FILES})
        get_filename_component(fname ${file} NAME)
        if(NOT fname MATCHES "^_EXCLUDE.*")
            list(APPEND SRC_FILES ${file})
        endif()
    endforeach()
    
    set(HEADERS "")
    foreach(file ${ALL_SRC_FILES})
        get_filename_component(fname ${file} NAME)
        if(NOT fname MATCHES "^_EXCLUDE.*")
            list(APPEND SRC_FILES ${file})
        endif()
    endforeach()

    # 3. Handle Header-Only libraries vs Standard libraries
    list(LENGTH SOURCES GEN_SRC_LEN)

    if(GEN_SRC_LEN EQUAL 0)
        # If no .cpp files found, create an INTERFACE library (header-only)
        message(STATUS "Creating header-only target: ${TARGET_NAME}")
        add_library(${TARGET_NAME} INTERFACE)
        
        # Propagate the include directory
        target_include_directories(${TARGET_NAME} INTERFACE 
            $<BUILD_INTERFACE:${FULL_DIR_PATH}>
        )
        
        # Attach headers to the target so they show up in IDEs (VS, Xcode)
        # This requires a dummy interface target property in older CMake, 
        # but serves as a hint here.
        target_sources(${TARGET_NAME} INTERFACE ${HEADERS})

    else()
        # Create a standard library (STATIC or SHARED based on BUILD_SHARED_LIBS)
        message(STATUS "Creating library target: ${TARGET_NAME}")
        add_library(${TARGET_NAME} ${SOURCES} ${HEADERS})

        # 4. Setup Include Directories
        # PUBLIC means: 
        #  - I need this dir to build myself.
        #  - Anyone linking to me gets this dir added to their include path automatically.
        target_include_directories(${TARGET_NAME} PUBLIC 
            $<BUILD_INTERFACE:${FULL_DIR_PATH}>
        )
    endif()
    
    # Optional: Enable C++ standard features (e.g., C++17)
    if(NOT GEN_SRC_LEN EQUAL 0)
        target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)
    endif()

endfunction()
