#ifndef CEVALUATION_STAGE_BASE_H
#define CEVALUATION_STAGE_BASE_H

#include "..\CEndingStageBase\CEndingStageBase.h"
#include "..\..\UI\SceneUI\EndingUI\SurpriseDegree\SurpriseDegreeManager\CSurpriseDegreeManager.h"
#include "..\..\UI\SceneUI\EndingUI\EvaluationUI\EvaluationUIManager\CEvaluationUIManager.h"

/**********************************************
*		�]���X�e�[�W���N���X.
************************/
class CEvaluationStageBase
	: public CEndingStageBase
{
public:
	CEvaluationStageBase();
	CEvaluationStageBase(const int& EvaluationNum);
	~CEvaluationStageBase();
	
	//======================�֐�=========================//.
	void Update();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.

protected:

private:
	//===================�萔======================//.
	const D3DXVECTOR3	PUSH_ENTER_POS = D3DXVECTOR3(800.0f, 600.0f, 0.0f);	//PushEnter�̍��W.
	const float			ALPHA_MAX = 1.0f;									//���ߒl�ő�l.
	const float			ALPHA_MIN = 0.0f;									//���ߒl�ŏ��l.
	const float			PUSH_ENTER_SCALE_MAX = 2.0f;						//PushEnter�傫��.

	//======================�֐�=========================//.
	void InitUI();			//UI�̏����������֐�.
	void UpdateCommonUI();	//���ʂ�UI�̍X�V�����֐�.
	void RenderCommonUI();	//���ʂ�UI�̕`�揈���֐�.
	void UpdatePushEnter();	//PushEnter�̍X�V�����֐�.
	void RenderPushEnter();	//PushEnter�̕`�揈���֐�.

	//========================�ϐ�=============================//.
	std::unique_ptr<CSurpriseDegreeManager> m_pCSurpriseDegreeManager;	//�������x�̊Ǘ��N���X.
	std::unique_ptr<CEvaluationUIManager>	m_pCEvaluationUIManager;	//�]��UI�Ǘ��N���X.
	CSpriteUI*								m_pCPushEnterUI;			//SpriteUI�N���X(PushEnter�̕���).
	float									m_fPushEnterUIAlpha;		//SpriteUI�̓��ߒl.
	int										m_AlphaAddDecDirect;		//���ߒl�̉��Z���Z����.

};

#endif	//#ifndef CEVALUATION_STAGE_BASE_H.