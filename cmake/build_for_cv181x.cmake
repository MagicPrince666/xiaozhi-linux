######## cross compile env define ###################
SET(CMAKE_SYSTEM_NAME Linux)
# 配置库的安装路径
SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

SET(CMAKE_SYSTEM_PROCESSOR "riscv64")

# 工具链地址
SET(TOOLCHAIN_DIR  "/home/huangliquan/duo-buildroot-sdk/buildroot-2021.05/output/milkv-duos-emmc_musl_riscv64/host/bin/")
SET(SYSROOT_DIR "${TOOLCHAIN_DIR}../riscv64-buildroot-linux-musl/sysroot")

# 设置 sysroot，防止编译器混用主机系统的头文件
SET(CMAKE_SYSROOT ${SYSROOT_DIR})
SET(CMAKE_FIND_ROOT_PATH ${SYSROOT_DIR})
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# 编译器和编译标志
SET(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}riscv64-unknown-linux-musl-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}riscv64-unknown-linux-musl-g++)

# CPU 架构标志
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=c906fdv -march=rv64imafdcv0p7xthead -mcmodel=medany -mabi=lp64d")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=c906fdv -march=rv64imafdcv0p7xthead -mcmodel=medany -mabi=lp64d")

# 不需要再配置这些，CMAKE_SYSROOT 会自动处理
set(CMAKE_PREFIX_PATH ${SYSROOT_DIR})
