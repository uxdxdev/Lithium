CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Lithium)

# Set compiler
SET(CMAKE_C_COMPILER /usr/bin/gcc)

# Set header and source files
SET(HEADER_FILES
${CMAKE_SOURCE_DIR}/include/server/Server.h
)

SET(SOURCE_FILES
${CMAKE_SOURCE_DIR}/src/Server.cpp
)

# Include header files
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

# Set executable name
SET(EXECUTABLE Server)

# Create binary
ADD_EXECUTABLE(${EXECUTABLE} ${SOURCE_FILES} ${HEADER_FILES})

# Set target properties to output artifacts to bin directory
SET_TARGET_PROPERTIES(${EXECUTABLE}
  PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
  )

# Link against uuid library on *NIX platforms
IF(UNIX AND NOT APPLE)
TARGET_LINK_LIBRARIES(${EXECUTABLE} uuid)
ENDIF()
