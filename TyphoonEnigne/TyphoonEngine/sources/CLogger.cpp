/*******************************************************************/
/* Filename:                  CLogger.cpp                           */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         17.05.2006                           */
/* Last revision:             17.05.2006                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/



#include "bibloteki.h"
#include "CLogger.h"
// ---------------------------------------------------------
// CLogger::CLogger()
// constructor
// ---------------------------------------------------------
//
CLogger::CLogger() 
{
	errors = 0;
	succes = 0;
	s = false; 
}
// ---------------------------------------------------------
// CLogger::Creat(const TCHAR *name)
// funcion creat log file
// ---------------------------------------------------------
//
void CLogger::Create(const TCHAR *name)
{	
	
	logFile = _wfopen(name, TEXT("wt"));
	
	fwprintf(logFile, _T("</head> <body> <pre><table width=400 bgcolor=#CFCFE5><tr> <td> <font face=arial size=+3> \n"));
	fwprintf(logFile, _T("Typhoon Log File \n"));
	fwprintf(logFile, _T("</font></table><table width=400 cellspacing=0 cellpadding=0><tr><td width=0 bgcolor=#EDEDF5>&nbsp;</td><td width=0 bgcolor=#FFFFFF>&nbsp;</td><td width=auto><pre>"));
	fwprintf(logFile, _T("</pre></table><table width=400 bgcolor=#DFDFE5><tr><td><font face=arial size=+2> \n"));
	fwprintf(logFile, _T("Logging \n"));
	fwprintf(logFile, _T("</font></table><table width=400 cellspacing=0 cellpadding=0><tr><td width=0 bgcolor=#EDEDF5>&nbsp;</td><td width=0 bgcolor=#FFFFFF>&nbsp;</td><td width=auto> \n"));
}
// ---------------------------------------------------------
// CLogger::Append(const TCHAR *name)
// funcion open and append log file
// ---------------------------------------------------------
//
void CLogger::Append(const TCHAR *name)
{
	logFile = _wfopen(name, TEXT("a"));
	fseek(logFile,0, SEEK_CUR);
}
// ---------------------------------------------------------
// CLogger::NewSection(const TCHAR *name)
// funcion is starting new section
// ---------------------------------------------------------
//
void CLogger::NewSection(const TCHAR *name)
{
	fwprintf(logFile, _T("[[Section]] :  %s \n <br>"), name);

}
// ---------------------------------------------------------
// CLogger::LogSucces(const TCHAR *data)
// funcion is logging succes event
// ---------------------------------------------------------
//
void CLogger::LogSucces(const TCHAR *data)
{
	fwprintf(logFile, _T("&nbsp;&nbsp;&nbsp; + [Succes] : %s \n <br>"), data);
	succes++;
}
// ---------------------------------------------------------
// CLogger::LogError(const TCHAR *data)
// funcion is logging error event
// ---------------------------------------------------------
//
void CLogger::LogError(const TCHAR *data)
{
	fwprintf(logFile, _T("<font color = red>&nbsp;&nbsp;&nbsp; + [Error] : %s \n <br></red>"), data);
	errors++;
}

// ---------------------------------------------------------
// CLogger::CheckInt(const TCHAR *text, int data)
// funcion write value of int data
// ---------------------------------------------------------
//
void CLogger::CheckInt(const TCHAR *text, int data)
{
	fwprintf(logFile, _T("&nbsp;&nbsp;&nbsp; + [Check INT] : |%s| == %d \n <br>"), text, data);
}
// ---------------------------------------------------------
// CLogger::CheckFloat(const TCHAR *text, float data)
// funcion write value of float data
// ---------------------------------------------------------
//
void CLogger::CheckFloat(const TCHAR *text, float data)
{
	fwprintf(logFile, _T("&nbsp;&nbsp;&nbsp; + [Check FLOAT] : |%s| == %f \n <br>"), text, data);
}
// ---------------------------------------------------------
// CLogger::CheckChar(const TCHAR *text, TCHAR *data)
// funcion write value of char data
// ---------------------------------------------------------
//
void CLogger::CheckChar(const TCHAR *text, TCHAR *data)
{
	fwprintf(logFile, _T("&nbsp;&nbsp;&nbsp; + [Check CHAR] : |%s| == %s \n <br>"), text, data);
}
// ---------------------------------------------------------
// CLogger::Finish()
// finish logging
// ---------------------------------------------------------
//
void CLogger::Finish()
{
	fseek(logFile,0, SEEK_END);
	fwprintf(logFile, _T("</pre></table><table width=400 bgcolor=#DFDFE5><tr><td><font face=arial size=+2> \n"));
	fwprintf(logFile, _T("Results \n"));
	fwprintf(logFile, _T("</font></table><table width=* cellspacing=0 cellpadding=0><tr><td width=0 bgcolor=#EDEDF5>&nbsp;</td><td width=0 bgcolor=#FFFFFF>&nbsp;</td><td width=*> \n"));
	fwprintf(logFile, _T("%d error(s), %d succes \n"), errors, succes);
	fwprintf(logFile, _T("</pre></table><table   width=400 height=20 bgcolor=#CFCFE5><tr><td><font face=arial size=+2> \n"));
	fwprintf(logFile, _T("</font></table></body></html> \n"));
	
	fclose(logFile);

}
void CLogger::Load()
{
	fclose(logFile);
}
// ---------------------------------------------------------
// CLogger::~CLogger()
// destructor. Kill 
// ---------------------------------------------------------
//
CLogger::~CLogger()
{	
	//if(!s) fclose(logFile);
}
