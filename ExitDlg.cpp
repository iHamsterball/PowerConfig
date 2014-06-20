// ExitDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PowerConfig.h"
#include "PowerConfigDlg.h"
#include "ExitDlg.h"
#include "afxdialogex.h"


// ExitDlg �Ի���

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


// ExitDlg ��Ϣ�������


void ExitDlg::OnBnClickedOk()
{
	//��С��������
	CPowerConfigDlg Dlg;
	Dlg.OnMinimize();
	CDialogEx::OnOK();
}


void ExitDlg::OnBnClickedCancel()
{
	//�˳�����
	CPowerConfigDlg Dlg;
	Dlg.On32776();
	CDialogEx::OnCancel();
}
