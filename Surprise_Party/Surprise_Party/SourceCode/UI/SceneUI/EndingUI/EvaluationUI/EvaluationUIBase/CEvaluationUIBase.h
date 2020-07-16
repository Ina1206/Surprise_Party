#ifndef CEVALUATION_UI_BASE_H
#define CEVALUATION_UI_BASE_H

#include "..\..\..\..\CUI.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/****************************************
*		�]��UI�̊��N���X.
*******************/
class CEvaluationUIBase
	: public CUI
{
public:
	CEvaluationUIBase();
	virtual ~CEvaluationUIBase();

	//====================�萔========================//.
	const D3DXVECTOR3	EATCH_SCALE_MAX = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//���ꂼ��̑傫���ő�l.
	const D3DXVECTOR3	EATCH_SCALE_MIN = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���ꂼ��̑傫���ŏ��l
	const float			ALPHA_MIN		= 0.0f;								//���ߒl�ŏ��l.

	//====================�֐�========================//.
	virtual void Update() = 0;	//�X�V�����֐�.
	void Render();				//�`�揈���֐�.

	//==============���擾�����֐�===================//.
	//�S�Ă�\������t���O.
	bool GetFinishedAllDispFlag() const { return m_bFinishedAllDispFlag; }

	//==============���u�������֐�===================//.
	//�S�ĕ\������t���O.
	void SetDisplayAllAtOnce(const bool& bFlag) { m_bDisplayAllAtOnce = bFlag; }

protected:
	//====================�֐�=========================//.
	void InitElementCount();	//�v�f���Ə����l�̏����������֐�.

	//====================�ϐ�=========================//.
	std::vector<CSpriteUI*>		m_pCEvaluationUI;			//�]��UI.
	std::vector<D3DXVECTOR3>	m_vEvaluationPos;			//�\�����W.
	D3DXVECTOR3					m_vPrePos;					//���S���𓮂������W.
	std::vector<D3DXVECTOR3>	m_vEvaluationRot;			//�p�x.
	std::vector<D3DXVECTOR3>	m_vEvaluationScale;			//�傫��.
	std::vector<D3DXVECTOR2>	m_vEvaluationUV;			//UV���W.
	std::vector<float>			m_fEvaluationAlpha;			//���ߒl.

	SPRITE_STATE				m_stSpriteState;			//�X�v���C�g���.

	bool						m_bFinishedAllDispFlag;		//�S�ĕ\������t���O.
	bool						m_bDisplayAllAtOnce;		//��C�ɕ\������t���O.
	int							m_UpdateNum;				//�X�V����ԍ�.

	CPlaySoundManager*			m_pCPlaySoundManager;		//���Đ��Ǘ��N���X.
};

#endif	//#ifndef CEVALUATION_UI_BASE_H.