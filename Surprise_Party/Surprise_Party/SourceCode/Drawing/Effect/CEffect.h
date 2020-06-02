#ifndef CEFFECT_H
#define CEFFECT_H
//警告についてのｺｰﾄﾞ分析を無効にする.4005:再定義.
#pragma warning(disable:4005)
//XAudio2関係のｺｰﾄﾞを有効にする.
//#define ENABLE_XAUDIO2

//-------------------------------------------------
//	先に読み込む、ﾍｯﾀﾞ、ﾗｲﾌﾞﾗﾘ.
//-------------------------------------------------
#include <stdio.h>

#include <d3d11.h>
#ifdef ENABLE_XAUDIO2
#include <XAudio2.h>
#endif//#ifdef ENABLE_XAUDIO2
#pragma comment(lib,"d3d11.lib")

//-------------------------------------------------
//	ここからEffekseer関係 ﾍｯﾀﾞ、ﾗｲﾌﾞﾗﾘ読み込み.
//-------------------------------------------------
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#ifdef ENABLE_XAUDIO2
#include <EffekseerSoundXAudio2.h>
#endif//#ifdef ENABLE_XAUDIO2

#if _DEBUG
	#pragma comment(lib,"VS2017\\_Debug\\Effekseer.lib")
	#pragma comment(lib,"VS2017\\_Debug\\EffekseerRendererDX11.lib")
#ifdef ENABLE_XAUDIO2
	#pragma comment(lib,"VS2017\\Debug\\EffekseerSoundXAudio2.lib")
#endif//#ifdef ENABLE_XAUDIO2
#else//#if _DEBUG
	#pragma comment(lib,"VS2017\\_Release\\Effekseer.lib")
	#pragma comment(lib,"VS2017\\_Release\\EffekseerRendererDX11.lib")
#ifdef ENABLE_XAUDIO2
	#pragma comment(lib,"VS2017\\Release\\EffekseerSoundXAudio2.lib")
#endif//#ifdef ENABLE_XAUDIO2
#endif//#if _DEBUG

//「D3DX～」使用で必須.
//注意:Effekseer関係より後で読み込むこと.
#include <D3DX10.h>
#pragma comment(lib, "d3dx10.lib")

/************************************************************
*	ﾌﾘｰｿﾌﾄ Effeksserのﾃﾞｰﾀを使う為のｸﾗｽ.
**/
class CEffect
{
public:
	CEffect();
	~CEffect();	//ﾃﾞｽﾄﾗｸﾀ.

	//ｲﾝｽﾀﾝｽ取得(唯一のｱｸｾｽ経路).
	//static CEffect* GetInstance()
	//{
	//	//唯一のｲﾝｽﾀﾝｽを作成する.
	//	//(staticで作成されたので2回目は無視される).
	//	static CEffect s_Instance;
	//	return &s_Instance;
	//}

	//初期化.
	HRESULT Init();
	//構築.
	HRESULT Create(
		ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);
	//破棄.
	void Destroy();
	//ﾃﾞｰﾀ読み込み.
	HRESULT LoadData(const EFK_CHAR* fileName);
	//ﾃﾞｰﾀ解放.
	void ReleaseData();
	//描画関数.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj);

	//再生関数.
	Effekseer::Handle Play(const D3DXVECTOR3& vPos) {
		//今回、ｴﾌｪｸﾄは固定.
		return m_pManager->Play(m_pEffect, vPos.x, vPos.y, vPos.z);
	}
	//停止関数.
	void Stop(Effekseer::Handle handle) {
		m_pManager->StopEffect(handle);
	}
	//全て停止関数.
	void StopAll() {
		m_pManager->StopAllEffects();
	}
	//一時停止.
	void Pause(Effekseer::Handle handle, bool bFlag) {
		m_pManager->SetPaused(handle, bFlag);
	}

	//位置を指定する.
	void SetLocation(Effekseer::Handle handle, const D3DXVECTOR3& vPos){
		m_pManager->SetLocation(handle, ConvertToVec3Efk(vPos));
	}
	//ｻｲｽﾞを指定する.
	void SetScale(Effekseer::Handle handle, const D3DXVECTOR3& vScale){
		m_pManager->SetScale(handle, vScale.x, vScale.y, vScale.z);
	}
	//回転を指定する.
	void SetRotation(Effekseer::Handle handle, const D3DXVECTOR3& vRot) {
		m_pManager->SetRotation(handle, vRot.x, vRot.y, vRot.z);
	}
	//回転を指定する(軸とﾗｼﾞｱﾝ).
	void SetRotation(Effekseer::Handle handle,
		const D3DXVECTOR3& vAxis, float fRadian)
	{
		m_pManager->SetRotation(handle, ConvertToVec3Efk(vAxis), fRadian);
	}
	//再生速度を設定する.
	void SetSpeed(Effekseer::Handle handle, float fSpeed) {
		m_pManager->SetSpeed(handle, fSpeed);
	}

	bool GetEffectShow(Effekseer::Handle handle)
	{
		return m_pManager->GetShown(handle);
	}

private:
	//生成やｺﾋﾟｰを禁止する.
	//CEffect();	//ｺﾝｽﾄﾗｸﾀ.
	CEffect(const CEffect& rhs) {};
	CEffect& operator = (const CEffect& rhs) { return *this; };

	//--------------------------------------
	//	DirectX <--> Effekseer 変換関数.
	//--------------------------------------
	//vector変換.
	Effekseer::Vector3D	ConvertToVec3Efk(const D3DXVECTOR3& SrcVec3Dx);
	D3DXVECTOR3 ConvertToVec3Dx(const Effekseer::Vector3D& SrcVec3Efk);
	//matrix変換.
	Effekseer::Matrix44 ConvertToMatEfk(const D3DXMATRIX& SrcMatDx);
	D3DXMATRIX ConvertToMatDx(const Effekseer::Matrix44& SrcMatEfk);

	//ﾋﾞｭｰ行列を設定.
	void SetViewMatrix(D3DXMATRIX& mView);
	//ﾌﾟﾛｼﾞｪｸｼｮﾝ行列を設定.
	void SetProjectionMatrix(D3DXMATRIX& mProj);

	//ｴﾌｪｸﾄを動作させるために必要.
	::Effekseer::Manager*			m_pManager;
	::EffekseerRenderer::Renderer*	m_pRenderer;
#ifdef ENABLE_XAUDIO2
	//ｴﾌｪｸﾄﾃﾞｰﾀに含まれる音の再生に必要.
	::EffekseerSound::Sound*		m_pSound;
	IXAudio2*						m_pXA2;
	IXAudio2MasteringVoice*			m_pXA2Master;
#endif//#ifdef ENABLE_XAUDIO2
	
	//ｴﾌｪｸﾄの種類ごとに用意.
	::Effekseer::Effect*			m_pEffect;
	//ｴﾌｪｸﾄごとに必要.
	//※同じｴﾌｪｸﾄを同時に３つ出すなら３つ必要.
	::Effekseer::Handle				m_Handle;
};


#endif//#ifndef CEFFECT_H