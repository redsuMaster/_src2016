#include "stdafx.h"
#include "ChatList.h"
#include "resourcedll.h"
/*
IDB_PNG197              PNG                     "Res\\网络资源\\_.png"
IDB_PNG198              PNG                     "Res\\网络资源\\+.png"
IDB_PNG199              PNG                     "Res\\网络资源\\撤回.png"
IDB_PNG200              PNG                     "Res\\网络资源\\打开.png"
IDB_PNG201              PNG                     "Res\\网络资源\\放大.png"
IDB_PNG202              PNG                     "Res\\网络资源\\会话-初始.png"
IDB_PNG203              PNG                     "Res\\网络资源\\会话-触发.png"
IDB_PNG204              PNG                     "Res\\网络资源\\聊天初始.png"
IDB_PNG205              PNG                     "Res\\网络资源\\聊天触发.png"
IDB_PNG206              PNG                     "Res\\网络资源\\聊天-记录.png"
IDB_PNG207              PNG                     "Res\\网络资源\\聊天-截屏.png"
IDB_PNG208              PNG                     "Res\\网络资源\\聊天-图片.png"
IDB_PNG209              PNG                     "Res\\网络资源\\聊天-文件.png"
IDB_PNG210              PNG                     "Res\\网络资源\\列表初始.png"
IDB_PNG211              PNG                     "Res\\网络资源\\列表触发.png"
IDB_PNG212              PNG                     "Res\\网络资源\\气泡1-右上.png"
IDB_PNG213              PNG                     "Res\\网络资源\\气泡1-右下.png"
IDB_PNG214              PNG                     "Res\\网络资源\\气泡1-左上.png"
IDB_PNG215              PNG                     "Res\\网络资源\\气泡1-左下.png"
IDB_PNG216              PNG                     "Res\\网络资源\\气泡2-右上.png"
IDB_PNG217              PNG                     "Res\\网络资源\\气泡2-右下.png"
IDB_PNG218              PNG                     "Res\\网络资源\\气泡2-左上.png"
IDB_PNG219              PNG                     "Res\\网络资源\\气泡2-左下.png"
IDB_PNG220              PNG                     "Res\\网络资源\\搜索.png"
IDB_PNG221              PNG                     "Res\\网络资源\\统计-初始.png"
IDB_PNG222              PNG                     "Res\\网络资源\\统计-触发.png"
IDB_PNG223              PNG                     "Res\\网络资源\\图片.png"
IDB_PNG224              PNG                     "Res\\网络资源\\图片打开.png"
IDB_PNG225              PNG                     "Res\\网络资源\\图片加载.png"
IDB_PNG226              PNG                     "Res\\网络资源\\图片下载.png"
IDB_PNG227              PNG                     "Res\\网络资源\\下载.png"
IDB_PNG228              PNG                     "Res\\网络资源\\右上-撤回.png"
IDB_PNG229              PNG                     "Res\\网络资源\\右上打开.png"
IDB_PNG230              PNG                     "Res\\网络资源\\右上-放大O.png"
IDB_PNG231              PNG                     "Res\\网络资源\\右上-缩小-.png"
IDB_PNG232              PNG                     "Res\\网络资源\\右上-提交.png"
IDB_PNG233              PNG                     "Res\\网络资源\\右上-退出X.png"
IDB_PNG234              PNG                     "Res\\网络资源\\右上-退回.png"
IDB_PNG235              PNG                     "Res\\网络资源\\右上-下载.png"
IDB_PNG236              PNG                     "Res\\网络资源\\左列表消息-鼠标显示退出.png"
IDB_PNG237              PNG                     "Res\\网络资源\\左列表-消息提醒.png"
IDB_PNG238              PNG                     "Res\\网络资源\\左列表消息-退出.png"
IDB_PNG239              PNG                     "Res\\网络资源\\左上-搜索.png"
*/
GrowChatList::GrowChatList()
{
	m_UserName = _T("周主任");
	m_NextStartPos = USER_ITEM_START_LINE_SPACE;
	m_bPageRichedInitOver = false;
	m_yOffest = 0;
	MResDll.LoadResToImage(IDB_PNG214, m_pImgbub1);
	MResDll.LoadResToImage(IDB_PNG212, m_pImgbub2);
	MResDll.LoadResToImage(IDB_PNG215, m_pImgbub3);
	MResDll.LoadResToImage(IDB_PNG213, m_pImgbub4);

	MResDll.LoadResToImage(IDB_PNG216, m_pImgbub2_fx);
	MResDll.LoadResToImage(IDB_PNG218, m_pImgbub1_fx);
	MResDll.LoadResToImage(IDB_PNG217, m_pImgbub4_fx);
	MResDll.LoadResToImage(IDB_PNG219, m_pImgbub3_fx);

	/*m_pImgbub1_fx->RotateFlip(Gdiplus::RotateNoneFlipX);
	m_pImgbub2_fx->RotateFlip(Gdiplus::RotateNoneFlipX);
	m_pImgbub3_fx->RotateFlip(Gdiplus::RotateNoneFlipX);
	m_pImgbub4_fx->RotateFlip(Gdiplus::RotateNoneFlipX);*/

	  m_bisShowScroll = false;
	  m_bisHoverView = false;
	  m_bisHoverScroll = false;
	  m_MoreMsgRc = CRect(0, 10, 0, 22);
	  m_MoreMsgHeight = 12;
	  m_bonpaint = true;
	  m_bisHoverMoreString = false;
}



GrowChatList::~GrowChatList()
{ 
	_DELETE_IMAGE(m_pImgbub1)
		_DELETE_IMAGE(m_pImgbub2)
		_DELETE_IMAGE(m_pImgbub3)
		_DELETE_IMAGE(m_pImgbub4)

		_DELETE_IMAGE(m_pImgbub1_fx)
		_DELETE_IMAGE(m_pImgbub2_fx)
		_DELETE_IMAGE(m_pImgbub3_fx)
		_DELETE_IMAGE(m_pImgbub4_fx)

		if (m_pMeasurewr) delete m_pMeasurewr;
}

//视图窗口创建
BOOL GrowChatList::Create(CWnd *Parent, CRect Rect, DWORD Style, int ID)
{
	if (Rect.Width() <= 370) Rect.right = Rect.left + 370;
	m_Rect = Rect;
	if (Style == 0)
		return CWnd::Create(NULL, NULL,   WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE | WS_CLIPSIBLINGS, Rect, Parent, ID, NULL);
	else
		return CWnd::Create(NULL, NULL, Style, Rect, Parent, NULL, NULL);
}

