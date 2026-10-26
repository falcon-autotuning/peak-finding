cmake_minimum_required(VERSION 3.20)
project(
  peak-finding
  VERSION 1.0.0
  DESCRIPTION "Contains falcon algorithms for analysing peaks in experimental data"
  HOMEPAGE_URL "https://github.com/falcon-autotuning/peak-finding"
  LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build Options
option(BUILD_TESTS "Build tests" OFF)

# Performance options
option(USE_CCACHE "Enable ccache or sccache if available" ON)

# Windows-specific definitions
if(WIN32)
  add_compile_definitions(NOMINMAX)
  add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# Try to auto-detect a compiler launcher (prefer sccache if present)
if(USE_CCACHE)
  find_program(SCCACHE_PROGRAM sccache)
  if(SCCACHE_PROGRAM)
    message(STATUS "Using sccache: ${SCCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER ${SCCACHE_PROGRAM})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${SCCACHE_PROGRAM})
  else()
    find_program(CCACHE_PROGRAM ccache)
    if(CCACHE_PROGRAM)
      message(STATUS "Using ccache: ${CCACHE_PROGRAM}")
      set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
      set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
    else()
      message(
        STATUS "No ccache/sccache found (fine, builds will just be normal).")
    endif()
  endif()
endif()

#find_package(falcon-typing CONFIG REQUIRED)

# Core library
add_library(
  peak-finding
    SHARED
      src/peak-finding.cpp
)

set_target_properties(
  peak-finding
    PROPERTIES
      POSITION_INDEPENDENT_CODE ON
)

#target_compile_definitions(peak-finding)

# Add version information
#target_compile_definitions(peak-finding)
target_link_libraries(
  peak-finding
#  PUBLIC
#    falcon-typing::falcon-typing
)

target_include_directories(
  peak-finding
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Tests
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# ── Install ───────────────────────────────────────────────────────────────────
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS peak-finding
  EXPORT peak-finding-targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  DIRECTORY include/peak-finding
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING
    PATTERN "*.hpp"
    PATTERN "*.h"
)

install(EXPORT peak-finding-targets
  FILE      peak-finding-targets.cmake
  NAMESPACE peak-finding::
  DESTINATION ${CMAKE_INSTALL_DATADIR}/peak-finding
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/peak-finding-config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/peak-finding-config-version.cmake"
  DESTINATION ${CMAKE_INSTALL_DATADIR}/peak-finding
)
