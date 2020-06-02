#ifndef CEFFECT_H
#define CEFFECT_H
//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)
//XAudio2�֌W�̺��ނ�L���ɂ���.
//#define ENABLE_XAUDIO2

//-------------------------------------------------
//	��ɓǂݍ��ށAͯ�ށAײ����.
//-------------------------------------------------
#include <stdio.h>

#include <d3d11.h>
#ifdef ENABLE_XAUDIO2
#include <XAudio2.h>
#endif//#ifdef ENABLE_XAUDIO2
#pragma comment(lib,"d3d11.lib")

//-------------------------------------------------
//	��������Effekseer�֌W ͯ�ށAײ���ؓǂݍ���.
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

//�uD3DX�`�v�g�p�ŕK�{.
//����:Effekseer�֌W����œǂݍ��ނ���.
#include <D3DX10.h>
#pragma comment(lib, "d3dx10.lib")

/************************************************************
*	�ذ��� Effeksser���ް����g���̸ׂ׽.
**/
class CEffect
{
public:
	CEffect();
	~CEffect();	//�޽�׸�.

	//�ݽ�ݽ�擾(�B��̱����o�H).
	//static CEffect* GetInstance()
	//{
	//	//�B��̲ݽ�ݽ���쐬����.
	//	//(static�ō쐬���ꂽ�̂�2��ڂ͖��������).
	//	static CEffect s_Instance;
	//	return &s_Instance;
	//}

	//������.
	HRESULT Init();
	//�\�z.
	HRESULT Create(
		ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);
	//�j��.
	void Destroy();
	//�ް��ǂݍ���.
	HRESULT LoadData(const EFK_CHAR* fileName);
	//�ް����.
	void ReleaseData();
	//�`��֐�.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj);

	//�Đ��֐�.
	Effekseer::Handle Play(const D3DXVECTOR3& vPos) {
		//����A�̪�Ă͌Œ�.
		return m_pManager->Play(m_pEffect, vPos.x, vPos.y, vPos.z);
	}
	//��~�֐�.
	void Stop(Effekseer::Handle handle) {
		m_pManager->StopEffect(handle);
	}
	//�S�Ē�~�֐�.
	void StopAll() {
		m_pManager->StopAllEffects();
	}
	//�ꎞ��~.
	void Pause(Effekseer::Handle handle, bool bFlag) {
		m_pManager->SetPaused(handle, bFlag);
	}

	//�ʒu���w�肷��.
	void SetLocation(Effekseer::Handle handle, const D3DXVECTOR3& vPos){
		m_pManager->SetLocation(handle, ConvertToVec3Efk(vPos));
	}
	//���ނ��w�肷��.
	void SetScale(Effekseer::Handle handle, const D3DXVECTOR3& vScale){
		m_pManager->SetScale(handle, vScale.x, vScale.y, vScale.z);
	}
	//��]���w�肷��.
	void SetRotation(Effekseer::Handle handle, const D3DXVECTOR3& vRot) {
		m_pManager->SetRotation(handle, vRot.x, vRot.y, vRot.z);
	}
	//��]���w�肷��(����׼ޱ�).
	void SetRotation(Effekseer::Handle handle,
		const D3DXVECTOR3& vAxis, float fRadian)
	{
		m_pManager->SetRotation(handle, ConvertToVec3Efk(vAxis), fRadian);
	}
	//�Đ����x��ݒ肷��.
	void SetSpeed(Effekseer::Handle handle, float fSpeed) {
		m_pManager->SetSpeed(handle, fSpeed);
	}

	bool GetEffectShow(Effekseer::Handle handle)
	{
		return m_pManager->GetShown(handle);
	}

private:
	//�������߰���֎~����.
	//CEffect();	//�ݽ�׸�.
	CEffect(const CEffect& rhs) {};
	CEffect& operator = (const CEffect& rhs) { return *this; };

	//--------------------------------------
	//	DirectX <--> Effekseer �ϊ��֐�.
	//--------------------------------------
	//vector�ϊ�.
	Effekseer::Vector3D	ConvertToVec3Efk(const D3DXVECTOR3& SrcVec3Dx);
	D3DXVECTOR3 ConvertToVec3Dx(const Effekseer::Vector3D& SrcVec3Efk);
	//matrix�ϊ�.
	Effekseer::Matrix44 ConvertToMatEfk(const D3DXMATRIX& SrcMatDx);
	D3DXMATRIX ConvertToMatDx(const Effekseer::Matrix44& SrcMatEfk);

	//�ޭ��s���ݒ�.
	void SetViewMatrix(D3DXMATRIX& mView);
	//��ۼު���ݍs���ݒ�.
	void SetProjectionMatrix(D3DXMATRIX& mProj);

	//�̪�Ă𓮍삳���邽�߂ɕK�v.
	::Effekseer::Manager*			m_pManager;
	::EffekseerRenderer::Renderer*	m_pRenderer;
#ifdef ENABLE_XAUDIO2
	//�̪���ް��Ɋ܂܂�鉹�̍Đ��ɕK�v.
	::EffekseerSound::Sound*		m_pSound;
	IXAudio2*						m_pXA2;
	IXAudio2MasteringVoice*			m_pXA2Master;
#endif//#ifdef ENABLE_XAUDIO2
	
	//�̪�Ă̎�ނ��Ƃɗp��.
	::Effekseer::Effect*			m_pEffect;
	//�̪�Ă��ƂɕK�v.
	//�������̪�Ă𓯎��ɂR�o���Ȃ�R�K�v.
	::Effekseer::Handle				m_Handle;
};


#endif//#ifndef CEFFECT_H