#include "stdafx.h"
#include "LoadStr.h"
#include "FileCoderDlg.h"


LoadStr::LoadStr()
{
}


LoadStr::~LoadStr()
{
}

CString LoadStr::loadStr(CString id)
{
	CString result = L"";
	wchar_t load_wstr[MAX_SIZE+1] = L"";
	int lang = ((CFileCoderDlg)AfxGetMainWnd()).m_lang;
	CString lang_cstr = L"";
	switch (lang)
	{
	case 0: lang_cstr = L"zh_CN"; break;
	case 1: lang_cstr = L"en_US"; break;
	case 2: lang_cstr = L"ja_JP"; break;
	default: lang_cstr = L"zh_CN";
		break;
	}

	GetPrivateProfileStringW(lang_cstr, id.MakeUpper(), L"", load_wstr, MAX_SIZE, L".//setting.ini");
	result.Format(L"%ls", load_wstr);
	return result;
}