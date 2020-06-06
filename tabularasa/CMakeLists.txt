set(
    LIBRARY_SOURCE_FILES
    HorizontalAlignment.cpp
    Table.cpp
    TableColumn.cpp
    TableRow.cpp
)

# compile library from the following source files
add_library(
    tabularasa SHARED
    ${LIBRARY_SOURCE_FILES}
)

# add the root of this source tree to the include path
target_include_directories(
    tabularasa
    PRIVATE ${CMAKE_SOURCE_DIR}
)

# link library to other dependend libraries
# target_link_libraries(
#     tabularasa
# )

# set properties on the generated library
set_target_properties(
    tabularasa PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
)

# install library to the target
install(
    TARGETS
    tabularasa
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# generate pkg-config file
configure_file(
    tabularasa.pc.in
    tabularasa.pc
    @ONLY
)

# install pkg-config file to the target
install(
    FILES
    ${CMAKE_BINARY_DIR}/tabularasa/tabularasa.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

# compile testable library which gets linked against gtest
add_library(
    testable
    EXCLUDE_FROM_ALL
    STATIC
    ${LIBRARY_SOURCE_FILES}
)
target_include_directories(
    testable
    PRIVATE ${CMAKE_SOURCE_DIR}
)
target_compile_options(
    testable
    PRIVATE
    -O2 -g -fprofile-arcs -ftest-coverage -coverage
)
# target_link_libraries(
#     testable
# )
