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
	
}
// ---------------------------------------------------------
// CLogger::Creat(const TCHAR *name)
// funcion creat log file
// ---------------------------------------------------------
//
void CLogger::Create(const TCHAR *name)
{	
	logFile = _wfopen(name, TEXT("w"));
	fwprintf(logFile, _T("START : logging \n"));
}
// ---------------------------------------------------------
// CLogger::Append(const TCHAR *name)
// funcion open and append log file
// ---------------------------------------------------------
//
void CLogger::Append(const TCHAR *name)
{
	logFile = _wfopen(name, TEXT("a"));
}
// ---------------------------------------------------------
// CLogger::LogSucces(const TCHAR *data)
// funcion is logging succes event
// ---------------------------------------------------------
//
void CLogger::LogSucces(const TCHAR *data)
{
	fwprintf(logFile, _T(" + [Succes] : %s \n"), data);
}
// ---------------------------------------------------------
// CLogger::LogError(const TCHAR *data)
// funcion is logging error event
// ---------------------------------------------------------
//
void CLogger::LogError(const TCHAR *data)
{
	fwprintf(logFile, _T(" + [Error] : %s \n"), data);
}
// ---------------------------------------------------------
// CLogger::NewSection(const TCHAR *name)
// funcion is starting new section
// ---------------------------------------------------------
//
void CLogger::NewSection(const TCHAR *name)
{
	fwprintf(logFile, _T("START :  %s \n"), name);

}
// ---------------------------------------------------------
// CLogger::CheckInt(const TCHAR *text, int data)
// funcion write value of int data
// ---------------------------------------------------------
//
void CLogger::CheckInt(const TCHAR *text, int data)
{
	fwprintf(logFile, _T(" + [Check INT] : |%s| == %d \n"), text, data);
}
// ---------------------------------------------------------
// CLogger::CheckFloat(const TCHAR *text, float data)
// funcion write value of float data
// ---------------------------------------------------------
//
void CLogger::CheckFloat(const TCHAR *text, float data)
{
	fwprintf(logFile, _T(" + [Check FLOAT] : |%s| == %f \n"), text, data);
}
// ---------------------------------------------------------
// CLogger::CheckChar(const TCHAR *text, TCHAR *data)
// funcion write value of char data
// ---------------------------------------------------------
//
void CLogger::CheckChar(const TCHAR *text, TCHAR *data)
{
	fwprintf(logFile, _T(" + [Check CHAR] : |%s| == %s \n"), text, data);
}
// ---------------------------------------------------------
// CLogger::~CLogger()
// destructor. Kill 
// ---------------------------------------------------------
//
CLogger::~CLogger()
{
	
	fclose(logFile);
}
