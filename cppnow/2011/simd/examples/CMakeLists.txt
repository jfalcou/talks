cmake_minimum_required(VERSION 2.6)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(NT2 COMPONENTS operators REQUIRED)
include_directories(${NT2_INCLUDE_DIR})
link_directories(${NT2_LIBRARY_DIR})
link_libraries(${NT2_LIBRARIES})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_subdirectory(memcpy)
