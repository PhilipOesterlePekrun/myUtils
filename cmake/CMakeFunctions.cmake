include(GNUInstallDirs)

# This function intentionally does nothing.
# It ignores all arguments passed to it.
function(commentBlock)
endfunction()

# This function creates the target with the necessary includes; propagates into subdirectories
function(create_target_from_dir target dir)
  get_filename_component(root "${PROJECT_SOURCE_DIR}/${dir}" ABSOLUTE)

  file(GLOB_RECURSE CONFIGURE_DEPENDS src
    "${CMAKE_CURRENT_SOURCE_DIR}/${dir}*.cpp"
  )
  file(GLOB_RECURSE CONFIGURE_DEPENDS hdr
    "${CMAKE_CURRENT_SOURCE_DIR}/${dir}*.hpp"
  )

  list(FILTER src EXCLUDE REGEX ".*/_EXCLUDE_.*")
  list(FILTER hdr EXCLUDE REGEX ".*/_EXCLUDE_.*")
  
  list(LENGTH hdr nhdr)
  message(STATUS "${target}: root='${root}', nhdr=${nhdr}")
  
  # collect all header directories under this module
  set(inc_dirs "${root}")
  foreach(h IN LISTS hdr)
    get_filename_component(d "${h}" DIRECTORY)
    list(APPEND inc_dirs "${d}")
  endforeach()
  list(REMOVE_DUPLICATES inc_dirs)

  list(LENGTH src nsrc)
  if(nsrc EQUAL 0)
    add_library(${target} INTERFACE)
    target_sources(${target} INTERFACE ${hdr})
    target_include_directories(${target} INTERFACE
      $<BUILD_INTERFACE:${inc_dirs}>
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )
  else()
    add_library(${target} ${src} ${hdr})
    target_include_directories(${target} PUBLIC
      $<BUILD_INTERFACE:${inc_dirs}>
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )
  endif()
  
  list(LENGTH hdr nhdr)
  message(STATUS "${target}: root='${root}', nhdr=${nhdr}")

  if(nhdr GREATER 0)
    message(STATUS "${target}: installing headers")
    install(FILES ${hdr} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
  endif()
endfunction()
