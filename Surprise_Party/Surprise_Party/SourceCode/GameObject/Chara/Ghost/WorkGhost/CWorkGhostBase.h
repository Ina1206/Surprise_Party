#ifndef CWORK_GHOST_BASE_H
#define CWORK_GHOST_BASE_H

#include "..\CGhostBase.h"
#include "..\..\..\..\UI\GameWorldUI\Act_Selection\CAct_Selection.h"
#include "..\..\..\..\UI\MapUI\CharaUI\Icon\GhostIcon\CGhostIcon.h"
#include "..\..\..\..\UI\GameWorldUI\GhostStrengthIcon\CGhostStrengthIcon.h"
#include "..\..\SpriteEffect\SurpriseEffect\CSurpriseEffect.h"

/*************************************
*		�������������N���X.
******/
class CWorkGhostBase
	: public CGhostBase
{
public:
	CWorkGhostBase();
	virtual ~CWorkGhostBase();

	//=============================�萔======================================//.
	const float			WAIT_ANIM_START_POS = 0.95f;	//�ҋ@���̃A�j���[�V�������W.

	//=============�񋓑�================//.
	//�������̎��.
	enum class enGhostType {
		DispGhost,			//����邨����.
		SwitchGhost,		//�X�C�b�`����������.

		Max,				//�ő�l.
		Start = DispGhost,	//�J�n�l.
	};


protected:
	//==============================�֐�====================================//.
	void InitAnimation();							//�A�j���[�V���������������֐�.
	void RenderDispGhost(const D3DXVECTOR3& vPos);	//����邨�����`�揈���֐�.
	void InitStaticMeshGhost();						//�ÓI�I�u�W�F�N�g�����������������֐�.
	void RenderSwitchGhost(const D3DXVECTOR3& vPos);//�X�C�b�`�������`�揈���֐�.

	//==============================�ϐ�====================================//.
	CDX9SkinMesh*				m_pCSkinMesh;		//�X�L�����b�V���N���X.
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;		//�A�j���[�V�����R���g���[��.
	CDX9Mesh*					m_pCMesh;			//���b�V��.

private:
};

#endif	//#ifndef CWORK_GHOST_BASE_H.