set(
    UNITTEST_SOURCE_FILES
    TableColumnTest.cpp
    TableTest.cpp

    gtest_main.cpp
)

# compile testable library which gets linked against gtest
add_library(
    unittests
    EXCLUDE_FROM_ALL
    STATIC
    ${UNITTEST_SOURCE_FILES}
)
target_include_directories(
    unittests
    PRIVATE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/unittest ${CMAKE_SOURCE_DIR}/external/gtest/include
)
# target_link_libraries(
#     unittests
# )
