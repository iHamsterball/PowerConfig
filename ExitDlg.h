#pragma once


// ExitDlg 对话框

class ExitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ExitDlg)

public:
	ExitDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ExitDlg();

// 对话框数据
	enum { IDD = IDD_EXIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
