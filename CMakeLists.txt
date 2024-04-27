cmake_minimum_required(VERSION 3.10)
project(dost)

# Compiler flags
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${SRC_DIR}/include)

# Files
file(GLOB SRCS ${SRC_DIR}/*.cpp)
file(GLOB DEPS ${INCLUDE_DIR}/*.h ${INCLUDE_DIR}/*.hpp)

# Executable name
set(TARGET_NAME ${PROJECT_NAME})
set(EXEC ${BIN_DIR}/${TARGET_NAME})

# Include directories
include_directories(${INCLUDE_DIR})

# Build executable
add_executable(${TARGET_NAME} ${SRCS})

# Install target
install(TARGETS ${TARGET_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
