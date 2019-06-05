# D2D_Project
A 2D Game based on Direct 2D and code partly with assembly lang.

You can also access the [Readme file](https://github.com/DoubleVII/D2D_Project/blob/master/README_CN.md) wrote in Chinese.(您也可以访问用中文写的Readme文件)

## Introduce
This is a game graphics framework made with Direct 2D. By calling some built-in interfaces, you can easily output graphics to the screen, including lines, circles, rectangles, bitmaps, and more.

## Start Up
### Draw a rectangle
### Draw a Circle
### Draw a Bitmap

## Architecture
### Windows Program
First, you may need to understand the basic structure of a Windows program, such as the initialization of a form and the main loop of the program. You may need to run your main game program in the main loop. Second, you should understand the concept of Windows message loops and the typical way of handling messages in a program (often appearing as a function).
For the basic knowledge of the above Windows programs, especially programmers who need to use assembly code in the program, we recommend that you read the ["32-bit assembly language programming under Windows environment" (Luo Yunbin)](https://npupt.com/details.php?id=59136&hit=1) Chapter 4, you can be more comprehensive in the book To understand the running process of Windows programs, if you need to try to replace some of the code related to the Windows window in this project, including the part of the message loop, with assembly language, then the code sample provided by Luo Shu will be particularly helpful.
