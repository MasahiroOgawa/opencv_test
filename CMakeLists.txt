cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)
project(opencv_test)
find_package(OpenCV REQUIRED)

add_executable(binarize src/binarize.cpp)
target_link_libraries(binarize ${OpenCV_LIBS})

add_executable(image_arithmetic src/image_arithmetic.cpp)
target_link_libraries(image_arithmetic ${OpenCV_LIBS})