BEGIN_MESSAGE_MAP(GrowChatList, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEHWHEEL()
	ON_WM_NCHITTEST()
	ON_WM_SIZE()
END_MESSAGE_MAP()


int GrowChatList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)  return -1;

	//初始化虚拟测量riched
	/*m_Measurewr.CreateWlessRiched(this->m_hWnd, GetParent()->m_hWnd, CRect(0, 0, (m_Rect.Width() - USER_HEAD_EDIT_SPACE)*0.9, m_Rect.Height()));
	m_Measurewr.KillFocus(); */
	m_MeasurewrWnd.Create(NULL, NULL, WS_CHILD | WS_CLIPCHILDREN  | WS_CLIPSIBLINGS, CRect(0,0,0,0), GetParent(), 0, NULL);
	m_MeasurewrWnd.ShowWindow(SW_HIDE);
	m_pMeasurewr = new CWlessRiched;
	m_pMeasurewr->CreateWlessRiched(m_MeasurewrWnd.m_hWnd, m_MeasurewrWnd.m_hWnd, CRect(0, 0, (m_Rect.Width() - USER_HEAD_EDIT_SPACE)*0.9, m_Rect.Height()));
	m_pMeasurewr->KillFocus();
	//初始化页面pageriched
	for (int i = 0; i < MAX_WLESS_RICHEDIT;i++)
	{
		m_PageRiched[i].IdAttachItem = -1;
		m_PageRiched[i].bShowInPage = false;
		m_PageRiched[i].Riched.CreateWlessRiched(this->m_hWnd, GetParent()->m_hWnd, CRect(0, 0, (m_Rect.Width() - USER_HEAD_EDIT_SPACE)*0.9, 611));
		m_PageRiched[i].Riched.SetReadOnly(true);
		m_PageRiched[i].Riched.KillFocus();
	}
	m_bPageRichedInitOver = true;
	AddStringItem(_T("行距"), _T("zhang"));
	for (int i = 0; i < 100; i++)
	{
		CString p;
		p.Format(_T("i=%dv "), i);
		AddStringItem(_T("非法"), _T("0000"));
		AddStringItem(_T("啦啦啦"), _T("你好") + p);
		AddStringItem(_T("周主任"), _T("你好") + p);
		AddStringItem(_T("赵虎"), _T("你好"));
		AddStringItem(_T("周主任"), _T("立坤咯卡收立坤咯卡收费呢似懂非懂的立坤咯卡收费呢似"));
		AddStringItem(_T("赵虎"), _T("立坤咯卡收立坤咯卡收费呢似懂非懂的立坤咯卡收费呢似立坤咯卡收立坤咯卡收费呢似懂非懂的立坤咯卡收费呢似懂非懂的立坤咯卡收费呢似懂非懂的费呢12345679"));
		AddStringItem(_T("周主任"), _T("立坤咯卡收立坤咯卡收费呢似懂非懂的立坤咯卡收费呢似立坤咯卡收立坤咯卡收费呢似懂非懂的立坤咯卡收费呢似懂非懂的立坤咯卡收费呢似懂非懂的费呢"));
		AddTimeItem(_T("2016/6/6 15:33:15"));

		AddStringItem(_T("周主任"), _T("你好"));
		AddStringItem(_T("刘u"), _T("你好"));
		AddTimeItem(_T("2016/6/6 15:33:15"));
		AddStringItem(_T("清肺"), _T("你好,大家好"));
		AddStringItem(_T("流量费"), _T("01你好"));
	}
	AddStringItem(_T("周主任"), _T("你好22245233333333222222234"));

	AddMoreMsgItem();


	StartInsertItemGroupInFront();


	AddStringItemToItemGroup(_T("赵虎2"), _T("你好098543223577"));
	AddTimeItemToItemGroup(_T("2016/6/8 18:33:15"));

	AddMoreMsgItemToItemGroup();

	OverInsertItemGroupInFront();



	printf("总:%d", m_Item.size());

	SetScrollPosInBom();
	/*IRichEditOle* pp = m_rich.m_tWinHost->GetOle();
	if (pp)
	{
		HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetApp()->m_hInstance, _T("d:\\test.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);//从文件中加载，
		if (NULL == hBitmap)
		{
			::MessageBox(NULL, _T("图片文件没有找到"), NULL, MB_OK);
		}
		CImageDataObject::InsertBitmap(pp, hBitmap, 0);
		CImageDataObject::InsertBitmap(pp, hBitmap, 0);
		pp->Release();
		pp = NULL;
		m_rich.m_tWinHost->InsertGif(_T("d:\\l.gif"), 0);
	}*/

	return 0;
}

SIZE GrowChatList::GetStringSize(CString pString)
{
	SIZE size = m_pMeasurewr->GetStringBox(pString);

	return size;
}


BOOL GrowChatList::PreTranslateMessage(MSG* pMsg)
{
	return CWnd::PreTranslateMessage(pMsg);
}

//绘制气泡
void GrowChatList::DrawBubble(CDC *pDC, Graphics &graph,CHAT_LIST_ITEM *pItem, bool bleft)
{
	COLORREF bkclr = RGB(201, 233, 244);
	COLORREF bkclrRihgt = RGB(224, 224, 224);
	CRect prc = pItem->BubblePos;
	if (bleft)
	{	
	prc.top += pItem->StartPos;
	prc.bottom += pItem->StartPos;
	prc.left  += PAGE_BUBBLE_LEFT_OF;
	prc.right += PAGE_BUBBLE_LEFT_OF;
	graph.DrawImage(m_pImgbub1, prc.left, prc.top-m_yOffest, m_pImgbub1->GetWidth(), m_pImgbub1->GetHeight());
	graph.DrawImage(m_pImgbub2, prc.right - m_pImgbub2->GetWidth(), prc.top - m_yOffest, m_pImgbub2->GetWidth(), m_pImgbub2->GetHeight());
	graph.DrawImage(m_pImgbub3, BUBBLE_TAB + prc.left, prc.bottom - m_pImgbub3->GetHeight() - m_yOffest, m_pImgbub3->GetWidth(), m_pImgbub3->GetHeight());
	graph.DrawImage(m_pImgbub4, prc.right - m_pImgbub4->GetWidth(), INT(prc.bottom - m_pImgbub4->GetHeight()) - m_yOffest, m_pImgbub4->GetWidth(), m_pImgbub4->GetHeight());

	pDC->FillSolidRect(_GRECT(BUBBLE_TAB + prc.left, prc.top + m_pImgbub1->GetHeight() - m_yOffest, m_pImgbub3->GetWidth(), prc.Height() - m_pImgbub1->GetHeight() - m_pImgbub3->GetHeight()), bkclr);
	pDC->FillSolidRect(_GRECT(prc.right - m_pImgbub4->GetWidth(), prc.top + m_pImgbub2->GetHeight() - m_yOffest, m_pImgbub2->GetWidth(), prc.Height() - m_pImgbub2->GetHeight() - m_pImgbub4->GetHeight()), bkclr);
	pDC->FillSolidRect(_GRECT(prc.left + m_pImgbub1->GetWidth(), prc.top - m_yOffest, prc.Width() - m_pImgbub2->GetWidth() - m_pImgbub1->GetWidth(), prc.Height()), bkclr);
	}
	else
	{
		int wid = prc.Width();
		prc.top += pItem->StartPos;
		prc.bottom += pItem->StartPos;
		prc.left += (m_Rect.Width() - PAGE_BUBBLE_LEFT_OF - wid);
		prc.right += (m_Rect.Width() - PAGE_BUBBLE_LEFT_OF - wid);

		graph.DrawImage(m_pImgbub1_fx, prc.left, prc.top - m_yOffest, m_pImgbub1_fx->GetWidth(), m_pImgbub1_fx->GetHeight());
		graph.DrawImage(m_pImgbub2_fx, prc.right - m_pImgbub2_fx->GetWidth(), prc.top - m_yOffest, m_pImgbub2_fx->GetWidth(), m_pImgbub2_fx->GetHeight());
		graph.DrawImage(m_pImgbub3_fx, prc.left, prc.bottom - m_pImgbub3_fx->GetHeight() - m_yOffest, m_pImgbub3_fx->GetWidth(), m_pImgbub3_fx->GetHeight());
		graph.DrawImage(m_pImgbub4_fx, prc.right - m_pImgbub4_fx->GetWidth() - BUBBLE_TAB, INT(prc.bottom - m_pImgbub4_fx->GetHeight()) - m_yOffest, m_pImgbub4_fx->GetWidth(), m_pImgbub4_fx->GetHeight());

		pDC->FillSolidRect(_GRECT(prc.left, prc.top + m_pImgbub1_fx->GetHeight() - m_yOffest, m_pImgbub3_fx->GetWidth(), prc.Height() - m_pImgbub1_fx->GetHeight() - m_pImgbub3_fx->GetHeight()), bkclrRihgt);
		pDC->FillSolidRect(_GRECT(prc.right - m_pImgbub4_fx->GetWidth() - BUBBLE_TAB, prc.top + m_pImgbub2_fx->GetHeight() - m_yOffest, m_pImgbub4_fx->GetWidth(), prc.Height() - m_pImgbub2_fx->GetHeight() - m_pImgbub4_fx->GetHeight()), bkclrRihgt);
		pDC->FillSolidRect(_GRECT(prc.left + m_pImgbub1_fx->GetWidth(), prc.top - m_yOffest, prc.Width() - m_pImgbub2_fx->GetWidth() - m_pImgbub1_fx->GetWidth(), prc.Height()), bkclrRihgt);

	}
}

