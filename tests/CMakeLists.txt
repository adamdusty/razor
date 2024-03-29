cmake_minimum_required(VERSION 3.27)

project(
    razorTests
    LANGUAGES CXX
)

# If test project is built independently, find the project package
if(PROJECT_IS_TOP_LEVEL)
    find_package(razor REQUIRED)
    enable_testing()
endif()

# Get the testing library
include(FetchContent)
FetchContent_Declare(
    snitch
    GIT_REPOSITORY https://github.com/snitch-org/snitch.git
    GIT_TAG        v1.2.4
    GIT_SHALLOW    TRUE
    SYSTEM
)
FetchContent_MakeAvailable(snitch)

# Add test exe
add_executable(razor_tests)

# Add test sources
target_sources(razor_tests PRIVATE
    src/razor_test.cpp
)

# Link libs
target_link_libraries(razor_tests PRIVATE passionfruit::razor passionfruit::echidna snitch::snitch)

# Add test
add_test(NAME razor_tests COMMAND razor_tests)

# Enable test binary to find the DLL if building a shared lib
if(BUILD_SHARED_LIBS)
    set_tests_properties(razor_tests PROPERTIES
        ENVIRONMENT_MODIFICATION
            "PATH=path_list_append:$<TARGET_FILE_DIR:passionfruit::seed>;PATH=path_list_append:$<TARGET_FILE_DIR:passionfruit::razor>;PATH=path_list_append:$<TARGET_FILE_DIR:passionfruit::echidna>;PATH=path_list_append:$<TARGET_FILE_DIR:wgpu>;PATH=path_list_append:$<TARGET_FILE_DIR:snitch::snitch>;PATH=path_list_append:$<TARGET_FILE_DIR:SDL2::SDL2>"
    )
endif()
