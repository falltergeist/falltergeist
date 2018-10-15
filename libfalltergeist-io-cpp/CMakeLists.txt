cmake_minimum_required(VERSION 3.1)

project(libfalltergeist-io-cpp)

file(GLOB_RECURSE CPP_FILES src/**/*.cpp)

include_directories(${libfalltergeist-common-cpp_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ${CPP_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(${PROJECT_NAME} libfalltergeist-common-cpp)

#https://stackoverflow.com/questions/16398937/cmake-and-finding-other-projects-and-their-dependencies
target_include_directories(${PROJECT_NAME} PUBLIC include)
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include ${libfalltergeist-common-cpp_INCLUDE_DIRS} CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
