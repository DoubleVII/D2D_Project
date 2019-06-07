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

You can also draw a stroked rectangle with a `StrokeRectangle`
```cpp
///x=400, y=300, width=70, height=30, stroke=5
StrokeRectangle* Rect = new StrokeRectangle(m_pCornflowerBlueBrush.Get(), 400.f, 300.f, 70.f, 30.f, 5.0f);
```

result

![绘制的描边矩形](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawStrokeRectangle.PNG)

### Draw a rounded rectangle
Create a rounded rectangle with a brush
```cpp
RoundedRectangle* Rect = new RoundedRectangle(m_pLightSlateGrayBrush.Get(), 300.f, 500.f, 120.f, 50.f, 10.f);
```
Add a rounded rectangle to the graphics queue
```cpp
addGraphic(Rect);
```

result

![绘制的圆角矩形](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawRoundedRectangle.PNG)

You can also draw a rounded rectangle with a stroke by `StrokeRoundedRectangle`
```cpp
///x=500, y=500, width=120, height=50, stroke=3, radius=10
StrokeRectangle* Rect = new StrokeRoundedRectangle(m_pLightSlateGrayBrush.Get(), 500.f, 500.f, 120.f, 50.f, 3.f, 10.f);
```

result

![绘制的描边圆角矩形](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawRoundedStrokeRectangle.PNG)


### Draw a circle

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


### Draw a bitmap

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

### Draw a line
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

### Draw text
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

### Draw background

Use the default grid background built into the program

```cpp
GirdBackground* background = new GirdBackground(m_pLightSlateGrayBrush.Get());
addGraphic(background);
```

result

![绘制的背景](https://github.com/DoubleVII/D2D_Project/blob/master/readme_image/drawBackground.PNG)

You may notice that this background consists of a solid background and many line segments. In fact, the interior of the `GirdBackground` is done using the drawn line segments.

### Custom graphics

All graphics classes should inherit directly or indirectly from the `Drawable` class, which has a `void draw(ID2D1HwndRenderTarget* m_pRenderTarget)` method, and the Direct2D render target is passed as a parameter. Custom graphics classes can draw various graphics or images in this method via `m_pRenderTarget`.

### Respond to keyboard and mouse events
Use `m_pMouse`, `m_MouseTracker`, `m_pKeyboard`, and `m_KeyboardTracker` to get the status of the mouse and keyboard.

They are declared in the base class of `GameController`:

```cpp
std::unique_ptr<DirectX::Mouse> m_pMouse;
DirectX::Mouse::ButtonStateTracker m_MouseTracker;
std::unique_ptr<DirectX::Keyboard> m_pKeyboard;
DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;
```

The `UpdateScene` method is called continuously while the program is running, and the parameter dt gives the length of time since the last call. You can update the data of the graphics added to the graphics queue in the `UpdateScene` method, and they will be drawn on the screen.

Here are some ways to use `m_pMouse`, `m_MouseTracker`, `m_pKeyboard`, and `m_KeyboardTracker`, and implement the function of controlling the movement of rectangles by W, A, S, and D keys.

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

## Program

In order to write your game, you only need to pay attention to `GameControll` and the graphics class that comes with the framework (or you can implement the graphics class yourself).

### `ComPtr`Smart pointer
The `ComPtr` smart pointer is used in the project to reduce the memory leak. Here is a brief introduction to the smart pointer interface method. For more details on smart pointers, please refer to [DirectX11--ComPtr Smart Pointer] (https://www.cnblogs.com/X-Jun/p/10189859.html).

>The smart pointer needs to include the header file wrl/client.h, and the smart pointer class template ComPtr is located in the namespace Microsoft::WRL.
>
>First, there are five more commonly used methods that need to be understood.：
>
>|Method|Description|
>|---|:---:|
>|ComPtr::Get|This method returns `T*` and does not trigger the reference count plus one, which is commonly used in the function input of the COM component interface.|
>|ComPtr::GetAddressOf|This method returns `T**`, which is commonly used in the function output of the COM component interface.|
>|ComPtr::Reset|This method calls the `Release` method on the instance inside and sets the pointer to `nullptr`|
>|ComPtr::ReleaseAndGetAddressOf|This method is equivalent to first calling the `Reset` method, then calling the `GetAddressOf` method to get the `T**`, which is commonly used in the function output of the COM component interface, and is suitable for cases where the instance may be constructed repeatedly.|
>|ComPtr::As|A template function that replaces the call to IUnknown::QueryInterface and needs to pass the address of a ComPtr instance|
>
>Then there are some methods of operator overloading.：
>
>|Operator|Description|
>|---|:---:|
>|&|Equivalent to calling the `ComPtr<T>::ReleaseAndGetAddressOf` method, it is not recommended|
>|->|Consistent with the behavior of the bare pointer|
>|=|Do not assign an instance of the bare pointer to it, if an instance of `ComPtr` is passed, the exchange occurs.|
>|==and!=|Can be compared to `nullptr`, or another `ComPtr` instance|



### `GameControll`的接口

In the `GameController` class, there are two methods that require special attention,`void GameController::GameInit()
`and`void GameController::UpdateScene(float dt)`。

Simply put, you need to initialize your game in `GameInit`, complete all data updates in `UpdateScene`, and your game's main logic is also executed in `UpdateScene`.

#### `void addGraphic(Drawable* g)`

Add a graphic to the end of the graphics queue. All graphics in the graphics queue are drawn on the screen.

It should be noted that the order in which the graphics are added has an effect on the final rendering effect, ie the graphics that are first added to the graphics queue will be at the bottom of the screen. Therefore we recommend that you place the background in the first position of the graphics queue, otherwise it will block all graphics added in front of it.

#### `void addGraphicToFront(Drawable* g)`

Add a graphic to the head of the graphics queue.

#### `void removeGraphic(Drawable* g)`

Remove a graphic from the graphics queue and the removed graphic will no longer be drawn.

In addition, if you need more detailed insert or delete operations, you can directly use the variable `std::list<Drawable*> graphics` that saved the graphics queue.

## Architecture
### Windows Program
First, you may need to understand the basic structure of a Windows program, such as the initialization of a form and the main loop of the program. You may need to run your main game program in the main loop. Second, you should understand the concept of Windows message loops and the typical way of handling messages in a program (often appearing as a function).
For the basic knowledge of the above Windows programs, especially programmers who need to use assembly code in the program, we recommend that you read the ["32-bit assembly language programming under Windows environment" (Luo Yunbin)](https://npupt.com/details.php?id=59136&hit=1) Chapter 4, you can be more comprehensive in the book To understand the running process of Windows programs, if you need to try to replace some of the code related to the Windows window in this project, including the part of the message loop, with assembly language, then the code sample provided by Luo Shu will be particularly helpful.
