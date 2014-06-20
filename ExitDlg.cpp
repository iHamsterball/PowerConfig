// ExitDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PowerConfig.h"
#include "PowerConfigDlg.h"
#include "ExitDlg.h"
#include "afxdialogex.h"


// ExitDlg 对话框

IMPLEMENT_DYNAMIC(ExitDlg, CDialogEx)

ExitDlg::ExitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ExitDlg::IDD, pParent)
{

}

ExitDlg::~ExitDlg()
{
}

void ExitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ExitDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ExitDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ExitDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// ExitDlg 消息处理程序


void ExitDlg::OnBnClickedOk()
{
	//最小化主窗口
	CPowerConfigDlg Dlg;
	Dlg.OnMinimize();
	CDialogEx::OnOK();
}


void ExitDlg::OnBnClickedCancel()
{
	//退出程序
	CPowerConfigDlg Dlg;
	Dlg.On32776();
	CDialogEx::OnCancel();
}
