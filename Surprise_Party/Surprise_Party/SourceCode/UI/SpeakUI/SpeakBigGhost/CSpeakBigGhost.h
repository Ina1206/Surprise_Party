#ifndef CSPEAK_BIG_GHOST_H
#define CSPEAK_BIG_GHOST_H

#include "..\CSpeakUI.h"

/**********************************************
*		�r�b�O�S�[�X�g������ׂ�N���X.
*************/
class CSpeakBigGhost
	: public CSpeakUI
{
public:
	CSpeakBigGhost();
	~CSpeakBigGhost();

	//======================�萔=======================//.
	const float		STRING_WIDTH_MAX	= 950.0f;		//���͂̕��ő吔.
	const float		ALPHA_MIN			= 0.0f;			//���ߒl�ŏ��l.
	const float		ALPHA_MAX			= 1.0f;			//���ߒl�ő�l.
	const float		ALPHA_SPEED			= 0.1f;			//���ߒl���x.
	const float		FONT_SCALE			= 50.0f;		//�����̑傫��.
	const int		FIRST_CHARACTER_NUM = 0;			//�ꕶ���ڂ̕���.


	const int		SELECT_MAX			= 2;			//�I���ő吔.

	const unsigned int TRANSPARENTING_FLAG	= (1 << 0);	//���ߏ������t���O.
	const unsigned int SELECT_FLAG			= (1 << 1);	//�I���t���O.
	const unsigned int SELECTED_STRING_FLAG = (1 << 2);	//�I���������̓t���O.

	const unsigned int FINISH_NEXT_TITLE	= (1 << 0);	//�����^�C�g���ł̏I��.
	const unsigned int FINISH_NEXT_GAME		= (1 << 1);	//�����Q�[���ł̏I��.

	//======================�֐�=======================//.
	void Update();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.
	void RenderInit(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos);	//�`�揉���ݒ菈���֐�.

	//================���l�������֐�==================//.
	int GetEmotionNum() const { return m_EmotionNum[m_SpeakNum]; }
	unsigned int GetFinishFlag() const { return m_FinishFlag; }
	bool GetTutorialFlag() const { return m_bTutorialFlag; }

	//================���u�������֐�==================//.
	void SetControlFlag(const bool& flag) { m_bControlFlag = flag; }

private:
	//======================�֐�========================//.
	void Init();									//�����������֐�.
	void Release();									//��������֐�.
	void LoadSpeakString();							//��b���͓ǂݍ��ݏ����֐�.
	void TransparentFont();							//�������ߏ����֐�.
	void DecisionSelectString();					//�I�𕶏͏����֐�.
	void FindNextString(const int& NextStringNum);	//���̕��͂������鏈���֐�.
	void SelectingMove();							//�I�𒆈ړ������֐�.
	void ChangeString();							//���͕ύX�����֐�.

	//======================�ϐ�========================//.
	D3DXMATRIX					m_mView;			//�r���[�s��.
	D3DXMATRIX					m_mProj;			//�v���W�F�N�V�����s��.
	D3DXVECTOR3					m_vCameraPos;		//�J�������W.

	CSpriteUI*					m_pCSpriteUI;		//�X�v���C�gUI.
	std::vector<CSprite*>		m_pCSprite;			//�X�v���C�g�N���X.
	std::vector<D3DXVECTOR3>	m_vSelectPos;		//���W.
	std::vector<D3DXVECTOR3>	m_vSelectRot;		//�p�x.
	std::vector<float>			m_fSelectAlpha;		//���ߒl.
	std::vector<float>			m_fSelectScale;		//�傫��.

	std::vector<std::string>	m_stSelectString;	//�I�𕶏�.
	std::vector<int>			m_EmotionNum;		//����ԍ�.
	unsigned int				m_StringFlag;		//���̓t���O.
	int							m_SelectNum;		//�I��ԍ�.
	int							m_SelectCnt;		//�I���J�E���g.

	unsigned int				m_FinishFlag;		//�I���t���O.
	bool						m_bTutorialFlag;	//�`���[�g���A���t���O.

	bool						m_bControlFlag;		//����t���O.

};


#endif	//#ifndef CSPEAK_BIG_GHOST_H.