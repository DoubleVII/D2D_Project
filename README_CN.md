# D2D_Project
A 2D Game based on Direct 2D and code partly with assembly lang.
## 介绍
这是一个使用Direct 2D制作的游戏图形框架，通过调用一些内置的接口，可以简易地向屏幕输出图形，包括线、圆、矩形、位图等。

## 环境和项目配置
本项目使用Microsoft Visual Studio 2019编写，使用VS2019直接打开项目根目录的sln文件即可。
### 项目配置
打开项目后，需要手动设置项目的属性，否则不能成功编译。
* 鼠标右击项目（DirextX2DDemo）->属性->常规->字符集->使用Unicode字符集
* 项目属性->链接器->系统->子系统>窗口 (/SUBSYSTEM:WINDOWS)

## 开始
### 绘制矩形
绘制部分的代码全部位于 `void GameController::GameInit()`

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


您也可以通过StrokeRectangle绘制描边的矩形
```cpp
///x=400, y=300, width=70, height=30, stroke=5
StrokeRectangle* Rect = new StrokeRectangle(m_pCornflowerBlueBrush.Get(), 400.f, 300.f, 70.f, 30.f, 5.0f);
```

效果

![绘制的描边矩形](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawStrokeRectangle.PNG)

### 绘制圆角矩形
使用笔刷创建一个圆角矩形
```cpp
RoundedRectangle* Rect = new RoundedRectangle(m_pLightSlateGrayBrush.Get(), 300.f, 500.f, 120.f, 50.f, 10.f);
```
将圆角矩形添加到图形队列中
```cpp
addGraphic(Rect);
```

效果

![绘制的圆角矩形](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawRoundedRectangle.PNG)

您也可以通过StrokeRoundedRectangle绘制描边的圆角矩形
```cpp
///x=500, y=500, width=120, height=50, stroke=3, radius=10
StrokeRectangle* Rect = new StrokeRoundedRectangle(m_pLightSlateGrayBrush.Get(), 500.f, 500.f, 120.f, 50.f, 3.f, 10.f);
```

效果

![绘制的描边圆角矩形](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawRoundedStrokeRectangle.PNG)

### 绘制圆

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


### 绘制位图
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

### 绘制背景
使用程序内置的默认网格背景
```cpp
GirdBackground* background = new GirdBackground(m_pLightSlateGrayBrush.Get());
addGraphic(background);
```

效果

![绘制的背景](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawBackground.PNG)

你可能会注意到，这个背景由一个纯色底色和许多线段组成，事实上GirdBackground的内部就是使用绘制线段完成的。

### 自定义图形
所有的图形类都应该直接或间接继承自Drawable类，它有一个`void draw(ID2D1HwndRenderTarget* m_pRenderTarget)`方法，Direct2D的渲染目标被作为参数传入。自定义的图形类可以在该方法中通过m_pRenderTarget绘制各种图形或图像。

### 响应键盘和鼠标事件
使用m_pMouse、m_MouseTracker、m_pKeyboard和m_KeyboardTracker获取鼠标和键盘的状态。

它们被声明在GameController的基类中：
```cpp
std::unique_ptr<DirectX::Mouse> m_pMouse;
DirectX::Mouse::ButtonStateTracker m_MouseTracker;
std::unique_ptr<DirectX::Keyboard> m_pKeyboard;
DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;
```

在程序运行时，UpdateScene方法会被不断调用，参数dt给出了距离上次调用的时间长度。您可以在UpdateScene方法中更新被加入图形队列中的图形的数据，然后它们会被绘制在屏幕上。

