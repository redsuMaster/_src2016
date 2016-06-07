#pragma once
#include <atlimage.h>  
#include "GdiPlus.h"
using namespace Gdiplus;
#pragma comment(lib,"GdiPlus.lib")
#include "resourcedll.h"


#define DELETE_IMAGE(p) if (p) delete p;

class CResDll
{
public:
	CResDll();
	~CResDll();
public:

	HINSTANCE m_hinstResDll;
	CString m_ResDllPath;
	//返回程序所在的绝对目录
	CString ReturnPath();
	BOOL LoadResDll(CString DllPath);
	BOOL RemoveResDll();
	//通过资源ID从Dlld导入到Image(GDI+)
	BOOL LoadResToImage(DWORD nID, Image *&pImg);

	//通过资源ID从Dlld导入到Image(CImage)
	BOOL LoadResToCImage(DWORD nID, CImage&pImage);
};

