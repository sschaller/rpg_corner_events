cmake_minimum_required(VERSION 2.8.3)
project(corner_event_detector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

find_package(Eigen3 REQUIRED)

include_directories(
  include
  ${EIGEN3_INCLUDE_DIR}
)

list(APPEND SOURCE_FILES
  src/detector.cpp
  src/harris_detector.cpp
  src/fast_detector.cpp
  src/distinct_queue.cpp
  src/fixed_distinct_queue.cpp
)

add_executable(detector src/main.cpp src/harris_detector.cpp src/fast_detector.cpp src/fixed_distinct_queue.cpp src/distinct_queue.cpp)
target_link_libraries(detector)
