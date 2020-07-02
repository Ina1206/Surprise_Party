#ifndef CFILE_RESOURCE_H
#define CFILE_RESOURCE_H
 
#include "..\FileNumber\CFileNumber.h"
#include "..\FileString\CFileString.h"

/*****************************************
*		�t�@�C���ǂݍ��݃N���X.
********/
class CFileResource
{
public:
	CFileResource();
	~CFileResource();

	//===================�֐�=======================//.
	const int ONETYPE_STAGE_MAX = 3;	//1�^�C�v�̃X�e�[�W�̍ő吔.

	//==================�񋓑�======================//.
	//�X�e�[�W���.
	enum class enStageType {
		ObjectPos,			//�I�u�W�F�N�g���W.
		PeopleComeOder,		//�l�����鏇��.
		GhostPos,			//�������̈ʒu1����.

		Max,				//�ő�l.
		Start = ObjectPos,
	};
	//�X�e�[�^�X�K�v�L����.
	enum class enStatusCharaType {
		Ghost = 0,		//������.
		People,			//�l.

		Max,			//�ő�l.
		Start = Ghost,
	};
	//��b�t�@�C�����.
	enum class enSpeakFileType {
		GhostSpeakFirstStage,
		GhostSpeakStage,
		SpeakTutorialBigGhost,
		EndingSpeak,
	};

	//===================�֐�=======================//.
	void Load();		//�ǂݍ��ݏ����֐�.

	//�V���O���g��.
	static CFileResource* GetResourceInstance() {
		static CFileResource s_Instance;
		return &s_Instance;
	}
	//=============���擾�����֐�=================//.
	//�X�e�[�W�̃}�b�v�`�b�v�̎擾.
	int GetStageNum(int fileNum, int column, int line) { return static_cast<int>(m_pCStageFileNumber[fileNum]->GetDataNum(column, line)); }
	//�X�e�[�^�X�̃}�b�v�`�b�v�̎擾.
	float GetStatusNum(int fileNum, int column, int line) { return m_pCStatusFileNumber[fileNum]->GetDataNum(column, line); }
	//�X�e�[�W�̍ő�.
	int GetStageMax(const int& fileNum, const int& column) { return m_pCStageFileNumber[fileNum]->GetLineMax(column); }
	//��b����.
	std::string GetSpeakString(const int& fileNum, const int& column, const CFileString::enStringType& line) { return m_pCSpeakFileString[fileNum]->GetData(column, line); }
	int	GetSringMax(const int& fileNum) const { return m_pCSpeakFileString[fileNum]->GetColumnMax(); }

private:
	//===================�֐�=======================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void StageLoad();	//�X�e�[�W�ǂݍ��ݏ����֐�.
	void StatusLoad();	//�X�e�[�^�X�ǂݍ��ݏ����֐�.
	void SpeakLoad();	//��b���͓ǂݍ��ݏ����֐�.

	//===================�ϐ�=======================//.
	std::vector<CFileNumber*>					m_pCStageFileNumber;	//�}�b�v�`�b�v�̃t�@�C���ǂݍ���.
	std::vector<CFileNumber*>					m_pCStatusFileNumber;	//�X�e�[�^�X�̃t�@�C���ǂݍ���.
	std::vector<std::unique_ptr<CFileString>>	m_pCSpeakFileString;	//��b���͓ǂݍ���.
};

#endif	//#ifndef CFILE_RESOURCE_H.