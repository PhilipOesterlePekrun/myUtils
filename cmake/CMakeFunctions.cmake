# This function intentionally does nothing.
# It ignores all arguments passed to it.
function(commentBlock)
endfunction()

# This function creates the target with the necessary includes; propagates into subdirectories
function(create_target_from_dir target dir)
  get_filename_component(root "${dir}" ABSOLUTE)

  file(GLOB_RECURSE CONFIGURE_DEPENDS src "${root}/*.cpp")
  file(GLOB_RECURSE CONFIGURE_DEPENDS hdr "${root}/*.hpp")

  list(FILTER src EXCLUDE REGEX ".*/_EXCLUDE_.*")
  list(FILTER hdr EXCLUDE REGEX ".*/_EXCLUDE_.*")

  set(build_root "${CMAKE_CURRENT_SOURCE_DIR}/src")

  list(LENGTH src nsrc)
  if(nsrc EQUAL 0)
    add_library(${target} INTERFACE)
    target_sources(${target} INTERFACE ${hdr})
    target_include_directories(${target} INTERFACE
      $<BUILD_INTERFACE:${build_root}>              # enables <Core/...> in-tree
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>  # enables <myUtils/...> after install
    )
  else()
    add_library(${target} ${src} ${hdr})
    target_include_directories(${target} PUBLIC
      $<BUILD_INTERFACE:${build_root}>
      $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )
  endif()
endfunction()
