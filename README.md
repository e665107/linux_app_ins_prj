<div id="table-of-contents">
<h2>Table of Contents</h2>
<div id="text-table-of-contents">
<ul>
<li><a href="#sec-1">1. project</a>
<ul>
<li><a href="#sec-1-1">1.1. 介绍</a>
<ul>
<li><a href="#sec-1-1-1">1.1.1. 特征：</a></li>
</ul>
</li>
<li><a href="#sec-1-2">1.2. 使用</a>
<ul>
<li><a href="#sec-1-2-1">1.2.1. 添加一个app</a></li>
</ul>
</li>
</ul>
</li>
</ul>
</div>
</div>

# project<a id="sec-1" name="sec-1"></a>

## 介绍<a id="sec-1-1" name="sec-1-1"></a>

本项目主要用于linux-c开发,包括测试和实际开发,要做到类似freertos架构式的开发，以app为中心
以后方便两者之间的相互移植，转换，，适用于Linux下的应用开发。

### 特征：<a id="sec-1-1-1" name="sec-1-1-1"></a>

1.  配合u-boot，linux，rootfs（buildroot）共同构成嵌入式linux的系统实现。
2.  采用cmake进行文件的组织，宏定义来进行裁剪。
3.  本项目将不断进行更新，改造，长期维护
4.  借鉴zephyr，成熟工程cmake的组织形式
5.  初期，采用linux c进行应用的开发，中期添加c++，Python新的语言
6.  项目暂时不采用license，做好后使用GPLlicense。

## 使用<a id="sec-1-2" name="sec-1-2"></a>

### 添加一个app<a id="sec-1-2-1" name="sec-1-2-1"></a>

1.  在根目录CMakeLists.txt中添加一个app
    eg: set(HELLO<sub>WORLD</sub><sub>APP</sub> 1)
2.  在app目录，bsp目录等等添加
    if (${HELLO<sub>WORLD</sub><sub>APP</sub>})
      do something else&#x2026;
    endif (${HELLO<sub>WORLD</sub><sub>APP</sub>})
3.  在 app/中添加一个相应的app目录
4.  在该app目录中添加相应的thread/process源文件
5.  在该app目录中添加相应的function<sub>f源文件</sub>,like freertos工程
6.  在bsp中编写相应的设备底层初始化文件
    eg: bsp<sub>ttyusb0</sub>.c bsp<sub>ttyusb0</sub>.h
7.  在flib的CMakeLists.txt中做类似2的改变
8.  在main的CMakeLists.txt中添加相应app要连接的静态库