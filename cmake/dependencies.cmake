include(FetchContent)

# echidna
if(NOT TARGET passionfruit::echidna)
    FetchContent_Declare(
        echidna
        GIT_REPOSITORY https://github.com/adamdusty/echidna.git
        GIT_TAG        main
        GIT_SHALLOW    TRUE
        SYSTEM            # Don't include in warnings
        FIND_PACKAGE_ARGS # Use system package if installed
    )
    FetchContent_MakeAvailable(snitch)
endif()

if(NOT TARGET passionfruit::seed)
FetchContent_Declare(
    seed
    GIT_REPOSITORY https://github.com/adamdusty/pf-seed.git
    GIT_TAG        main
    GIT_SHALLOW    TRUE
    SYSTEM            # Don't include in warnings
    FIND_PACKAGE_ARGS # Use system package if installed
)
FetchContent_MakeAvailable(seed)
endif()