
# CMake QT Custom Window

本项目的目的在于构建一个基于CMake跨平台开发环境的多模块的QT配置示例。  
同时在其中内置了一个QT自定义窗体的基类。具体详细信息将会在后面逐一进行介绍。  
如果代码中有不足之处，或者有更好的解决方法，欢迎随时联系[我](mailto:nianziyishi@foxmail.com)。  
假如此项目中的部分代码能够对您有一定的帮助，我会感到非常的荣幸。  

The purpose of this project is to build a multi-module QT configuration example based on CMake cross-platform development environment.  
A QT base class for custom window is built in. Detailed information will be introduced one by one later.  
If there are any deficiencies in the code, or if you have a better solution. Please feel free to contact [me](mailto:nianziyishi@foxmail.com). 
If some of the code in this project can be of some help to you, I will feel very honored  


## 基于CMake的特性

- 支持windows、linux、macos。  
- 支持qt的moc、uic、rcc编译。  
- 支持使用visual studio在windows上开发调试。  
- 支持使用visual studio远程连接linux开发调试。  


## 自定义窗体的特性

- 支持自定义标题栏。  
- 支持通过样式文件设置全局或局部样式。  
- 支持点击标题栏拖动。  
- 支持在显示状态栏时点击右下角调整大小。  
- 支持最小化、最大化、恢复、全屏。  
- 支持显示蒙板时阻塞整个窗体。  
- 支持自定义对话框。  
- 支持窗体模态和非模态。  
- 支持窗体阻塞和非阻塞。  
- 支持界面显示完成后再初始化数据处理。  
- 支持窗体是否关闭处理。  
- 支持窗体隐藏和关闭时返回状态。  
- 支持设置控件错误样式。  
- 还有更多的特性等待您的发现。  


## 示例中项目工作的环境

- windos: 10.0.19042.985。  
- linux: ubuntu-20.04, 5.13.0-30-generic, x86_64。  
- vs2019: 16.11.10。  
- qt: 5.15.2。  

## 编译方式

首先需要在**CMakeQT-CustomWindow/CMakeLists.txt**文件中设置您的QT路径  

### 在Windows上编译

打开“Developer Command Propt for VS 2019”工具并进入源码目录。  
```  
mkdir build && cd build  
```  
```  
cmake.exe .. -G "Visual Studio 16 2019"  
```  
```  
msbuild /m QCustomWindow.sln /p:Platform=x64 /p:Configuration=Release /t:build  
```  
输出的文件将会在QCustomWindow\out\bin\Release  

### 在Linux上编译

进入源码目录  
```  
mkdir build && cd build  
```  
```  
cmake .. -DCMAKE_BUILD_TYPE=Release  
```  
```  
make  
```  

输出的文件将会在~/QCustomWindow/bin/Release  

### 编译截图示例

![windows-cmake编译1](/Screenshots/windows-cmake编译1.png)  
![windows-cmake编译2](/Screenshots/windows-cmake编译2.png)  

![linux-cmake编译1](/Screenshots/linux-cmake编译1.png)  
![linux-cmake编译2](/Screenshots/linux-cmake编译2.png)  


## 开发调试

### 环境配置

使用visual studio 2019在windows和linux开发的环境配置请参考如下的链接示例：  

- [在visual studio中创建cmake项目](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170)  
- [在visual studio中创建linux cmake项目](https://docs.microsoft.com/en-us/cpp/linux/cmake-linux-project?view=msvc-170)  
- [开始linux cmake项目](https://docs.microsoft.com/en-us/cpp/build/get-started-linux-cmake?view=msvc-170)  

![调试1-windows](/Screenshots/调试1-windows.png)  
![调试2-linux](/Screenshots/调试2-linux.png)  

为了操作方便，建议您安装Qt VS CMake Tools扩展工具，目前只有vs2019版本的。  
安装该工具是为了在cmake项目模式下，使添加QT类和QT控件类的操作更方便。  

![添加qt类1](/Screenshots/添加qt类1.png)  
![添加qt类2](/Screenshots/添加qt类2.png)  
![添加qt类3](/Screenshots/添加qt类3.png)  
![添加qt类4](/Screenshots/添加qt类4.png)  
![添加qt类5](/Screenshots/添加qt类5.png)  

### 调试时查看变量值

在windows下调试时qt5.natvis文件能够很好的支持QT变量值的解析显示。  
在linux下调试时qt5.natvis文件不能支持一些变量的显示。目前已知有3种解决方案，但是都不够完善。如果您有更好的解决方法，欢迎随时联系我。  
- 1.根据Qt5.15.2/Tools/QtCreator/share/qtcreator/debugger目录下描述的方式进行配置。  
- 2.根据https://github.com/Lekensteyn/qt5printers链接描述的方式进行配置。  
- 3.本项目目录下的qt5-linux.natvis文件是在qt5.natvis文件基础上进行了一些修改，增加并修复了一些变量解析时错误显示的问题，但还不够完善。该文件只要在当前目录下就能工作。具体效果示例请查看[csdn链接](https://blog.csdn.net/qq_31412239/article/details/123311712)。  

### 自定义窗体效果展示

界面中所使用的qss文件[请参考](https://github.com/spyder-ide/qtsass)。  
界面中所使用的图片资源暂不知道原作者是谁，如果有谁知道的话可以告诉我。  
![界面1-light](/Screenshots/界面1-light.png)  
![界面2-light](/Screenshots/界面2-light.png)  
![界面3-light](/Screenshots/界面3-light.png)  
![界面4-light](/Screenshots/界面4-light.png)  
![界面5-dark](/Screenshots/界面5-dark.png)  
![界面6-dark](/Screenshots/界面6-dark.png)  
![界面7-dark](/Screenshots/界面7-dark.png)  



