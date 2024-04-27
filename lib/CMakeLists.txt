cmake_minimum_required(VERSION 3.10)
project(dost-lib)

# Directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${SRC_DIR}/include)

# Files
file(GLOB SRCS ${SRC_DIR}/*.cpp)
file(GLOB DEPS ${INCLUDE_DIR}/*.h ${INCLUDE_DIR}/*.hpp)

# Executable name
set(TARGET_NAME ${PROJECT_NAME})
set(EXEC ${BIN_DIR}/${TARGET_NAME})

# Build executable
add_library(${TARGET_NAME} ${SRCS})

# Include directories
target_include_directories(${TARGET_NAME} PUBLIC ${INCLUDE_DIR})

# Install target
install(TARGETS ${TARGET_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
