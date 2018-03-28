cmake_minimum_required(VERSION 3.1)

project(GSA_OpenMP)

set(CMAKE_CXX_STANDARD 11)

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
