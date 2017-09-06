# 环境配置（VS2017）

## 项目属性页配置

### 说明

因为有看到建议说：

> 单个项目相关的头文件、静态库（lib）和运行库（dll）等文件最好放置在相应的工程目录下，如果直接复制进VS安装目录下对应的include文件夹、lib文件夹和Windows下的system文件夹不方便管理，也可能会污染环境，尤其是在使用大量的测试库时

想到我上图形学课程时，助教教我们配置glut的方法都是直接放进VS安装目录和Windows系统目录，感觉这样的习惯不太好，正好借这个熟悉环境的机会重新配置下。

### 配置头文件（include）目录

1. VS2017菜单 -> 项目 -> xxx属性 -> 配置属性 -> VC++目录
2. 在`包含目录`中添加头文件所在目录，要添加相对目录可使用`$(ProjectDir)\相对项目文件夹的路径`

### 配置静态库（lib）目录

1. VS2017菜单 -> 项目 -> xxx属性 -> 配置属性 -> VC++目录
2. 在`库目录`中添加静态库文件所在目录，要添加相对目录可使用`$(ProjectDir)\相对项目文件夹的路径`
3. VS2017菜单 -> 项目 -> xxx属性 -> 配置属性 -> 链接器 -> 输入4
4. 在`附加依赖项`中添加所使用到的静态库文件（\*.lib）

### 配置运行库（dll）目录

> 在配置运行库（dll）时本应该类似地到：`VS2017菜单 -> 项目 -> xxx属性 -> 配置属性 -> VC++目录` 中的`可执行文件目录`中添加即可，但是发现运行时仍然找不到对应的运行库（dll），因此采用临时添加PATH环境变量的方法来解决：

1. VS2017菜单 -> 项目 -> xxx属性 -> 配置属性 -> 调试
2. 在`环境`中添加运行库（dll）所在目录，例如：`PATH=%PATH%;$(ProjectDir)\相对项目文件夹的路径`


# 内存泄漏检测

Windows集成了一套内存泄漏检测的库，在Visual Studio中可以直接使用（只在Debug版本中生效）。

## 示例代码

```cpp
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif

int main()
{
    int *leak = new int[10];
    _CrtDumpMemoryLeaks();
    return 0;
}
```

## 逐行解释

* 第1~3行声明了\_CRTDBG\_MAP\_ALLOC的宏定义，然后include crtdbg库，在调试版本中就会启动Windows内置的一套内存分配和泄漏检测的工具。
* 第5~7行重新声明了new关键字，这样可以在最后dump memory的时候看到泄漏的内存分配的位置。
* 第12行使用\_CrtDumpMemoryLeaks函数在最后程序退出的时候显示出所有内存的泄漏情况。

