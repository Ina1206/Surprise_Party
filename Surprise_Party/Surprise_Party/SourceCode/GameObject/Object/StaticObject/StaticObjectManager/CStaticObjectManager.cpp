#include "CStaticObjectManager.h"
#include <random>

CStaticObjectManager::CStaticObjectManager()
	: CStaticObjectManager(0, 0)
{

}

CStaticObjectManager::CStaticObjectManager(const int& filenum, const int& stagenum)
	: m_mView				()
	, m_mProj				()
	, m_stLight				()
	, m_Filenum				(0)
	, m_Stagenum			(0)
	, m_pCFileResource		(nullptr)
	, m_pCObjectBase		()
	, m_vObjectPos			()
	, m_pCOtherObjectBase	()
	, m_vOtherObjectPos		()
	, m_vCameraPos			(0.0f, 0.0f, 0.0f)
	, m_fStageDistanceMax	(0.0f)
{
	//�t�@�C���ԍ�.
	m_Filenum = filenum;
	//�X�e�[�W�ԍ�.
	m_Stagenum = stagenum;

	//�����������֐�.
	Init();
}

CStaticObjectManager::~CStaticObjectManager()
{
	//��������֐�.
	Release();
}

//====================================.
//		�X�V�����֐�.
//====================================.
void CStaticObjectManager::Updata()
{
	//�I�u�W�F�N�g�ݒ�p�ԍ�.
	int num = 0;

	int checkStageNum = 0;
	for (int stage = 0; stage < m_pCFileResource->GetStageMax(m_Filenum, m_Stagenum) * COLUMN_MAX; stage++) {
		//�ǂɍ��킹�ĕ\���ꏊ�����߂�.
		if (stage % COLUMN_MAX == 0) {
			checkStageNum = stage;
		}

		if (m_vCameraPos.x + DISP_CAMERA_WIDHT > m_vObjectPos[checkStageNum].x &&
			m_vCameraPos.x - DISP_CAMERA_WIDHT < m_vObjectPos[checkStageNum].x) {
			//�I�u�W�F�N�g���W�ݒ�.
			m_pCObjectBase[num]->SetPos(m_vObjectPos[stage]);
			//�I�u�W�F�N�g�X�V�����֐�.
			m_pCObjectBase[num]->Update();
			num++;
		}

		if (num >= ALL_OBJECT_MAX) {
			break;
		}
	}

	//���̑��̃I�u�W�F�N�g.
	std::vector<int> m_ObjDispCnt(static_cast<int>(enStaticObjectType::ObjMax));
	for (unsigned int obj = 0; obj < static_cast<int>(enStaticObjectType::ObjMax); obj++) {
		//��ނ��Ƃ̃I�u�W�F�N�g�̍ő吔.
		int objMax = 0;
		if (obj >= m_BeforeObjMax.size() - 1) {
			objMax = m_vOtherObjectPos.size() - m_BeforeObjMax[obj];
		}
		else {
			objMax = m_BeforeObjMax[obj + 1] - m_BeforeObjMax[obj];
		}
		for (int stage = 0; stage < objMax; stage++) {
			if (m_vCameraPos.x + DISP_CAMERA_WIDHT > m_vOtherObjectPos[stage + m_BeforeObjMax[obj]].x &&
				m_vCameraPos.x - DISP_CAMERA_WIDHT < m_vOtherObjectPos[stage + m_BeforeObjMax[obj]].x) {
				m_pCOtherObjectBase[m_ObjDispCnt[obj] + (obj * OTHER_CREATION_MAX)]->SetPos(m_vOtherObjectPos[stage + m_BeforeObjMax[obj]]);
				m_pCOtherObjectBase[m_ObjDispCnt[obj] + (obj * OTHER_CREATION_MAX)]->Update();
				m_ObjDispCnt[obj]++;
			}

			if (m_ObjDispCnt[obj] >= OTHER_CREATION_MAX) {
				break;
			}
		}
	}
}

//====================================.
//		�`�揈���֐�.
//====================================.
void CStaticObjectManager::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos, const LIGHT& stLight)
{
	m_mView = mView;
	m_mProj = mProj;
	m_vCameraPos = vCameraPos;
	m_stLight = stLight;

	//�ǂƏ��̕`��.
	ObjectRender(m_pCObjectBase, m_pCObjectBase.size());
	//���̑��̃I�u�W�F�N�g�̕`��.
	ObjectRender(m_pCOtherObjectBase, m_pCOtherObjectBase.size());
}

//====================================.
//		�����������֐�.
//====================================.
void CStaticObjectManager::Init()
{
	m_pCFileResource = CFileResource::GetResourceInstance();

	//�ǂƏ��̐ݒ菈���֐�.
	WallAndFloorSetting();

	//���̃I�u�W�F�N�g�ݒ菈���֐�.
	OtherObjectSetting();
}

//====================================.
//		��������֐�.
//====================================.
void CStaticObjectManager::Release()
{
	//�I�u�W�F�N�g�̃C���X�^���X�������N���X�̉��.
	for (int obj = static_cast<int>(m_pCOtherObjectBase.size()) - 1; obj >= 0; obj--) {
		SAFE_DELETE(m_pCOtherObjectBase[obj]);
	}
	//�ǂƏ��̃C���X�^���X�������N���X�̉��.
	for (int stage = static_cast<int>(m_pCObjectBase.size()) - 1; stage >= 0; stage--) {
		SAFE_DELETE(m_pCObjectBase[stage]);
	}

	m_pCFileResource = nullptr;
}

