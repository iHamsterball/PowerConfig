
// PowerConfigDlg.h : ͷ�ļ�
//

#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "resource.h"
#define WM_SHOWTASK WM_USER

// CPowerConfigDlg �Ի���
class CPowerConfigDlg : public CDialogEx
{
// ����
public:
	CPowerConfigDlg(CWnd* pParent = NULL);	// ��׼���캯��
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
// �Ի�������
	enum { IDD = IDD_POWERCONFIG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
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
	//Mode�࣬���ڼ�¼��ǰ�ĵ�Դģʽ��Ϣ
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
	//static int counter;//��¼����
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
	}//Ĭ�Ϲ��캯��
	Event(Event *b)
	{
		SetTime.Hour = b->SetTime.Hour;
		SetTime.Minute = b->SetTime.Minute;
		SetTime.Second = b->SetTime.Second;
	}//���ƹ��캯��
	int GetCounter()
	{
		return counter;
	}
private:
	static int counter;
};