cmake_minimum_required(VERSION 3.11)
project(Raspternal)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)
add_executable(Raspternal ${SOURCE_FILES})

target_link_libraries(Raspternal libstdc++fs.a dl X11 Xtst pthread xdo)
