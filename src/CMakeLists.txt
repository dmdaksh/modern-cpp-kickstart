# Source files for the tutorial and core library

# Core library (reusable for projects)
add_library(core_lib
    core/utils.cpp
)

target_include_directories(core_lib PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

# Tutorial library
add_library(tutorial_lib
    tutorial/quest.cpp
    tutorial/basics_quest.cpp
    tutorial/memory_quest.cpp
    tutorial/oop_quest.cpp
    tutorial/templates_quest.cpp
    tutorial/stl_quest.cpp
    tutorial/concurrency_quest.cpp
)

target_include_directories(tutorial_lib PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(tutorial_lib 
    core_lib
)

# Main executable
add_executable(cpp_tutorial
    main.cpp
)

target_link_libraries(cpp_tutorial
    tutorial_lib
    core_lib
)

# Compiler-specific settings for the executable
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(cpp_tutorial PRIVATE 
        -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(cpp_tutorial PRIVATE /W4)
endif()

# Enable additional warnings for development
target_compile_definitions(cpp_tutorial PRIVATE
    $<$<CONFIG:Debug>:DEBUG_BUILD>
    $<$<CONFIG:Release>:RELEASE_BUILD>
)
