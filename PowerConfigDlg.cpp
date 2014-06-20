
// PowerConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PowerConfig.h"
#ifndef POWERCONFIG
#define POWERCONFIG
#include "PowerConfigDlg.h"
#endif
#include "afxdialogex.h"
#include <timeapi.h>
#include <mmsystem.h>
#include <afxwin.h>
#include "HelpDlg.h"
#include "ExitDlg.h"
#pragma comment(lib, "winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAbout();
	afx_msg void OnMinimize();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPowerConfigDlg 对话框

//函数声明部分
void RunCmd(CString Command);
void Proceed(UINT_PTR nIDEvent);
void Active(int ID);
bool CheckTime(UINT_PTR nIDEvent);
void UpdateLeftTime(UINT_PTR nIDEvent);
void UpdateState();//更新状态

//全局变量声明部分
Event temp;
Event store[10];
Mode a[10];
CPowerConfigDlg * pDlg;
CPowerConfigDlg::CPowerConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPowerConfigDlg::IDD, pParent)
	, output(_T(""))
	, Output(_T(""))
	, CurrentMode(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPowerConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, Time);
	DDX_Control(pDX, IDC_LIST2, List);
	DDX_Control(pDX, IDC_COMBO1, Combo);
	DDX_Text(pDX, IDC_EDIT1, CurrentMode);
}

BEGIN_MESSAGE_MAP(CPowerConfigDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CPowerConfigDlg::OnBnClickedButton2)
	ON_MESSAGE(WM_SHOWTASK, &CPowerConfigDlg::OnShowTask)
	ON_BN_CLICKED(IDC_BUTTON1, &CPowerConfigDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CPowerConfigDlg::OnCbnSelchangeCombo1)
	ON_COMMAND(ID_32777, &CPowerConfigDlg::OnMinimize)
	ON_COMMAND(ID_32776, &CPowerConfigDlg::On32776)
	ON_COMMAND(ID_32778, &CPowerConfigDlg::OnAboutDlg)
	ON_COMMAND(ID_32779, &CPowerConfigDlg::OnReportBug)
	ON_EN_SETFOCUS(IDC_EDIT1, &CPowerConfigDlg::OnEnSetfocusEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CPowerConfigDlg::OnBnClickedButton3)
	ON_COMMAND(ID_32780, &CPowerConfigDlg::OnHelp)
	ON_COMMAND(ID_32781, &CPowerConfigDlg::OnMinimized)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPowerConfigDlg 消息处理程序
