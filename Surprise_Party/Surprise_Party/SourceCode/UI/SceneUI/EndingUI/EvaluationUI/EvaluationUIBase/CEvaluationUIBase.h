#ifndef CEVALUATION_UI_BASE_H
#define CEVALUATION_UI_BASE_H

#include "..\..\..\..\CUI.h"

/****************************************
*		�]��UI�̊��N���X.
*******************/
class CEvaluationUIBase
	: public CUI
{
public:
	CEvaluationUIBase();
	virtual ~CEvaluationUIBase();
	
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
	//====================�ϐ�=========================//.
	std::vector<CSpriteUI>		m_pCEvaluationUI;			//�]��UI.
	std::vector<D3DXVECTOR3>	m_vEvaluationPos;			//�\�����W.
	std::vector<D3DXVECTOR3>	m_vPrePos;					//���S���𓮂������W.
	std::vector<D3DXVECTOR3>	m_vEvaluationRot;			//�p�x.
	std::vector<D3DXVECTOR3>	m_vEvaluationScale;			//�傫��.
	std::vector<D3DXVECTOR2>	m_vEvaluationUV;			//UV���W.
	std::vector<float>			m_fEvaluationAlpha;			//���ߒl.

	bool						m_bFinishedAllDispFlag;		//�S�ĕ\������t���O.
	bool						m_bDisplayAllAtOnce;		//��C�ɕ\������t���O.
	int							m_UpdateNum;				//�X�V����ԍ�.

};

#endif	//#ifndef CEVALUATION_UI_BASE_H.