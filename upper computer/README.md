# 无人帆船教学README

## 01：收发来自`Motion Capture`的信息

Prerequisite: Python函数的编写

Lib: `NatNetClient.py`

在本节中需要用到的`Motion Capture`的API：`NatNetClient.newFrameListener` `NatNetClient.rigidBodyListener`。这是NatNetClient的两个参数（其实是函数），我们只需要把我们自定义写的函数名赋值到这两个参数上就可以让`Motion Capture`使用我们所编写的函数。但是，这里需要注意的一点：我们编写的函数的具体的Input Parameters可能要符合官方给出的规范，我们才能正常使用。

同时需要注意的是，我们需要设置本机与Motion Capture的主机在同一给局域网下，并在`NatNetClient.py`文件中修改两个IP地址：

- 第33行：修改`serverIPAddress`为Motion Capture主机的IP地址

- 第36行：修改`localIPAddress`为本机的IP地址

## 02: 串口收发消息

本节内容：
- 利用Arduino的`Wire.h`和python的`serial`库进行串口通信
- 烧写Arduino程序

## 03： 利用Motion Capture实现无人帆船自动驾驶