BOOL CPowerConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	pDlg = this;//初始化对话框指针

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	//以下代码用于初始化
	//获取电源模式列表
	RunCmd(_T("powercfg -l"));
	CString temp;//用于承接电源模式名的变量
	int index = 0;//用于记录当前的记录指针位置
	int counter = 0;//用于记录当前的模式个数
	/*示例输出
	
	现有电源使用方案 (* Active)
	-----------------------------------
	电源方案 GUID: 08746e70-8723-40f0-bcae-07fca492a3ce  (夜间)
	电源方案 GUID: 381b4222-f694-41f0-9685-ff5bb260df2e  (平衡)
	电源方案 GUID: 8c5e7fda-e8bf-4a96-9a85-a6e23a8c635c  (高性能) *
	电源方案 GUID: a1841308-3541-4fab-bc81-f71556f20b4a  (节能)
	*/

	UpdateState();
	do{
		index = output.Find(_T("GUID: "),index);
		temp = output.Mid(index+6, 36); 
		//MessageBox(temp);
		if (temp[8] != '-')
			break;
		a[counter].SetGUID(temp);
		
		index = output.Find(_T("("), index);
		int t,begin,end;
		for (t = index; output[t] != ')'; t++)
		{
			if (output[t] == '(')
				begin = t;
		}
		end = t;
		temp = output.Mid(begin + 1, end - 1 - begin);
		a[counter].SetName(temp);
		counter++;
		//MessageBox(temp);
	}while (true);


	//刚才的初始化部分读取到了现有的电源模式及其GUID
	//下面的部分将会将其写入到ComboBox控件
	int t;
	CComboBoxEx* Combobox = (CComboBoxEx*)GetDlgItem(IDC_COMBO1);
	a[0].GetGUID();
	for (t = 0;t<counter; t++)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(a[t].GetName());
	}


	//---------------------------托盘显示---------------------------------//
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK;             // 自定义的消息名称
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(m_nid.szTip, _T("电源模式管理"));                // 
	Shell_NotifyIcon(NIM_ADD, &m_nid);                // 在托盘区添加图标


	//-----------------------------帮助提示--------------------------------//
	EnableToolTips(true);
	m_tip.Create(this);
	//IDC_BUTTON为你要添加提示信息的按钮的ID
	m_tip.AddTool(GetDlgItem(IDC_BUTTON1), _T("创建计划任务"));
	m_tip.AddTool(GetDlgItem(IDC_BUTTON2), _T("使程序隐藏运行"));
	m_tip.AddTool(GetDlgItem(IDC_COMBO1), _T("此计算机已有的电源模式"));
	m_tip.AddTool(GetDlgItem(IDC_LIST2), _T("已配置的计划任务"));
	m_tip.AddTool(GetDlgItem(IDC_DATETIMEPICKER1), _T("设定时间"));
	m_tip.AddTool(GetDlgItem(IDC_EDIT1), _T("单击文本框更新"));
	m_tip.AddTool(GetDlgItem(IDC_BUTTON3), _T("单击文本框也可以更新哦"));
	//m_tip.AddTool(GetDlgItem(IDCANCEL), _T("完全退出程序"));
	m_tip.SetDelayTime(100); //设置延迟
	//m_tip.SetTipTextColor( RGB(0,0,255) ); //设置提示文本的颜色
	//m_tip.SetTipBkColor( RGB(255,255,255)); //设置提示框的背景颜色
	m_tip.Activate(true); //设置是否启用提示
	

	//------------------------初始化列表框---------------------------------//
	LONG lStyle;
	lStyle = GetWindowLong(List.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(List.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = List.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用于report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用于report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	List.SetExtendedStyle(dwStyle); //设置扩展风格
	List.InsertColumn(0, _T(""), LVCFMT_LEFT, 20);
	List.InsertColumn(1, _T("任务时间"), LVCFMT_CENTER, 90);
	List.InsertColumn(2, _T("将切换的电源模式"), LVCFMT_CENTER, 120);
	List.InsertColumn(3, _T("剩余执行时间"), LVCFMT_CENTER, 120);


	//通知
	//MessageBox(_T("此软件目前有不能在短期内解决的问题\r\n一个程序同时不能执行多个程序\r\n如果需要设置多个计划任务请开多个程序"),_T("提示"),MB_ICONWARNING);
	//return TRUE必须放在最后
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
BOOL CPowerConfigDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_MOUSEMOVE:
	{
		m_tip.RelayEvent(pMsg);
	}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
void CPowerConfigDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPowerConfigDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPowerConfigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPowerConfigDlg::OnClose()
{
	Shell_NotifyIcon(NIM_DELETE, &m_nid);//销毁图标
	ExitDlg Dlg;
	Dlg.DoModal();
}
void CPowerConfigDlg::OnCancel()
{
	Shell_NotifyIcon(NIM_DELETE, &m_nid);//销毁图标
	CDialogEx::OnCancel();
}
void CPowerConfigDlg::OnOK()
{
	Shell_NotifyIcon(NIM_DELETE, &m_nid);//销毁图标
	CDialogEx::OnOK();
}

void UpdateState()
{
	pDlg->output.Empty();//清空output用于刷新
	RunCmd(_T("powercfg -l"));

	CString temp;//用于承接电源模式名的变量
	int index = 0;//用于记录当前的记录指针位置
	//读取当前所在的模式
	int begin, end;
	index = pDlg->output.Find(_T(") *"));
	end = index - 1;
	int t;
	for (t = end; pDlg->output[t] != '('; t--);
	begin = t;
	temp = pDlg->output.Mid(begin + 1, end - begin);
	//MessageBox(temp);
	index = pDlg->output.Find(temp);//这里既然已经得到了就直接显示出来好了
	pDlg->CurrentMode = temp;
	pDlg->UpdateData(false);
	int s = (index - 64) / 57 + 1;
	a[s].SetActive(true);//这里貌似真的没用到
}

DWORD g_time;
CString output=_T("");
UINT Timer(LPVOID nIDEvent)
{
	CTime CurTime = CTime::GetCurrentTime();
	pDlg->CurHour = CurTime.GetHour();
	pDlg->CurMinute = CurTime.GetMinute();
	pDlg->CurSecond = CurTime.GetSecond();

	do
	{
		UpdateLeftTime((UINT_PTR)nIDEvent);
		Sleep(1000);
	}
	while (!CheckTime((UINT_PTR)nIDEvent));
	//这个线程创建后的任务就是不断检测是否到时间，没到时间就更新，到时间就退出
	
	Proceed((UINT_PTR)nIDEvent);
	UpdateState();
	return 0;
}
DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	unsigned char buf[4096];
	const int size = 4096;
	HANDLE *phRead = (HANDLE *)lpParameter;
	DWORD dwRead;
	while (true)
	{
		if (!ReadFile(*phRead, buf, size, &dwRead, NULL))
		{
			pDlg->MessageBox(_T("Error, Lock"));
			//while (1);
		}
		g_time = timeGetTime();
		buf[dwRead] = 0;
		pDlg->output += (CString)buf;
		Sleep(100);
	}
	return 0;
}
void RunCmd(CString Command)
{
	HANDLE hRead;
	HANDLE hWrite;

	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);

	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		MessageBox(NULL,_T("创建匿名管道失败"),_T(""),MB_ICONERROR);
		return;
	}

	STARTUPINFO sui;
	PROCESS_INFORMATION pi;

	ZeroMemory(&sui, sizeof(STARTUPINFO));

	sui.cb = sizeof(STARTUPINFO);
	sui.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	sui.hStdOutput = hWrite;
	sui.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	sui.wShowWindow = SW_HIDE;

	if (!CreateProcess(NULL, (LPWSTR)(LPCWSTR)Command, NULL, NULL, TRUE, 0, NULL, NULL, &sui, &pi))
	{
		MessageBox(NULL,_T("创建子进程失败"),_T(""),MB_ICONERROR);
		return;
	}
	DWORD exitcode;
	if (0 == GetExitCodeProcess(pi.hProcess, &exitcode))
	{
		MessageBox(NULL, _T("首次读取状态失败"), _T(""), MB_ICONERROR);
		return;
	}

	HANDLE hand = CreateThread(NULL, 0, ThreadProc1, &hRead, 0, NULL);

	DWORD timenow;
	g_time = timeGetTime();
	while (1)
	{
		if (0 == GetExitCodeProcess(pi.hProcess, &exitcode))
		{
			MessageBox(NULL, _T("读取状态失败"), _T(""), MB_ICONERROR);
			return;
		}
		timenow = timeGetTime();

		if (STILL_ACTIVE != exitcode && ((timenow - g_time)>1000))
		{
			break;
		}
		Sleep(100);
	}
}

