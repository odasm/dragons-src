
//#include "stdafx.h"
#include "utility.h"

#include <tchar.h>
#include <Windows.h>

//get the app path
StdString GetAppPath(void)
{
	TCHAR bufPath[MAX_PATH] = _T("");
	::GetModuleFileName(NULL, bufPath, MAX_PATH);

	StdString strAppPath(bufPath);
	//csAppPath = csAppPath.Left(csAppPath.ReverseFind(_T('\\')));
	//strAppPath = strAppPath.substr(0, strAppPath.rfind(_T("\\")));

	return strAppPath.substr(0, strAppPath.rfind(_T("\\")));;
}

