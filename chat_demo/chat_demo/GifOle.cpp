//+-------------------------------------------------------------------------
//
//  GifRichEdit - RichEdit Plus Control
//  Copyright (C) BodSoft
//
//  File:       GifOle.cpp
//
//  History:    Oct-25-2010   Eric Qian  Created
//
//--------------------------------------------------------------------------
#include "stdafx.h"
#include "GifOle.h"

extern void _TRACE(const TCHAR *lpszFormat, ...);

#define DEFINE_GUIDXXX(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
	EXTERN_C const GUID CDECL name \
	= { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

DEFINE_GUIDXXX(IID_ITextDocument,0x8CC497C0,0xA1DF,0x11CE,0x80,0x98,
			   0x00,0xAA,0x00,0x47,0xBE,0x5D);

///////////////////////////////////////////////////////////////////////////////
CGifOleObject::CGifOleObject()
{
	m_ulRef = 0;
	m_pGifImage = NULL;
	m_puFrameElapse = NULL;
	m_nFrameCount = 0;
	m_nFramePosition = 0;
	m_pOleClientSite = NULL;
	m_hWndRichEdit = NULL;

	ZeroMemory(m_szGifFile, MAX_PATH * sizeof(TCHAR));
}

CGifOleObject::~CGifOleObject()
{
	DeleteGif();
}

HRESULT WINAPI CGifOleObject::QueryInterface(REFIID iid, void ** ppvObject)
{
	if (iid == IID_IUnknown || iid == IID_IOleObject)
	{
		*ppvObject = (IOleObject *)this;
		((IOleObject *)(*ppvObject))->AddRef();
		return S_OK;
	}
	else if (iid == IID_IViewObject || iid == IID_IViewObject2)
	{
		*ppvObject = (IViewObject2 *)this;
		((IViewObject2 *)(*ppvObject))->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}

ULONG WINAPI CGifOleObject::AddRef(void)
{
	m_ulRef++;

	//_TRACE(_T("AddRef :%d\r\n"), m_ulRef);

	return m_ulRef;
}

ULONG WINAPI CGifOleObject::Release(void)
{
	//_TRACE(_T("Release :%d\r\n"), m_ulRef-1);

	if (--m_ulRef == 0)
	{
		delete this;
		return 0;
	}

	return m_ulRef;
}

HRESULT WINAPI CGifOleObject::SetClientSite(IOleClientSite *pClientSite)
{
	m_pOleClientSite = pClientSite;
	return S_OK;
}

HRESULT WINAPI CGifOleObject::GetClientSite(IOleClientSite **ppClientSite)
{
	*ppClientSite = m_pOleClientSite;
	return S_OK;
}

HRESULT WINAPI CGifOleObject::SetHostNames(LPCOLESTR szContainerApp, LPCOLESTR szContainerObj)
{
	return S_OK;
}

HRESULT WINAPI CGifOleObject::Close(DWORD dwSaveOption)
{
	::KillTimer(m_hWndRichEdit, (UINT_PTR)this);

	DeleteGif();
	return S_OK;
}

HRESULT WINAPI CGifOleObject::SetMoniker(DWORD dwWhichMoniker, IMoniker *pmk)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::InitFromData(IDataObject *pDataObject, BOOL fCreation, DWORD dwReserved)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::GetClipboardData(DWORD dwReserved, IDataObject **ppDataObject)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::DoVerb(LONG iVerb, LPMSG lpmsg, IOleClientSite *pActiveSite, LONG lindex, HWND hwndParent, LPCRECT lprcPosRect)
{
	return S_OK;
}

HRESULT WINAPI CGifOleObject::EnumVerbs(IEnumOLEVERB **ppEnumOleVerb)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::Update(void)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::IsUpToDate(void)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::GetUserClassID(CLSID *pClsid)
{
	*pClsid = IID_NULL;
	return S_OK;
}

HRESULT WINAPI CGifOleObject::GetUserType(DWORD dwFormOfType, LPOLESTR *pszUserType)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::SetExtent(DWORD dwDrawAspect, SIZEL *psizel)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::GetExtent(DWORD dwDrawAspect, SIZEL *psizel)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::Advise(IAdviseSink *pAdvSink, DWORD *pdwConnection)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::Unadvise(DWORD dwConnection)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::EnumAdvise(IEnumSTATDATA **ppenumAdvise)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::GetMiscStatus(DWORD dwAspect, DWORD *pdwStatus)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::SetColorScheme(LOGPALETTE *pLogpal)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::Draw(DWORD dwDrawAspect, LONG lindex, void *pvAspect, DVTARGETDEVICE *ptd,
							HDC hdcTargetDev, HDC hdcDraw, LPCRECTL lprcBounds, LPCRECTL lprcWBounds,
							BOOL ( WINAPI *pfnContinue )(ULONG_PTR dwContinue), ULONG_PTR dwContinue)
{
	if (lindex != -1)
		return S_FALSE;

	RECT rcOleGif;
	rcOleGif.left   = lprcBounds->left;
	rcOleGif.top    = lprcBounds->top;
	rcOleGif.right  = lprcBounds->right;
	rcOleGif.bottom = lprcBounds->bottom;

	DrawFrame(hdcDraw, &rcOleGif);
	return S_OK;
}

HRESULT WINAPI CGifOleObject::GetColorSet(DWORD dwDrawAspect, LONG lindex, void *pvAspect, 
								   DVTARGETDEVICE *ptd, HDC hicTargetDev, LOGPALETTE **ppColorSet)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::Freeze(DWORD dwDrawAspect, LONG lindex, void *pvAspect, DWORD *pdwFreeze)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::Unfreeze(DWORD dwFreeze)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::SetAdvise(DWORD aspects, DWORD advf, IAdviseSink *pAdvSink)
{
	if (m_puFrameElapse)
	{
		long lElapse = m_puFrameElapse[m_nFramePosition];
		::SetTimer(m_hWndRichEdit, (UINT_PTR)this, lElapse, TimerProc);
	}

	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::GetAdvise(DWORD *pAspects, DWORD *pAdvf, IAdviseSink **ppAdvSink)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CGifOleObject::GetExtent(DWORD dwDrawAspect, LONG lindex, DVTARGETDEVICE *ptd, LPSIZEL lpsizel)
{
	SIZE size;
	GetGifSize(&size);

	HDC hDC = ::GetDC(NULL);
	lpsizel->cx = ::MulDiv(size.cx + 2, 2540, GetDeviceCaps(hDC, LOGPIXELSX));
	lpsizel->cy = ::MulDiv(size.cy + 2, 2540, GetDeviceCaps(hDC, LOGPIXELSY));
	::ReleaseDC(NULL, hDC);

	return S_OK;
}

void CGifOleObject::SetRichEditHwnd(HWND hWnd)
{
	m_hWndRichEdit = hWnd;
}

HWND CGifOleObject::GetRichEditHwnd()
{
	return m_hWndRichEdit;
}

BOOL CGifOleObject::LoadGifFromFile(const TCHAR *lpszGifFile)
{
	if (lpszGifFile == NULL || *lpszGifFile == NULL)
		return FALSE;

	DeleteGif();

	//wchar_t szFilePath[300];
	//ZeroMemory(szFilePath, 300);

	//size_t converted = 0;
	//size_t len = strlen(lpszGifFile) + 1;
	//mbstowcs_s(&converted, szFilePath, len, lpszGifFile, _TRUNCATE);

	m_pGifImage = new Image( lpszGifFile );
	if (m_pGifImage == NULL)
		return FALSE;

	_tcsncpy_s(m_szGifFile, lpszGifFile, MAX_PATH);
	
	UINT nCount = 0;
	nCount = m_pGifImage->GetFrameDimensionsCount();
	
	GUID* pDimensionIDs = new GUID[nCount];
	m_pGifImage->GetFrameDimensionsList(pDimensionIDs, nCount);
	
	m_nFrameCount = m_pGifImage->GetFrameCount(&pDimensionIDs[0]);
	
	int nSize = m_pGifImage->GetPropertyItemSize(PropertyTagFrameDelay);
	PropertyItem *pPropertyItem = (PropertyItem *)malloc(nSize);
	m_pGifImage->GetPropertyItem(PropertyTagFrameDelay, nSize, pPropertyItem);

	m_puFrameElapse = new UINT[nSize];

	unsigned int i = 0;
	for (i = 0;i < m_nFrameCount; i++)
	{
		m_puFrameElapse[i] = ((long*)pPropertyItem->value)[i] * 10;
	}

	free(pPropertyItem);
	delete pDimensionIDs;

	return TRUE;
}

void CGifOleObject::GetGifSize(LPSIZE lpSize)
{
	if (lpSize == NULL || m_pGifImage == NULL)
		return;

	lpSize->cx = m_pGifImage->GetWidth();
	lpSize->cy = m_pGifImage->GetHeight();
}

UINT CGifOleObject::GetFrameCount()
{
	return m_nFrameCount;
}

void CGifOleObject::DeleteGif()
{
	if (m_pGifImage)
	{
		delete m_pGifImage;
		m_pGifImage = NULL;
	}

	ZeroMemory(m_szGifFile, MAX_PATH * sizeof(TCHAR));
	if (m_puFrameElapse)
	{
		delete m_puFrameElapse;
		m_puFrameElapse = NULL;
	}

	m_nFrameCount = 0;
	m_nFramePosition = 0;
}

BOOL CGifOleObject::IsAnimatedGIF()
{
	return m_nFrameCount > 1;
}

void CGifOleObject::OnTimer(UINT_PTR idEvent)
{
	if (idEvent != (UINT_PTR)this)
		return;

	::KillTimer(m_hWndRichEdit, (UINT_PTR)this);

	RECT rcOleObject;
	::SetRectEmpty(&rcOleObject);
	GetOleObjectRect(&rcOleObject);

	m_nFramePosition++;
	if (m_nFramePosition == m_nFrameCount)
		m_nFramePosition = 0;

	InvalidateRect(m_hWndRichEdit, &rcOleObject, FALSE);
	//HDC hDC = ::GetDC(m_hWndRichEdit);
	//DrawFrame(hDC, &rcOleObject);
	//::ReleaseDC(m_hWndRichEdit, hDC);

	if (m_puFrameElapse)
	{
		long lElapse = m_puFrameElapse[m_nFramePosition];
		::SetTimer(m_hWndRichEdit, (UINT_PTR)this, lElapse, TimerProc);
	}
}

void CGifOleObject::GetOleObjectRect(LPRECT lpRect)
{
	if (lpRect == NULL || m_hWndRichEdit == NULL)
		return;

	IRichEditOle *pRichEditOle = NULL;
	::SendMessage(m_hWndRichEdit, EM_GETOLEINTERFACE, 0, (LPARAM)&pRichEditOle);

	if (pRichEditOle == NULL)
		return;

	int nObjCount = pRichEditOle->GetObjectCount();
	int i = 0;
	for (i = 0;i < nObjCount;i++)
	{	
		REOBJECT reo;
		ZeroMemory(&reo, sizeof(REOBJECT));
		reo.cbStruct = sizeof(REOBJECT);
	
		HRESULT hr = pRichEditOle->GetObject(i, &reo, REO_GETOBJ_ALL_INTERFACES);
		if (hr != S_OK)
			continue;

		if (reo.poleobj)
			reo.poleobj->Release();

		if (reo.polesite)
			reo.polesite->Release();

		if (reo.pstg)
			reo.pstg->Release();

		if (reo.poleobj == (IOleObject *)this)
		{
			SIZE size;
			GetGifSize(&size);

			ITextDocument *pTextDocument = NULL;
			ITextRange *pTextRange = NULL;

			pRichEditOle->QueryInterface(IID_ITextDocument, (void **)&pTextDocument);
			if (!pTextDocument)
				return;

			long nLeft = 0;
			long nBottom = 0;
			pTextDocument->Range(reo.cp, reo.cp, &pTextRange);
			if (reo.dwFlags & REO_BELOWBASELINE)
				hr = pTextRange->GetPoint(TA_BOTTOM|TA_LEFT, &nLeft, &nBottom);
			else
				hr = pTextRange->GetPoint(TA_BASELINE|TA_LEFT, &nLeft, &nBottom);

			pTextDocument->Release();
			pTextRange->Release();

			RECT rectWindow;
			::GetWindowRect(m_hWndRichEdit, &rectWindow);

			lpRect->left   = nLeft - rectWindow.left;
			lpRect->bottom = nBottom - rectWindow.top;
			lpRect->right  = lpRect->left + size.cx + 2;
			lpRect->top    = lpRect->bottom - size.cy - 2;

			break;
		}
	}

	pRichEditOle->Release();
}

void CGifOleObject::DrawFrame(HDC hDC, LPRECT lpRect)
{
	GUID pageGuid = FrameDimensionTime;

	long hmWidth = m_pGifImage->GetWidth();
	long hmHeight = m_pGifImage->GetHeight();


	Graphics graphics(hDC);
	graphics.DrawImage(m_pGifImage, lpRect->left+1, lpRect->top+1, lpRect->right-lpRect->left-2, 
		lpRect->bottom-lpRect->top-2);

	m_pGifImage->SelectActiveFrame(&pageGuid, m_nFramePosition);
}

/*++ InsertGifRichEdit

Routine Description:

	在RICHEDIT编辑框控件中插入GIF图片

Arguments:

	hWnd           - RICHEDIT控件句柄
	pRichEditOle   - RICHEDIT OLE对象指针
	lpGifPath      - GIF图片文件位置

Return Value:
	
	如果成功,返回真(TRUE).如果失败,返回假(FALSE).

Revision History:

	Oct-26-2010 Eric Qian  Created

--*/
BOOL WINAPI InsertGifRichEdit(HWND hWnd, IRichEditOle* pRichEditOle, const TCHAR *lpGifPath, DWORD dwUserData)
{
	SCODE sc;

	IOleClientSite *pOleClientSite = NULL;
	pRichEditOle->GetClientSite(&pOleClientSite);

	IStorage *pStorage = NULL;

	LPLOCKBYTES lpLockBytes = NULL;
	sc = ::CreateILockBytesOnHGlobal(NULL, TRUE, &lpLockBytes);
	if (sc != S_OK)
		return FALSE;

	sc = ::StgCreateDocfileOnILockBytes(lpLockBytes,
		STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE, 0, &pStorage);
	if (sc != S_OK)
	{
		lpLockBytes->Release();
		lpLockBytes = NULL;
		return FALSE;
	}

	CGifOleObject *pGifOleObject = new CGifOleObject;
	pGifOleObject->SetRichEditHwnd(hWnd);
	pGifOleObject->LoadGifFromFile(lpGifPath);

	IOleObject *pOleObject = NULL;
	pGifOleObject->QueryInterface(IID_IOleObject, (void **)&pOleObject);
	pOleObject->SetClientSite(pOleClientSite);

	HRESULT hr = ::OleSetContainedObject(pOleObject, TRUE);

	REOBJECT reobject;
	ZeroMemory(&reobject, sizeof(REOBJECT));
	reobject.cbStruct = sizeof(REOBJECT);

	reobject.clsid    = CLSID_NULL;
	reobject.cp       = REO_CP_SELECTION;
	reobject.dvaspect = DVASPECT_CONTENT;
	reobject.poleobj  = pOleObject;
	reobject.polesite = pOleClientSite;
	reobject.pstg     = pStorage;
	reobject.dwUser   = dwUserData;

	pRichEditOle->InsertObject(&reobject);

	pOleObject->Release();
	pOleClientSite->Release();
	pStorage->Release();

	return TRUE;
}

/*++ TimerProc

Routine Description:

	GIF动画定时器回调函数

Arguments:

	hWnd           - RICHEDIT控件句柄.
	uMsg           - WM_TIMER消息.
	idEvent        - 定时器标识,这里为CGifOleObject指针.
	dwTime         - 未使用

Return Value:

Revision History:

	Oct-26-2010 Eric Qian  Created

--*/
VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	CGifOleObject *pGifOleObject = (CGifOleObject *)idEvent;
	if (pGifOleObject)
		pGifOleObject->OnTimer(idEvent);
}

