cmake_minimum_required(VERSION 3.10)
project(pdf-toolkit-utility)

set(CMAKE_CXX_STANDARD 17)

find_package(Poppler REQUIRED)

add_executable(pdf-toolkit-utility
    src/main.cpp
    src/pdf_utils.cpp
)

target_link_libraries(pdf-toolkit-utility ${Poppler_LIBRARIES})
target_include_directories(pdf-toolkit-utility PRIVATE ${Poppler_INCLUDE_DIRS})

enable_testing()
add_subdirectory(tests)