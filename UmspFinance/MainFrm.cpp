// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "UmspFinance.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(TB_START, OnStart)
	ON_COMMAND(TB_END, OnEnd)
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(TB_START, OnUpdateStart)
	//}}AFX_MSG_MAP
	ON_MESSAGE(TRAY_ICON_MSG,OnTrayIconClick)
	ON_WM_MENUSELECT()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{	
	adapEB=NULL;
	bStartButtonEnable=TRUE;
}

CMainFrame::~CMainFrame()
{
	//DelTrayICon();
	if(adapEB!=NULL)
		delete adapEB;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	CenterWindow(this);
	AddTrayICon();
	CRect rect;
	this->GetWindowRect (&rect);
	SetWindowPos (&wndTopMost,rect.left ,rect.top,rect.Width (),rect.Height (),WS_EX_TOPMOST );
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{	
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnStart() 
{
	if(adapEB==NULL)
		adapEB=new (CUmspEBAdap);
	
	CWinThread * pThread=NULL;
	pThread=adapEB->StartListen();
	if(pThread==NULL)
		return;
	bStartButtonEnable=FALSE;

	//Sleep(1000);	
}

void CMainFrame::OnEnd() 
{
	if(adapEB!=NULL)		
	{
		adapEB->StopListen ();
		bStartButtonEnable=TRUE;
	}
}
BOOL MyTaskBarAddIcon(HWND hwnd, UINT uID, HICON hicon, LPSTR lpszTip) 
{ 
	BOOL res; 
	NOTIFYICONDATA tnid; 

	tnid.cbSize = sizeof(NOTIFYICONDATA); 
	tnid.hWnd = hwnd; 
	tnid.uID = uID; 
	tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; 
	tnid.uCallbackMessage = (WM_USER+1000); 
	tnid.hIcon = hicon; 
	if (lpszTip) 
	lstrcpyn(tnid.szTip, lpszTip, sizeof(tnid.szTip)); 
	else 
	tnid.szTip[0] = '\0'; 

	res = Shell_NotifyIcon(NIM_ADD, &tnid); 

	if (hicon) 
	DestroyIcon(hicon); 

	return res; 
} 
BOOL MyTaskBarDeleteIcon(HWND hwnd, UINT uID) 
{ 
	BOOL res; 
	NOTIFYICONDATA tnid; 

	tnid.cbSize = sizeof(NOTIFYICONDATA); 
	tnid.hWnd = hwnd; 
	tnid.uID = uID; 
 
	res = Shell_NotifyIcon(NIM_DELETE, &tnid); 
	return res; 
} 

void CMainFrame::AddTrayICon()
{
	HICON hicon;
	HINSTANCE hinst=::AfxGetApp ()->m_hInstance  ;
	hicon=::LoadIcon (hinst ,MAKEINTRESOURCE(IDR_MAINFRAME));
	MyTaskBarAddIcon(this->m_hWnd,100,hicon,"½ðÈÚ·þÎñ");
}

void CMainFrame::DelTrayICon()
{
	MyTaskBarDeleteIcon(this->m_hWnd,100);
}
void CMainFrame::OnTrayIconClick(WPARAM wParam, LPARAM lParam)
{
	static BOOL bHide=FALSE;
	

	UINT uID; 
	UINT uMouseMsg; 

	uID = (UINT) wParam; 
	uMouseMsg = (UINT) lParam; 
 
	if (uMouseMsg == WM_LBUTTONDOWN) 
	{ 
		switch (uID) 
		{ 
		case 100: 
			if(bHide)
			{
				this->ShowWindow (SW_SHOW);
			}
			else
			{
				this->ShowWindow (SW_HIDE);
			}
			bHide=!bHide;
			break; 

		default: 
			break; 
		} 
	} 
	return; 

}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	DelTrayICon();
	CMDIFrameWnd::OnClose();
}
void CMainFrame::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{

}

void CMainFrame::OnUpdateStart(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable (bStartButtonEnable);
}