void CPowerConfigDlg::OnBnClickedButton1()
{
	//添加计划任务

	//获取时间信息
	CTime picker;
	Time.GetTime(picker);
	temp.SetTime.Hour = picker.GetHour();
	temp.SetTime.Minute = picker.GetMinute();
	temp.SetTime.Second = picker.GetSecond();
	//判断这个时间是否已经过了，貌似没有必要
	//if (!CheckTime(temp.SetTime))
	//{
	//	MessageBox(_T("这个时间已经过了"), _T("警告"), MB_ICONERROR);
	//	return;
	//}

	//获取电源模式信息
	temp.mode = Combo.GetCurSel();
	if (temp.mode == -1)
	{
		MessageBox(_T("未选定电源模式！"), _T("警告"), MB_ICONERROR);
		return;
	}

	//在列表框里显示
	//时间

	CString num;
	num.Format(_T("%d"), List.GetItemCount()+1);
	int t = pDlg->List.InsertItem(0, num);
	CString time;
	time.Format(_T("%02d"),temp.SetTime.Hour);
	time += ':';
	time.AppendFormat(_T("%02d"), temp.SetTime.Minute);
	time += ':';
	time.AppendFormat(_T("%02d"), temp.SetTime.Second);
	List.SetItemText(t,1,time);

	//任务
	pDlg->List.SetItemText(t,2, a[temp.mode].GetName());
	//剩余时间
	CString lefttime;
	lefttime.Format(_T("%d"), temp.SetTime.Hour - pDlg->CurHour < 0 ? temp.SetTime.Hour - pDlg->CurHour + 24 : temp.SetTime.Hour - pDlg->CurHour);
	lefttime += _T("小时");
	lefttime.AppendFormat(_T("%d"), temp.SetTime.Minute - pDlg->CurMinute < 0 ? temp.SetTime.Minute - pDlg->CurMinute + 60 : temp.SetTime.Minute - pDlg->CurMinute);
	lefttime += _T("分钟");
	lefttime.AppendFormat(_T("%d"), temp.SetTime.Second - pDlg->CurSecond < 0 ? temp.SetTime.Second - pDlg->CurSecond + 60 : temp.SetTime.Second - pDlg->CurSecond);
	lefttime += _T("秒");
	pDlg->List.SetItemText(t, 3, lefttime);
	temp.index = t;

	//写入存储
	store[List.GetItemCount() - 1] = temp;
	//int tttt = List.GetItemCount();
	//SetTimer(temp.GetCounter(), 1000, NULL);
	AfxBeginThread((AFX_THREADPROC)Timer, (LPVOID)List.GetItemCount(), 0, 0, 0, NULL);
	//SetTimer(AfxGetMainWnd()->m_hWnd, (UINT_PTR)
}
void CPowerConfigDlg::OnBnClickedButton2()
{
	//最小化到系统托盘
	wcscpy_s(m_nid.szTip, _T("电源模式管理"));
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nid.hWnd = m_hWnd;
	lstrcpy(m_nid.szTip, _T("电源模式管理"));
	m_nid.uCallbackMessage = WM_SHOWTASK;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &m_nid);
	ShowWindow(SW_HIDE);
}

