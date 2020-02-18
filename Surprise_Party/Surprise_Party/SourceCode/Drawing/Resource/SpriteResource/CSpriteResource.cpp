#include "CSpriteResource.h"

template <class Sprite, class SpriteType>
CSprite_Resource<Sprite, SpriteType>::CSprite_Resource()
	: m_ppSprite	(nullptr)
	, m_pSpriteState(nullptr)
{

}

template<class Sprite, class SpriteType>
CSprite_Resource<Sprite, SpriteType>::~CSprite_Resource()
{
	//��������֐�.
	for (int sprite = m_ResourceMax - 1; sprite >= 0; sprite--) {
		Release(static_cast<SpriteType>(sprite));
	}
	//�z����.
	SAFE_DELETE_ARRAY(m_ppSprite);
}

//==============================================.
//		�����������֐�.
//==============================================.
template<class Sprite, class SpriteType>
HRESULT CSprite_Resource<Sprite, SpriteType>::Init(int max)
{
	//�ő吔�ݒ�.
	m_ResourceMax = max;


	m_ppSprite		= new Sprite*[m_ResourceMax]();

	//����������.
	for (int sprite = 0; sprite < m_ResourceMax; sprite++) {
		m_ppSprite[sprite] = nullptr;
	}

	return S_OK;
}

//============================================.
//		�ǂݍ��ݏ����֐�.
//============================================.
template<class Sprite, class SpriteType>
HRESULT CSprite_Resource<Sprite, SpriteType>::Load(std::vector<std::string> vecFileName)
{
	//�t�@�C���p�X.
	const char** fileName = nullptr;
	fileName = new const char*[m_ResourceMax]();

	for (int sprite = 0; sprite < m_ResourceMax; sprite++) {
		fileName[sprite] = vecFileName[sprite].c_str();
		//�쐬�����֐�.
		Create(static_cast<SpriteType>(sprite), fileName[sprite]);
	}

	SAFE_DELETE_ARRAY(fileName);

	return S_OK;
}

//===================================================.
//		����Ăяo�������֐�.
//===================================================.
template<class Sprite, class SpriteType>
HRESULT CSprite_Resource<Sprite, SpriteType>::ReleaseCalling()
{
	for (int sprite = m_ResourceMax - 1; sprite >= 0; sprite--) {
		//��������֐�.
		Release(static_cast<SpriteType>(sprite));
	}
	return S_OK;
}

//====================================================.
//	�X�v���C�g�n�̃N���X�̃A�h���X���擾�����֐�.
//====================================================.
template<class Sprite, class SpriteType>
Sprite* CSprite_Resource<Sprite, SpriteType>::GetSprite(SpriteType enSpriteType) 
{
	//�͈͊m�F�����֐�.
	if (FAILED(Check_SpriteRange(enSpriteType))) {
		return nullptr;
	}

	if (m_ppSprite[static_cast<int>(enSpriteType)] == nullptr) {
		return nullptr;
	}

	return m_ppSprite[static_cast<int>(enSpriteType)];
}

//==================================================.
//		�쐬�����֐�.
//==================================================.
template<class Sprite, class SpriteType>
HRESULT CSprite_Resource<Sprite, SpriteType>::Create(SpriteType enSpriteType, const char* pfileName)
{
	//�͈͊m�F�����֐�.
	if (FAILED(Check_SpriteRange(enSpriteType))) {
		return E_FAIL;
	}

	if (m_ppSprite[static_cast<int>(enSpriteType)] != nullptr) {
		return E_FAIL;
	}

	if (m_pSpriteState == nullptr) {
		_ASSERT_EXPR(m_pSpriteState != nullptr, "m_pSpriteState == nullptr");
		return E_FAIL;
	}
	SPRITE_STATE ss = m_pSpriteState[static_cast<int>(enSpriteType)];

	_ASSERT_EXPR(ss.Base.w != 0.0f, L"ss.Base.w == 0.0f");
	m_ppSprite[static_cast<int>(enSpriteType)] = new Sprite();
	//�����������֐�.
	if (FAILED(m_ppSprite[static_cast<int>(enSpriteType)]->Init(m_pDevice11, m_pContext11, pfileName, &ss))) {
		return E_FAIL;
	}

	return S_OK;
}

//===================================================.
//		��������֐�.
//===================================================.
template<class Sprite, class SpriteType>
HRESULT CSprite_Resource<Sprite, SpriteType>::Release(SpriteType enSpriteType)
{
	//�͈͊m�F�����֐�.
	if (FAILED(Check_SpriteRange(enSpriteType))) {
		return E_FAIL;
	}

	//nullptr��������I��.
	if (m_ppSprite[static_cast<int>(enSpriteType)] == nullptr) {
		return S_OK;
	}

	//��������֐�.
	m_ppSprite[static_cast<int>(enSpriteType)]->Release();
	SAFE_DELETE(m_ppSprite[static_cast<int>(enSpriteType)]);

	return S_OK;
}

//======================================.
//	�X�v���C�g�͈̔͂��m�F�����֐�.
//======================================.
template<class Sprite, class SpriteType>
HRESULT CSprite_Resource<Sprite, SpriteType>::Check_SpriteRange(SpriteType enSpriteType)
{
	if (static_cast<int>(enSpriteType) < 0 || m_ResourceMax <= static_cast<int>(enSpriteType)) {
		return E_FAIL;
	}

	return S_OK;
}

//================�N���X�̎��̉�=================//.
template class CSprite_Resource<CSprite, enSprite>;
template class CSprite_Resource<CSpriteUI, enSpriteUI>;