void GrowChatList::DrawVerticalScroll(CDC *pDC, Graphics &graph)
{
	if (m_bisShowScroll)
	{
		if (m_bisHoverView)
		{
			//绘制滚动条背景
			FillVRoundRectangle(graph, RGB(204, 204, 204), m_Rect.right - 14, 1, 10, m_Rect.Height() - 2, 5, 5);

			FillVRoundRectangle(graph, RGB(122, 122, 122), m_VScrollRect.left, m_VScrollRect.top, m_VScrollRect.Width(), m_VScrollRect.Height(), 5, 5);

		}
		else if (m_bisHoverScroll)
		{
			//绘制滚动条
			FillVRoundRectangle(graph, RGB(204, 204, 204), m_VScrollRect.left, m_VScrollRect.top, m_VScrollRect.Width(), m_VScrollRect.Height(), 5, 5);

		}
	}
	
}


void GrowChatList::DrawStringMsg(CDC*pDC, Graphics &graph,  CHAT_LIST_ITEM *pItem)
{

	if (pItem->bIsMyMsg)
	{
		FillRoundRectangle(graph, RGB(107, 210, 252), m_Rect.Width() - PAGE_RIGHT - USER_HEAD_PIC_WIDTH, pItem->StartPos - m_yOffest, USER_HEAD_PIC_WIDTH, USER_HEAD_PIC_HEIGHT, 8, 8);
		DrawBubble(pDC, graph, pItem, false);
		CString pHeaderStr = CString(pItem->UserName[0]);

		//绘制姓名
		Gdiplus::Font grFont(_TEXT("微软雅黑"), 18, FontStyleRegular, UnitPixel);
		SolidBrush brush(Color::MakeARGB(255, 0, 0, 0));
		StringFormat strformat1;
		strformat1.SetAlignment(StringAlignmentCenter);
		strformat1.SetLineAlignment(StringAlignmentCenter);
		graph.DrawString(pHeaderStr, -1, &grFont, RectF(m_Rect.Width() - PAGE_RIGHT - USER_HEAD_PIC_WIDTH, pItem->StartPos - m_yOffest, USER_HEAD_PIC_WIDTH, USER_HEAD_PIC_HEIGHT), &strformat1, &brush);
		
		//Gdiplus::Font grFont2(_TEXT("微软雅黑"), 12, FontStyleRegular, UnitPixel);
		//SolidBrush brush2(Color::MakeARGB(255, 0x69, 0x69, 0x69));
		//StringFormat strformat2;
		//strformat2.SetAlignment(StringAlignmentFar);
		//strformat2.SetLineAlignment(StringAlignmentCenter);
		//graph.DrawString(pItem->UserName, -1, &grFont2, RectF(0, pItem->StartPos - m_yOffest, m_Rect.Width() - PAGE_RIGHT - USER_HEAD_PIC_WIDTH-2, 20), &strformat2, &brush2);
	}
	else
	{
		FillRoundRectangle(graph, RGB(107, 210, 252), PAGE_LEFT, pItem->StartPos - m_yOffest, USER_HEAD_PIC_WIDTH, USER_HEAD_PIC_HEIGHT, 8, 8);
		DrawBubble(pDC, graph, pItem);
		CString pHeaderStr = CString(pItem->UserName[0]);

		//绘制姓名
		Gdiplus::Font grFont(_TEXT("微软雅黑"), 18, FontStyleRegular, UnitPixel);
		Gdiplus::Font grFont2(_TEXT("微软雅黑"), 12, FontStyleRegular, UnitPixel);
		SolidBrush brush(Color::MakeARGB(255, 0, 0, 0));
		SolidBrush brush2(Color::MakeARGB(255, 0x69, 0x69, 0x69));
		StringFormat strformat1;
		strformat1.SetAlignment(StringAlignmentCenter);
		strformat1.SetLineAlignment(StringAlignmentCenter);
		StringFormat strformat2;
		strformat2.SetAlignment(StringAlignmentNear);
		strformat2.SetLineAlignment(StringAlignmentCenter);
		graph.DrawString(pHeaderStr, -1, &grFont, RectF(PAGE_LEFT, pItem->StartPos - m_yOffest, USER_HEAD_PIC_WIDTH, USER_HEAD_PIC_HEIGHT), &strformat1, &brush);
		graph.DrawString(pItem->UserName, -1, &grFont2, RectF(PAGE_LEFT + 40 + 2, pItem->StartPos - m_yOffest, 300, 20), &strformat2, &brush2);
	}

}

void GrowChatList::DrawTimeMsg(CDC*pDC,Graphics &graph,CHAT_LIST_ITEM *pItem)
{
	SYSTEMTIME sTime;
	CString  strTime;
	GetLocalTime(&sTime);
	strTime.Format(_T("%d/%d/%d"), sTime.wYear, sTime.wMonth, sTime.wDay);
	CString DayT=pItem->UserMsg.Left(pItem->UserMsg.ReverseFind(' '));
	CString Hour = pItem->UserMsg.Right(pItem->UserMsg.GetLength()-pItem->UserMsg.ReverseFind(' ')-1);
	CString DrawString_;
	if (DayT == strTime)
	{
		DrawString_ = Hour;
	}
	else
	{
		DrawString_ = pItem->UserMsg;
	}

	Gdiplus::Font grFont12(_TEXT("微软雅黑"), 12, FontStyleRegular, UnitPixel);
	SolidBrush brush2(Color::MakeARGB(255, 0x69, 0x69, 0x69));
	StringFormat strformat1;
	strformat1.SetAlignment(StringAlignmentCenter);
	strformat1.SetLineAlignment(StringAlignmentCenter);
	graph.DrawString(DrawString_, -1, &grFont12, RectF(0, pItem->StartPos - m_yOffest, m_Rect.Width(), pItem->ItemHeight), &strformat1, &brush2);



}
void GrowChatList::DrawMoreMsg(CDC*pDC, Graphics &graph, CHAT_LIST_ITEM *pItem)
{
	Gdiplus::Font grFont12(_TEXT("微软雅黑"), 12, FontStyleRegular, UnitPixel);
	Gdiplus::Font grFont12_(_TEXT("微软雅黑"), 12, FontStyleUnderline, UnitPixel);

	SolidBrush brush2(Color::MakeARGB(255, 95, 196, 224));
	SolidBrush brush22(Color::MakeARGB(255, 22, 112, 235));
	StringFormat strformat1;
	strformat1.SetAlignment(StringAlignmentCenter);
	strformat1.SetLineAlignment(StringAlignmentCenter);
	if (m_bisHoverMoreString)
		graph.DrawString(pItem->UserMsg, -1, &grFont12_, RectF(0, pItem->StartPos - m_yOffest, m_Rect.Width(), pItem->ItemHeight), &strformat1, &brush22);
	else graph.DrawString(pItem->UserMsg, -1, &grFont12, RectF(0, pItem->StartPos - m_yOffest, m_Rect.Width(), pItem->ItemHeight), &strformat1, &brush2);



}
void GrowChatList::OnDraw(CDC *pDC, CRect rc)
{
	pDC->FillSolidRect(rc, RGB(250, 250, 250));
	Graphics graph(pDC->m_hDC);

	for (int i = m_ShowIdStart; i < m_ShowIdEnd+1; i++)
	{
	
		if (m_Item[i].MsgType == ENUM_TYPE_STRING)
		{
			DrawStringMsg(pDC, graph, &m_Item[i]);

		}
		if (m_Item[i].MsgType == ENUM_TYPE_PICTRUE)
		{

		}
		if (m_Item[i].MsgType == ENUM_TYPE_FILE)
		{

		}
		if (m_Item[i].MsgType == ENUM_TYPE_TIME)
		{
			DrawTimeMsg(pDC, graph,&m_Item[i]);
		}
		if (m_Item[i].MsgType == ENUM_TYPE_MORE_MSG)
		{
			DrawMoreMsg(pDC, graph, &m_Item[i]);
		}
	}
	DrawVerticalScroll(pDC, graph);

	//绘制attach edit
	int nOldMode = ::SetGraphicsMode(pDC->m_hDC, GM_COMPATIBLE);
	for (int i = 0; i < MAX_WLESS_RICHEDIT; i++)
	{
		if (m_PageRiched[i].bShowInPage)
		{
			m_PageRiched[i].Riched.OnPaint(pDC);
		}
	}
	::SetGraphicsMode(pDC->m_hDC, nOldMode);
	//绘制外边框
	CPen pens(PS_SOLID, 1, RGB(180, 180, 180));
	pDC->SelectObject(pens);
	pDC->SelectObject(GetStockObject(NULL_BRUSH));
	pDC->Rectangle(rc);
	graph.ReleaseHDC(pDC->m_hDC);
}

void GrowChatList::OnPaint()
{
	if (m_bonpaint)
	{
		CWnd::OnPaint();
		CClientDC dc(this);
		CDC*pDC = &dc;
		CDC  MemDC;
		CBitmap Bmp;
		CRect m_Rc;
		GetClientRect(&m_Rc);
		MemDC.CreateCompatibleDC(pDC);
		Bmp.CreateCompatibleBitmap(pDC, m_Rc.Width(), m_Rc.Height());
		MemDC.SelectObject(&Bmp);
		OnDraw(&MemDC, m_Rc);
		pDC->BitBlt(0, 0, m_Rc.Width(), m_Rc.Height(), &MemDC, 0, 0, SRCCOPY);
		Bmp.DeleteObject();
		MemDC.DeleteDC();
	}
}

void GrowChatList::AttachWlessRichedit(int ItemId)
{
	for (int i = 0; i < MAX_WLESS_RICHEDIT; i++)
	{
		if (m_PageRiched[i].bShowInPage == false)
		{
			m_PageRiched[i].bShowInPage = true;
			m_PageRiched[i].IdAttachItem = ItemId;
			m_PageRiched[i].Riched.m_tWinHost->GetTextServices()->TxSetText(m_Item[ItemId].UserMsg);
			//需要矫正Left偏移
			if (m_Item[ItemId].bIsMyMsg)
			{
				int ofx = (m_Rect.Width() - PAGE_BUBBLE_LEFT_OF - m_Item[ItemId].BubblePos.Width() - 9);
				//int rl = (m_Item[ItemId].BubblePos.Width() - BUBBLE_TAB - m_Item[i].RichedSize.cx) / 2.0;
				m_PageRiched[i].Riched.SetViewRect(_GRECT(ofx + m_Item[ItemId].BubblePos.left + BUBBLE_TAB + USER_MSG_BUBBLE_LEFTRIGHT, m_Item[ItemId].BubblePos.top + USER_MSG_BUBBLE_TOPBOM - 2, m_Item[i].RichedSize.cx, m_Item[i].RichedSize.cy));
			}
			else
			{
				//int rl = (m_Item[ItemId].BubblePos.Width() - BUBBLE_TAB - m_Item[i].RichedSize.cx) / 2.0;
				m_PageRiched[i].Riched.SetViewRect(_GRECT(PAGE_BUBBLE_LEFT_OF + m_Item[ItemId].BubblePos.left + BUBBLE_TAB + USER_MSG_BUBBLE_LEFTRIGHT, m_Item[ItemId].BubblePos.top + USER_MSG_BUBBLE_TOPBOM - 2, m_Item[i].RichedSize.cx, m_Item[i].RichedSize.cy));
			}
			break;
		}
	}

}

void GrowChatList::AddStringItem(CString UserName, CString MsgStr)
{
		CHAT_LIST_ITEM tmp;
		if (m_UserName == UserName) tmp.bIsMyMsg = true;
		else tmp.bIsMyMsg = false;
		tmp.UserName = UserName;
		tmp.UserMsg = MsgStr;
		tmp.MsgType = ENUM_TYPE_STRING;
		//先计算整体高度
		SIZE size = GetStringSize(MsgStr);
		int sigleOffestx = 0;
		/*if (size.cx<m_Measurewr.m_pos.Width())
		{
			//sigleOffestx = 5;//处理多余
			size.cx = size.cx - sigleOffestx;
		}*/
		//printf("%ws===size.cx=%d\n", MsgStr, size.cx);
		tmp.RichedSize = size;
		tmp.StartPos = m_NextStartPos;
		if (tmp.bIsMyMsg)
		{
			if (size.cy > USER_HEAD_PIC_HEIGHT)
				tmp.ItemHeight = size.cy + USER_ITEM_LINE_SPACE + USER_MSG_BUBBLE_TOPBOM * 2;
			else tmp.ItemHeight = USER_HEAD_PIC_HEIGHT + USER_ITEM_LINE_SPACE;
			tmp.BubblePos = _GRECT(0, 0, tmp.RichedSize.cx + USER_MSG_BUBBLE_LEFTRIGHT * 2 + BUBBLE_TAB, tmp.RichedSize.cy + USER_MSG_BUBBLE_TOPBOM * 2);
		}
		else
		{
			tmp.ItemHeight = size.cy + USER_ITEM_LINE_SPACE + USER_HEAD_NAMETOMSG_SPACE + USER_MSG_BUBBLE_TOPBOM * 2;
			tmp.BubblePos = _GRECT(0, USER_HEAD_NAMETOMSG_SPACE, tmp.RichedSize.cx + USER_MSG_BUBBLE_LEFTRIGHT * 2 + BUBBLE_TAB, tmp.RichedSize.cy + USER_MSG_BUBBLE_TOPBOM * 2);
		}


		m_Item.push_back(tmp);
		m_NextStartPos += tmp.ItemHeight;
		YOffestReset();
	
}

void GrowChatList::AddFileItem()
{
	/*CHAT_LIST_ITEM tmp;
	tmp.UserMsg = TimeStr;
	tmp.MsgType = ENUM_TYPE_TIME;
	tmp.StartPos = m_NextStartPos;
	tmp.ItemHeight = 32;
	m_Item.push_back(tmp);
	m_NextStartPos += tmp.ItemHeight;
	JudgeShowScroll();*/

}

void GrowChatList::AddPictureItem()
{


}

void GrowChatList::AddTimeItem(CString TimeStr)
{
	
		CHAT_LIST_ITEM tmp;
		tmp.UserMsg = TimeStr;
		tmp.MsgType = ENUM_TYPE_TIME;
		tmp.StartPos = m_NextStartPos;
		tmp.ItemHeight = 32;
		m_Item.push_back(tmp);
		m_NextStartPos += tmp.ItemHeight;
		JudgeShowScroll();
	
}

//添加一个TopMoreGet 
void GrowChatList::AddMoreMsgItem()
{
	/*CHAT_LIST_ITEM tmp;
	tmp.UserMsg = _T("点击获取更多消息");
	tmp.MsgType = ENUM_TYPE_MORE_MSG;
	tmp.StartPos = USER_ITEM_START_LINE_SPACE;
	tmp.ItemHeight = 22;
	//对之前的所有Pos+22
	for (int i = 0; i < m_Item.size();i++)
	{
		m_Item[i].StartPos = m_Item[i].StartPos + 22;
	}
	m_Item.push_front(tmp);
	m_NextStartPos += tmp.ItemHeight;
	YOffestReset();*/
	StartInsertItemGroupInFront();
	AddMoreMsgItemToItemGroup();
	OverInsertItemGroupInFront();


}

void GrowChatList::MoveWindowEx(int x, int y, int ox, int oy)
{
	
	if (ox < 370) ox = 370;
	if (oy < 200) oy = 200;
	m_Rect = _GRECT(0, 0, ox, oy);
	m_pMeasurewr->SetViewRect(CRect(0, 0, (ox - USER_HEAD_EDIT_SPACE)*0.9, 611));
	
	/*if (m_pMeasurewr)
	{
	delete m_pMeasurewr;
	m_pMeasurewr = new CWlessRiched;
	m_pMeasurewr->CreateWlessRiched(m_MeasurewrWnd.m_hWnd, m_MeasurewrWnd.m_hWnd, CRect(0, 0, (ox - USER_HEAD_EDIT_SPACE)*0.9, oy));
	m_pMeasurewr->KillFocus();
	}*/
	
	//重新校准气泡和riched位置
	RuntStart()
	m_NextStartPos = USER_ITEM_START_LINE_SPACE;
	for (int i = 0; i < m_Item.size(); i++)
	{
		int lh = m_pMeasurewr->GetLineHeight();
		m_Item[i].StartPos = m_NextStartPos; 
		if (m_Item[i].MsgType == ENUM_TYPE_STRING)
		{
			SIZE size = m_Item[i].RichedSize;
			if (!(m_Item[i].RichedSize.cx <= (ox - USER_HEAD_EDIT_SPACE)*0.9&&m_Item[i].RichedSize.cy <= lh))
			{
				size = GetStringSize(m_Item[i].UserMsg);
				//printf("%d[%d,%d] \n",i, size.cx, size.cy);
				m_Item[i].RichedSize = size;
			}
			if (m_Item[i].bIsMyMsg)
			{
				if (size.cy > USER_HEAD_PIC_HEIGHT)
					m_Item[i].ItemHeight = size.cy + USER_ITEM_LINE_SPACE + USER_MSG_BUBBLE_TOPBOM * 2;
				else 	m_Item[i].ItemHeight = USER_HEAD_PIC_HEIGHT + USER_ITEM_LINE_SPACE;
				m_Item[i].BubblePos = _GRECT(0, 0, m_Item[i].RichedSize.cx + USER_MSG_BUBBLE_LEFTRIGHT * 2 + BUBBLE_TAB, m_Item[i].RichedSize.cy + USER_MSG_BUBBLE_TOPBOM * 2);
			}
			else
			{
				m_Item[i].ItemHeight = size.cy + USER_ITEM_LINE_SPACE + USER_HEAD_NAMETOMSG_SPACE + USER_MSG_BUBBLE_TOPBOM * 2;
				m_Item[i].BubblePos = _GRECT(0, USER_HEAD_NAMETOMSG_SPACE, m_Item[i].RichedSize.cx + USER_MSG_BUBBLE_LEFTRIGHT * 2 + BUBBLE_TAB, m_Item[i].RichedSize.cy + USER_MSG_BUBBLE_TOPBOM * 2);
			}
		}
		m_NextStartPos += m_Item[i].ItemHeight;
	}
	RuntEnd(T24);
	YOffestReset();
	MoveWindow(_GRECT(x, y, ox, oy));

}

void GrowChatList::StartInsertItemGroupInFront()
{
	ItemGroup.clear();
}

void GrowChatList::OverInsertItemGroupInFront()
{
	if (ItemGroup.size() <= 0) return;
	//记录所有已经存在的Item应当加上的偏移
	int ItemHeightOffest=0;
	//记录已有的ItemPos起始点和终止点
	int Al_Item_Start;
	int Al_Item_End;
	//校准Id记录
	int Attach_id_offest=0;
	//判断topMsg是否是更多消息
	if (m_Item.size()>0 && m_Item[0].MsgType == ENUM_TYPE_MORE_MSG) 
	{
		//删除这个更多消息
		ItemHeightOffest = ItemHeightOffest-m_Item[0].ItemHeight;
		m_Item.erase(m_Item.begin() + 0);
		Attach_id_offest = -1;
	}
	Al_Item_Start = ItemGroup.size();
	Al_Item_End = m_Item.size() + ItemGroup.size() - 1;
	Attach_id_offest += ItemGroup.size();
	//计算添加的Group总高度
	int GroupSumHeight = USER_ITEM_START_LINE_SPACE;
	for (int i = 0; i < ItemGroup.size();i++)
	{
		GroupSumHeight += ItemGroup[i].ItemHeight;
	}
	int TmpHeight = GroupSumHeight;
	//偏移高度计算
	ItemHeightOffest = ItemHeightOffest + GroupSumHeight;
	for (int i = 0; i < ItemGroup.size(); i++)
	{
		TmpHeight = TmpHeight - ItemGroup[i].ItemHeight;
		ItemGroup[i].StartPos = TmpHeight;
		m_Item.push_front(ItemGroup[i]);
	}
	//重新计算已有ItemStartPos
	for (int i = Al_Item_Start; i <=Al_Item_End; i++)
	{
		m_Item[i].StartPos = m_Item[i].StartPos + ItemHeightOffest;
	}
	//设置页面总高度
	m_NextStartPos = m_NextStartPos + ItemHeightOffest;


	//校准AttachItemId
	for (int i = 0; i < MAX_WLESS_RICHEDIT; i++)
	{
		if (m_PageRiched[i].bShowInPage == true)
		{
			m_PageRiched[i].IdAttachItem += Attach_id_offest;
		}
	}

	//刷新界面
	YOffestReset();
}

//组元素添加 添加一个点击获取更多消息
bool GrowChatList::AddMoreMsgItemToItemGroup()
{
	if (ItemGroup.size() && ItemGroup[ItemGroup.size() - 1].MsgType == ENUM_TYPE_MORE_MSG) return false;
	//注意获取更多消息在队列中最多只存留一个Item
	CHAT_LIST_ITEM tmp;
	tmp.UserMsg = _T("点击获取更多消息");
	tmp.MsgType = ENUM_TYPE_MORE_MSG;
	tmp.StartPos = USER_ITEM_START_LINE_SPACE;
	tmp.ItemHeight = 22;
	ItemGroup.push_back(tmp);
	return true;
}

bool GrowChatList::AddStringItemToItemGroup(CString UserName, CString MsgStr)
{
	if (ItemGroup.size() && ItemGroup[ItemGroup.size() - 1].MsgType == ENUM_TYPE_MORE_MSG) return false;
	CHAT_LIST_ITEM tmp;
	if (m_UserName == UserName) tmp.bIsMyMsg = true;
	else tmp.bIsMyMsg = false;
	tmp.UserName = UserName;
	tmp.UserMsg = MsgStr;
	tmp.MsgType = ENUM_TYPE_STRING;
	//先计算整体高度
	SIZE size = GetStringSize(MsgStr);
	tmp.RichedSize = size;
	if (tmp.bIsMyMsg)
	{
		if (size.cy > USER_HEAD_PIC_HEIGHT)
			tmp.ItemHeight = size.cy + USER_ITEM_LINE_SPACE + USER_MSG_BUBBLE_TOPBOM * 2;
		else tmp.ItemHeight = USER_HEAD_PIC_HEIGHT + USER_ITEM_LINE_SPACE;
		tmp.BubblePos = _GRECT(0, 0, tmp.RichedSize.cx + USER_MSG_BUBBLE_LEFTRIGHT * 2 + BUBBLE_TAB, tmp.RichedSize.cy + USER_MSG_BUBBLE_TOPBOM * 2);
	}
	else
	{
		tmp.ItemHeight = size.cy + USER_ITEM_LINE_SPACE + USER_HEAD_NAMETOMSG_SPACE + USER_MSG_BUBBLE_TOPBOM * 2;
		tmp.BubblePos = _GRECT(0, USER_HEAD_NAMETOMSG_SPACE, tmp.RichedSize.cx + USER_MSG_BUBBLE_LEFTRIGHT * 2 + BUBBLE_TAB, tmp.RichedSize.cy + USER_MSG_BUBBLE_TOPBOM * 2);
	}
	ItemGroup.push_back(tmp);
	return true;
}

bool GrowChatList::AddTimeItemToItemGroup(CString TimeStr)
{
	if (ItemGroup.size()&&ItemGroup[ItemGroup.size() - 1].MsgType == ENUM_TYPE_MORE_MSG) return false;
	CHAT_LIST_ITEM tmp;
	tmp.UserMsg = TimeStr;
	tmp.MsgType = ENUM_TYPE_TIME;
	tmp.ItemHeight = 32;
	ItemGroup.push_back(tmp);
	return true;
}

void GrowChatList::JudgeShowScroll()
{
	if (m_NextStartPos > m_Rect.Height()) m_bisShowScroll = true;
	else m_bisShowScroll = false;

	//计算垂直滚动条高度
	float dyscr = m_Rect.Height() / (float)m_NextStartPos*(m_Rect.Height() - 2-30)+30;
	float dypre = m_yOffest / (float)m_NextStartPos*(m_Rect.Height() - 2 - 30);
	m_VScrollRect = CRect(m_Rect.right - 14, dypre + 1, m_Rect.right - 14 + 10, dypre + 1 + dyscr);


}

LRESULT GrowChatList::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LONG x = LOWORD(lParam);
	LONG y = HIWORD(lParam);

	if (m_bPageRichedInitOver)
	{
		switch (message)
		{
		case WM_LBUTTONDOWN://处理响应焦点问题
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(&pt);
			for (int i = 0; i < MAX_WLESS_RICHEDIT; i++)
			{
				if (m_PageRiched[i].bShowInPage)
				{
					if (PtInRect(m_PageRiched[i].Riched.m_pos, pt))
					{
						m_PageRiched[i].Riched.SetSel(-1, 0);
						//如果不是点击这个Edit 就取消所有选中和失焦
						for (int j = 0; j < MAX_WLESS_RICHEDIT; j++)
						{
							if (i != j)
							{
								m_PageRiched[j].Riched.KillFocus();
								m_PageRiched[j].Riched.SetSel(-1, 0);
							}
						}

						if (m_PageRiched[i].Riched.m_bFocus == FALSE)  m_PageRiched[i].Riched.SetFocus();
							LRESULT lres = m_PageRiched[i].Riched.m_tWinHost->TxWindowProc(this->m_hWnd, message, wParam, lParam);
							if (lres != S_MSG_KEY_IGNORED)
							{
								return lres;
							}
						
					}
					else
					{
						m_PageRiched[i].Riched.KillFocus();
						m_PageRiched[i].Riched.SetSel(-1, 0);
					}
				}
			}
		}
		
		case WM_SETCURSOR:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(&pt);
			for (int i = 0; i < MAX_WLESS_RICHEDIT; i++)
			{
				if (m_PageRiched[i].bShowInPage)
				{
					if (PtInRect(m_PageRiched[i].Riched.m_pos, pt))
					{
						if (!m_PageRiched[i].Riched.m_tWinHost->DoSetCursor(NULL, &pt))
						{
							SetCursor(LoadCursor(NULL, IDC_ARROW));
						}
						return 0;
					}
				}
			}

			break;
		}
		default:
			for (int i = 0; i < MAX_WLESS_RICHEDIT; i++)
			{
				if (m_PageRiched[i].bShowInPage)
				{
					if (m_PageRiched[i].Riched.m_bFocus)
					{
						if (m_PageRiched[i].Riched.m_tWinHost)
						{
							LRESULT lres = m_PageRiched[i].Riched.m_tWinHost->TxWindowProc(this->m_hWnd, message, wParam, lParam);
							if (lres != S_MSG_KEY_IGNORED)
							{
								return lres;
							}
						}
						break;
					}
				}
			}
			break;
		}
	}

	
	return CWnd::DefWindowProc(message, wParam, lParam);
}

BOOL GrowChatList::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}



void GrowChatList::DrawRoundRectangle(Graphics &pGraph, COLORREF pens, int x, int y, int width, int height, int r, int ry)
{
		int OFFSET_X = r;
		int OFFSET_Y = ry;
		//设置画图时的滤波模式为消除锯齿现象  
		pGraph.SetSmoothingMode(SmoothingModeAntiAlias);

		//创建一个红色的画笔  
		Gdiplus::Pen pen(Color(255, GetRValue(pens), GetGValue(pens), GetBValue(pens)), 1);

		//画矩形上面的边  
		pGraph.DrawLine(&pen, x + OFFSET_X, y, x + width - OFFSET_X, y);

		//画矩形下面的边  
		pGraph.DrawLine(&pen, x + OFFSET_X, y + height, x + width - OFFSET_X, y + height);

		//画矩形左面的边  
		pGraph.DrawLine(&pen, x, y + OFFSET_Y, x, y + height - OFFSET_Y);

		//画矩形右面的边  
		pGraph.DrawLine(&pen, x + width, y + OFFSET_Y, x + width, y + height - OFFSET_Y);

		//画矩形左上角的圆角  
		pGraph.DrawArc(&pen, x, y, OFFSET_X * 2, OFFSET_Y * 2, 180, 90);

		//画矩形右下角的圆角  
		pGraph.DrawArc(&pen, x + width - OFFSET_X * 2, y + height - OFFSET_Y * 2, OFFSET_X * 2, OFFSET_Y * 2, 360, 90);

		//画矩形右上角的圆角  
		pGraph.DrawArc(&pen, x + width - OFFSET_X * 2, y, OFFSET_X * 2, OFFSET_Y * 2, 270, 90);

		//画矩形左下角的圆角  
		pGraph.DrawArc(&pen, x, y + height - OFFSET_Y * 2, OFFSET_X * 2, OFFSET_Y * 2, 90, 90);

}

void GrowChatList::FillRoundRectangle(Graphics &pGraph, COLORREF pens, int x, int y, int width, int height, int r, int ry)
{
		pGraph.SetSmoothingMode(SmoothingModeAntiAlias);
		int OFFSET_X = r;
		int OFFSET_Y = ry;
		//创建画刷  
		SolidBrush brush(Color::MakeARGB(254, GetRValue(pens), GetGValue(pens), GetBValue(pens)));
		pGraph.FillRectangle(&brush, x, y + OFFSET_Y, width, height - OFFSET_Y * 2);
		pGraph.FillRectangle(&brush, x + OFFSET_X, y, width - OFFSET_X * 2, height);
#define PIE_OFFSET 2  
		pGraph.FillPie(&brush, x, y, OFFSET_X * 2 + PIE_OFFSET, OFFSET_Y * 2 + PIE_OFFSET, 180, 90);
		pGraph.FillPie(&brush, x + width - (OFFSET_X * 2 + PIE_OFFSET), y + height - (OFFSET_Y * 2 + PIE_OFFSET), OFFSET_X * 2 + PIE_OFFSET, OFFSET_Y * 2 + PIE_OFFSET, 360, 90);
		pGraph.FillPie(&brush, x + width - (OFFSET_X * 2 + PIE_OFFSET), y, (OFFSET_X * 2 + PIE_OFFSET), (OFFSET_Y * 2 + PIE_OFFSET), 270, 90);
		pGraph.FillPie(&brush, x, y + height - (OFFSET_X * 2 + PIE_OFFSET), (OFFSET_X * 2 + PIE_OFFSET), (OFFSET_Y * 2 + PIE_OFFSET), 90, 90);

}

void GrowChatList::FillVRoundRectangle(Graphics&pGraph, COLORREF pens, int x, int y, int width, int height, int r, int ry)
{
	pGraph.SetSmoothingMode(SmoothingModeAntiAlias);
	int OFFSET_X = r;
	int OFFSET_Y = ry;
	//创建画刷  
	SolidBrush brush(Color::MakeARGB(254, GetRValue(pens), GetGValue(pens), GetBValue(pens)));
	pGraph.FillRectangle(&brush, x, y + OFFSET_Y, width, height - OFFSET_Y * 2);

	pGraph.FillEllipse(&brush, x, y, OFFSET_X * 2, OFFSET_Y * 2);
	pGraph.FillEllipse(&brush, x , y + height - 2*OFFSET_Y, OFFSET_X * 2, OFFSET_Y * 2);

}


void GrowChatList::OnMouseHover(UINT nFlags, CPoint point)
{
	SetFocus();
	CWnd::OnMouseHover(nFlags, point);
}


void GrowChatList::OnMouseLeave()
{
	if (!m_bisDownScroll)
	{
		m_bisHoverView = false;
		m_bisHoverScroll = false;
		Invalidate();
	}
	CWnd::OnMouseLeave();
}

void GrowChatList::MoreStringDoing()
{
	AfxGetApp()->DoWaitCursor(1);
	StartInsertItemGroupInFront();

	AddStringItemToItemGroup(_T("赵虎2"), _T("你好098543223577"));

	SYSTEMTIME sTime;
	CString  strTime;
	GetLocalTime(&sTime);
	strTime.Format(_T("%d/%d/%d:%d"), sTime.wYear, sTime.wMonth, sTime.wDay,sTime.wSecond);


	AddTimeItemToItemGroup(strTime);
	AddMoreMsgItemToItemGroup();

	OverInsertItemGroupInFront();
	Sleep(200);
	AfxGetApp()->DoWaitCursor(-1);
	MoveWindowEx(0, 0, 600, 380);
}

