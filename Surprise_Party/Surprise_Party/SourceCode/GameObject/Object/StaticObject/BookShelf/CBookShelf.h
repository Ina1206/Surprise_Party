#ifndef CBOOK_SHELF_H
#define CBOOK_SHELF_H

#include "..\CStaticObjectBase.h"

/************************************
*		�{�I�N���X.
*****************/
class CBookShelf
	: public CStaticObjectBase
{
public:
	CBookShelf();
	~CBookShelf();

	//=============�֐�===============//.
	void Update();	//�X�V�����֐�.
private:
	//=============�֐�===============//.
	void Init();	//�����������֐�.
	void Release();	//��������֐�.


};

#endif	//#ifndef CBOOK_SHELF_H.