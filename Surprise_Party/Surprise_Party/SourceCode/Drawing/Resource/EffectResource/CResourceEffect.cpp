#include "CResourceEffect.h"

/*****************************************
*		�G�t�F�N�g�ǂݍ��݃N���X.
*****************/
CResourceEffect::CResourceEffect()
	: m_hWnd		(nullptr)
	, m_pDevice11	(nullptr)
	, m_pContext11	(nullptr)
	, m_ppCEffect	(nullptr)
{

}

CResourceEffect::~CResourceEffect()
{
	if (m_ppCEffect != nullptr)
	{
		for (int i = static_cast<int>(CResourceEffect::enEffect::Max) - 1; i >= 0; i--)
		{
			if (m_ppCEffect[i] != nullptr) {
				ReleaseEffect(static_cast<CResourceEffect::enEffect>(i));
			}
		}

		delete[] m_ppCEffect;
		m_ppCEffect = nullptr;
	}
}

//=============================================.
//		�����������֐�.
//=============================================.
HRESULT CResourceEffect::Init(HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_hWnd = hWnd;
	m_pDevice11 = pDevice11;
	m_pContext11 = pContext11;

	//��è��ү�����߲�����߲���̗̈�m��.
	//���߲���^�̔z��̈�̊m��.
	m_ppCEffect = new CEffect*[static_cast<int>(CResourceEffect::enEffect::Max)];
	for (int i = 0; i < static_cast<int>(CResourceEffect::enEffect::Max); i++)
	{
		//������:nullptr�Ŗ��߂�.
		m_ppCEffect[i] = nullptr;
	}
	return S_OK;

}

//=============================================.
//		Effect�N���X�̃A�h���X�擾�����֐�.
//=============================================.
CEffect* CResourceEffect::GetEffect(CResourceEffect::enEffect enEffectType)
{
	//�͈͊O�Ȃ�I��.
	if (enEffectType < CResourceEffect::enEffect::Start || CResourceEffect::enEffect::Max <= enEffectType) {
		return nullptr;
	}
	const int EffectNo = static_cast<int>(enEffectType);
	//���ق����݂��Ȃ��̂ŏI��.
	if (m_ppCEffect[EffectNo] == nullptr) {
		return nullptr;
	}

	return m_ppCEffect[EffectNo];

}

//=============================================.
//		�ǂݍ��ݏ����֐�.
//=============================================.
HRESULT CResourceEffect::LoadEffect()
{

	const EFK_CHAR* pathName[] = {
		(const EFK_CHAR*)L"Data\\Effect\\GimmickEffect\\DispGhost_Area.efk",
		(const EFK_CHAR*)L"Data\\Effect\\GimmickEffect\\ObjectMove_Area.efk",
		(const EFK_CHAR*)L"Data\\Effect\\GimmickEffect\\PlaySound_Area.efk",
	};

	int max = sizeof(pathName) / sizeof(pathName[0]);

	for (int i = 0; i < max; i++)
	{
		CreateEffect(static_cast<CResourceEffect::enEffect>(i), pathName[i]);
	}

	return S_OK;
}


//=============================================.
//		�쐬�����֐�.
//=============================================.
HRESULT CResourceEffect::CreateEffect(CResourceEffect::enEffect enEffectType, const EFK_CHAR* pathName)
{
	//�͈͊O�Ȃ�I��.
	if (enEffectType < CResourceEffect::enEffect::Start || CResourceEffect::enEffect::Max <= enEffectType) {
		return E_FAIL;
	}

	//���ق����ɑ��݂��Ă���I��.
	if (m_ppCEffect[static_cast<int>(enEffectType)] != nullptr) {
		return E_FAIL;
	}

	//���ٓǂݍ���.
	m_ppCEffect[static_cast<int>(enEffectType)] = new CEffect();
	if (FAILED(
		m_ppCEffect[static_cast<int>(enEffectType)]->Init()))
	{
		return E_FAIL;
	}
	if (FAILED(m_ppCEffect[static_cast<int>(enEffectType)]->Create(m_pDevice11, m_pContext11)))
	{
		return E_FAIL;
	}
	if (FAILED(m_ppCEffect[static_cast<int>(enEffectType)]->LoadData(pathName)))
	{
		return E_FAIL;
	}

	return S_OK;


}

//=============================================.
//		��������֐�.
//=============================================.
HRESULT CResourceEffect::ReleaseEffect(CResourceEffect::enEffect enEffectType)
{
	//�͈͊O�Ȃ�I��.
	if (enEffectType < CResourceEffect::enEffect::Start || CResourceEffect::enEffect::Max <= enEffectType) {
		return E_FAIL;
	}
	const int EffectNo = static_cast<int>(enEffectType);

	//���ق����݂��ĂȂ���ΏI��.
	if (m_ppCEffect[EffectNo] == nullptr) {
		return S_OK;
	}

	//�������.
	m_ppCEffect[EffectNo]->Destroy();
	delete m_ppCEffect[EffectNo];//�폜.
	m_ppCEffect[EffectNo] = nullptr;

	return S_OK;

}

//=============================================.
//		��������֐�.
//=============================================.
HRESULT CResourceEffect::ReleaseEffect()
{
	for (int effect = static_cast<int>(CResourceEffect::enEffect::Max) - 1; effect >= 0; effect--) {
		ReleaseEffect(static_cast<CResourceEffect::enEffect>(effect));
	}
	return S_OK;
}
