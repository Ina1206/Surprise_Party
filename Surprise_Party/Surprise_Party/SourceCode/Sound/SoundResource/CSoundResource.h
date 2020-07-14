#ifndef CSOUND_RESOURCE_H
#define CSOUND_RESOURCE_H

#include "..\..\Global.h"
#include "..\CSound.h"

/**********************************************
*	�T�E���h�ǂݍ��݃N���X.
******/
class CSoundResource
{
public:
	CSoundResource();
	~CSoundResource();

	//============�񋓑�=============//.
	//���[�v���Ȃ���.
	enum class enSEType {
		Jump,				//�W�����v.
		Max,				//�ő吔.
		Start ,				//�ŏ�.
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

	//=============�萔==============//.
	const int SE_RESEVE		= 10;											//SE�̕⌇.

	const int ONE_SE_MAX	= static_cast<int>(enSEType::Max);				//�P��SE�̍ő吔.
	const int LENGTH_MAX	= 256;											//�������ő吔.
	const int ALL_SE_MAX	= ONE_SE_MAX * SE_RESEVE;						//�⌇�����킹�����ׂĂ̒P��SE�̍ő吔.
	
	const int BGM_MAX		= static_cast<int>(enBGMType::Max);				//BGM�̍ő吔.

	//=============�֐�==============//.
	HRESULT Init(HWND hWnd);												//�����������֐�.
	HRESULT Load();															//�ǂݍ��ݏ����֐�.
	HRESULT Release();														//��������֐�.

	//���擾�����֐�.
	clsSound* GetSE(const int& SENum) { return m_pCSE[SENum].get(); }		//SE�̃T�E���h�N���X.
	clsSound* GetBGM(const int& BGMNum) { return m_pCBGM[BGMNum].get(); }	//BGM�̃T�E���h�N���X.
private:
	//=============�֐�==============//.
	HRESULT Create(const std::string& pfilename, 
					std::unique_ptr<clsSound>& pCSound,
					const std::string& paliasname);							//�쐬�����֐�.

	HRESULT Check(int sound, 
				  std::unique_ptr<clsSound>& pCSound);						//���ׂ鏈���֐�.
	
	void	AddAliasName(char* alias_name, int name);						//�G�C���A�X���̌��������֐�.												
	HRESULT	LoadSE();														//�P��SE�̓ǂݍ��ݏ����֐�.
	HRESULT LoadBGM();														//���[�vSE�̓ǂݍ��ݏ����֐�.
	
	void	InitSound(	std::vector<std::unique_ptr<clsSound>>& CSound, 
						std::vector<std::string>& stName);					//���̏����������֐�.

	//=============�ϐ�==============//.
	HWND		m_hWnd;				//�E�B���h�E�n���h��.

	std::vector<std::unique_ptr<clsSound>>	m_pCSE;							//�T�E���h�N���X�iSE�j.
	std::vector<std::string>				m_stSEaliasName;				//SE�̖��O�G�C���A�X��.

	std::vector<std::unique_ptr<clsSound>>	m_pCBGM;						//�T�E���h�N���X�iBGM�j.
	std::vector<std::string>				m_stBGMaliasName;				//BGM�̃G�C���A�X��.
};

#endif	//#ifndef CSOUND_RESOURCE_H.