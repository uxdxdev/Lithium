cmake_minimum_required(VERSION 2.8)
project(Lithium)

set(SOURCES
  src/udpserver.c
  )

add_executable(udpserver ${SOURCES})

set_target_properties(MyLib PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
