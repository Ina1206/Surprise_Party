#include "CEffect.h"
#include "..\..\Global.h"

//’è”éŒ¾.
//•`‰æ—p²Ý½ÀÝ½(½Ìß×²Ä)Å‘å”.
const int RENDER_SPRITE_MAX = 2000;
//´Ìª¸ÄŠÇ——p²Ý½ÀÝ½Å‘å”.
const int EFFECT_INSTANCE_MAX = 1000;

//ºÝ½Ä×¸À.
CEffect::CEffect()
	: m_pManager(nullptr)
	, m_pRenderer(nullptr)
#ifdef ENABLE_XAUDIO2
	, m_pSound(nullptr)
	, m_pXA2(nullptr)
	, m_pXA2Master(nullptr)
#endif//#ifdef ENABLE_XAUDIO2
{
}

//ÃÞ½Ä×¸À.
CEffect::~CEffect()
{
}

//‰Šú‰».
HRESULT CEffect::Init()
{


	return S_OK;
}

//\’z.
HRESULT CEffect::Create(
	ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
#ifdef ENABLE_XAUDIO2
	//XAudio2‚Ì‰Šú‰»‚ðs‚¤.
	if (FAILED(
		XAudio2Create(&m_pXA2)))
	{
		_ASSERT_EXPR(false, "XAudio2ì¬Ž¸”s");
		return E_FAIL;
	}
	if (FAILED(
		m_pXA2->CreateMasteringVoice(&m_pXA2Master)))
	{
		_ASSERT_EXPR(false, "MasteringVoiceì¬Ž¸”s");
		return E_FAIL;
	}
#endif/#ifdef ENABLE_XAUDIO2
	
	//•`‰æ—p²Ý½ÀÝ½‚Ì¶¬.
	m_pRenderer
		= ::EffekseerRendererDX11::Renderer::Create(
			pDevice11, pContext11, RENDER_SPRITE_MAX);

	//´Ìª¸ÄŠÇ——p²Ý½ÀÝ½‚Ì¶¬.
	m_pManager
		= ::Effekseer::Manager::Create(EFFECT_INSTANCE_MAX);

	//•`‰æ—p²Ý½ÀÝ½‚©‚ç•`‰æ‹@”\‚ðÝ’è.
	m_pManager->SetSpriteRenderer(m_pRenderer->CreateSpriteRenderer());
	m_pManager->SetRibbonRenderer(m_pRenderer->CreateRibbonRenderer());
	m_pManager->SetRingRenderer(m_pRenderer->CreateRingRenderer());
	m_pManager->SetModelRenderer(m_pRenderer->CreateModelRenderer());

	//•`‰æ—p²Ý½ÀÝ½‚©‚çÃ¸½Á¬‚Ì“Ç‚Ýž‚Ý‹@”\‚ðÝ’è.
	//“ÆŽ©Šg’£‰Â”\AŒ»Ý‚ÍÌ§²Ù‚©‚ç“Ç‚Ýž‚ñ‚Å‚¢‚é.
	m_pManager->SetTextureLoader(m_pRenderer->CreateTextureLoader());
	m_pManager->SetModelLoader(m_pRenderer->CreateModelLoader());

#ifdef ENABLE_XAUDIO2
	//‰¹‚ÌÄ¶—p²Ý½ÀÝ½‚Ì¶¬.
	m_pSound = ::EffekseerSound::Sound::Create(m_pXA2, 16, 16);

	//‰¹‚ÌÄ¶—p²Ý½ÀÝ½‚©‚çÄ¶‹@”\‚ðÝ’è.
	m_pManager->SetSoundPlayer(m_pSound->CreateSoundPlayer());

	//‰¹‚ÌÄ¶—p²Ý½ÀÝ½‚©‚ç»³ÝÄÞÃÞ°À‚Ì“Ç‚Ýž‚Ý‹@”\‚ðÝ’è.
	//“ÆŽ©Šg’£‰Â”\AŒ»Ý‚ÍÌ§²Ù‚©‚ç“Ç‚Ýž‚ñ‚Å‚¢‚é.
	m_pManager->SetSoundLoader(m_pSound->CreateSoundLoader());
#endif//#ifdef ENABLE_XAUDIO2

	return S_OK;
}


//”jŠü.
void CEffect::Destroy()
{
	//´Ìª¸ÄÃÞ°À‚Ì‰ð•ú.
	ReleaseData();

	//æ‚É´Ìª¸ÄŠÇ——p²Ý½ÀÝ½‚ð”jŠü.
	m_pManager->Destroy();

#ifdef ENABLE_XAUDIO2
	//ŽŸ‚É‰¹‚ÌÄ¶—p²Ý½ÀÝ½‚ð”jŠü.
	m_pSound->Destroy();
#endif//#ifdef ENABLE_XAUDIO2

	//ŽŸ‚É•`‰æ—p²Ý½ÀÝ½‚ð”jŠü.
	m_pRenderer->Destroy();

#ifdef ENABLE_XAUDIO2
	//XAudio2‚Ì‰ð•ú.
	if (m_pXA2Master != nullptr) {
		m_pXA2Master->DestroyVoice();
		m_pXA2Master = nullptr;
	}
	SAFE_RELEASE(m_pXA2);
#endif//#ifdef ENABLE_XAUDIO2
}

