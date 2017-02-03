
/*******************************************************************/
/* Filename:                  CLogger.h                              */
/* Author:                    Michal Szczepanowski                 */
/* Last modification:         18.05.2006                           */
/* Last revision:             18.05.2006                           */
/* Revised by:                Michal Szczepanowski                 */
/*******************************************************************/
class CLogger
{
private:
	int errors;
	int succes;

	bool s;

public:
	FILE *logFile;
	CLogger();

	void Create(const TCHAR *name);
	void Append(const TCHAR *name);

	void LogSucces(const TCHAR *data);
	void LogError(const TCHAR *data);

	void NewSection(const TCHAR *name);

	void CheckFloat(const TCHAR *text, float data);
	void CheckInt(const TCHAR *text, int data);
	void CheckChar(const TCHAR *text, TCHAR *data);

	void Load();

	void Finish();
	~CLogger();

};