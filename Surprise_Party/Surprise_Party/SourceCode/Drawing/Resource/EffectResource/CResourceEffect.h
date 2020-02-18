#ifndef CRESOURCE_EFFECT_H
#define	CRESOURCE_EFFECT_H

#include "..\..\Effect\CEffect.h"

class CResourceEffect
{
public:
	CResourceEffect();
	~CResourceEffect();

	//===============�񋓑�===================//.
	enum class enEffect {
		DispGhost_Area_Effect,	//���������o�Ă���͈̓G�t�F�N�g.
		ObjectMove_Area_Effect,	//�I�u�W�F�N�g�������͈̓G�t�F�N�g.
		PlaySound_Area_Effect,	//���������͈̓G�t�F�N�g.

		Max,
		Start = DispGhost_Area_Effect,
	};

	//�����������֐�.
	HRESULT Init(HWND hWnd,
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11);

	//Effect�N���X�̃A�h���X�擾�����֐�.
	CEffect* GetEffect(enEffect enMesh);
	//�ǂݍ��ݏ����֐�.
	HRESULT LoadEffect();

private:

	//�쐬�����֐�.
	HRESULT CreateEffect(enEffect enEffectType, const EFK_CHAR* Efk_Char);
	//��������֐�.
	HRESULT ReleaseEffect(enEffect enEffectType);
	//��������֐�.
	HRESULT ReleaseEffect();

	//================�ϐ�====================//.
	HWND					m_hWnd;			//�E�B���h�E�n���h��.
	ID3D11Device*			m_pDevice11;	//�f�o�C�X.
	ID3D11DeviceContext*	m_pContext11;	//�f�o�C�X�R���e�L�X�g.

	CEffect**				m_ppCEffect;
};

#endif	//#ifndef CRESOURCE_EFFECT_H.