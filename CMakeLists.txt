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

# BINARY SETUP

add_executable(prog
    src/main.c
    src/ppm.c
    src/ray.c
    src/raycast.c
    src/scene.c
    src/scene_parser.c
    src/collision.c
)

target_compile_options(prog PRIVATE ${COMMON_COMPILE_FLAGS})

target_include_directories(prog PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(prog PRIVATE m)

# TEST SETUP

add_executable(test_runner
    tests/test_runner.c
    tests/test_image.c
    tests/test_scene.c
    tests/test_vec3.c
    tests/test_camera.c
    tests/test_ray.c
    tests/test_collision.c
    src/ppm.c
    src/ray.c
    src/raycast.c
    src/scene.c
    src/scene_parser.c
    src/collision.c
)

target_compile_options(test_runner PRIVATE ${COMMON_COMPILE_FLAGS})

target_include_directories(test_runner PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(test_runner PRIVATE unity m)

add_custom_target(run_test test_runner
    DEPENDS $<TARGET_FILE:test_runner>
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running unit tests :"
)

add_custom_command(TARGET test_runner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${PROJECT_SOURCE_DIR}/tests/test_scenes
        $<TARGET_FILE_DIR:test_runner>/test_scenes
    COMMENT "Copying test data files for test_runner"
)

add_test(NAME main_test COMMAND test_runner)
