#ifndef CSCENE_MANAGER_H
#define CSCENE_MANAGER_H

#include "..\Title\CTitle.h"
#include "..\GameMain\CGameMain.h"
#include "..\Ending\CEnding.h"

#include "..\..\Drawing/Resource/CResourceManager.h"
#include "..\GameMain\CGameMain.h"

#include "..\..\UI\Fade\SceneFade\CSceneFade.h"

/*****************************************
*		�V�[���Ǘ��N���X.
*********/
class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

	//==================�񋓑�=====================//.
	//�Q�[���̃V�[�����.
	enum class enSceneType {
		Title = 0,		//�^�C�g��.
		GameMain,		//�Q�[�����C��.
		Ending,			//�N���A.

		Max,			//�ő�l.
		Start = Title,	//�ŏ��̃V�[��.
	};

	//===================�֐�======================//.
	void Init(HWND hWnd,LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext*	pContext11);					//�����������֐�.
	void Load();																													//�ǂݍ��ݏ����֐�.
	void UpDate();																													//�X�V�����֐�.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos);		//�`�揈���֐�.
	void Release();																													//��������֐�.

	//=============���l�������֐�=================//.
	D3DXVECTOR4	GetBackColor() { return m_Color; }		//���̐F�̏��l�������֐�.

private:
	//===================�֐�=======================//.
	void ChangeScene();									//�V�[���ύX�����֐�.

	//===================�ϐ�=======================//.
	HWND						m_hWnd;					//�E�B���h�E�n���h��.
	LPDIRECT3DDEVICE9			m_pDevice9;
	ID3D11Device*				m_pDevice11;			//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*		m_pContext11;			//�f�o�C�X�R���e�L�X�g.

	std::unique_ptr<CSceneBase>	m_pCSceneBase;			//�V�[���N���X.
	D3DXVECTOR4					m_Color;
	int							m_ChangeSceneCnt;		//�V�[���ύX�J�E���g.
	int							m_SceneType;			//�V�[�����.

	std::unique_ptr<CSceneFade> m_pCSceneFade;			//�V�[���t�F�[�h�N���X.
};

#endif	//#ifndef CSCENE_MANAGER_H.