//ÃÞ°À“Ç‚Ýž‚Ý.
HRESULT CEffect::LoadData(const EFK_CHAR* fileName)
{
	
	//´Ìª¸Ä‚Ì“Ç‚Ýž‚Ý.
	m_pEffect = Effekseer::Effect::Create(
		m_pManager, fileName);
	if (m_pEffect == nullptr) {
		_ASSERT_EXPR(false, L"´Ìª¸Ä“Ç‚Ýž‚ÝŽ¸”s");
		return E_FAIL;
	}

	return S_OK;
}

//ÃÞ°À‰ð•ú.
void CEffect::ReleaseData()
{
	//´Ìª¸Ä‚Ì‰ð•ú.
	SAFE_RELEASE(m_pEffect);
}

//•`‰æŠÖ”.
void CEffect::Render(D3DXMATRIX & mView, D3DXMATRIX & mProj)
{
	//ËÞ­°s—ñ‚ðÝ’è.
	SetViewMatrix(mView);

	//ÌßÛ¼Þª¸¼®Ýs—ñ‚ðÝ’è.
	SetProjectionMatrix(mProj);

	//´Ìª¸Ä‚ÌXVˆ—.
	m_pManager->Update();

	//--------------------------------------
	//	EffekseerÚÝÀÞØÝ¸ÞŠÖŒW.
	//--------------------------------------
	//´Ìª¸Ä‚Ì•`‰æŠJŽnˆ—.
	m_pRenderer->BeginRendering();

	//´Ìª¸Ä‚Ì•`‰æ.
	m_pManager->Draw();

	//´Ìª¸Ä‚Ì•`‰æI—¹ˆ—.
	m_pRenderer->EndRendering();
}


//DirectX D3DXVECTOR3 -> Effekseer Vector3 ‚É•ÏŠ·‚·‚é.
Effekseer::Vector3D	CEffect::ConvertToVec3Efk(
	const D3DXVECTOR3& SrcVec3Dx)
{
	return Effekseer::Vector3D(
		SrcVec3Dx.x, SrcVec3Dx.y, SrcVec3Dx.z);
}

//Effekseer Vector3 -> DirectX D3DXVECTOR3 ‚É•ÏŠ·‚·‚é.
D3DXVECTOR3 CEffect::ConvertToVec3Dx(
	const Effekseer::Vector3D& SrcVec3Efk)
{
	return D3DXVECTOR3(SrcVec3Efk.X, SrcVec3Efk.Y, SrcVec3Efk.Z);
}

//DirectX D3DXMATRIX -> Effekseer Matrix44 ‚É•ÏŠ·‚·‚é.
Effekseer::Matrix44 CEffect::ConvertToMatEfk(
	const D3DXMATRIX & SrcMatDx)
{
	Effekseer::Matrix44 DestMatEfk;

	//DestMatEfk.Values[0][0] = SrcMatDx._11;
	//DestMatEfk.Values[0][1] = SrcMatDx._12;
	//DestMatEfk.Values[0][2] = SrcMatDx._13;
	//DestMatEfk.Values[0][3] = SrcMatDx._14;

	//DestMatEfk.Values[1][0] = SrcMatDx._21;
	//DestMatEfk.Values[1][1] = SrcMatDx._22;
	//DestMatEfk.Values[1][2] = SrcMatDx._23;
	//DestMatEfk.Values[1][3] = SrcMatDx._24;

	//DestMatEfk.Values[2][0] = SrcMatDx._31;
	//DestMatEfk.Values[2][1] = SrcMatDx._32;
	//DestMatEfk.Values[2][2] = SrcMatDx._33;
	//DestMatEfk.Values[2][3] = SrcMatDx._34;

	//DestMatEfk.Values[3][0] = SrcMatDx._41;
	//DestMatEfk.Values[3][1] = SrcMatDx._42;
	//DestMatEfk.Values[3][2] = SrcMatDx._43;
	//DestMatEfk.Values[3][3] = SrcMatDx._44;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			DestMatEfk.Values[i][j] = SrcMatDx.m[i][j];
		}
	}

	return DestMatEfk;
}

//Effekseer Matrix44 -> DirectX D3DXMATRIX ‚É•ÏŠ·‚·‚é.
D3DXMATRIX CEffect::ConvertToMatDx(
	const Effekseer::Matrix44& SrcMatEfk)
{
	D3DXMATRIX DestMatDx;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			DestMatDx.m[i][j] = SrcMatEfk.Values[i][j];
		}
	}

	return DestMatDx;
}
//ËÞ­°s—ñ‚ðÝ’è.
void CEffect::SetViewMatrix(D3DXMATRIX& mView)
{
	Effekseer::Matrix44 mViewEfk = ConvertToMatEfk(mView);

	//¶Ò×s—ñ‚ðÝ’è.
	m_pRenderer->SetCameraMatrix(mViewEfk);
}

//ÌßÛ¼Þª¸¼®Ýs—ñ‚ðÝ’è.
void CEffect::SetProjectionMatrix(D3DXMATRIX& mProj)
{
	Effekseer::Matrix44 mProjEfk = ConvertToMatEfk(mProj);

	//ÌßÛ¼Þª¸¼®Ýs—ñ‚ðÝ’è.
	m_pRenderer->SetProjectionMatrix(mProjEfk);
}
