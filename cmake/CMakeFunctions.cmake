# This function intentionally does nothing.
# It ignores all arguments passed to it.
function(commentBlock)
endfunction()

# This function creates the target with the necessary includes; propagates into subdirectories
function(create_target_from_dir target dir)
  get_filename_component(root "${dir}" ABSOLUTE)

  file(GLOB_RECURSE CONFIGURE_DEPENDS src
    "${root}/*.c" "${root}/*.cpp"
  )
  file(GLOB_RECURSE CONFIGURE_DEPENDS hdr
    "${root}/*.h" "${root}/*.hpp"
  )

  list(FILTER src EXCLUDE REGEX ".*/_EXCLUDE_.*")
  list(FILTER hdr EXCLUDE REGEX ".*/_EXCLUDE_.*")

  set(inc_dirs "")
  foreach(h IN LISTS hdr)
    get_filename_component(d "${h}" DIRECTORY)
    list(APPEND inc_dirs "${d}")
  endforeach()
  list(REMOVE_DUPLICATES inc_dirs)

  list(LENGTH src nsrc)
  if(nsrc EQUAL 0)
    add_library(${target} INTERFACE)
    target_sources(${target} INTERFACE ${hdr})
    target_include_directories(${target} INTERFACE ${inc_dirs})
    target_compile_features(${target} INTERFACE cxx_std_17)
  else()
    add_library(${target} ${src} ${hdr})
    target_include_directories(${target} PUBLIC ${inc_dirs})
    target_compile_features(${target} PUBLIC cxx_std_17)
  endif()
endfunction()
