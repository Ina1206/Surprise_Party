#ifndef CSOUND_RESOURCE_H
#define CSOUND_RESOURCE_H

#include "..\..\Global.h"
#include "..\CSound.h"

//============�񋓑�=============//.
//���[�v���Ȃ���.
enum class enSEType {
	Shutter,						//�V���b�^�[.
	MoveCursor,						//�J�[�\���ړ�.
	LimitMoveCursor,				//�J�[�\������ړ�.
	SelectDecide,					//�I��������.
	Jump,							//�W�����v.
	Turn,							//��].

	Font,							//�t�H���g.
	Swet,							//��.
	Question,						//�͂Ă�.
	Redjuice,						//���.
	Bubble,							//�A.

	MoveCurtain,					//�J�[�e���ړ�.
	OpenBell,						//�Ŕ�].

	ReturnSelect,					//�I��������.
	OpenActSelect,					//�I�����J��.
	FlowerSwing,					//�Ԃ̗h��鉹.
	PushSwitchPlaySound,			//�{�^���������Đ�����鉹.
	PushSwitch,						//�{�^��������.
	FallDownPicture,				//�G�旎����.
	NotSelect,						//�I������I�ׂȂ�.
	GimmickDecide,					//�M�~�b�N����.
	ReturnFromGimmickSelect,		//�M�~�b�N�I������.
	GhostGimmickMove,				//�������ƃM�~�b�N�Ɉړ����鉹.
	GhostGimmickSelectLimit,		//�������ƃM�~�b�N�I�����.

	ManShout,						//�j���̋��ѐ�.
	WomanShout,						//�����̋��ѐ�.

	ExtensionCheers,				//��������.
	Stump,							//�X�^���v.

	Max,							//�ő吔.
	Start ,							//�ŏ�.
};
//���[�v���鉹.
enum class enBGMType {
	Title,							//�^�C�g��.
	GhostSpeakStage,				//��������b�X�e�[�W.
	GameMain,						//�Q�[�����C��.
	ResultBefore,					//���U���g�O�X�e�[�W.
	LowEvaluationStage,				//��]���X�e�[�W.
	IntermediateEvaluationStage,	//���ԕ]���X�e�[�W.
	HightEvaluationStage,			//���]���X�e�[�W.

	Max,							//�ő吔.
	Start = Title,					//�ŏ�.
};

/**********************************************
*	�T�E���h�ǂݍ��݃N���X.
******/
class CSoundResource
{
public:
	CSoundResource();
	~CSoundResource();

	//=============�萔==============//.
	const int SE_TYPE_MAX	= static_cast<int>(enSEType::Max);				//��ނ��Ƃ�SE�̍ő吔.
	const int SE_RESEVE		= 10;											//SE�̕⌇.
	
	const int BGM_MAX		= static_cast<int>(enBGMType::Max);				//BGM�̍ő吔.

	//=============�֐�==============//.
	HRESULT Init(HWND hWnd);												//�����������֐�.
	HRESULT Load();															//�ǂݍ��ݏ����֐�.

	//���擾�����֐�.
	clsSound* GetSE(const int& SENum) { return m_pCSE[SENum].get(); }		//SE�̃T�E���h�N���X.
	clsSound* GetBGM(const int& BGMNum) { return m_pCBGM[BGMNum].get(); }	//BGM�̃T�E���h�N���X.
	int GetSEMax() const { return static_cast<int>(m_pCSE.size()); }		//SE�̍ő吔.
	int GetBGMMax() const { return static_cast<int>(m_pCBGM.size()); }		//BGM�̍ő吔.
private:
	
	//=============�֐�==============//.
	HRESULT Release();														//��������֐�.
	
	HRESULT Create( const std::string& pfilename, 
					std::unique_ptr<clsSound>& pCSound,
					const std::string& paliasname);							//�쐬�����֐�.
	
	void	AddAliasName(const std::string& alias_name, 
						 const int& name);									//�G�C���A�X���̌��������֐�.												
	HRESULT	LoadSE();														//SE�̓ǂݍ��ݏ����֐�.
	HRESULT LoadBGM();														//���[�vSE�̓ǂݍ��ݏ����֐�.
	
	void	InitSound( std::vector<std::unique_ptr<clsSound>>& CSound, 
					   std::vector<std::string>& stName);					//���̏����������֐�.

	//=============�ϐ�==============//.
	HWND									m_hWnd;							//�E�B���h�E�n���h��.

	std::vector<std::unique_ptr<clsSound>>	m_pCSE;							//�T�E���h�N���X�iSE�j.
	std::vector<std::string>				m_stSEaliasName;				//SE�̖��O�G�C���A�X��.

	std::vector<std::unique_ptr<clsSound>>	m_pCBGM;						//�T�E���h�N���X�iBGM�j.
	std::vector<std::string>				m_stBGMaliasName;				//BGM�̃G�C���A�X��.
};

#endif	//#ifndef CSOUND_RESOURCE_H.