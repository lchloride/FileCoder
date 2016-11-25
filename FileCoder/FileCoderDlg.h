
// FileCoderDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CFileCoderDlg �Ի���
class CFileCoderDlg : public CDialogEx
{
// ����
public:
	CFileCoderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILECODER_DIALOG };
#endif

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
//	CButton m_operRadioGroup;
	CString m_filename;
	CListBox m_log;
	afx_msg void OnBnClickedOk();
	BOOL m_operRatioGroup;
//	BOOL CFileCoderDlg::execmd(wchar_t* filename, wchar_t* para);
	unsigned int MAXLEN = 1;
	unsigned int VERSION = 1;
	bool decode(CString filename);
	int m_lang;
	afx_msg void OnBnClickedSaveLang();
private:
	bool restart_flag;
public:
	afx_msg void OnClose();
};
