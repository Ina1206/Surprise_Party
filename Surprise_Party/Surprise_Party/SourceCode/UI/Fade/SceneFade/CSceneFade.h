#ifndef CSCENE_FADE_H
#define CSCENE_FADE_H

#include "..\CFade.h"

/****************************************
*		�V�[���̃t�F�[�h�N���X.
**********/
class CSceneFade
	: public CFade
{
public:
	CSceneFade();
	~CSceneFade();

	//==================�萔======================//.
	const unsigned int	CLOSE_FLAG				= (1 << 0);							//�t�F�[�h�C���t���O.
	const unsigned int  OPEN_FLAG				= (1 << 1);							//�t�F�[�h�A�E�g�t���O.
	const unsigned int	CHANGE_SCENE_FLAG		= (1 << 2);							//�V�[���ύX�t���O.

	const float			SHUTTER_MOVE_SPEED		= 8.0f;								//�V���b�^�[�ړ����x.
	const float			SHUTTER_HEIGHT_MIN		= -850.0f;							//�V���b�^�[�����ŏ��l.
	const D3DXVECTOR3	SHUTTER_INIT_POS		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�V���b�^�[�����l.

	const int			WAIT_CHANGE_SCENE_TIME	= 30;								//�V�[���ύX�ҋ@����.

	//==================�֐�======================//.
	void UpDate();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

	//==============���u�������֐�==============//.
	//�V���b�^�[�����t���O.
	void SetShutterFlag(const unsigned int& flag) { m_ShutterFlag = flag; }

	//==============���擾�����֐�==============//.
	//�V���b�^�[�����t���O.
	unsigned int GetShutterFlag() { return m_ShutterFlag; }

private:
	//==================�֐�======================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void ShutterDown();	//�V���b�^�[�����鏈���֐�.
	void ShutterUp();	//�V���b�^�[�グ�鏈���֐�.

	//==================�ϐ�======================//.
	CSpriteUI*		m_pCSpriteUI;	//�X�v���C�gUI.
	D3DXVECTOR3		m_vPos;			//���W.

	unsigned int	m_ShutterFlag;	//�V���b�^�[�����t���O.
	int				m_WaitChangeCnt;//�ύX�ҋ@�J�E���g.

};

#endif	//#ifndef CSCENE_FADE_H.