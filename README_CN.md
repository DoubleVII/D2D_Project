# D2D_Project
A 2D Game based on Direct 2D and code partly with assembly lang.
## 介绍
这是一个使用Direct 2D制作的游戏图形框架，通过调用一些内置的接口，可以简易地向屏幕输出图形，包括线、圆、矩形、位图等。

## 开始
### 绘制一个矩形
绘制部分的代码全部位于 "void GameController::GameInit()"

首先创建一个笔刷
```cpp
ComPtr<ID2D1SolidColorBrush> m_pCornflowerBlueBrush;
CreateSolidColorBrush(m_pLightSlateGrayBrush.GetAddressOf(), D2D1::ColorF(D2D1::ColorF::LightSlateGray));
```
然后使用笔刷创建一个矩形
```cpp
//x=100, y=100, width=50, height=80, angle = 30
GameRectangle* Rect = new GameRectangle(m_pLightSlateGrayBrush.Get(), 100.f, 100.f, 50.f, 80.f, 30.f);
```
将矩形添加到图形队列中
```cpp
addGraphic(Rect);
```
效果

![绘制的矩形](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawRectangle.PNG)

### 绘制一个圆

使用笔刷创建一个圆
```cpp
//x=600, y=400, radius=40
GameCircle* Circle = new GameCircle(m_pCornflowerBlueBrush.Get(), 600.f, 400.f, 40.f);
```
将圆添加到图形队列中
```cpp
addGraphic(Circle);
```
效果

![绘制的圆](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawCircle.PNG)


### 绘制一个位图
从资源中加载位图
```cpp
ComPtr<ID2D1Bitmap> Bitmap;
LoadResourceBitmap(MAKEINTRESOURCE(IDB_PNG2), L"PNG", 0, 0, Bitmap.GetAddressOf());
```
使用位图创建一个位图矩形
```cpp
BitmapRect = new BitmapRectangle(temBitmap.Get(), ((Bitmap)->GetSize()).width, ((Bitmap)->GetSize()).height);
```
将位图矩形添加到图形队列中
```cpp
addGraphic(BitmapRect);
```
效果

![绘制的位图](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawBitmap.PNG)

### 绘制线段
使用笔刷创建一个线段
```cpp
CreateSolidColorBrush(m_pCornflowerBlueBrush.GetAddressOf(), D2D1::ColorF(D2D1::ColorF::CornflowerBlue));
//x1=300, y1 = 300, x2 = 600, y2 = 900, stroke = 3
GameLine* line = new GameLine(m_pCornflowerBlueBrush.Get(), 300.f, 300.f, 600.f, 900.f, 3.f);
```
将线段添加到图形队列中
```cpp
addGraphic(line);
```
效果

![绘制的线段](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawLine.PNG)

### 绘制文本
创建字体格式和笔刷
```cpp
std::wstring textStr = L"Use W,A,S,D to move.";
ComPtr<IDWriteTextFormat> defaultTextFormat;
CreateTextFormat(defaultTextFormat.GetAddressOf(), 30.f, L"Microsoft YaHei");
CreateSolidColorBrush(m_pCornflowerBlueBrush.GetAddressOf(), D2D1::ColorF(D2D1::ColorF::CornflowerBlue));
```
使用字体格式和笔刷创建文本
```cpp
//The matrix of text alignment: x1=0, y1 = 0, x2 = 1200, y2 = 100
GameText* gameText = new GameText(m_pCornflowerBlueBrush.Get(), defaultTextFormat.Get(), textStr.c_str(), textStr.size(), 0, 0, 1200, 100);
```
将线段添加到图形队列中
```cpp
addGraphic(gameText);
```

效果

![绘制的文本](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawText.PNG)

## 架构
### Windows编程
首先，你可能需要了解Windows程序的基本结构，如窗体的初始化和程序的主循环，你可能需要在主循环中运行你的游戏主程序。其次，你应该了解Windows消息循环的概念，以及在程序中典型的消息处理方式（常常作为一个函数出现）。
对于以上Windows程序的基本知识，特别是需要在程序中使用汇编代码的编程人员，我们推荐您阅读[《Windows环境下32位汇编语言程序设计》（罗云彬）](https://npupt.com/details.php?id=59136&hit=1)第4章，你可以在书中比较全面地了解Windows程序的运行过程，如果你需要尝试将本项目中的部分与Windows窗口相关的代码，包括消息循环的部分用汇编语言代替，那么罗书中提供的代码范例将特别有帮助。
