cmake_minimum_required(VERSION 2.8)
project(Lithium)



# Include header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# Set header and source files
set(HEADER_FILES
    ${CMAKE_SOURCE_DIR}/include/Definitions.h
    ${CMAKE_SOURCE_DIR}/include/util/Util.h
    ${CMAKE_SOURCE_DIR}/include/server/Server.h
)

set(SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/Util.cpp
    ${CMAKE_SOURCE_DIR}/src/Server.cpp
)

add_library(lithium ${SOURCE_FILES} ${HEADER_FILES})

# Set target properties to output artifacts to bin directory
set_target_properties(lithium
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

# Set executable name
set(EXECUTABLE LithiumServer)

# Create binary
add_executable(${EXECUTABLE} ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Set target properties to output artifacts to bin directory
set_target_properties(${EXECUTABLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(${EXECUTABLE} lithium)

# Link against uuid library on *NIX platforms
if(UNIX AND NOT APPLE)
    target_link_libraries(${EXECUTABLE} uuid)
endif()



# GTest
set(UNIT_TEST_EXECUTABLE runUnitTests)
add_subdirectory(lib/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/test/test_Server.cpp
)

add_executable(${UNIT_TEST_EXECUTABLE} ${TEST_SOURCE_FILES})

target_link_libraries(${UNIT_TEST_EXECUTABLE} lithium gtest gtest_main)
add_test(NAME test COMMAND ${UNIT_TEST_EXECUTABLE})

set_target_properties(${UNIT_TEST_EXECUTABLE}
PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test
)
