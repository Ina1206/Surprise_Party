#ifndef CPEOPLE_MANAGER_H
#define CPEOPLE_MANAGER_H

#include "..\..\FileLoad\FileResource\CFileResource.h"
#include "..\Boy\CBoy.h"
#include "..\Girl\CGirl.h"
#include "..\..\UI\MapUI\CharaUI\Icon\PeopleIcon\GirlIcon\CGirlIcon.h"
#include "..\..\\UI\MapUI\CharaUI\Icon\PeopleIcon\BoyIcon\CBoyIcon.h"

/***************************************
*		�l�X�̊Ǘ��N���X.
********/
class CPeopleManager
{
public:
	CPeopleManager();
	~CPeopleManager();

	//=================�萔==================//.
	const D3DXVECTOR3	INIT_POS		= D3DXVECTOR3(-1.0f, 0.0f, -2.5f);		//�ŏ��̈ʒu.
	const unsigned int	DISP_TIME		= 60;									//�\�������鎞��.
	const int			HUMAN_TYPE_MAX	= 2;									//�l�Ԏ�ލő吔.

	//=================�֐�==================//.
	void Init(int FileNum, int max, float StageMax);	//�����������֐�.
	void UpDate();										//�X�V�����֐�.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos, const LIGHT& stLight);	//�`�揈���֐�.

	//===========���u�������֐�============//.
	//�X�e�[�W�����ő�l.
	void SetStageDistanceMax(const float& fStageDistanceMax) { m_fStageDistanceMax = fStageDistanceMax; }
	//�������t���O.
	void SetSurpriseFlag(const int& SurpriseHumanNum, const bool& bFlag) { m_bSurpriseFlag[SurpriseHumanNum] = bFlag; }
	//�����Ă���l�ԍ�.
	void SetNowHumanSurprise(const std::vector<int>& HumanNum);

	//===========���l�������֐�============//.
	//�l�̍��W�擾.
	std::vector<D3DXVECTOR3> GetHumanPos() { return m_vHumanPos; }
	//�ǉ��|�C���g��.
	int GetAddSurprisePoint() { return m_AddSurprisePoint; }

private:
	//=================�֐�==================//.
	void Release();		//��������֐�.
	void HumanApp();	//�l�̕\�������֐�.
	void HumanMove();	//�l�̈ړ������֐�.

	//=================�ϐ�==================//.
	CFileResource*								m_pCFileResource;	//�t�@�C���ǂݍ��݃N���X.

	std::vector<int>							m_HumanAppOrder;	//�l���o������.
	std::vector<CPeopleBase*>					m_pCPeopleBase;		//�l�̃N���X.
	std::vector<bool>							m_bDispFlag;		//�\���t���O.
	std::vector<D3DXVECTOR3>					m_vHumanPos;		//�l�̍��W.
	float										m_fStageDistanceMax;//�X�e�[�W�ő吔.
	unsigned int								m_CreateHumanMax;	//�쐬�ő吔.
	std::vector<bool>							m_bSurpriseFlag;	//�������t���O.

	unsigned int								m_DispCnt;			//�\���J�E���g.
	unsigned int								m_AppHumanNum;		//�����l�Ԃ̔ԍ�.

	std::vector<int>							m_SurpriseHumanNum;	//�����Ă���l�ԍ�.
	int											m_AddSurprisePoint;	//�ǉ������|�C���g.

	std::vector<std::unique_ptr<CPeopleIcon>>	m_pCPeopleIcon;		//�l�̃A�C�R��.
};


#endif	//#ifndef CPEOPLE_MANAGER_H.