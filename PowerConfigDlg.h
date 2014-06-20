
// PowerConfigDlg.h : 头文件
//

#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "resource.h"
#define WM_SHOWTASK WM_USER

// CPowerConfigDlg 对话框
class CPowerConfigDlg : public CDialogEx
{
// 构造
public:
	CPowerConfigDlg(CWnd* pParent = NULL);	// 标准构造函数
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
// 对话框数据
	enum { IDD = IDD_POWERCONFIG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl Time;
	NOTIFYICONDATA m_nid;
	CListCtrl List;
	CString output;
	CToolTipCtrl m_tip;
	int CurHour, CurMinute, CurSecond;
	afx_msg void OnBnClickedButton2();
	CString Output;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox Combo;
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnMinimize();
	afx_msg void On32776();
	afx_msg void OnAboutDlg();
	afx_msg void OnReportBug();
	CString CurrentMode;
	afx_msg void OnEnSetfocusEdit1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnHelp();
	afx_msg void OnMinimized();
	afx_msg void OnClose();

};

class Mode
{
	//Mode类，用于记录当前的电源模式信息
public:

	void SetName(CString name);
	void SetGUID(CString GUID);
	void SetActive(bool a);
	CString GetName();
	CString GetGUID();
	bool GetState();
	//static int GetCount();
private:
	CString GUID = { _T("                                    "), 36 };
	CString name;
	bool state = false;
	//static int counter;//记录个数
};
struct SetTime
{
	int Hour;
	int Minute;
	int Second;
};
class Event
{
public:
	SetTime SetTime;
	int mode;
	int index;
	Event()
	{
		counter++;
	}//默认构造函数
	Event(Event *b)
	{
		SetTime.Hour = b->SetTime.Hour;
		SetTime.Minute = b->SetTime.Minute;
		SetTime.Second = b->SetTime.Second;
	}//复制构造函数
	int GetCounter()
	{
		return counter;
	}
private:
	static int counter;
};