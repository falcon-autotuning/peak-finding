find_package(falcon-core CONFIG REQUIRED)
find_package(falcon-typing CONFIG REQUIRED)

# FFI wrapper shared library: coulomb-peak-wrapper
add_library(coulomb-peak-wrapper SHARED
  coulomb-peak-wrapper.cpp
)

set_target_properties(coulomb-peak-wrapper PROPERTIES
  PREFIX ""
  OUTPUT_NAME "coulomb-peak-wrapper"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build"
)

target_include_directories(coulomb-peak-wrapper
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(coulomb-peak-wrapper
  PRIVATE
    peak-finding
    falcon-core::falcon-core
    falcon::falcon-typing
)

set_target_properties(
  coulomb-peak-wrapper
    PROPERTIES
      POSITION_INDEPENDENT_CODE ON
)

