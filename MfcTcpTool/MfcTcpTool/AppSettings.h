#pragma once


// AppSettings コマンド ターゲット

enum class ConnectionType
{
	Client,
	Server
};

enum class LogType
{
	ASCII,
	Binary
};

class AppSettings : public CObject
{
public:
	AppSettings();
	virtual ~AppSettings();

public:
	ConnectionType m_eConnectionType;
	CString m_sIpAddress;
	int m_nPortNumber;
	LogType m_eLogType;
};


