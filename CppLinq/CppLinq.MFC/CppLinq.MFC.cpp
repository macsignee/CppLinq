
// CppLinq.MFC.cpp : アプリケーションのクラス動作を定義します。
//

#include "pch.h"
#include "framework.h"
#include "CppLinq.MFC.h"
#include "..\CppLinq\MacLinq.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace macsignee::cppLinq;
// CppLinqApp

BEGIN_MESSAGE_MAP(CppLinqApp, CWinApp)
END_MESSAGE_MAP()


// CppLinqApp の構築
CppLinqApp::CppLinqApp(){}


// 唯一の CppLinqApp オブジェクト
CppLinqApp theApp;


// CppLinqApp の初期化
BOOL CppLinqApp::InitInstance()
{
	CWinApp::InitInstance();

	CArray<size_t, size_t> ary;
	for (size_t idx = 0; idx < 10; idx++) {
		ary.Add(idx);
	}
	auto a = From(ary);

	AfxMessageBox(_T("OK"));

	return FALSE;
}

