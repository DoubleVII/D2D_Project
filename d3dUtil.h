//***************************************************************************************
// d3dUtil.h by X_Jun(MKXJun) (C) 2018-2019 All Rights Reserved.
// Licensed under the MIT License.
//
// D3Dʵ�ù��߼�
// Direct3D utility tools.
//***************************************************************************************


//
// �����
//

// Ĭ�Ͽ���ͼ�ε�����������
// �������Ҫ����ܣ���ͨ��ȫ���ı��滻����ֵ����Ϊ0
#ifndef GRAPHICS_DEBUGGER_OBJECT_NAME
#define GRAPHICS_DEBUGGER_OBJECT_NAME (1)
#endif

template<class Interface>
inline void SafeRelease(
	Interface** ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif



#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif