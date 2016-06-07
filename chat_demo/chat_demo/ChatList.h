/*


	Yang.GuoQiang
	2016/6/7

	消息显示列表控件

*/


#pragma once
#include "afxwin.h"
#include "WlessRiched.h"
#include <vector>
#include <list>
#include <deque>
#define _DELETE_IMAGE(p) if(p) delete p;
#define  _GRECT(a,b,c,d) CRect(a,b,c+a,b+d)
#define  USER_HEAD_PIC_WIDTH  40
#define  USER_HEAD_PIC_HEIGHT 40
#define  USER_HEAD_NAMETOMSG_SPACE 12+10
#define  USER_HEAD_EDIT_SPACE 64
#define  USER_ITEM_LINE_SPACE 10
#define  USER_ITEM_START_LINE_SPACE 10
#define  USER_MSG_BUBBLE_LEFTRIGHT 3
#define  USER_MSG_BUBBLE_TOPBOM    7
#define  BUBBLE_TAB    9
#define  PAGE_BUBBLE_LEFT_OF 64

#define  PAGE_LEFT 20
#define  PAGE_RIGHT 20
#define  MAX_WLESS_RICHEDIT    80
#define  LINE_MORE_STRING_WIDTH    100
#define  LINE_MORE_STRING_HEIGHT    13
enum ITEM_MSG_TYPE
{
	ENUM_TYPE_STRING,
	ENUM_TYPE_PICTRUE,
	ENUM_TYPE_FILE,
	ENUM_TYPE_TIME,
	ENUM_TYPE_MORE_MSG,
};


struct  CHAT_LIST_ITEM
{
	ITEM_MSG_TYPE MsgType;
	CString UserName;
	CString UserMsg;
	CString Path;
	bool    bIsMyMsg;
	SIZE    RichedSize;
	int 	StartPos;
	CRect   BubblePos;
	int 	ItemHeight;
	bool    PosOld;
};

struct  CHAT_LIST_PAGE_WLESSRICHEDIT
{
	bool bShowInPage;
	int  IdAttachItem;
	CWlessRiched Riched;
};

namespace std
{
	template <typename T, typename A = allocator<T>>
	class Mylist : public list < T, A >
	{
	public:
		T& operator[](int idx)
		{
			iterator it = begin();
			for (int i = 0; i < idx; i++)
				++it;
			return *it;
		}
		const T& operator[](int idx)const
		{
			const_iterator it = begin();
			for (int i = 0; i < idx; i++)
				++it;
			return *it;
		}
	};
}

class GrowChatList :
	public CWnd
{
public:
	GrowChatList();
	~GrowChatList();
	CString		m_UserName;
	//CWlessRiched m_Measurewr;
	CWnd m_MeasurewrWnd;
	CWlessRiched *m_pMeasurewr;
	CRect m_Rect;
	BOOL Create(CWnd *Parent, CRect Rect, DWORD Style, int ID); //创建视图
	void OnDraw(CDC *pDC,CRect rc);
	CWlessRiched m_rich;
	std::deque<CHAT_LIST_ITEM> m_Item;
	int m_ShowIdStart;
	int m_ShowIdEnd;
	void SetShowRangeWlessEditPos();
	SIZE GetStringSize(CString pString);
	void SetScrollPosInBom();
	void SetScrollPosInTop();
public://维护一个页面Richedit数组
	bool m_bPageRichedInitOver;
	CHAT_LIST_PAGE_WLESSRICHEDIT m_PageRiched[MAX_WLESS_RICHEDIT];//整个控件窗口最多显示40个richedit
	void AttachWlessRichedit(int ItemId);

public://更多消息行为
	bool m_bisHoverMoreString;
	bool m_bisDownMoreString;
	void MoreStringDoing();

public:
	void AddStringItem(CString UserName, CString MsgStr);
	void AddFileItem();
	void AddPictureItem();
	void AddTimeItem(CString TimeStr);
	void AddMoreMsgItem();
	void MoveWindowEx(int x, int y, int ox, int oy);
	//插入一组数据Item到消息顶部 ItemGroup 的末尾元素置于最顶端
	void StartInsertItemGroupInFront();
	void OverInsertItemGroupInFront();
	bool AddMoreMsgItemToItemGroup();
	bool AddStringItemToItemGroup(CString UserName, CString MsgStr);
	bool AddTimeItemToItemGroup(CString TimeStr);
	std::vector<CHAT_LIST_ITEM> ItemGroup;
public://DrawTool
	void DrawRoundRectangle(Graphics &pGraph, COLORREF pens, int x, int y, int width, int height, int r, int ry);
	void FillRoundRectangle(Graphics &pGraph, COLORREF pens, int x, int y, int width, int height, int r, int ry);
	void FillVRoundRectangle(Graphics &pGraph, COLORREF pens, int x, int y, int width, int height, int r, int ry);
public:
	void DrawStringMsg(CDC*pDC, Graphics &graph, CHAT_LIST_ITEM *pItem);
	void DrawTimeMsg(CDC*pDC, Graphics &graph, CHAT_LIST_ITEM *pItem);
	void DrawMoreMsg(CDC*pDC, Graphics &graph, CHAT_LIST_ITEM *pItem);
	//绘制气泡
	void DrawBubble(CDC *pDC, Graphics &graph, CHAT_LIST_ITEM *pItem, bool bleft = true);
	Image *m_pImgbub1;
	Image *m_pImgbub2;
	Image *m_pImgbub3;
	Image *m_pImgbub4;

	Image *m_pImgbub1_fx;
	Image *m_pImgbub2_fx;
	Image *m_pImgbub3_fx;
	Image *m_pImgbub4_fx;
	bool m_bonpaint;
	//显示获取更多消息
	bool m_bhaveMoreMsg;
	CRect m_MoreMsgRc;
	int  m_MoreMsgHeight;
	int  m_DrawyOffest;
public:
	int m_Itemlen; //总长
	int m_RcWnd;
	//寻找起始Item
	int FindStartItem();
public://垂直滚动条实现
	CRect m_VScrollRect;
	int   m_NextStartPos;   //页面总高度
	int   m_yOffest;        //垂直偏移(相当于当前页面起始高度)
	bool  m_bisShowScroll;   //是否需要显示滚动条
	bool  m_bisHoverView;   //焦点在视图上但不在滚动条上
	bool  m_bisHoverScroll; //焦点滚动条上
	bool  m_bisDownScroll;
	CPoint m_pDownPos;
	CRect  m_lastVScrollRect;
	void  DrawVerticalScroll(CDC *pDC, Graphics &graph);
	void  JudgeShowScroll();
	void  YOffestReset(bool trju=true);

	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

