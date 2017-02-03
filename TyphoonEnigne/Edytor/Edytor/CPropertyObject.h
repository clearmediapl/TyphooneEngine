#include "Libraries.h"
#include "CWindow.h"
//constrols
#include "CComboBox.h"
#include "CEdit.h"
#include "CGroupBox.h"

class CPropertyObject : public CWindow
{

private: 
	CGroupBox *m_box;

	

	CEdit *m_eCollidable;
	CEdit *m_eCollisionType;

public:
	CComboBox *m_cCollidable;
	CComboBox *m_cCollisionType;

public:

	CPropertyObject();
	~CPropertyObject();

	void Visable(bool stage);
	void Draw();

	void SetCollidable(bool stage);
	void SetCollisionType(int ID);
	bool getCollidable();
	int  getCollisionType();


};
