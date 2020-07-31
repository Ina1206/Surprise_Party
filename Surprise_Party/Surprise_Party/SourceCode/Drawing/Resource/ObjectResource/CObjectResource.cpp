#include "CObjectResource.h"

/*************************************
*	オブジェクト系の読み込みクラス.
*************/
template <class T1, class T2>
CObjectResource<T1, T2>::CObjectResource()
	: m_ppCObject	(nullptr)
{

}

template<class T1, class T2>
CObjectResource<T1, T2>::~CObjectResource()
{
	if (m_ppCObject != nullptr) {
		for (int objNum = m_ResourceMax - 1; objNum >= 0; objNum--) {
			if (m_ppCObject[objNum] != nullptr) {
				//解放処理関数.
				Release(static_cast<T2>(objNum));
			}
		}
		//配列解放.
		SAFE_DELETE_ARRAY(m_ppCObject);
	}
}

//=======================================.
//		初期化処理関数.
//=======================================.
template<class T1, class T2>
HRESULT CObjectResource<T1, T2>::Init(int max)
{
	//最大値.
	m_ResourceMax = max;

	//配列動的確保.
	m_ppCObject = new T1*[m_ResourceMax]();
	//初期化.
	for (int objNum = 0; objNum < m_ResourceMax; objNum++) {
		m_ppCObject[objNum] = nullptr;
	}

	return S_OK;
}

//=======================================.
//		読み込み処理関数.
//=======================================.
template<class T1, class T2>
HRESULT CObjectResource<T1, T2>::Load(std::vector<std::tuple<std::string, bool>> tStringFlag)
{
	for (int ObjNum = 0; ObjNum < m_ResourceMax; ObjNum++) {
		//ファイル名.
		const std::string FileName = std::get<0>(tStringFlag[ObjNum]);

		//スポットライトを使うフラグ.
		const bool bUseSpotLightFlag = std::get<1>(tStringFlag[ObjNum]);

		//読み込み処理関数.
		Create(static_cast<T2>(ObjNum), FileName.c_str(), bUseSpotLightFlag);
	}

	return S_OK;
}

//=======================================.
//		解放呼び出し処理関数.
//=======================================.
template<class T1, class T2>
HRESULT CObjectResource<T1, T2>::ReleaseCalling()
{
	for (int ObjNum = m_ResourceMax - 1; ObjNum >= 0; ObjNum--) {
		Release(static_cast<T2>(ObjNum));
	}
	return S_OK;
}

//=======================================.
//		情報取得処理関数.
//=======================================.
template<class T1, class T2>
T1* CObjectResource<T1, T2>::GetMeshObject(T2 enObjectInof)
{
	//範囲外なら終了.
	if (FAILED(Check_ObjectRange(enObjectInof))) {
		return nullptr;
	}

	//モデルがなければ終了.
	if (m_ppCObject[static_cast<int>(enObjectInof)] == nullptr) {
		return nullptr;
	}

	return m_ppCObject[static_cast<int>(enObjectInof)];
}

//=======================================.
//		作成処理関数.
//=======================================.
template<class T1, class T2>
HRESULT CObjectResource<T1, T2>::Create(T2 enObjectInfo, const char* pFileName, const bool& bSpotLight) 
{
	//範囲外なら終了.
	if (FAILED(Check_ObjectRange(enObjectInfo))) {
		return E_FAIL;
	}

	//モデルが既にある場合は終了.
	if (m_ppCObject[static_cast<int>(enObjectInfo)] != nullptr) {
		return E_FAIL;
	}

	//モデルの読み込み.
	m_ppCObject[static_cast<int>(enObjectInfo)] = new T1();
	if (FAILED(m_ppCObject[static_cast<int>(enObjectInfo)]->Init(m_hWnd, m_pDevice9, m_pDevice11, m_pContext11, pFileName, bSpotLight))) {
		return E_FAIL;
	}

	return S_OK;
}

//=======================================.
//		解放処理関数.
//=======================================.
template<class T1, class T2>
HRESULT CObjectResource<T1, T2>::Release(T2 enObjectInfo)
{
	//範囲外なら終了.
	if (FAILED(Check_ObjectRange(enObjectInfo))) {
		return E_FAIL;
	}

	//モデルが無ければ終了.
	if (m_ppCObject[static_cast<int>(enObjectInfo)] == nullptr) {
		return S_OK;
	}

	//解放処理.
	m_ppCObject[static_cast<int>(enObjectInfo)]->Release();
	SAFE_DELETE(m_ppCObject[static_cast<int>(enObjectInfo)]);

	return S_OK;
}

//=======================================.
//		範囲確認処理関数.
//=======================================.
template<class T1, class T2>
HRESULT CObjectResource<T1, T2>::Check_ObjectRange(T2 enObjectInfo)
{
	//範囲外なら終了.
	if (static_cast<int>(enObjectInfo) < 0 || m_ResourceMax <= static_cast<int>(enObjectInfo)) {
		return E_FAIL;
	}

	return S_OK;
}

template class CObjectResource<CDX9Mesh, enStaticMeshType>;
template class CObjectResource<CDX9SkinMesh, enSkinMeshType>;