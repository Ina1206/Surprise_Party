#ifndef CREPUTATION_SNS_H
#define CREPUTATION_SNS_H

#include "..\CSpeakUI.h"

/***************************************
*		SNS�ł̕]���N���X.
*******************/
class CReputationSNS
	: public CSpeakUI
{
public:
	CReputationSNS();
	~CReputationSNS();

	//===========================�萔=================================//.
	const D3DXVECTOR3	INIT_FONT_POS		= D3DXVECTOR3(50.0f, 250.0f, 0.0f);	//�����񏉊����W.
	const float			FONT_SCALE			= 90.0f;							//�t�H���g�傫��.
	const float			STRING_WIDTH_MAX	= 1000.0f;							//�����񕝍ő�l.
	const float			ADJUSTMENT_HEIGHT	= 15.0f;							//�J�[�\������������.
	const int			FLASING_CNT_MAX		= 20;								//�_�ŃJ�E���g�ő�l.

	//===========================�֐�=================================//.
	void Update();									//�X�V�����֐�.
	void Render();									//�`�揈���֐�.
	void DecideString(const int& EndingNum);		//���͌��菈���֐�.

private:
	//===========================�֐�=================================//.
	void Init();									//�����������֐�.
	void Release();									//��������֐�.
	void UpdateCursor();							//�J�[�\���X�V�����֐�.
	void RenderCursor();							//�J�[�\���`�揈���֐�.
	void MoveCursor();								//�J�[�\���ړ�.

	//===========================�ϐ�=================================//.
	CSpriteUI*					m_pCSpriteUI;		//�X�v���C�gUI.	
	D3DXVECTOR3					m_vCursorPos;		//�J�[�\�����W.
	float						m_fCursorAlpha;		//�J�[�\�����ߒl.
	int							m_FlashingCursorCnt;//�J�[�\���_�ŃJ�E���g.
	std::vector<std::string>	m_stArticleDetail;	//�L���ڍ�.
	int							m_EndingTypeNum;	//�G���f�B���O�^�C�v�ԍ�.

};

#endif	//#ifndef CREPUTATION_SNS_H.