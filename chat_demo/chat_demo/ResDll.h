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
	//���س������ڵľ���Ŀ¼
	CString ReturnPath();
	BOOL LoadResDll(CString DllPath);
	BOOL RemoveResDll();
	//ͨ����ԴID��Dlld���뵽Image(GDI+)
	BOOL LoadResToImage(DWORD nID, Image *&pImg);

	//ͨ����ԴID��Dlld���뵽Image(CImage)
	BOOL LoadResToCImage(DWORD nID, CImage&pImage);
};

