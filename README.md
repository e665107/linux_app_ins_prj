
# Table of Contents

1.  [project](#org68cd666)
    1.  [介绍](#org13856f5)
        1.  [特征：](#org509ada3)
    2.  [使用](#orgc58633c)
        1.  [添加一个linux c/c++ app](#org7b6c708)
        2.  [auto creat app](#org3f3ab99)


<a id="org68cd666"></a>

# project


<a id="org13856f5"></a>

## 介绍

本项目主要用于linux-c开发,包括测试和实际开发,要做到类似freertos架构式的开发，以app为中心
以后方便两者之间的相互移植，转换，，适用于Linux下的应用开发。


<a id="org509ada3"></a>

### 特征：

1.  配合u-boot，linux，rootfs（buildroot）共同构成嵌入式linux的系统实现。
2.  采用cmake进行文件的组织，宏定义来进行裁剪。
3.  本项目将不断进行更新，改造，长期维护
4.  借鉴zephyr，成熟工程cmake的组织形式
5.  初期，采用linux c进行应用的开发，中期添加c++，Python新的语言
6.  项目暂时不采用license，做好后使用GPLlicense。


<a id="orgc58633c"></a>

## 使用


<a id="org7b6c708"></a>

### 添加一个linux c/c++ app

1.  在根目录CMakeLists.txt中添加一个app
    eg: set(HELLO<sub>WORLD</sub><sub>APP</sub> 1)
2.  在app目录，bsp目录等等添加
    if (\({HELLO_WORLD_APP})
             do something else...
           endif (\){HELLO<sub>WORLD</sub><sub>APP</sub>})
3.  在 app/中添加一个相应的app目录
4.  在该app目录中添加相应的thread/process源文件
5.  在该app目录中添加相应的function<sub>f源文件,like</sub> freertos工程
6.  在bsp中编写相应的设备底层初始化文件
    eg: bsp<sub>ttyusb0.c</sub> bsp<sub>ttyusb0.h</sub>
7.  在flib的CMakeLists.txt中做类似2的改变
8.  在main的CMakeLists.txt中添加相应app要连接的静态库
9.  add the app name to the app<sub>config.in.h</sub>


<a id="org3f3ab99"></a>

### auto creat app

1.  ./auto.sh clean
2.  ./auto.sh app app<sub>name</sub>(eg.  test0)
3.  ./auto.sh  (compile)
4.  ./auto.sh run (run)

