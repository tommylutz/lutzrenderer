CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

ENABLE_TESTING()

SET(CMAKE_CXX_FLAGS "-std=c++11")

SET(CMAKE_BUILD_TYPE Debug)

CONFIGURE_FILE(gtest-download/CMakeLists.txt.in
               gtest-download/CMakeLists.txt)
EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gtest-download )
EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} --build .
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gtest-download )

SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
ADD_SUBDIRECTORY(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build )

CONFIGURE_FILE(tinyrenderer-download/CMakeLists.txt.in
               tinyrenderer-download/CMakeLists.txt)
EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tinyrenderer-download )
EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} --build .
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tinyrenderer-download )

PROJECT(LutzRenderer)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_SUBDIRECTORY(main)
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(librend)

