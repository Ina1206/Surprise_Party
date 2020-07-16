#ifndef CSPRITE_EFFECT_BASE_H
#define CSPRITE_EFFECT_BASE_H

#include "..\Drawing\Resource\CResourceManager.h"
#include "..\..\Global.h"
#include "..\Sound\PlaySoundManager\CPlaySoundManager.h"

/*********************************************
*		�X�v���C�g�̃G�t�F�N�g���N���X.
********/
class CSpriteEffectBase
{
public:
	CSpriteEffectBase();
	virtual ~CSpriteEffectBase();

	//================�萔====================//.
	const D3DXVECTOR3	SCALE_MAX			= D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//�傫���ő�l.
	const D3DXVECTOR3	SCALE_MIN			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�傫���ŏ��l.
	const float			ALPHA_MAX			= 1.0f;								//���ߒl�ő�l.
	const float			ALPHA_MIN			= 0.0f;								//���ߒl�ŏ��l.

	const int			ADDITION_NUM		= 1;								//���Z�ԍ�.
	const int			CHANGE_ADD_SUB		= -1;								//���Z���Z�ύX���l.

	const float			CIRCLE_HALF_ANGLE	= 180.0f;							//���~�̊p�x.
	const float			PI					= 3.14159265358979323846264338f;	//�~����.

	//================�֐�====================//.
	virtual void Update() = 0;																			//�X�V�����֐�.
	virtual void PlayStartInit(const int& num) = 0;														//�G�t�F�N�g�J�n�����������֐�.
	void	Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos);	//�`�揈���֐�.

	//==========���u�������֐�==============//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }		//�������W.
	void SetPlayFlag(const bool& flag) { m_bPlayFlag = flag; }
	void SetAngle(const float& angle);										//�p�x.
	void SetStartAngle(const float& angle) { m_fStartAngle = angle; }

	//==========���擾�����֐�==============//.
	int GetSpriteMax() { return m_pCSprite.size(); }						//�X�v���C�g�ő吔.
	bool GetRenderFlag() const { return m_bRenderFlag; }

protected:
	//================�֐�====================//.
	virtual void Init() = 0;							//�����������֐�.
	virtual void Release() = 0;							//��������֐�.
	virtual void AppeartJudgement(const int& num) = 0;	//�\�����菈���֐�.
	virtual void Move(const int& num) = 0;				//�ړ������֐�.
	void SettingDefaultValue(const int& num);			//�����l�ݒ菈���֐�.
	void SettingElementsCount();						//�v�f���ݒ菈���֐�.
	bool ScalingTransparent(const int& num);			//���ߏ����֐�.

	//================�ϐ�====================//.
	std::vector<CSprite*>		m_pCSprite;				//�X�v���C�g�N���X.
	std::vector<D3DXVECTOR3>	m_vPos;					//���W.
	std::vector<D3DXVECTOR3>	m_vRot;					//�p�x.
	std::vector<D3DXVECTOR3>	m_vScale;				//�傫��.
	std::vector<float>			m_fAlpha;				//���ߒl.
	std::vector<float>			m_fAngle;				//�p�x.
	std::vector<float>			m_fDistance;			//����.
	std::vector<D3DXVECTOR2>	m_vPart;				//���摜�̏ꏊ.
	D3DXVECTOR3					m_vCenterPos;			//�������W.
	float						m_fAlphaSpeed;			//���ߑ��x.
	float						m_fScalingSpeed;		//�傫�����x.
	CResourceManager*			m_pCResourceManager;	//�ǂݍ��݊Ǘ��N���X.
	CDepth_Stencil*				m_pCDepthStencil;		//�f�v�X�X�e���V��.
	
	std::vector<bool>			m_bDispFlag;			//�\���t���O.
	int							m_DispTime;				//�\����؂莞��.
	std::vector<int>			m_ChangeAddSub;			//���Z���Z�ύX.

	bool						m_bPlayFlag;			//�Đ��t���O.
	bool						m_bRenderFlag;			//�`��t���O.

	float						m_fStartAngle;			//�J�n���W.

	CPlaySoundManager*			m_pCPlaySoundManager;	//���Đ��Ǘ��N���X.

private:

};

#endif	//#ifndef CSPRITE_EFFECT_BASE_H.