#pragma once


// HelpDlg �Ի���

class HelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HelpDlg)

public:
	HelpDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~HelpDlg();

// �Ի�������
	enum { IDD = IDD_HELP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString Help;
	virtual BOOL OnInitDialog();
};
