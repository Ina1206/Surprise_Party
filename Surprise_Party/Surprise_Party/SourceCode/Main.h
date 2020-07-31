#ifndef MAIN_H
#define MAIN_H
//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )
#include <Windows.h>
#include <stdio.h>

#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>
#include <D3D10.h>
#include <d3dx9.h>

#include "MyMacro.h"
#include "Global.h"

#include <memory>
#include "Scene/SceneManager/CSceneManager.h"
#include "Scene/Load/CLoad.h"

//���C�u�����ǂݍ���.
#pragma comment( lib, "winmm.lib")
#pragma comment( lib, "d3dx11.lib")
#pragma comment( lib, "d3d11.lib")
#pragma comment( lib, "d3dx10.lib")	
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//=================================================.
//	�萔.
//=================================================.
const char WND_TITLE[] = "SurpriseParty";
const char APP_NAME[] = "SurpriseParty";

/********************************************
*	���C���N���X.
**/
class CMain
{
public:

	CMain();	//�R���X�g���N�^.
	~CMain();	//�f�X�g���N�^.

	//�E�B���h�E�������֐�.
	HRESULT InitWindow(
		HINSTANCE hInstance,
		INT x, INT y, INT width, INT height,
		const char* WindowName);

	//�E�B���h�E�֐�(���b�Z�[�W���̏���).
	LRESULT MsgProc(
		HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam);

	//���b�Z�[�W���[�v.
	void Loop();

	//�ǂݍ��ݏ����֐�.
	void Load();
	//�X�V�����֐�.
	void UpDate();
	//�����_�����O(�`��).
	void Render();


//------------------------------.
//	��������RD�֌W.

	//DirectX������.
	HRESULT InitD3D();
	//Direct3D�I������.
	void DestroyD3D();

	//���b�V���̓ǂݍ��݊֐�.
	HRESULT LoadMesh();

	//�o�b�N�o�b�t�@�N���A�֐�.
	void ClearBackBuffer();
	//�v���W�F�N�V�����֐�.
	void Proj();


	//=============���u�������֐�===========//.
	void SethWnd(HWND hWnd) {
		m_hWnd = hWnd;
	}
private:
	HWND							m_hWnd;					//�E�B���h�E�n���h��.
	ID3D11Device*					m_pDevice11;			//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*			m_pContext11;			//�f�o�C�X�R���e�L�X�g.
	IDXGISwapChain*					m_pSwapChain;			//�X���b�v�`�F�[��.
	ID3D11RenderTargetView*			m_pBackBuffer_TexRTV;	//�����_�[�^�[�Q�b�g�r���[.
	ID3D11Texture2D*				m_pBackBuffer_DSTex;	//�f�v�X�X�e���V���p�e�N�X�`��.
	ID3D11DepthStencilView*			m_pBackBuffer_DSTexDSV;	//�f�v�X�X�e���V���r���[.
	LPDIRECT3D9						m_pD3d9;				//Dx9�I�u�W�F�N�g.
	LPDIRECT3DDEVICE9				m_pDevice9;				//Dx9�f�o�C�X.

	D3DXMATRIX						m_mProj;				//�v���W�F�N�V�����s��.

	std::unique_ptr<CSceneManager>	m_pCSceneManager;		//�V�[���Ǘ��N���X.
	std::unique_ptr<CLoad>			m_pCLoad;				//�ǂݍ��݃N���X.
	
};

#endif//#ifndef MAIN_H
