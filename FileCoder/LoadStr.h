#pragma once
class LoadStr
{
public:
	LoadStr();
	~LoadStr();
	static CString loadStr(CString id);
	static const int MAX_SIZE = 1024;
};

