cmake_minimum_required(VERSION 3.10)
project(dost-gui)

# Directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${SRC_DIR}/include)

# Files
file(GLOB SRCS ${SRC_DIR}/*.cpp)
file(GLOB DEPS ${INCLUDE_DIR}/*.h ${INCLUDE_DIR}/*.hpp)

# Executable name
set(TARGET_NAME ${PROJECT_NAME})
set(EXEC ${BIN_DIR}/${TARGET_NAME})

# Include directories
include_directories(${INCLUDE_DIR})

# Dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)
pkg_check_modules(adwaita REQUIRED libadwaita-1)

include_directories(${GTK4_INCLUDE_DIRS} ${adwaita_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS} ${adwaita_LIBRARY_DIRS})
add_definitions(${GTK4_CFLAGS_OTHER} ${adwaita_CFLAGS_OTHER})

# Build executable
add_executable(${TARGET_NAME} ${SRCS})

target_link_libraries(${TARGET_NAME} dost-lib)
target_link_libraries(${TARGET_NAME} ${GTK_LIBRARIES} ${adwaita_LIBRARIES})
# Install target
#install(TARGETS ${TARGET_NAME}
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
