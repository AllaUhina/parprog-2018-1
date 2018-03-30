cmake_minimum_required(VERSION 3.1)

project(GSA_OpenMP)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(GSA_EXE ./sources/global_search_algorithm.cpp)

set(TASKSMAKER_EXE ./sources/tasksmaker.cpp)
set(ANSWERSMAKER_EXE ./sources/answersmaker.cpp)
set(CHECKER_EXE ./sources/checker.cpp)

set(TOFUNC_LIB ./sources/tofunction/tofunction.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/executables/)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/)

add_library(tofunction STATIC ${TOFUNC_LIB})

add_executable(tasksmaker ${TASKSMAKER_EXE})
add_executable(answersmaker ${ANSWERSMAKER_EXE})
add_executable(checker ${CHECKER_EXE})

add_executable(gsa ${GSA_EXE})

target_link_libraries(answersmaker tofunction)
target_link_libraries(gsa tofunction)
