# D2D_Project
A 2D Game based on Direct 2D and code partly with assembly lang.

You can also access the [Readme file](https://github.com/DoubleVII/D2D_Project/blob/master/README_CN.md) wrote in Chinese.(您也可以访问用中文写的Readme文件)

## Introduce
This is a game graphics framework made with Direct 2D. By calling some built-in interfaces, you can easily output graphics to the screen, including lines, circles, rectangles, bitmaps, and more.


这是一个使用Direct 2D制作的游戏图形框架，通过调用一些内置的接口，可以简易地向屏幕输出图形，包括线、圆、矩形、位图等。

## Start Up
### Draw a rectangle
### Draw a Circle
### Draw a Bitmap

## Architecture
### Windows Program
First, you may need to understand the basic structure of a Windows program, such as the initialization of a form and the main loop of the program. You may need to run your main game program in the main loop. Second, you should understand the concept of Windows message loops and the typical way of handling messages in a program (often appearing as a function).
For the basic knowledge of the above Windows programs, especially programmers who need to use assembly code in the program, we recommend that you read the ["32-bit assembly language programming under Windows environment" (Luo Yunbin)](https://npupt.com/details.php?id=59136&hit=1) Chapter 4, you can be more comprehensive in the book To understand the running process of Windows programs, if you need to try to replace some of the code related to the Windows window in this project, including the part of the message loop, with assembly language, then the code sample provided by Luo Shu will be particularly helpful.


首先，你可能需要了解Windows程序的基本结构，如窗体的初始化和程序的主循环，你可能需要在主循环中运行你的游戏主程序。其次，你应该了解Windows消息循环的概念，以及在程序中典型的消息处理方式（常常作为一个函数出现）。
对于以上Windows程序的基本知识，特别是需要在程序中使用汇编代码的编程人员，我们推荐您阅读[《Windows环境下32位汇编语言程序设计》（罗云彬）](https://npupt.com/details.php?id=59136&hit=1)第4章，你可以在书中比较全面地了解Windows程序的运行过程，如果你需要尝试将本项目中的部分与Windows窗口相关的代码，包括消息循环的部分用汇编语言代替，那么罗书中提供的代码范例将特别有帮助。