int GrowChatList::FindStartItem()
{
	if (m_Item.size() <= 0) return -1;
	int low = 0;
	int high = m_Item.size() - 1;
	//这里的10像素是第一个Item的预留位置
	if (m_yOffest <= 10) return 0;
	while (low <= high)
	{
		int middle = (high - low) / 2 + low; // 直接使用(high + low) / 2 可能导致溢出
		if (m_Item[middle].StartPos <m_yOffest&&m_Item[middle].ItemHeight + m_Item[middle].StartPos >m_yOffest)
			return middle;
		//在左半边
		else if (m_Item[middle].StartPos > m_yOffest)
			high = middle - 1;
		//在右半边
		else
			low = middle + 1;
	}
	//没找到
	return -1;
}


void  GrowChatList::SetShowRangeWlessEditPos()
{
	if (m_ShowIdEnd - m_ShowIdStart > MAX_WLESS_RICHEDIT) return;

	std::vector<int> m_NeedAlToEditShow;

	for (int i = 0; i < MAX_WLESS_RICHEDIT; i++)
	{
		if (m_PageRiched[i].bShowInPage == true)
		{
			if (!(m_PageRiched[i].IdAttachItem >= m_ShowIdStart&&m_PageRiched[i].IdAttachItem <= m_ShowIdEnd))
			{
				m_PageRiched[i].bShowInPage = false;
			}
			else
			{
				//这些是已经存在还需绘制Riched 需要矫正Y偏移
				int ItemId = m_PageRiched[i].IdAttachItem;
				if (m_Item[ItemId].bIsMyMsg)
				{
					int ofx = (m_Rect.Width() - PAGE_BUBBLE_LEFT_OF - m_Item[ItemId].BubblePos.Width() - 9);
					m_PageRiched[i].Riched.SetViewRect(_GRECT(ofx + m_Item[ItemId].BubblePos.left + BUBBLE_TAB + USER_MSG_BUBBLE_LEFTRIGHT, m_Item[ItemId].BubblePos.top + m_Item[ItemId].StartPos + USER_MSG_BUBBLE_TOPBOM - 2 - m_yOffest, m_Item[ItemId].RichedSize.cx, m_Item[ItemId].RichedSize.cy));
				}
				else
				{
					m_PageRiched[i].Riched.SetViewRect(_GRECT(PAGE_BUBBLE_LEFT_OF + m_Item[ItemId].BubblePos.left + BUBBLE_TAB + USER_MSG_BUBBLE_LEFTRIGHT, m_Item[ItemId].BubblePos.top + m_Item[ItemId].StartPos + USER_MSG_BUBBLE_TOPBOM - 2 - m_yOffest, m_Item[ItemId].RichedSize.cx, m_Item[ItemId].RichedSize.cy));
				}

				m_NeedAlToEditShow.push_back(m_PageRiched[i].IdAttachItem);
			}
		}
	}

	//找出新增需要显示的ItemRiched
	std::vector<int> m_NewToEditShow;
	for (int i = 0; i < m_ShowIdEnd - m_ShowIdStart + 1; i++)
	{
		bool findit = false;
		for (int j =0; j<m_NeedAlToEditShow.size();j++)
		{
			if (m_ShowIdStart+i == m_NeedAlToEditShow[j])
			{
				findit = true;
			}
		}
		if (!findit)
		{
			if (m_Item[m_ShowIdStart + i].MsgType==ENUM_TYPE_STRING)
			m_NewToEditShow.push_back(m_ShowIdStart+i);
		}
	}

	for (int i = 0; i < m_NewToEditShow.size(); i++)
	{
		for (int j = 0; j < MAX_WLESS_RICHEDIT; j++)
		{
			if (m_PageRiched[j].bShowInPage == false)
			{
				int ItemId = m_NewToEditShow[i];
				m_PageRiched[j].IdAttachItem = ItemId;
				//需要矫正Left偏移
				if (m_Item[ItemId].bIsMyMsg)
				{
					int ofx = (m_Rect.Width() - PAGE_BUBBLE_LEFT_OF - m_Item[ItemId].BubblePos.Width() - 9);
					m_PageRiched[j].Riched.SetViewRect(_GRECT(ofx + m_Item[ItemId].BubblePos.left + BUBBLE_TAB + USER_MSG_BUBBLE_LEFTRIGHT, m_Item[ItemId].BubblePos.top + m_Item[ItemId].StartPos + USER_MSG_BUBBLE_TOPBOM - 2 - m_yOffest, m_Item[ItemId].RichedSize.cx, m_Item[ItemId].RichedSize.cy));
				}
				else
				{
					m_PageRiched[j].Riched.SetViewRect(_GRECT(PAGE_BUBBLE_LEFT_OF + m_Item[ItemId].BubblePos.left + BUBBLE_TAB + USER_MSG_BUBBLE_LEFTRIGHT, m_Item[ItemId].BubblePos.top + m_Item[ItemId].StartPos + USER_MSG_BUBBLE_TOPBOM - 2 - m_yOffest, m_Item[ItemId].RichedSize.cx, m_Item[ItemId].RichedSize.cy));
				}
				m_PageRiched[j].bShowInPage = true;
				//SetText2此处影响显示性能 主要由于SetText发送Wm_Paint到父窗口 优化方案是屏蔽掉Onpaint
				m_bonpaint = false;
				m_PageRiched[j].Riched.SetText2(m_Item[ItemId].UserMsg);
				m_bonpaint = true;
		
				break;
			}
		}
	}
}

void  GrowChatList::YOffestReset(bool trju)
{

	if (m_yOffest >= m_NextStartPos - m_Rect.Height())  m_yOffest = m_NextStartPos - m_Rect.Height();
	if (m_yOffest <= 0)  m_yOffest = 0;


	if (trju)
	JudgeShowScroll();
	int msID=FindStartItem();
	std::vector<CHAT_LIST_ITEM> mTmp;
	if (msID != -1)
	{
		m_ShowIdStart = msID-10;
		if (m_ShowIdStart <= 0)m_ShowIdStart = 0;
		//printf("%d", msID);
		for (int i = msID; i < m_Item.size(); i++)
		{
			mTmp.push_back(m_Item[i]);
			m_ShowIdEnd = i;
			if (m_Item[i].StartPos + m_Item[i].ItemHeight > m_yOffest + m_Rect.Height()) { break; }
		}
		m_ShowIdEnd = m_ShowIdEnd + 10;
		if (m_ShowIdEnd >= m_Item.size())m_ShowIdEnd = m_Item.size() - 1;
		//重新
		SetShowRangeWlessEditPos();
		Invalidate();
	}


}

void GrowChatList::OnLButtonDown(UINT nFlags, CPoint point)
{
	//判断是否在滚动条上
	if (PtInRect(_GRECT(m_Rect.right - 14, 1, 10, m_Rect.Height() - 2), point))
	{
		if (PtInRect(m_VScrollRect, point))
		{
			SetCapture();
			m_bisDownScroll = true;
			m_lastVScrollRect = m_VScrollRect;
			GetCursorPos(&m_pDownPos);
		}
		else
		{
			if (point.y > m_VScrollRect.bottom)
			{
				m_yOffest = m_yOffest + 100;
				if (m_yOffest >= m_NextStartPos - m_Rect.Height())  m_yOffest = m_NextStartPos - m_Rect.Height();
				YOffestReset();
			}
			if (point.y < m_VScrollRect.top)
			{
				m_yOffest = m_yOffest - 100;
				if (m_yOffest <= 0)  m_yOffest = 0;
				YOffestReset();
			}
		}
	}

	//判断是否点击在更多消息
	if (m_Item.size() > 0 && m_Item[0].MsgType == ENUM_TYPE_MORE_MSG)
	{
		if (PtInRect(_GRECT((m_Rect.Width() - LINE_MORE_STRING_WIDTH) / 2, 10 - m_yOffest, LINE_MORE_STRING_WIDTH, LINE_MORE_STRING_HEIGHT), point))
		{
			SetCapture();
			m_bisDownMoreString = true;
		}
	}

	CWnd::OnLButtonDown(nFlags, point);
}


