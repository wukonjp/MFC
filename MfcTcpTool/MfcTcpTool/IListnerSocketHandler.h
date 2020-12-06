#pragma once


class IListnerSocketHandler
{
public:
	IListnerSocketHandler();
	virtual ~IListnerSocketHandler();
	virtual void OnAccept() = 0;
};

