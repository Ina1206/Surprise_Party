#ifndef CSELECT_STRING_UI_H
#define CSELECT_STRING_UI_H

#include "..\..\CUI.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/***************************************
*		�I����UI�N���X.
********************/
class CSelectStringUI
	: public CUI
{
public:
	CSelectStringUI();
	CSelectStringUI(const bool& bStartFlag);
	~CSelectStringUI();

	//====================�萔======================//.
	const D3DXVECTOR3	SELECT_STRING_POS	= D3DXVECTOR3(800.0f, 450.0f, 0.0f);	//�I�𕶏͍��W.

	const int			SELECT_STRING_MAX	= 2;									//�I���X�v���C�g.

	const unsigned int FETCH_FLAG			= (1 << 0);								//���ɍs���t���O.
	const unsigned int MOVE_FLAG			= (1 << 1);								//�^�ԃt���O.
	const unsigned int CONTROL_FLAG			= (1 << 2);								//����t���O.

	//====================�֐�======================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

	//==============���擾�����֐�================//.
	//�������̃J�[�\�����W.
	D3DXVECTOR3 GetGhostCursorPos() const { return m_vGhostCursorPos; }
	//�ړ���~�t���O.
	bool GetMoveStopFlag() const { return m_bMoveStopFlag; }

	//==============���u�������֐�================//.
	//�ړ��t���O.
	void SetMoveFlag(const unsigned int& Flag) { m_MoveFlag = Flag; }
	//�ړ������t���O.
	void SetMoveDistance(const float& fDistance) { m_fMoveDistance = fDistance; }
	//�덷�͈�.
	void SetErrorRange(const float& fRange) { m_fErrorRange = fRange; }

private:
	//====================�֐�======================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void Fetch();		//���ɍs�������֐�.
	void Move();		//�ړ������֐�.

	void ControlPos();	//���쎞�̍��W�����֐�.

	//====================�ϐ�======================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;			//�X�v���C�gUI.
	std::vector<D3DXVECTOR3>	m_vStringPos;			//���W.
	std::vector<D3DXVECTOR3>	m_vBeforeMovePos;		//�ړ��O�̍��W.
	std::vector<D3DXVECTOR3>	m_vLastPos;				//�ŏI���W.

	D3DXVECTOR3					m_vGhostCursorPos;		//�������̃J�[�\�����W.

	bool						m_bStartFlag;			//�Q�[���J�n�t���O.
	bool						m_bMoveStopFlag;		//�ړ���~�t���O.

	unsigned int				m_MoveFlag;				//�ړ��t���O.

	float						m_fMoveDistance;		//�ړ�����.
	float						m_fErrorRange;			//�덷�͈�.

	CPlaySoundManager*			m_pCPlaySoundManager;	//���Đ��Ǘ��N���X.
};

#endif	//#ifndef CSELECT_STRING_UI_H.