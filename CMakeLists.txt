cmake_minimum_required(VERSION 2.8)
project(Lithium)

set(SOURCES
  src/udpserver.c
  )

add_executable(udpserver ${SOURCES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
