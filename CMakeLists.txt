cmake_minimum_required(VERSION 3.10.2)

# set project name and version
project(libtabularasa VERSION 0.1.1 LANGUAGES CXX)

# require compiler features
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# require external packages
find_package(Threads REQUIRED)
# find_package(PkgConfig REQUIRED)
# find_package(Qt5 5.5 COMPONENTS Core Xml REQUIRED)

# import directory names used on GNU systems
include(GNUInstallDirs)

# import CMakeLists.txt from subdirectory
add_subdirectory(tabularasa)
add_subdirectory(unittest)

set(
    WITH_UNITTESTS FALSE CACHE
    BOOL "Add target gtest for compiling unittests, requires GTest sources in devel/include/gtest"
)

if(WITH_UNITTESTS)
add_executable(
    gtest
    EXCLUDE_FROM_ALL
    ${LIBRARY_SOURCE_FILES}
    external/gtest/src/gtest-all.cc
)

target_include_directories(
    gtest
    PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/external/gtest ${CMAKE_SOURCE_DIR}/external/gtest/include
)

target_link_libraries(
    gtest
    -Wl,--whole-archive
    unittests
    testable
    -Wl,--no-whole-archive
    Threads::Threads
    -coverage
)

enable_testing()
add_test(gtest gtest)
endif(WITH_UNITTESTS)
