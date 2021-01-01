
// CppLinq.MFC.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//
#pragma once
#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif
#include "resource.h"		// メイン シンボル

// CppLinqApp:
class CppLinqApp : public CWinApp
{
public:
	CppLinqApp();
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};

extern CppLinqApp theApp;
