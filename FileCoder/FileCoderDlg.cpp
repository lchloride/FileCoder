
// FileCoderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileCoder.h"
#include "FileCoderDlg.h"
#include "afxdialogex.h"
#include <direct.h>
#include "LoadStr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnClose();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CFileCoderDlg 对话框



CFileCoderDlg::CFileCoderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FILECODER_DIALOG, pParent)
	, m_filename(_T(""))
	, m_operRatioGroup(TRUE)
{
	restart_flag = false;
	m_lang = GetPrivateProfileIntW(L"Setting", L"Language", 0, L".//setting.ini");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileCoderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_ENCODE, m_operRadioGroup);
	DDX_Text(pDX, IDC_EDITBROWSE_FILENAME, m_filename);
	DDV_MaxChars(pDX, m_filename, 260);
	DDX_Control(pDX, IDC_LIST_RESULT, m_log);
	DDX_Radio(pDX, IDC_ENCODE, m_operRatioGroup);
	DDX_Radio(pDX, IDC_ZHCN, m_lang);
}

BEGIN_MESSAGE_MAP(CFileCoderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFileCoderDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SAVE_LANG, &CFileCoderDlg::OnBnClickedSaveLang)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CFileCoderDlg 消息处理程序

BOOL CFileCoderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFileCoderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFileCoderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFileCoderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileCoderDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	char result[1024 * 4] = "";                   //定义存放结果的字符串数组 
	wchar_t path_wstr[1024] = L"";
	wchar_t *path_1 = &path_wstr[1];

	_wgetcwd(path_1, MAX_PATH);
	path_wstr[0] = L'\"';
	wcscat_s(path_wstr, wcslen(path_wstr) + 12, L"\\decode.exe");
	path_wstr[wcslen(path_wstr)] = L'\"';
	
	//CString str(path_wstr);

	//MessageBox(str);
	//str.Format(L"%ls \"%ls\"", str, m_filename);
	if (decode(m_filename))
	{
		MessageBox(LoadStr::loadStr(L"DECODE_SUCCESS"));
	}
	else
		MessageBox(LoadStr::loadStr(L"DECODE_FAILED"));

	//CDialogEx::OnOK();
}


bool CFileCoderDlg::decode(CString filename)
{
	FILE *fin, *fout;
	int rc;
	CString msg = L"";
	_wfopen_s(&fin, filename, L"rb");
	if (fin == NULL)
	{
		MessageBox(LoadStr::loadStr(L"FILE_CANNOT_OPEN"));
		return false;
	}
	else
	{
		int filename_leng;
		rc = fread(&filename_leng, sizeof(int), 1, fin);
		if (rc == 0)
		{
			MessageBox(LoadStr::loadStr(L"READ_FILE_FAILED"));
			fclose(fin);
			return false;
		}
		int ver;
		rc = fread(&ver, sizeof(int), 1, fin);
		if (rc == 0)
		{
			MessageBox(LoadStr::loadStr(L"READ_FILE_FAILED"));
			fclose(fin);
			return false;
		}

		int count_check;
		fread(&count_check, sizeof(int), 1, fin);

		char origin_filename[500] = { '\0' };
		rc = fread(origin_filename, sizeof(char), filename_leng, fin);
		if (rc == 0)
		{
			MessageBox(LoadStr::loadStr(L"READ_FILE_FAILED"));
			fclose(fin);
			return false;
		}
		CString str(origin_filename);
		msg.Format(LoadStr::loadStr(L"PROCESS_MSG"), filename, str);
		m_log.AddString(msg);
		UpdateData(FALSE);

		fopen_s(&fout, origin_filename, "wb");
		char a1, a2;
		int count = 0;
		int rc1 = 1132, rc2 = -96;
		bool set = true;
		while (true)
		{
			a1 = 0;
			a2 = 0;
			rc1 = fread(&a1, sizeof(char), MAXLEN, fin);
			if (rc1 == 0)
			{
				set = true; break;
			}
			rc2 = fread(&a2, sizeof(char), MAXLEN, fin);
			if (rc2 == 0)
			{
				set = false; break;
			}
			fwrite(&a2, sizeof(char), rc2, fout);
			fwrite(&a1, sizeof(char), rc1, fout);
			if (count % (1 << 19) == 0)
			{
				msg.Format(LoadStr::loadStr(L"PROCESS_BAR_MSG"), count / (1 << 19));
				m_log.AddString(msg);
				m_log.SetCurSel(m_log.GetCount());
				UpdateData(FALSE);
			}
			count++;
			// if (count==1)
			// 	break;
		}
		//printf("%d\n", set);
		if (!set)
			fwrite(&a1, sizeof(char), rc1, fout);

		if (count_check == count)
			;// MessageBox(L"Decode Successfully Finished!\n");
		else
			MessageBox(LoadStr::loadStr(L"WRONG_DECODE_FILE"));
		fclose(fout);
	}
	fclose(fin);

	return true;
}



void CFileCoderDlg::OnBnClickedSaveLang()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str = L"";
	str.Format(L"%d", m_lang);
	if (!WritePrivateProfileStringW(
		L"Setting",      // 同上
		L"Language",      // 同上
		str,//LPCTSTR lpString,       // 同上
		L".//setting.ini"
		))
	{
		CString msg = L"";
		msg.Format(L"%ld", GetLastError());
		MessageBox(LoadStr::loadStr(L"SAVE_LANG_FAILED") +str);
	}
	else
	{
		restart_flag = true;
		PostMessage(WM_CLOSE, 0, 0);
	}

}


void CFileCoderDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (restart_flag)
	{
		CString strFileName = _T("");
		GetModuleFileName(NULL, strFileName.GetBuffer(MAX_PATH), MAX_PATH);
		ShellExecute(NULL, _T(""), strFileName, NULL, NULL, SW_SHOWNORMAL);
		strFileName.ReleaseBuffer();
	}
	CDialogEx::OnClose();
}
