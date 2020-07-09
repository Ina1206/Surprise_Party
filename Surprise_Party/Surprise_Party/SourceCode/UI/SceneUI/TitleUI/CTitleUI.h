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
	//m_SelectTypeFlag.
	const unsigned int GAME_START_FLAG		= (1 << 0);		//�Q�[���X�^�[�g�t���O.
	const unsigned int GAME_FINISH_FLAG		= (1 << 1);		//�Q�[���I���t���O.	
	//m_ControlFlag.
	const unsigned int CONTROL_WAIT_FLAG	= (1 << 0);		//����ҋ@�t���O.
	const unsigned int CONTROL_FLAG			= (1 << 1);		//����t���O.

	//======================�֐�=======================//.
	void Update();	//�X�V�����֐�.

	//================���擾�����֐�=================//.
	unsigned int GetSelectTypeFlag() const;	//�I����ނ̃t���O���擾�����֐�.
	
private:
	//======================�֐�=======================//.
	void Init();	//�����������֐�.

	//======================�ϐ�=======================//.
	unsigned int m_SelectTypeFlag;	//�I����ރt���O.
	unsigned int m_ControlFlag;		//����t���O.

};

#endif	//#ifndef CTITLE_UI_H.