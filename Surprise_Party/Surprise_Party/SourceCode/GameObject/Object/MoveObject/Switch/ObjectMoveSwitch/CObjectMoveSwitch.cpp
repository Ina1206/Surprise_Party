#include "CObjectMoveSwitch.h"

CObjectMoveSwitch::CObjectMoveSwitch()
	: m_vAttachedOldPos	(0.0f, 0.0f, 0.0f)
{
	//�����������֐�.
	Init();
}

CObjectMoveSwitch::~CObjectMoveSwitch()
{
	//��������֐�.
	Release();
}

//===============================.
//		�X�V�����֐�.
//===============================.
void CObjectMoveSwitch::Update()
{
	//�X�C�b�`�̉��s���W.
	m_vPos.z = SWITCH_DEPTH_POS;

	//�G�t�F�N�g�X�V�����֐�.
	EffectUpdate();

	//���̍��W�ݒ�.
	if (m_vAttachedObjPos[FLOWER_NUM].x != m_vAttachedObjPos[TABLE_NUM].x) {
		if (m_vAttachedObjPos[TABLE_NUM].x > 0.0f) {
			//�����ȊO��x�����擾.
			m_vAttachedObjPos[TABLE_NUM].x = m_vAttachedObjPos[FLOWER_NUM].x;
			return;
		}
		//�����͍��W�S�̂��擾.
		m_vAttachedObjPos[TABLE_NUM] = m_vAttachedObjPos[FLOWER_NUM];
	}
}

//===============================.
//		�����������֐�.
//===============================.
void CObjectMoveSwitch::Init()
{
	//���b�V���I�u�W�F�N�g�ǂݍ��݃A�h���X�擾.
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::MoveObjectSwitch);
	m_fScale = 0.1f;

	//�G�t�F�N�g�ǂݍ��݃A�h���X�擾.
	m_pCEffect = m_pCResourceManager->GetEffect(CResourceEffect::enEffect::ObjectMove_Area_Effect);

	//�ړ��I�u�W�F�N�g���b�V���A�h���X�擾.
	m_pCAttachedObjMesh.push_back(m_pCResourceManager->GetStaticMesh(enStaticMeshType::Table));
	m_pCAttachedObjMesh.push_back(m_pCResourceManager->GetStaticMesh(enStaticMeshType::Vase_Flower));
	m_vAttachedObjPos.resize(m_pCAttachedObjMesh.size());
	m_vAttachedObjRot.resize(m_pCAttachedObjMesh.size());
	for (unsigned int attached = 0; attached < m_pCAttachedObjMesh.size(); attached++) {
		m_vAttachedObjPos[attached] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vAttachedObjRot[attached] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//===============================.
//		��������֐�.
//===============================.
void CObjectMoveSwitch::Release()
{
	for (int attached = static_cast<int>(m_pCAttachedObjMesh.size()) - 1; attached >= 0; attached--) {
		m_pCAttachedObjMesh[attached] = nullptr;
	}

	m_pCEffect = nullptr;
	m_pCMesh = nullptr;
}
