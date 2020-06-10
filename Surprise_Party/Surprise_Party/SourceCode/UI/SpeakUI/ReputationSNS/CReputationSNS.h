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
	const unsigned int	START_TRANSPARENT_FLAG	= (1 << 0);							//���߃X�^�[�g�t���O.
	const unsigned int	CHANGE_STAGE_FLAG		= (1 << 1);							//�X�e�[�W�ύX�t���O.

	const D3DXVECTOR3	INIT_FONT_POS			= D3DXVECTOR3(50.0f, 300.0f, 0.0f);	//�����񏉊����W.
	const float			FONT_SCALE				= 90.0f;							//�t�H���g�傫��.
	const float			STRING_WIDTH_MAX		= 1000.0f;							//�����񕝍ő�l.
	const float			ADJUSTMENT_HEIGHT		= 15.0f;							//�J�[�\������������.
	const int			FLASING_CNT_MAX			= 20;								//�_�ŃJ�E���g�ő�l.
	const int			CURSOR_NUM				= 0;								//�J�[�\���ԍ�.
	const int			PICTURE_NUM				= 1;								//�ʐ^�ԍ�.	

	//===========================�֐�=================================//.
	void Update();									//�X�V�����֐�.
	void Render();									//�`�揈���֐�.
	void DecideString(const int& EndingNum);		//���͌��菈���֐�.

	//=====================���擾�����֐�===========================//.
	//�X�e�[�W�ύX�t���O.
	unsigned int GetChangeStage() const { return m_ChangeStageFlag; }

private:
	//===========================�֐�=================================//.
	void Init();									//�����������֐�.
	void Release();									//��������֐�.
	void UpdateCursor();							//�J�[�\���X�V�����֐�.
	void MoveCursor();								//�J�[�\���ړ�.
	void DecidePicture(const int& EndingNum);		//�ʐ^���菈���֐�.
	void RenderSpriteUI();							//�X�v���C�gUI�`�揈���֐�.
	void TransparentAll();							//�S�Ă̓��ߏ����֐�.

	//===========================�ϐ�=================================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;		//�X�v���C�gUI.
	std::vector<D3DXVECTOR3>	m_vSpriteUIPos;		//�X�v���C�gUI���W.
	std::vector<float>			m_fSpriteUIAlpha;	//�X�v���C�gUI���ߒl.
	int							m_FlashingCursorCnt;//�J�[�\���_�ŃJ�E���g.
	std::vector<std::string>	m_stArticleDetail;	//�L���ڍ�.
	int							m_EndingTypeNum;	//�G���f�B���O�^�C�v�ԍ�.
	unsigned int				m_ChangeStageFlag;	//�X�e�[�W�ύX�t���O.
};

#endif	//#ifndef CREPUTATION_SNS_H.