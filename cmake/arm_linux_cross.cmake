set (CMAKE_SYSTEM_NAME Linux)
set (CMAKE_SYSTEM_PROCESSOR arm)
set (CMAKE_C_COMPILER_WORKS 1)
set (CMAKE_CXX_COMPILER_WORKS 1)

# set(tools "/home/e66/imx/arm-eabi-4.6")
# set(CMAKE_C_COMPILER  ${tools}/bin/arm-eabi-gcc)
# set(CMAKE_CXX_COMPILER ${tools}/bin/arm-eabi-g++)

# set(tools "/home/e66/imx/gcc-linaro-4.9arm-linux-gnueabihf")
# set(CMAKE_C_COMPILER  ${tools}/bin/arm-linux-gnueabihf-gcc)
# set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-gnueabihf-g++)

# set(tools "/home/e66/imx/fsl-linaro-toolchain-master")
# set(CMAKE_C_COMPILER  ${tools}/bin/arm-linux-gcc)
# set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-g++)

set(tools "/home/e66/imx/gcc-linaro-7.3.1-2018.05-x86_64_arm-linux-gnueabihf")

set(CMAKE_C_COMPILER  ${tools}/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-gnueabihf-g++)

set(CMAKE_FIND_ROOT_PATH ${tools})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(ARM_APP 1)
















