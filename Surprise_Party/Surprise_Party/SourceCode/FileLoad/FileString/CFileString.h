#ifndef CFILE_STRING_H
#define CFILE_STRING_H

#include "..\FileLoadBase\CFileLoad.h"

/************************************
*		���͓ǂݎ��N���X.
*********/
class CFileString
	: public CFile
{
public:
	CFileString();
	~CFileString();

	//===================�񋓑�=======================//.
	enum class enStringType {
		MainString = 0,	//���C������.
		SelectString,	//�I�𕶏�.
		EmotionNum,		//����ԍ�.
	};

	//====================�֐�========================//.
	HRESULT Init(const char*	pFileName);									//�����������֐�.

	//================���l�������֐�================//.
	//�t�@�C���̃f�[�^.
	std::string GetData(const int& column, const enStringType& line) const { return m_veclineData[column][static_cast<int>(line)]; }

private:
	//====================�֐�========================//.
	HRESULT DataSplita(const std::string& input, const char& delimiter);	//�f�[�^���������֐�.
	HRESULT DataArrage();													//�s�Ɨ�ɕ����鏈���֐�.

	//====================�ϐ�========================//.
	std::vector<std::string>				m_strvec;						//�R���}�ŋ�؂镶����.
	std::vector<std::vector<std::string>>	m_veclineData;					//�s�Ɨ�̃f�[�^.
	int										m_lineMax;						//��̍ő吔.
	int										m_ColumneMax;					//�s�̍ő吔.

};

#endif	//#ifndef CFILE_STRING_H.