#include "stdafx.h"
#include "ResDll.h"

CResDll MResDll;

CResDll::CResDll()
{
	m_hinstResDll = NULL;
	m_ResDllPath = ReturnPath();
	m_ResDllPath = m_ResDllPath + _T("\\Cellsexres.dll");
}


CResDll::~CResDll()
{
}


BOOL CResDll::LoadResDll(CString DllPath)
{
	m_hinstResDll = LoadLibrary(DllPath);
	if (m_hinstResDll == NULL)
	{
		AfxMessageBox(_T("加载资源文件失败"));
		return FALSE;
	}
	return TRUE;
}
BOOL CResDll::RemoveResDll()
{
	if (m_hinstResDll) 
	{ 
		AfxFreeLibrary(m_hinstResDll);
		return TRUE;
	}
	return FALSE;
}
//返回程序所在的绝对目录
CString CResDll::ReturnPath()
{
	WCHAR pStr[MAX_PATH];
	GetModuleFileNameW(NULL, pStr, MAX_PATH);
	CString    sPath(pStr);
	int    nPos;
	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);
	return    sPath;
}

BOOL CResDll::LoadResToImage(DWORD nID, Image *&pImg)
{
	if (m_hinstResDll)
	{
		HRSRC hRsrc = ::FindResource(m_hinstResDll, MAKEINTRESOURCE(nID), TEXT("PNG"));
		if (!hRsrc) return FALSE;

		DWORD len = SizeofResource(m_hinstResDll, hRsrc);
		BYTE* lpRsrc = (BYTE*)LoadResource(m_hinstResDll, hRsrc);
		if (!lpRsrc)  return FALSE;

		HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);
		BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
		memcpy(pmem, lpRsrc, len);
		IStream* pstm = NULL;
		CreateStreamOnHGlobal(m_hMem, TRUE, &pstm);
		pImg = Gdiplus::Image::FromStream(pstm);
		GlobalUnlock(m_hMem);
		pstm->Release();
		FreeResource(lpRsrc);
	}
	return TRUE;
}
//通过资源ID从Dlld导入到Image(CImage)
BOOL CResDll::LoadResToCImage(DWORD nID, CImage&pImage)
{
	if (m_hinstResDll)
	{
		HRSRC hRsrc = ::FindResource(m_hinstResDll, MAKEINTRESOURCE(nID), TEXT("PNG"));
		if (!hRsrc) return FALSE;

		DWORD len = SizeofResource(m_hinstResDll, hRsrc);
		BYTE* lpRsrc = (BYTE*)LoadResource(m_hinstResDll, hRsrc);
		if (!lpRsrc)  return FALSE;

		HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);
		BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
		memcpy(pmem, lpRsrc, len);
		IStream* pstm = NULL;
		CreateStreamOnHGlobal(m_hMem, TRUE, &pstm);
		pImage.Load(pstm);
		GlobalUnlock(m_hMem);
		pstm->Release();
		FreeResource(lpRsrc);
	}
	return TRUE;
}