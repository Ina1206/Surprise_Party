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

	const int			BUBBLE_MAX		= 4;								//�A�ő吔.
	const int			Z_MAX			= 3;								//Z�ő吔.
	const int			ALL_SPRITE_MAX	= BUBBLE_MAX + Z_MAX;				//�S�ẴX�v���C�g�ő吔.

	const D3DXVECTOR3	INIT_LOCAL_POS	= D3DXVECTOR3(-2.3f, 2.0f, 0.0f);	//�����̃��[�J�����W.

	const int			CHANGE_ADD_SUB	= -1;								//���Z���Z�ύX���l.

	const float			PI				= 3.14159265358979323846264338f;	//�~����.

	//================�֐�====================//.
	virtual void Update() = 0;																				//�X�V�����֐�.
	void	Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos);	//�`�揈���֐�.

	//==========���u�������֐�==============//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }		//�������W.

protected:
	//================�֐�====================//.
	virtual void Init() = 0;		//�����������֐�.
	virtual void Release() = 0;		//��������֐�.

	//================�ϐ�====================//.
	std::vector<CSprite*>		m_pCSprite;			//�X�v���C�g�N���X.
	std::vector<D3DXVECTOR3>	m_vPos;				//���W.
	std::vector<D3DXVECTOR3>	m_vRot;				//�p�x.
	std::vector<float>			m_fScale;			//�傫��.
	std::vector<float>			m_fAlpha;			//���ߒl.
	D3DXVECTOR3					m_vCenterPos;		//�������W.
	CResourceManager*			m_pCResourceManager;//�ǂݍ��݊Ǘ��N���X.
	CDepth_Stencil*				m_pCDepthStencil;	//�f�v�X�X�e���V��.
	
	std::vector<bool>			m_bDispFlag;		//�\���t���O.
	int							m_DispCnt;			//�\���J�E���g.
	int							m_ChangeAddSub;		//���Z���Z�ύX.

private:

};

#endif	//#ifndef CSPRITE_EFFECT_BASE_H.