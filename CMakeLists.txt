cmake_minimum_required(VERSION 3.27)

project(
    razor
    VERSION 0.1.0
    DESCRIPTION "A short description"
    LANGUAGES CXX
)

# Include utilities
include(cmake/options.cmake)
include(cmake/warning-guard.cmake)
include(cmake/compile-options.cmake)
include(cmake/dependencies.cmake)

# Declare library
add_library(passionfruit_razor)
add_library(passionfruit::razor ALIAS passionfruit_razor)

# Add sources
target_sources(passionfruit_razor PRIVATE
    src/razor.cpp
    src/context.cpp
)

# Add include directory
# warning_guard adds SYSTEM modifier if the project isn't top level
target_include_directories(
    passionfruit_razor ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

# Import export.hpp
target_include_directories(
    passionfruit_razor SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
)

# Include and link dependencies
target_link_libraries(passionfruit_razor
    PUBLIC
        passionfruit::echidna
        passionfruit::seed
)

# Add compile options
add_dev_compile_opts(passionfruit_razor)

# Generate header for export
include(GenerateExportHeader)
generate_export_header(
    passionfruit_razor
    BASE_NAME razor
    EXPORT_FILE_NAME include/razor/export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

# Set properties
set_target_properties(
    passionfruit_razor PROPERTIES
    CXX_VISIBILITY_PRESET "hidden"
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME razor
    OUTPUT_NAME razor
)

# Install rules
if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# Enable testing
if(BUILD_TESTING)
    include(CTest)
    add_subdirectory(tests)
endif()