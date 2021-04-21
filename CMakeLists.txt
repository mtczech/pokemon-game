cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(final-project-mtczech)

# This tells the compiler to not aggressively optimize and
# to include debugging information so that the debugger
# can properly read what's going on.
set(CMAKE_BUILD_TYPE Debug)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Warning flags
if(MSVC)
    # warning level 3 and all warnings as errors
    add_compile_options(/W3 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wpedantic -Werror)
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.6
)

# Adds Catch2 testing library
FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_library(catch2 INTERFACE)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif()

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.9.1
)

# Adds json parsing library
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_library(json INTERFACE)
    target_include_directories(json INTERFACE ${json_SOURCE_DIR}/single_include)
endif()


get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

list(APPEND CORE_SOURCE_FILES)

list(APPEND SOURCE_FILES    game_data/engine_data.cpp
        pokemon_engine_interface/pokemon_engine_interface.cpp
        data_classes/move.cpp ${CORE_SOURCE_FILES})

list(APPEND TEST_FILES tests/battle_math_tests.cpp
        tests/data_retrieval_tests.cpp
        tests/pokemon_data_tests.cpp
        tests/strategy_output_tests.cpp)

ci_make_app(
        APP_NAME        pokemon-engine-run
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         main/engine_main.cpp ${SOURCE_FILES}
        INCLUDES        include
        LIBRARIES       json
)

target_link_libraries(pokemon-engine-run json)

ci_make_app(
        APP_NAME        pokemon-engine-test
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         tests/test_main.cc ${SOURCE_FILES} ${TEST_FILES}
        INCLUDES        include
        LIBRARIES       catch2 json
)

target_link_libraries(pokemon-engine-test catch2 json)

if(MSVC)
    set_property(TARGET pokemon-engine-test APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:CONSOLE")
endif()