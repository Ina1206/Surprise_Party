#include "CObjectResource.h"

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
				//��������֐�.
				Release(static_cast<T2>(objNum));
			}
		}
		//�z����.
		SAFE_DELETE_ARRAY(m_ppCObject);
	}
}

//=======================================.
//		�����������֐�.
//=======================================.
template<class T1, class T2>
HRESULT CObjectResource<T1, T2>::Init(int max)
{
	//�ő�l.
	m_ResourceMax = max;

	//�z�񓮓I�m��.
	m_ppCObject = new T1*[m_ResourceMax]();
	//������.
	for (int objNum = 0; objNum < m_ResourceMax; objNum++) {
		m_ppCObject[objNum] = nullptr;
	}

	return S_OK;
}

//=======================================.
//		�ǂݍ��ݏ����֐�.
//=======================================.
template<class T1, class T2>
HRESULT CObjectResource<T1, T2>::Load(std::vector<std::string> vecFileName)
{
	//�t�@�C���p�X�̑��.
	const char** fileName = nullptr;
	fileName = new const char*[m_ResourceMax]();
	for (int file = 0; file < m_ResourceMax; file++) {
		fileName[file] = vecFileName[file].c_str();
	}
	
	//�ǂݍ��ݏ����֐�.
	for (int ObjNum = 0; ObjNum < m_ResourceMax; ObjNum++) {
		Create(static_cast<T2>(ObjNum), fileName[ObjNum]);
	}

	//�z�񓮓I�m�ۂ������̂̉��.
	SAFE_DELETE_ARRAY(fileName);

	return S_OK;
}

//=======================================.
//		����Ăяo�������֐�.
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
//		���擾�����֐�.
//=======================================.
template<class T1, class T2>
T1* CObjectResource<T1, T2>::GetMeshObject(T2 enObjectInof)
{
	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_ObjectRange(enObjectInof))) {
		return nullptr;
	}

	//���f�����Ȃ���ΏI��.
	if (m_ppCObject[static_cast<int>(enObjectInof)] == nullptr) {
		return nullptr;
	}

	return m_ppCObject[static_cast<int>(enObjectInof)];
}

//=======================================.
//		�쐬�����֐�.
//=======================================.
template<class T1, class T2>
HRESULT CObjectResource<T1, T2>::Create(T2 enObjectInfo, const char* pFileName) 
{
	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_ObjectRange(enObjectInfo))) {
		return E_FAIL;
	}

	//���f�������ɂ���ꍇ�͏I��.
	if (m_ppCObject[static_cast<int>(enObjectInfo)] != nullptr) {
		return E_FAIL;
	}

	//���f���̓ǂݍ���.
	m_ppCObject[static_cast<int>(enObjectInfo)] = new T1();
	if (FAILED(m_ppCObject[static_cast<int>(enObjectInfo)]->Init(m_hWnd, m_pDevice9, m_pDevice11, m_pContext11, pFileName))) {
		return E_FAIL;
	}

	return S_OK;
}

//=======================================.
//		��������֐�.
//=======================================.
template<class T1, class T2>
HRESULT CObjectResource<T1, T2>::Release(T2 enObjectInfo)
{
	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_ObjectRange(enObjectInfo))) {
		return E_FAIL;
	}

	//���f����������ΏI��.
	if (m_ppCObject[static_cast<int>(enObjectInfo)] == nullptr) {
		return S_OK;
	}

	//�������.
	m_ppCObject[static_cast<int>(enObjectInfo)]->Release();
	SAFE_DELETE(m_ppCObject[static_cast<int>(enObjectInfo)]);

	return S_OK;
}

//=======================================.
//		�͈͊m�F�����֐�.
//=======================================.
template<class T1, class T2>
HRESULT CObjectResource<T1, T2>::Check_ObjectRange(T2 enObjectInfo)
{
	//�͈͊O�Ȃ�I��.
	if (static_cast<int>(enObjectInfo) < 0 || m_ResourceMax <= static_cast<int>(enObjectInfo)) {
		return E_FAIL;
	}

	return S_OK;
}

template class CObjectResource<CDX9Mesh, enStaticMeshType>;
template class CObjectResource<CDX9SkinMesh, enSkinMeshType>;