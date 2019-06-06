# D2D_Project
A 2D Game based on Direct 2D and code partly with assembly lang.
## 介绍
这是一个使用Direct 2D制作的游戏图形框架，通过调用一些内置的接口，可以简易地向屏幕输出图形，包括线、圆、矩形、位图等。

## 开始
### 绘制一个矩形

首先创建一个笔刷
```
ComPtr<ID2D1SolidColorBrush> m_pCornflowerBlueBrush;
CreateSolidColorBrush(m_pLightSlateGrayBrush.GetAddressOf(), D2D1::ColorF(D2D1::ColorF::LightSlateGray));
```
### 绘制一个圆形
### 绘制一个位图

## 架构
### Windows编程
首先，你可能需要了解Windows程序的基本结构，如窗体的初始化和程序的主循环，你可能需要在主循环中运行你的游戏主程序。其次，你应该了解Windows消息循环的概念，以及在程序中典型的消息处理方式（常常作为一个函数出现）。
对于以上Windows程序的基本知识，特别是需要在程序中使用汇编代码的编程人员，我们推荐您阅读[《Windows环境下32位汇编语言程序设计》（罗云彬）](https://npupt.com/details.php?id=59136&hit=1)第4章，你可以在书中比较全面地了解Windows程序的运行过程，如果你需要尝试将本项目中的部分与Windows窗口相关的代码，包括消息循环的部分用汇编语言代替，那么罗书中提供的代码范例将特别有帮助。