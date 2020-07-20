#ifndef CSCENE_MANAGER_H
#define CSCENE_MANAGER_H

#include "..\Title\CTitle.h"
#include "..\GameMain\CGameMain.h"
#include "..\Ending\CEnding.h"
#include "..\Pause\CPause.h"
	
#include "..\..\Drawing/Resource/CResourceManager.h"
#include "..\GameMain\CGameMain.h"

#include "..\..\UI\Fade\SceneFade\CSceneFade.h"

#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

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

	//===================�萔======================//.
	const unsigned int	INIT_SETTED_FLAG	= (1 << 0);						//�����ݒ��t���O.
	const unsigned int	START_GAME_FLAG		= (1 << 1);						//�Q�[���J�n�t���O.
	const int			NORMAL_SCENE_NUM	= 0;							//�ʏ�V�[���ԍ�(�^�C�g���A�Q�[�����C���A�N���A���).
	const int			PAUSE_SCENE_NUM		= 1;							//�ꎞ��~�V�[���ԍ�.
	const D3DXVECTOR2	SCENE_NAME_POS		= D3DXVECTOR2(50.0f, 200.0f);	//�V�[�������W.
	const float			HIGHT_WIDTH			= 30.0f;						//������.
	const D3DXVECTOR2	CURSOR_POS			= D3DXVECTOR2(20.0f, 200.0f);	//�J�[�\�����W.

	//===================�֐�======================//.
	void Init(HWND hWnd,LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext*	pContext11);//�����������֐�.
	void Load();																								//�ǂݍ��ݏ����֐�.
	void UpDate();																								//�X�V�����֐�.
	void Render(const D3DXMATRIX& mProj);												//�`�揈���֐�.
	void Release();																								//��������֐�.

	//=============���l�������֐�=================//.
	D3DXVECTOR4	GetBackColor() { return m_Color; }		//���̐F�̏��l�������֐�.

private:
	//===================�֐�=======================//.
	void ChangeScene();									//�V�[���ύX�����֐�.
	void NextScene();									//���̃V�[���ɐi�ޏ����֐�.
	void Pause();										//�|�[�Y��������.
	void FlyToScene();									//�V�[���ɔ�ԏ����֐�.
	void RenderDebugFont();								//�f�o�b�O�p�t�H���g�`�揈���֐�.

	//===================�ϐ�=======================//.
	HWND										m_hWnd;						//�E�B���h�E�n���h��.
	LPDIRECT3DDEVICE9							m_pDevice9;
	ID3D11Device*								m_pDevice11;				//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*						m_pContext11;				//�f�o�C�X�R���e�L�X�g.
	CDepth_Stencil*								m_pCDepthStencil;			//�f�v�X�X�e���V��.

	std::vector<std::unique_ptr<CSceneBase>>	m_pCSceneBase;				//�V�[���N���X.
	D3DXVECTOR4									m_Color;
	int											m_ChangeSceneCnt;			//�V�[���ύX�J�E���g.
	int											m_SceneType;				//�V�[�����.

	std::unique_ptr<CSceneFade>					m_pCSceneFade;				//�V�[���t�F�[�h�N���X.
	bool										m_PausingFlag;				//�ꎞ��~�t���O.
	unsigned int								m_StartFlag;				//�J�n�t���O.

	CDebugText*									m_pCDebugText;				//�f�o�b�O�e�L�X�g.
	int											m_FlyToSceneNum;			//�ύX����V�[���ԍ�.
	int											m_FlyToSceneMax;			//�ύX����f�o�b�O�p�̃V�[���ő吔.
	bool										m_bFlyToSceneFlag;			//�V�[���ɔ�ԃt���O.

	int											m_FlyToSceneEvaluation;		//�V�[���ɔ�ԏꍇ�̕]��.

	CPlaySoundManager*							m_pCPlaySoundManager;		//���Đ��Ǘ��N���X.
};

#endif	//#ifndef CSCENE_MANAGER_H.