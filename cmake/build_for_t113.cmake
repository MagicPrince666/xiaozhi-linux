######## cross compile env define ###################
SET(CMAKE_SYSTEM_NAME Linux)
# 配置库的安装路径
SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

SET(CMAKE_SYSTEM_PROCESSOR "arm")

# 工具链地址
SET(TOOLCHAIN_DIR  "/home/pdk/Tina-t113-pro/prebuilt/gcc/linux-x86/arm/toolchain-sunxi-musl/toolchain/bin/")

# 设置头文件所在目录
include_directories(
    /home/pdk/Tina-t113-pro/out/t113-pro/staging_dir/target/usr/include
    /home/pdk/Tina-t113-pro/out/t113-pro/staging_dir/target/usr/include/libusb-1.0
    /home/pdk/Tina-t113-pro/out/t113-pro/staging_dir/target/usr/include/dbus-1.0
    /home/pdk/Tina-t113-pro/out/t113-pro/staging_dir/target/usr/include/glib-2.0
    /home/pdk/Tina-t113-pro/out/t113-pro/staging_dir/target/usr/lib/dbus-1.0/include
    /home/pdk/Tina-t113-pro/out/t113-pro/staging_dir/target/usr/lib/glib-2.0/include
)

# 设置第三方库所在位置
link_directories(
    /home/pdk/Tina-t113-pro/out/t113-pro/staging_dir/target/usr/lib
)
SET(OPENSSL_CRYPTO_LIBRARY crypto)
SET(OPENSSL_SSL_LIBRARY ssl)

# sunxi t113
SET(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}arm-openwrt-linux-muslgnueabi-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}arm-openwrt-linux-muslgnueabi-g++)
