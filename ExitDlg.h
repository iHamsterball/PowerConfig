#pragma once


// ExitDlg �Ի���

class ExitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ExitDlg)

public:
	ExitDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ExitDlg();

// �Ի�������
	enum { IDD = IDD_EXIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
