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

	//===========================�֐�=================================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//===========================�֐�=================================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void UpdateCursor();//�J�[�\���X�V�����֐�.
	void RenderCursor();//�J�[�\���`�揈���֐�.

	//===========================�ϐ�=================================//.
	CSpriteUI*					m_pCSpriteUI;		//�X�v���C�gUI.	
	D3DXVECTOR3					m_vCursorPos;		//�J�[�\�����W.
	float						m_fCursorAlpha;		//�J�[�\�����ߒl.
	int							m_FlashingCursorCnt;//�J�[�\���_�ŃJ�E���g.
	std::vector<std::string>	m_stArticleDetail;	//�L���ڍ�.
	int							m_EndingTypeNum;	//�G���f�B���O�^�C�v�ԍ�.

};

#endif	//#ifndef CREPUTATION_SNS_H.