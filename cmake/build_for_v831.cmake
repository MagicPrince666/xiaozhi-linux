######## cross compile env define ###################
SET(CMAKE_SYSTEM_NAME Linux)
# 配置库的安装路径
SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

SET(CMAKE_SYSTEM_PROCESSOR "arm")

# 工具链地址
SET(TOOLCHAIN_DIR  "/home/huangliquan/toolchain-sunxi-musl/toolchain/bin/")
SET(SYSROOT_DIR "${TOOLCHAIN_DIR}../")

# 设置 sysroot，防止编译器混用主机系统的头文件
SET(CMAKE_SYSROOT ${SYSROOT_DIR})
SET(CMAKE_FIND_ROOT_PATH ${SYSROOT_DIR})
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# 编译器设置
SET(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}arm-openwrt-linux-muslgnueabi-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}arm-openwrt-linux-muslgnueabi-g++)

# 库和头文件搜索路径
set(CMAKE_PREFIX_PATH ${SYSROOT_DIR})
