#ifndef CSPRITE_EFFECT_BASE_H
#define CSPRITE_EFFECT_BASE_H

#include "..\Drawing\Resource\CResourceManager.h"
#include "..\..\Global.h"

/*********************************************
*		�X�v���C�g�̃G�t�F�N�g���N���X.
********/
class CSpriteEffectBase
{
public:
	CSpriteEffectBase();
	virtual ~CSpriteEffectBase();

	//================�萔====================//.
	const float			SCALE_MAX		= 1.0f;								//�傫���ő�l.
	const float			SCALE_MIN		= 0.0f;								//�傫���ŏ��l.
	const float			ALPHA_MAX		= 1.0f;								//���ߒl�ő�l.
	const float			ALPHA_MIN		= 0.0f;								//���ߒl�ŏ��l.

	const int			ADDITION_NUM	= 1;								//���Z�ԍ�.
	const int			CHANGE_ADD_SUB	= -1;								//���Z���Z�ύX���l.

	const float			PI				= 3.14159265358979323846264338f;	//�~����.

	//================�֐�====================//.
	virtual void Update() = 0;																				//�X�V�����֐�.
	void	Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos);	//�`�揈���֐�.

	//==========���u�������֐�==============//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }		//�������W.

protected:
	//================�֐�====================//.
	virtual void Init() = 0;							//�����������֐�.
	virtual void Release() = 0;							//��������֐�.
	virtual void AppeartJudgement(const int& num) = 0;	//�\�����菈���֐�.
	virtual void Move(const int& num) = 0;				//�ړ������֐�.
	void SettingElementsCount();						//�v�f���ݒ菈���֐�.
	bool ScalingTransparent(const int& num);			//���ߏ����֐�.
	void SettingDefaultValue(const int& num);			//�����l�ݒ菈���֐�.

	//================�ϐ�====================//.
	std::vector<CSprite*>		m_pCSprite;			//�X�v���C�g�N���X.
	std::vector<D3DXVECTOR3>	m_vPos;				//���W.
	std::vector<D3DXVECTOR3>	m_vRot;				//�p�x.
	std::vector<float>			m_fScale;			//�傫��.
	std::vector<float>			m_fAlpha;			//���ߒl.
	std::vector<float>			m_fAngle;			//�p�x.
	D3DXVECTOR3					m_vCenterPos;		//�������W.
	float						m_fAlphaSpeed;		//���ߑ��x.
	float						m_fScalingSpeed;	//�傫�����x.
	CResourceManager*			m_pCResourceManager;//�ǂݍ��݊Ǘ��N���X.
	CDepth_Stencil*				m_pCDepthStencil;	//�f�v�X�X�e���V��.
	
	std::vector<bool>			m_bDispFlag;		//�\���t���O.
	int							m_DispTime;			//�\����؂莞��.
	std::vector<int>			m_ChangeAddSub;		//���Z���Z�ύX.

private:

};

#endif	//#ifndef CSPRITE_EFFECT_BASE_H.