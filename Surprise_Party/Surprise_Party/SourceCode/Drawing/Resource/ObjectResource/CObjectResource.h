#ifndef COBJECT_RESOURCE_H
#define COBJECT_RESOURCE_H

#include "..\CResourceBase.h"

#include "CObjectResourceInfo.h"
#include "..\..\Object\CDX9Mesh\CDX9Mesh.h"
#include "..\..\Object\CDX9SkinMesh\CDX9SkinMesh.h"

#include <tuple>

/*************************************
*	�I�u�W�F�N�g�n�̓ǂݍ��݃N���X.
*************/
template <class T1, class T2>
class CObjectResource
	: public CResourceBase
{
public:
	CObjectResource();
	~CObjectResource();

	//================�֐�==================//.
	HRESULT Init(int max);															//�����������֐�.
	HRESULT Load(std::vector<std::tuple<std::string, bool>> tStringFlag);			//�ǂݍ��ݏ����֐�.
	HRESULT ReleaseCalling();														//����Ăяo�������֐�.

	//=============���擾�����֐�=========//.
	T1*	GetMeshObject(T2 enObjectInfo);	
private:
	//================�֐�==================//.
	HRESULT Create(T2 enObjectInfo, const char* pFileName, const bool& bSpotLight);	//�쐬�����֐�.
	HRESULT Release(T2 enObjectInfo);												//��������֐�.
	HRESULT Check_ObjectRange(T2 enObjectInfo);										//�͈͊m�F�����֐�.

	//================�ϐ�==================//.
	T1**	m_ppCObject;	//�I�u�W�F�N�g.

};

#endif	//#ifndef COBJECT_RESOURCE_H.