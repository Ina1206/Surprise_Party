#ifndef CSTAGE_MAP_H
#define CSTAGE_MAP_H

#include "..\CMapUI.h"

/**************************************
*		�X�e�[�W�}�b�v�N���X.
********/
class CStageMap
	: public CMapUI
{
public:
	CStageMap();
	~CStageMap();

	
private:
	//=================�֐�=====================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CSTAGE_MAP_H.