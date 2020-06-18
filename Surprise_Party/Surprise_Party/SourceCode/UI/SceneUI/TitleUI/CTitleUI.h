#ifndef CTITLE_UI_H
#define CTITLE_UI_H

#include "..\CSceneUIBase.h"

/*************************************
*		�^�C�g��UI�N���X.
****************/
class CTitleUI
	: public CSceneUIBase
{
public:
	CTitleUI();
	~CTitleUI();
	//======================�萔=======================//.
	const unsigned int GAME_START_FLAG = (1 << 0);		//�Q�[���X�^�[�g�t���O.
	const unsigned int GAME_FINISH_FLAG = (1 << 1);		//�Q�[���I���t���O.	

	//======================�֐�=======================//.
	unsigned int GetSelectTypeFlag() const;	//�I����ނ̃t���O���擾�����֐�.
	
private:
	//======================�֐�=======================//.
	void Init();	//�����������֐�.

	//======================�ϐ�=======================//.
	unsigned int m_SelectTypeFlag;	//�I����ރt���O.

};

#endif	//#ifndef CTITLE_UI_H.