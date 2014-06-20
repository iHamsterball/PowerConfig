// HelpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PowerConfig.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// HelpDlg �Ի���

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


// HelpDlg ��Ϣ�������

BOOL HelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��ʼ�������ı�����ʾ
	Help += _T("�����������Զ��л���Դģʽ�����趨ʱ����Զ��л���ѡ���ĵ�Դģʽ\r\n");
	Help += _T("\r\n");
	Help += _T("����趨10�����������趨�󲻿�ɾ����������ر�ʱ�Ѿ��趨�����񽫲���ִ��\r\n");
	Help += _T("\r\n");
	Help += _T("������;���ᶨʱ�ϵ�����");
	SetDlgItemText(IDC_HELP, Help);
	UpdateData(false);
	
	SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


