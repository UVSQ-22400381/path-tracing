cmake_minimum_required(VERSION 3.15)
project(pathtracer VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(COMMON_COMPILE_FLAGS
    $<$<CONFIG:Debug>:-Wall -Wextra -g>
    $<$<CONFIG:Release>:-Wall -Wextra -03 -DNDEBUG>
)

include_directories(src include)

#== TEST SETUP ==#

include(FetchContent)
FetchContent_declare(
    unity
    GIT_REPOSITORY  https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG         v2.6.1
    GIT_SHALLOW     TRUE
)

FetchContent_GetProperties(unity)
if (NOT unity_POPULATED)
    FetchContent_Populate(unity)
    add_subdirectory(${unity_SOURCE_DIR} ${unity_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(test_runner tests/test_runner.c tests/test_image.c tests/test_vec3.c src/ppm.c)
target_include_directories(test_runner PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(test_runner PRIVATE unity)

add_custom_target(test test_runner
    DEPENDS $<TARGET_FILE:test_runner>
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running unit tests :"
)