//====================================.
//		�ǂƏ��̐ݒ菈���֐�.
//====================================.
void CStaticObjectManager::WallAndFloorSetting()
{
	for (int stage = 0; stage < ALL_OBJECT_MAX; stage++) {
		m_pCObjectBase.push_back(nullptr);

		if (stage % COLUMN_MAX == 0) {
			//�ǂ̃N���X�̃C���X�^���X��.
			m_pCObjectBase[stage] = new CWall();
			continue;
		}

		//���̃N���X�̃C���X�^���X��.
		m_pCObjectBase[stage] = new CFloor();
	}

	D3DXVECTOR3 vInitPos;
	int stagenum = 0;
	//���ƕǂ̍��W�ݒ�.
	for (int stage = 0; stage < m_pCFileResource->GetStageMax(m_Filenum, m_Stagenum) * COLUMN_MAX; stage++) {
		if (stage % COLUMN_MAX == 0) {
			//��ԍ�.
			stagenum = stage / COLUMN_MAX;
			//�ǂ̍��W.
			m_vObjectPos.push_back(D3DXVECTOR3(stagenum * OBJECT_WIDTH, 0.0f, 1.0f));
			continue;
		}
		//���̍��W.
		vInitPos.x = FLOOR_START_POS.x + (stagenum * OBJECT_WIDTH);
		vInitPos.y = FLOOR_START_POS.y;
		vInitPos.z = FLOOR_START_POS.z - (((stage % COLUMN_MAX) - 1)* OBJECT_WIDTH);
		m_vObjectPos.push_back(vInitPos);
	}

	//�X�e�[�W�̋����ő吔�v�Z.
	m_fStageDistanceMax = m_pCFileResource->GetStageMax(m_Filenum, m_Stagenum) * OBJECT_WIDTH;
}

//====================================.
//	���̃I�u�W�F�N�g�ݒ菈���֐�.
//====================================.
void CStaticObjectManager::OtherObjectSetting()
{
	//���̃I�u�W�F�N�g�̃C���X�^���X���ƍ��W�ݒ�.
	//�e�I�u�W�F�N�g�̃X�e�[�W�ő吔.
	int stageMax = m_pCFileResource->GetStageMax(m_Filenum, m_Stagenum);
	//�I�u�W�F�N�g�����X�e�[�W��.
	int objMax = stageMax * static_cast<int>(enStaticObjectType::ObjMax);
	int obj = 0;
	m_BeforeObjMax.push_back(m_vOtherObjectPos.size());

	for (int stage = 0; stage < objMax; stage++) {
		int stagenum = stage - (stageMax - m_pCFileResource->GetStageMax(m_Filenum, m_Stagenum));
		int objNum = m_pCFileResource->GetStageNum(m_Filenum, m_Stagenum, stagenum) - 1;
		if (objNum == obj) {
			//�I�u�W�F�N�g�ԍ����Ƃɐݒ�.
			switch (objNum) {
			case static_cast<int>(enStaticObjectType::Painting):
				m_vOtherObjectPos.push_back(D3DXVECTOR3(stagenum * OBJECT_WIDTH, 5.0f, 1.0f));
				break;
			case static_cast<int>(enStaticObjectType::BookShelf):
				m_vOtherObjectPos.push_back(D3DXVECTOR3(stagenum * OBJECT_WIDTH, 0.0f, 0.5f));
				break;

			}

		}
		//�I�u�W�F�N�g�̃X�e�[�W�ő吔�ɂȂ�Ǝ��̃I�u�W�F�N�g��.
		if (stage >= stageMax - 1) {
			obj++;
			stageMax += m_pCFileResource->GetStageMax(m_Filenum, m_Stagenum);
			m_BeforeObjMax.push_back(m_vOtherObjectPos.size());
		}
	}

	//�S�Ă̑��̃I�u�W�F�N�g�̍쐬.
	for (int stage = 0; stage < static_cast<int>(enStaticObjectType::ObjMax) * OTHER_CREATION_MAX; stage++) {
		int stagenum = static_cast<int>(stage / OTHER_CREATION_MAX);
		switch (static_cast<enStaticObjectType>(stagenum)) {
		//�G��.
		case enStaticObjectType::Painting:
			m_pCOtherObjectBase.push_back(nullptr);
			m_pCOtherObjectBase[m_pCOtherObjectBase.size() - 1] = new CPainting();
			break;
		case enStaticObjectType::BookShelf:
			m_pCOtherObjectBase.push_back(nullptr);
			m_pCOtherObjectBase[m_pCOtherObjectBase.size() - 1] = new CBookShelf();
			break;
		}
	}

}

//================================.
//	�I�u�W�F�N�g�̕`�揈���֐�.
//================================.
void CStaticObjectManager::ObjectRender(std::vector<CObjectBase*> obj, int max)
{
	for (int stage = 0; stage < max; stage++) {
		obj[stage]->SetCameraPos(m_vCameraPos);
		obj[stage]->RenderInitSetting(m_mView, m_mProj, m_stLight);
		obj[stage]->Render();
	}
}

