#ifndef CGAME_OBJECT_H
#define CGAME_OBJECT_H

#include "..\Global.h"
#include "..\Drawing\Resource\CResourceManager.h"

/************************************
*	�Q�[���I�u�W�F�N�g�N���X.
*******/
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

	//================�萔===================//.
	const D3DXVECTOR3	STANDERD_POS = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);

	//===============�񋓑�==================//.
	//�������I�u�W�F�N�g�̎��.
	enum class enSurpriseObjectType {
		Disp,		//�����.
		Switch,		//�X�C�b�`.
	};

	//================�֐�===================//.
	void RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& vLightPos);	//�`�揉���ݒ菈���֐�.
	virtual void UpDate() = 0;		//�X�V�����֐�.
	virtual void Render() = 0;		//�`�揈���֐�.

	//===========���u�������֐�============//.
	void SetPos(const D3DXVECTOR3& vPos) { m_vPos = vPos; }
	void SetDispFlag(const bool& bFlag) { m_bDisp = bFlag; }
	void SetCameraPos(const D3DXVECTOR3& vPos) { m_vCameraPos = vPos; }

	//===========���u�������֐�============//.
	bool		GetDispFlag() { return m_bDisp; }		//�\���t���O�擾.
	D3DXVECTOR3 GetPos(){ return m_vPos; }				//���W�擾.
protected:
	//================�֐�===================//.
	virtual void Init() = 0;	//�����������֐�.
	virtual void Release() = 0;	//��������֐�.

	//================�ϐ�===================//.
	D3DXMATRIX	m_mView;		//�r���[�s��.
	D3DXMATRIX	m_mProj;		//�v���W�F�N�V�����s��.
	LIGHT		m_stLight;		//���C�g���.
	D3DXVECTOR3 m_vCameraPos;	//�J�������W.
	
	D3DXVECTOR3	m_vPos;			//���W.
	D3DXVECTOR3 m_vRot;			//�p�x.
	float		m_fScale;		//�傫��.
	bool		m_bDisp;		//�\���t���O.

	CResourceManager*	m_pCResourceManager;//�ǂݍ��݊Ǘ��N���X.
private:

};

#endif	//#ifndef CGAME_OBJECT_H.