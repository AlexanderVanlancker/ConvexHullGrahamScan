cmake_minimum_required(VERSION 3.10)

project(grahamscan)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)

add_library(GrahamScanAlgorithm SHARED src/GrahamScanAlgorithm.cpp)
add_library(Point SHARED src/Point.cpp)

set(SOURCES
	src/main.cpp
) 

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(GrahamScan ${SOURCES} ${HEADERS})
target_link_libraries(GrahamScan PUBLIC sfml-graphics sfml-audio GrahamScanAlgorithm Point)

enable_testing()
add_subdirectory (test)

