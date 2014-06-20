#include "stdafx.h"
#include "PowerConfigDlg.h"
#include <iostream>
void Mode::SetGUID(CString input)
{
	GUID = input;
}
void Mode::SetName(CString input)
{
	name = input;
}
void Mode::SetActive(bool a)
{
	state = a;
}
CString Mode::GetGUID()
{
	return GUID;
}
CString Mode::GetName()
{
	return name;
}
bool Mode::GetState()
{
	return state;
}

//int Mode::counter = 0;
//int Mode::GetCount(){ return counter; }
