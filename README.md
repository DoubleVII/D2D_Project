# D2D_Project
A 2D Game based on Direct 2D and code partly with assembly lang.

You can also access the [Readme file](https://github.com/DoubleVII/D2D_Project/blob/master/README_CN.md) wrote in Chinese.(您也可以访问用中文写的Readme文件)

## Introduce
This is a game graphics framework made with Direct 2D. By calling some built-in interfaces, you can easily output graphics to the screen, including lines, circles, rectangles, bitmaps, and more.

## Start Up
### Draw a rectangle
The code for drawing parts is all in "void GameController::GameInit()"

First create a brush
```cpp
ComPtr<ID2D1SolidColorBrush> m_pCornflowerBlueBrush;
CreateSolidColorBrush(m_pLightSlateGrayBrush.GetAddressOf(), D2D1::ColorF(D2D1::ColorF::LightSlateGray));
```
Then use the brush to create a rectangle
```cpp
//x=100, y=100, width=50, height=80, angle = 30
GameRectangle* Rect = new GameRectangle(m_pLightSlateGrayBrush.Get(), 100.f, 100.f, 50.f, 80.f, 30.f);
```
Add a rectangle to the graphics queue
```cpp
addGraphic(Rect);
```
result

![Drawn rectangle](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawRectangle.PNG)

### Draw a Circle

Create a circle with a brush
```cpp
//x=600, y=400, radius=40
GameCircle* Circle = new GameCircle(m_pCornflowerBlueBrush.Get(), 600.f, 400.f, 40.f);
```
Add a circle to the graphics queue
```cpp
addGraphic(Circle);
```
result

![Drawn circle](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawCircle.PNG)


### Draw a Bitmap

Load a bitmap from resources
```cpp
ComPtr<ID2D1Bitmap> Bitmap;
LoadResourceBitmap(MAKEINTRESOURCE(IDB_PNG2), L"PNG", 0, 0, Bitmap.GetAddressOf());
```
Create a bitmap rectangle using a bitmap
```cpp
BitmapRect = new BitmapRectangle(temBitmap.Get(), ((Bitmap)->GetSize()).width, ((Bitmap)->GetSize()).height);
```
Add a bitmap rectangle to the graphics queue
```cpp
addGraphic(BitmapRect);
```
result

![Drawn bitmap](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawBitmap.PNG)

### Draw a Line
Create a line segment with a brush
```cpp
CreateSolidColorBrush(m_pCornflowerBlueBrush.GetAddressOf(), D2D1::ColorF(D2D1::ColorF::CornflowerBlue));
//x1=300, y1 = 300, x2 = 600, y2 = 900, stroke = 3
GameLine* line = new GameLine(m_pCornflowerBlueBrush.Get(), 300.f, 300.f, 600.f, 900.f, 3.f);
```
Add line segments to the graphics queue
```cpp
addGraphic(line);
```
result

![绘制的线段](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawLine.PNG)

### Draw Text
Create font formatting and brushes
```cpp
std::wstring textStr = L"Use W,A,S,D to move.";
ComPtr<IDWriteTextFormat> defaultTextFormat;
CreateTextFormat(defaultTextFormat.GetAddressOf(), 30.f, L"Microsoft YaHei");
CreateSolidColorBrush(m_pCornflowerBlueBrush.GetAddressOf(), D2D1::ColorF(D2D1::ColorF::CornflowerBlue));
```
Create text using font formatting and brushes
```cpp
//The matrix of text alignment: x1=0, y1 = 0, x2 = 1200, y2 = 100
GameText* gameText = new GameText(m_pCornflowerBlueBrush.Get(), defaultTextFormat.Get(), textStr.c_str(), textStr.size(), 0, 0, 1200, 100);
```
Add line segments to the graphics queue
```cpp
addGraphic(gameText);
```

result

![绘制的文本](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawText.PNG)

## Architecture
### Windows Program
First, you may need to understand the basic structure of a Windows program, such as the initialization of a form and the main loop of the program. You may need to run your main game program in the main loop. Second, you should understand the concept of Windows message loops and the typical way of handling messages in a program (often appearing as a function).
For the basic knowledge of the above Windows programs, especially programmers who need to use assembly code in the program, we recommend that you read the ["32-bit assembly language programming under Windows environment" (Luo Yunbin)](https://npupt.com/details.php?id=59136&hit=1) Chapter 4, you can be more comprehensive in the book To understand the running process of Windows programs, if you need to try to replace some of the code related to the Windows window in this project, including the part of the message loop, with assembly language, then the code sample provided by Luo Shu will be particularly helpful.
