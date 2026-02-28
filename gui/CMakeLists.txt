cmake_minimum_required(VERSION 3.10)
project(lvgl)

set(CMAKE_C_STANDARD 99)#C99 # lvgl officially support C99 and above
set(CMAKE_CXX_STANDARD 17)#C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(
  thirdparty/freetype/include
  thirdparty/freetype/include/freetype
)

# Define LVGL configuration macros early so they apply to the library build as well
add_definitions(-DLV_USE_LINUX_FBDEV=0 -DLV_USE_LINUX_DRM=0 -DLV_USE_SDL=1 -DLV_USE_EVDEV=0 -DLV_USE_LIBINPUT=0 -D_GNU_SOURCE -DHAVE_UNISTD_H)

# make libpng available for lvgl during its build
find_package(PNG REQUIRED)

add_subdirectory(lv_100ask_xz_ai)
add_subdirectory(thirdparty/freetype)
add_subdirectory(lvgl)
target_include_directories(lvgl PUBLIC ${PROJECT_SOURCE_DIR})

#add_subdirectory(lv_100ask_xz_ai)

add_executable(main main.c mouse_cursor_icon.c)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  include(${CMAKE_CURRENT_LIST_DIR}/lvgl/tests/FindLibDRM.cmake)
  include_directories(${Libdrm_INCLUDE_DIRS})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
if (${MACHINES} MATCHES "arm64")
  message(STATUS "apple slicon compile")
else()
  message(STATUS "intel compile")
endif()
    add_definitions(-DLV_USE_LINUX_FBDEV=0 -DLV_USE_LINUX_DRM=0 -DLV_USE_SDL=1 -DLV_USE_EVDEV=0 -DLV_USE_LIBINPUT=0 -D_GNU_SOURCE -DHAVE_UNISTD_H)
else()
  # windows not support
  message(STATUS "System : ${CMAKE_SYSTEM_NAME} not support")
endif()

find_package(SDL2)
find_package(SDL2_image)
include_directories(${CMAKE_SOURCE_DIR}/lv_100ask_xz_ai ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

target_link_libraries(main lv_100ask_xz_ai  lvgl lvgl::examples lvgl::demos lvgl::thorvg ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${Libdrm_LIBRARIES} m pthread freetype PNG::PNG)
add_custom_target (run COMMAND ${EXECUTABLE_OUTPUT_PATH}/lv_xiaozhiui DEPENDS main)

