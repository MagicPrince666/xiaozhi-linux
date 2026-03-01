######## cross compile env define ###################
SET(CMAKE_SYSTEM_NAME Linux)
# 配置库的安装路径
SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

SET(CMAKE_SYSTEM_PROCESSOR "riscv64")

# 工具链地址
SET(TOOLCHAIN_DIR  "/home/prince/tina/out/d1s-mq/staging_dir/toolchain/bin/")

# 设置头文件所在目录
include_directories(
    ${TOOLCHAIN_DIR}../../target/usr/include
    ${TOOLCHAIN_DIR}../../target/usr/include/libusb-1.0
    ${TOOLCHAIN_DIR}../../target/usr/include/dbus-1.0
    ${TOOLCHAIN_DIR}../../target/usr/include/glib-2.0
    ${TOOLCHAIN_DIR}../../target/usr/lib/dbus-1.0/include
    ${TOOLCHAIN_DIR}../../target/usr/lib/glib-2.0/include
)

# 设置第三方库所在位置
link_directories(
    ${TOOLCHAIN_DIR}../../target/usr/lib
)
SET(OPENSSL_CRYPTO_LIBRARY crypto)
SET(OPENSSL_SSL_LIBRARY ssl)

# allwinner d1s
SET(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}riscv64-unknown-linux-gnu-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}riscv64-unknown-linux-gnu-g++)

# 设置系统根目录（sysroot），这是目标文件系统的根目录
# set(CMAKE_SYSROOT ${TOOLCHAIN_DIR}../../target/rootfs)
# 设置查找模式，确保CMake在sysroot中查找库和头文件
# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# 指定pkg-config路径
set(PKG_CONFIG_EXECUTABLE ${TOOLCHAIN_DIR}../../target/usr/lib/pkgconfig)
