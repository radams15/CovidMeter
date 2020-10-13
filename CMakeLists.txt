cmake_minimum_required(VERSION 3.17)
project(CovidMeter C)

set(CMAKE_C_STANDARD 11)

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR})

add_executable(CovidMeter main.c)

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(CovidMeter ${CURL_LIBRARIES})