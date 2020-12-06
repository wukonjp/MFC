// AppSettings.cpp : 実装ファイル
//

#include "pch.h"
#include "AppSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// AppSettings

AppSettings::AppSettings()
{
	m_eConnectionType = ConnectionType::Client;
	m_sIpAddress = _T("127.0.0.1");
	m_nPortNumber = 0;
	m_eLogType = LogType::ASCII;
}

AppSettings::~AppSettings()
{
}


// AppSettings のメンバー関数
