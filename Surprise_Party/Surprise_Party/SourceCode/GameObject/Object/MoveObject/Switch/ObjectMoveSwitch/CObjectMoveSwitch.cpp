#include "CObjectMoveSwitch.h"

CObjectMoveSwitch::CObjectMoveSwitch()
	: m_vAttachedOldPos	(0.0f, 0.0f, 0.0f)
{
	//初期化処理関数.
	Init();
}

CObjectMoveSwitch::~CObjectMoveSwitch()
{
	//解放処理関数.
	Release();
}

//===============================.
//		更新処理関数.
//===============================.
void CObjectMoveSwitch::Update()
{
	//スイッチの奥行座標.
	m_vPos.z = SWITCH_DEPTH_POS;

	//エフェクト更新処理関数.
	EffectUpdate();

	//机の座標設定.
	if (m_vAttachedObjPos[FLOWER_NUM].x != m_vAttachedObjPos[TABLE_NUM].x) {
		if (m_vAttachedObjPos[TABLE_NUM].x > 0.0f) {
			//初期以外はx軸を取得.
			m_vAttachedObjPos[TABLE_NUM].x = m_vAttachedObjPos[FLOWER_NUM].x;
			return;
		}
		//初期は座標全体を取得.
		m_vAttachedObjPos[TABLE_NUM] = m_vAttachedObjPos[FLOWER_NUM];
	}
}

//===============================.
//		初期化処理関数.
//===============================.
void CObjectMoveSwitch::Init()
{
	//メッシュオブジェクト読み込みアドレス取得.
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::MoveObjectSwitch);
	m_fScale = 0.1f;

	//エフェクト読み込みアドレス取得.
	m_pCEffect = m_pCResourceManager->GetEffect(CResourceEffect::enEffect::ObjectMove_Area_Effect);

	//移動オブジェクトメッシュアドレス取得.
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
//		解放処理関数.
//===============================.
void CObjectMoveSwitch::Release()
{
	for (int attached = static_cast<int>(m_pCAttachedObjMesh.size()) - 1; attached >= 0; attached--) {
		m_pCAttachedObjMesh[attached] = nullptr;
	}

	m_pCEffect = nullptr;
	m_pCMesh = nullptr;
}
