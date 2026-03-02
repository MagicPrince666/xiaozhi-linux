cmake_minimum_required(VERSION 3.10)
project(xiaozhi-linux)

set(CMAKE_C_STANDARD 99)#C99 # lvgl officially support C99 and above
set(CMAKE_CXX_STANDARD 17)#C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
# Define LVGL configuration macros early so they apply to the library build as well
if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL ${CMAKE_HOST_SYSTEM_PROCESSOR})
  # 直接编译
  message(STATUS "host compile")
  if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64")
  elseif (${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
  endif()
else()
  # 交叉编译fb应用
  message(STATUS "cross compile")
endif()
  add_subdirectory(sound_app)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
if (${MACHINES} MATCHES "arm64")
  message(STATUS "apple slicon compile")
else()
  message(STATUS "intel compile")
endif()
else()
  # windows not support
  message(STATUS "System : ${CMAKE_SYSTEM_NAME} not support")
endif()

add_subdirectory(gui)
add_subdirectory(control_center)