LRESULT CPowerConfigDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if (lParam == WM_RBUTTONDOWN)
	{
		//右键时弹出快捷菜单


		LPPOINT   lpoint = new   tagPOINT;
		::GetCursorPos(lpoint);//得到鼠标位置
		CMenu menuTray;
		CPoint point;
		int id;
		GetCursorPos(&point);

		menuTray.LoadMenu(IDR_MENU1);
		SetForegroundWindow();
		id = menuTray.GetSubMenu(0)->TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
#if 0
		CString strInfo;
		strInfo.Format(L"menuid %d", id);
		LPCTSTR strtmp;
		strtmp = strInfo.GetBuffer(0);
		MessageBox(strtmp, L"test");
#endif
		switch (id)
		{
		case ID_TRAY_EXIT:
			OnOK();
			break;

		case ID_TRAY_RESTORE://窗口前端显示

			ShowWindow(SW_SHOWNORMAL);
			break;
		}
	}
	if (lParam == WM_LBUTTONDBLCLK) //双击托盘图标
	{
		ModifyStyleEx(0, WS_EX_TOPMOST);
		ShowWindow(SW_SHOWNORMAL);
		SetForegroundWindow();
	}
//	if (lParam == WM_LBUTTONDOWN)//单击托盘图标
//	{
//		//左键单击弹出菜单，和右键单击效果相同
//	}
	return 0;
}

bool CheckTime(UINT_PTR nIDEvent)
{
	if (store[nIDEvent - 1].SetTime.Hour == pDlg->CurHour
		&&store[nIDEvent - 1].SetTime.Minute == pDlg->CurMinute
		&&store[nIDEvent - 1].SetTime.Second == pDlg->CurSecond
		)
		return true;
	else 
		return false;
}
void Proceed(UINT_PTR nIDEvent)
{
	Active(store[nIDEvent-1].mode);
	pDlg->List.DeleteItem(store[nIDEvent - 1].index);
}
void Active(int mode)
{
	CString Command;
	Command = _T("powercfg /s ") + a[mode].GetGUID();
	RunCmd(Command);
}

