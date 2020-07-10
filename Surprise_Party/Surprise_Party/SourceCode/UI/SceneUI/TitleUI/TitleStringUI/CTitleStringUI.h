#ifndef CTITLE_STRING_UI_H
#define CTITLE_STRING_UI_H

#include "..\..\..\CUI.h"

/*********************************************
*		�^�C�g������UI�N���X.
*******************/
class CTitleStringUI
	: public CUI
{
public:
	CTitleStringUI();
	~CTitleStringUI();

	//====================�萔==========================//.
	const D3DXVECTOR3	TITLE_POS			= D3DXVECTOR3(40.5f, 90.8f, 0.0f);	//�^�C�g�����W.
	const int			TITLE_STRING_MAX	= 2;								//�^�C�g���̕��͍ő�l.	

	const unsigned int	FETCH_FLAG			= (1 << 0);							//���ɍs���t���O.
	const unsigned int  MOVE_FLAG			= (1 << 1);							//�ړ��t���O.
	const unsigned int  CONTROL_FLAG		= (1 << 2);							//����t���O.

	//====================�֐�==========================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

	//==============���擾�����֐�====================//.
	//���ɍs���������̍��W.
	D3DXVECTOR3 GetFetchGhostPos() const { return m_vFetchGhostPos; }
	//�ړ���~�t���O.
	bool GetStopMoveFlag() const { return m_bStopFlag[m_FetchStringNum]; }

	//==============���u�������֐�====================//.
	//�ړ�����.
	void SetMoveDistance(const float& fDistance) { m_fMoveDistance = fDistance; }
	//�덷�͈�.
	void SetErrorRange(const float& ErrorRange) { m_fErrorRange = ErrorRange; }
	//�ړ��t���O.
	void SetMoveFlag(const unsigned int& Flag) { m_MoveFlag = Flag; }
	//���̕��͂ɔԍ��ύX.
	void SetChangeNextStringNum() { m_FetchStringNum++; }

private:
	//====================�֐�==========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void ControlPos();	//���쎞�̍��W�����֐�.
	void FetchPos();	//���ɍs�����W�����֐�.
	void Move();		//�ړ������֐�.

	//====================�ϐ�==========================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;		//�X�v���C�gUI.
	std::vector<D3DXVECTOR3>	m_vTitlePos;		//���W.
	std::vector<D3DXVECTOR2>	m_vTitleUV;			//UV.
	std::vector<D3DXVECTOR3>	m_vBeforeMovePos;	//�ړ��O�̍��W.
	std::vector<D3DXVECTOR3>	m_vLastPos;			//�ŏI�I�ȍ��W.
	D3DXVECTOR3					m_vFetchGhostPos;	//���ɍs���������̍��W.
	int							m_FetchStringNum;	//���ɍs�����͔ԍ�.
	float						m_fMoveDistance;	//�ړ�����.
	std::vector<bool>			m_bStopFlag;		//��~�t���O.
	float						m_fErrorRange;		//�덷�͈�.
	unsigned int				m_MoveFlag;			//�ړ��t���O.
};

#endif	//#ifndef CTITLE_STRING_UI_H.