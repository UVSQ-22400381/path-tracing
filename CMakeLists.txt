cmake_minimum_required(VERSION 3.15)
project(pathtracer VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

enable_testing()

set(COMMON_COMPILE_FLAGS
    $<$<CONFIG:Debug>:-Wall -Wextra -g>
    $<$<CONFIG:Release>:-Wall -Wextra -O3 -DNDEBUG>
)

#== TEST SETUP ==#

include(FetchContent)
FetchContent_declare(
    unity
    GIT_REPOSITORY  https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG         v2.6.1
    GIT_SHALLOW     TRUE
    SOURCE_SUBDIR   src
)
FetchContent_MakeAvailable(unity)

add_library(unity STATIC ${unity_SOURCE_DIR}/src/unity.c)
target_include_directories(unity PUBLIC ${unity_SOURCE_DIR}/src)

add_executable(test_runner tests/test_runner.c tests/test_image.c src/ppm.c)
target_compile_options(test_runner PRIVATE ${COMMON_COMPILE_FLAGS})
target_include_directories(test_runner PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(test_runner PRIVATE unity)
add_test(NAME main_test COMMAND test_runner)
