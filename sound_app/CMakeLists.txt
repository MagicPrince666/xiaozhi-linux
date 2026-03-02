cmake_minimum_required(VERSION 3.5)
project(sound_app LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
  sound_app.cpp
  aplay.cpp
  record.cpp
  opus.cpp
  ipc_udp.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Threads REQUIRED)

# Try to find libasound, opus and speexdsp (link by name if not found via find_package)
find_library(ASOUND_LIB asound)

set(EXTRA_LIBS
  opus
  speexdsp
)
if(ASOUND_LIB)
  list(APPEND EXTRA_LIBS ${ASOUND_LIB})
else()
  list(APPEND EXTRA_LIBS asound)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${EXTRA_LIBS} Threads::Threads)

option(BUILD_OPUS_TEST "Build opus_test utility" OFF)
if(BUILD_OPUS_TEST AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/opus.cpp")
  add_executable(opus_test opus.cpp)
  target_include_directories(opus_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(opus_test PRIVATE opus speexdsp)
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