下面给出了一些使用m_pMouse、m_MouseTracker、m_pKeyboard和m_KeyboardTracker的方法，并实现了通过W，A，S，D键控制矩形移动的功能。
```cpp
// in void GameController::UpdateScene(float dt)
// get mouse state
	Mouse::State mouseState = m_pMouse->GetState();
	Mouse::State lastMouseState = m_MouseTracker.GetLastState();
	// get keyboard state
	Keyboard::State keyState = m_pKeyboard->GetState();
	Keyboard::State lastKeyState = m_KeyboardTracker.GetLastState();

	// Update mouse button status tracker
	m_MouseTracker.Update(mouseState);
	m_KeyboardTracker.Update(keyState);

	// example
	//Mouse drag event
	if (mouseState.leftButton == true && m_MouseTracker.leftButton == m_MouseTracker.HELD) {
     //To do somthing
	}

	// example
	// Keyboard event
	if (keyState.IsKeyDown(Keyboard::W))
		rect3->setY(temRect3->getY() - 100.f * dt);
	if (keyState.IsKeyDown(Keyboard::S))
		rect3->setY(temRect3->getY() + 100.f * dt);
	if (keyState.IsKeyDown(Keyboard::A))
		rect3->setX(temRect3->getX() - 100.f * dt);
	if (keyState.IsKeyDown(Keyboard::D))
		rect3->setX(temRect3->getX() + 100.f * dt);
```

## 编程
为了编写您的游戏，您只需要关注GameControll和框架自带的图形类即可（或者您可以自己实现图形类）。

### ComPtr智能指针
在项目中使用了ComPtr智能指针以减少内存泄漏的Bug，这里简要介绍智能指针的接口方法。更多关于智能指针的详细介请参考[DirectX11--ComPtr智能指针](https://www.cnblogs.com/X-Jun/p/10189859.html)。
>使用该智能指针需要包含头文件wrl/client.h，并且智能指针类模板ComPtr位于名称空间Microsoft::WRL内。

>首先有五个比较常用的方法需要了解一下：
>方法|描述
>---|---:
>ComPtr::Get|该方法返回T*，并且不会触发引用计数加1，常用在COM组件接口的函数输入
>ComPtr::GetAddressOf|该方法返回T**，常用在COM组件接口的函数输出
>ComPtr::Reset|该方法对里面的实例调用Release方法，并将指针置为nullptr
>ComPtr::ReleaseAndGetAddressOf|该方法相当于先调用Reset方法，再调用GetAddressOf方法获取T**，常用在COM组件接口的函数输出，适用于实例可能会被反复构造的情况下
>ComPtr::As|一个模板函数，可以替代IUnknown::QueryInterface的调用，需要传递一个ComPtr实例的地址



### GameControll的接口

在GameController类中，有两个方法需要特别关注，`void GameController::GameInit()
`和`void GameController::UpdateScene(float dt)`。

简单来讲，您需要在GameInit中初始化您的游戏，在UpdateScene中完成所有的数据更新，同时您的游戏主要逻辑也在UpdateScene中执行。

#### void addGraphic(Drawable* g)
向图形队列尾部添加一个图形。图形队列中的所有图形会被绘制在屏幕上。

需要注意的是，添加图形的顺序对最终的绘制效果有影响，即最先添加到图形队列中的图形会位于画面最底层。因此我们推荐您将背景放在图形队列的第一个位置，否则它会挡住所有在它前面添加的图形。

#### void addGraphicToFront(Drawable* g)
向图形队列头部添加一个图形。

#### void removeGraphic(Drawable* g)
从图形队列中移除一个图形，被移除的图形将不再被绘制。

另外，如果需要更加精细的插入或删除操作，您可以直接使用保存图形队列的变量`std::list<Drawable*> graphics`。

## 架构
### Windows编程
首先，你可能需要了解Windows程序的基本结构，如窗体的初始化和程序的主循环，你可能需要在主循环中运行你的游戏主程序。其次，你应该了解Windows消息循环的概念，以及在程序中典型的消息处理方式（常常作为一个函数出现）。
对于以上Windows程序的基本知识，特别是需要在程序中使用汇编代码的编程人员，我们推荐您阅读[《Windows环境下32位汇编语言程序设计》（罗云彬）](https://npupt.com/details.php?id=59136&hit=1)第4章，你可以在书中比较全面地了解Windows程序的运行过程，如果你需要尝试将本项目中的部分与Windows窗口相关的代码，包括消息循环的部分用汇编语言代替，那么罗书中提供的代码范例将特别有帮助。