void GrowChatList::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bisDownScroll)
	{
		m_bisDownScroll = false;
		ReleaseCapture();
	}

	//判断是否点击在更多消息
	if (m_bisDownMoreString&&m_Item.size() > 0 && m_Item[0].MsgType == ENUM_TYPE_MORE_MSG)
	{
		if (PtInRect(_GRECT((m_Rect.Width() - LINE_MORE_STRING_WIDTH) / 2, 10 - m_yOffest, LINE_MORE_STRING_WIDTH, LINE_MORE_STRING_HEIGHT), point))
		{
			ReleaseCapture();
			MoreStringDoing();
		}
		m_bisDownMoreString = false;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void GrowChatList::OnMouseMove(UINT nFlags, CPoint point)
{
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = m_hWnd;
	tme.dwFlags = TME_LEAVE | TME_HOVER;
	tme.dwHoverTime = 1;
	_TrackMouseEvent(&tme);
	if (m_bisDownScroll)
	{
		CPoint CurPos;
		GetCursorPos(&CurPos);

		int dy = CurPos.y - m_pDownPos.y;
		m_VScrollRect.top = m_lastVScrollRect.top + dy;
		if (m_VScrollRect.top < 1) m_VScrollRect.top = 1;
		if (m_VScrollRect.top > m_Rect.Height() - m_lastVScrollRect.Height() - 1) m_VScrollRect.top = m_Rect.Height() - m_lastVScrollRect.Height() - 1;
		m_yOffest =( m_VScrollRect.top-1) / float((m_Rect.Height() - 2) - m_lastVScrollRect.Height())*float(m_NextStartPos - m_Rect.Height());
		m_VScrollRect.bottom = m_lastVScrollRect.Height() + m_VScrollRect.top;
		YOffestReset(false);

	}
	if (!m_bisDownScroll)
	{
		if (m_bisShowScroll)
		{
			bool aCopy = m_bisHoverView;
			bool bCopy = m_bisHoverScroll;

			m_bisHoverScroll = true;
			if (PtInRect(_GRECT(m_Rect.right - 14, 1, 10, m_Rect.Height() - 2), point))
			{
				m_bisHoverView = true;
			}
			else
			{
				m_bisHoverView = false;
			}
			if (aCopy != m_bisHoverView || bCopy != m_bisHoverScroll) Invalidate();

		}
	}

	//判断是否在更多消息
	if (m_Item.size() > 0 && m_Item[0].MsgType == ENUM_TYPE_MORE_MSG)
	{
		bool bCopy = m_bisHoverMoreString;
		if (PtInRect(_GRECT((m_Rect.Width() - LINE_MORE_STRING_WIDTH) / 2, 10 - m_yOffest, LINE_MORE_STRING_WIDTH, LINE_MORE_STRING_HEIGHT), point))
		{
			m_bisHoverMoreString = true;
		}
		else
		{
			m_bisHoverMoreString = false;
		}
		if (bCopy != m_bisHoverMoreString) Invalidate();
	}


	CWnd::OnMouseMove(nFlags, point);
}

BOOL GrowChatList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (!m_bisDownScroll)
	{
		if (m_bisShowScroll)
		{
			if (zDelta > 0)
			{
				m_yOffest = m_yOffest - 100;
				if (m_yOffest <= 0)  m_yOffest = 0;
				YOffestReset();

			}
			else
			{
				m_yOffest = m_yOffest + 100;
				if (m_yOffest >= m_NextStartPos - m_Rect.Height())  m_yOffest = m_NextStartPos - m_Rect.Height();
				YOffestReset();
			}
		}
	}

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}


void GrowChatList::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	
	CWnd::OnMouseHWheel(nFlags, zDelta, pt);
}

void GrowChatList::SetScrollPosInBom()
{
	m_yOffest = m_NextStartPos - m_Rect.Height();
	YOffestReset();

}

void GrowChatList::SetScrollPosInTop()
{
	m_yOffest = 0;
	YOffestReset();
}

LRESULT GrowChatList::OnNcHitTest(CPoint point)
{

	CPoint MousePos = point;
	ScreenToClient(&MousePos);
	RECT rc;
	int retn = TRUE;
	::GetClientRect(m_hWnd, &rc);
	int iWidth = rc.right - rc.left;
	int iHeight = rc.bottom - rc.top;
	if (PtInRect(CRect(5, 0, iWidth - 100, 5), MousePos))
		retn = HTTOP;
	else if (PtInRect(CRect(0, 5, 5, iHeight - 5), MousePos))
		retn = HTLEFT;
	else if (PtInRect(CRect(iWidth - 5, 25, iWidth, iHeight - 5), MousePos))
		retn = HTRIGHT;
	else if (PtInRect(CRect(5, iHeight - 5, iWidth - 5, iHeight), MousePos))
		retn = HTBOTTOM;
	else if (PtInRect(CRect(0, 0, 5, 5), MousePos))
		retn = HTTOPLEFT;
	else if (PtInRect(CRect(0, iHeight - 5, 5, iHeight), MousePos))
		retn = HTBOTTOMLEFT;
	else if (PtInRect(CRect(iWidth - 5, iHeight - 5, iWidth, iHeight), MousePos))
		retn = HTBOTTOMRIGHT;
	return retn;

	return CWnd::OnNcHitTest(point);
}


void GrowChatList::OnSize(UINT nType, int cx, int cy)
{
	if (cx < 370) cx = 370;
	if (cy < 200) cy = 200;
	m_Rect = _GRECT(0, 0, cx, cy);
	if (m_pMeasurewr)
	{
	delete m_pMeasurewr;
	m_pMeasurewr = new CWlessRiched;
	m_pMeasurewr->CreateWlessRiched(m_MeasurewrWnd.m_hWnd, m_MeasurewrWnd.m_hWnd, CRect(0, 0, (cx - USER_HEAD_EDIT_SPACE)*0.9, 661));
	m_pMeasurewr->KillFocus();
	}

	//重新校准气泡和riched位置
	RuntStart()
	m_NextStartPos = USER_ITEM_START_LINE_SPACE;
	for (int i = 0; i < m_Item.size(); i++)
	{
		int lh = m_pMeasurewr->GetLineHeight();
		m_Item[i].StartPos = m_NextStartPos;
		
		if (m_Item[i].MsgType == ENUM_TYPE_STRING)
		{
			SIZE size = m_Item[i].RichedSize;
			if (!(m_Item[i].RichedSize.cx <= (cx - USER_HEAD_EDIT_SPACE)*0.9&&m_Item[i].RichedSize.cy <= lh))
			{
				size = GetStringSize(m_Item[i].UserMsg);
				//printf("%d[%d,%d] \n",i, size.cx, size.cy);
				m_Item[i].RichedSize = size;
			}
			if (m_Item[i].bIsMyMsg)
			{
				if (size.cy > USER_HEAD_PIC_HEIGHT)
					m_Item[i].ItemHeight = size.cy + USER_ITEM_LINE_SPACE + USER_MSG_BUBBLE_TOPBOM * 2;
				else 	m_Item[i].ItemHeight = USER_HEAD_PIC_HEIGHT + USER_ITEM_LINE_SPACE;
				m_Item[i].BubblePos = _GRECT(0, 0, m_Item[i].RichedSize.cx + USER_MSG_BUBBLE_LEFTRIGHT * 2 + BUBBLE_TAB, m_Item[i].RichedSize.cy + USER_MSG_BUBBLE_TOPBOM * 2);
			}
			else
			{
				m_Item[i].ItemHeight = size.cy + USER_ITEM_LINE_SPACE + USER_HEAD_NAMETOMSG_SPACE + USER_MSG_BUBBLE_TOPBOM * 2;
				m_Item[i].BubblePos = _GRECT(0, USER_HEAD_NAMETOMSG_SPACE, m_Item[i].RichedSize.cx + USER_MSG_BUBBLE_LEFTRIGHT * 2 + BUBBLE_TAB, m_Item[i].RichedSize.cy + USER_MSG_BUBBLE_TOPBOM * 2);
			}
		}
		m_NextStartPos += m_Item[i].ItemHeight;
	}

	YOffestReset();
	CWnd::OnSize(nType, cx, cy);
}