void CPowerConfigDlg::OnCbnSelchangeCombo1()
{
	//Combo控件已更改选择
	UpdateData(true);
}
void UpdateLeftTime(UINT_PTR nIDEvent)
{
	CString lefttime;
	//lefttime.Format(_T("%d"), store[index].SetTime.Hour - pDlg->CurHour < 0 ? store[index].SetTime.Hour - pDlg->CurHour + 24 : store[index].SetTime.Hour - pDlg->CurHour);
	//lefttime += _T("小时");
	//lefttime.AppendFormat(_T("%d"), store[index].SetTime.Minute - pDlg->CurMinute < 0 ? store[index].SetTime.Minute - pDlg->CurMinute + 60 : store[index].SetTime.Minute - pDlg->CurMinute);
	//lefttime += _T("分钟");
	//lefttime.AppendFormat(_T("%d"), store[index].SetTime.Second - pDlg->CurSecond < 0 ? store[index].SetTime.Second - pDlg->CurSecond + 60 : store[index].SetTime.Second - pDlg->CurSecond);
	//lefttime += _T("秒");
	CTime CurTime = CTime::GetCurrentTime();
	pDlg->CurHour = CurTime.GetHour();
	pDlg->CurMinute = CurTime.GetMinute();
	pDlg->CurSecond = CurTime.GetSecond();
	int tset, tcur;
	tset = ((store[store[nIDEvent].index].SetTime.Hour * 60) + store[store[nIDEvent].index].SetTime.Minute) * 60 + store[store[nIDEvent].index].SetTime.Second;
	tcur = ((pDlg->CurHour * 60 + pDlg->CurMinute) * 60 + pDlg->CurSecond);

	int ttemp = tset - tcur;
	if (ttemp < 0)
		ttemp += 86400;

	int sec, min, hour;
	sec = ttemp % 60;
	min = ttemp / 60 % 60;
	hour = ttemp / 60 / 60;
	if (hour != 0)
	{
		lefttime.Format(_T("%d"), hour);
		lefttime += _T("小时");
	}
	if (min != 0)
	{
		lefttime.AppendFormat(_T("%d"), min);
		lefttime += _T("分钟");
	}
	if (sec != 0)
	{
		lefttime.AppendFormat(_T("%d"), sec);
		lefttime += _T("秒");
	}

	/*wcscpy_s(pDlg->m_nid.szTip, lefttime);
	lstrcpy(pDlg->m_nid.szTip, lefttime);
	pDlg->UpdateWindow();*/
	pDlg->List.SetItemText(store[nIDEvent].index, 3, lefttime);
}
void CPowerConfigDlg::OnMinimize()
{
	//最小化到系统托盘
	wcscpy_s(m_nid.szTip, _T("电源模式管理"));
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nid.hWnd = m_hWnd;
	lstrcpy(m_nid.szTip, _T("电源模式管理"));
	m_nid.uCallbackMessage = WM_SHOWTASK;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &m_nid);
	ShowWindow(SW_HIDE);
}
void CPowerConfigDlg::On32776()
{
	//退出
	Shell_NotifyIcon(NIM_DELETE, &m_nid);//销毁图标
	CDialogEx::OnOK();
}
void CPowerConfigDlg::OnAboutDlg()
{
	//显示关于
	CAboutDlg Dlg;
	Dlg.DoModal();
}


void CPowerConfigDlg::OnReportBug()
{
	//报告Bug
	MessageBox(_T("懒得写了(●'◡'●)，有什么Bug用QQ跟我说一下就行\r\nQQ：635114964"), _T("提示"), MB_ICONINFORMATION);
}


void CPowerConfigDlg::OnEnSetfocusEdit1()
{
	//单击文本框更新
	UpdateState();
}


void CPowerConfigDlg::OnBnClickedButton3()
{
	//单击按钮更新
	UpdateState();
}


void CPowerConfigDlg::OnHelp()
{
	//显示帮助
	HelpDlg Dlg;
	Dlg.DoModal();
}


void CPowerConfigDlg::OnMinimized()
{
	//窗口最小化
	ShowWindow(SW_SHOWMINIMIZED);
}


