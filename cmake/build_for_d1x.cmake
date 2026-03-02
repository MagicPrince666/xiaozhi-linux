######## cross compile env define ###################
SET(CMAKE_SYSTEM_NAME Linux)
# 配置库的安装路径
SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

SET(CMAKE_SYSTEM_PROCESSOR "riscv64")

# 工具链地址
SET(TOOLCHAIN_DIR  "/home/prince/tina/out/d1s-mq/staging_dir/toolchain/bin/")

execute_process(
    COMMAND ${TOOLCHAIN_DIR}riscv64-unknown-linux-gnu-gcc --print-sysroot
    OUTPUT_VARIABLE SYSROOT_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "Using cross compiler sysroot: ${SYSROOT_DIR}")

# 设置 sysroot，防止编译器混用主机系统的头文件
SET(CMAKE_SYSROOT ${SYSROOT_DIR})

# The cross compiler's built‑in sysroot often only contains the bare
# runtime.  Platform headers (alsa, etc.) reside in the build system's
# staging tree, so we append that location to the search path.  Doing
# this here keeps the policy consistent across all subprojects.
set(STAGING_DIR "/home/prince/tina/out/d1s-mq/staging_dir/target/usr")
list(APPEND CMAKE_FIND_ROOT_PATH ${SYSROOT_DIR} ${STAGING_DIR})
include_directories(${STAGING_DIR}/include/libpng16)

SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# 编译器设置
SET(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}riscv64-unknown-linux-gnu-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}riscv64-unknown-linux-gnu-g++)

# 库和头文件搜索路径
set(CMAKE_PREFIX_PATH ${SYSROOT_DIR})

# 设置系统根目录（sysroot），这是目标文件系统的根目录
# set(CMAKE_SYSROOT ${TOOLCHAIN_DIR}../../target/rootfs)
# 设置查找模式，确保CMake在sysroot中查找库和头文件
# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# 指定pkg-config路径
set(PKG_CONFIG_EXECUTABLE ${TOOLCHAIN_DIR}../../target/usr/lib/pkgconfig)
