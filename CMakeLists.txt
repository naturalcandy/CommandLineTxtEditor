cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PROJECT_NAME
    CmdLineTextEditor)

set(SOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(SOURCE
    ${SOURCE_DIR}/main.cpp)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${SOURCE} "${SOURCE_DIR}/TextBuffer.cpp")

target_include_directories(CmdLineTextEditor
      PUBLIC 
      "${CMAKE_CURRENT_SOURCE_DIR}/include"
  )

