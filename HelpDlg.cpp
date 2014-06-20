// HelpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PowerConfig.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// HelpDlg 对话框

IMPLEMENT_DYNAMIC(HelpDlg, CDialogEx)

HelpDlg::HelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(HelpDlg::IDD, pParent)
	, Help(_T(""))
{

}

HelpDlg::~HelpDlg()
{
}

void HelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HelpDlg, CDialogEx)
	ON_COMMAND(ID_32780, &HelpDlg::OnHelp)
END_MESSAGE_MAP()


// HelpDlg 消息处理程序

BOOL HelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 初始化帮助文本并显示
	Help += _T("本程序用于自动切换电源模式，在设定时间会自动切换到选定的电源模式\r\n");
	Help += _T("\r\n");
	Help += _T("最多设定10个任务，任务设定后不可删除，当软件关闭时已经设定的任务将不会执行\r\n");
	Help += _T("\r\n");
	Help += _T("适用用途：会定时断电的情况");
	SetDlgItemText(IDC_HELP, Help);
	UpdateData(false);
	
	SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


