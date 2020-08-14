
// CppLinq.MFC.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CppLinqApp:
// このクラスの実装については、CppLinq.MFC.cpp を参照してください
//

class CppLinqApp : public CWinApp
{
public:
	CppLinqApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CppLinqApp theApp;
