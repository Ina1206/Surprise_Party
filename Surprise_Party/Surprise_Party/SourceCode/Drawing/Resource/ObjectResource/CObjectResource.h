#ifndef COBJECT_RESOURCE_H
#define COBJECT_RESOURCE_H

#include "..\CResourceBase.h"

#include "CObjectResourceInfo.h"
#include "..\..\Object\CDX9Mesh\CDX9Mesh.h"
#include "..\..\Object\CDX9SkinMesh\CDX9SkinMesh.h"

/*************************************
*	オブジェクト系の読み込みクラス.
*************/
template <class T1, class T2>
class CObjectResource
	: public CResourceBase
{
public:
	CObjectResource();
	~CObjectResource();

	//================関数==================//.
	HRESULT Init(int max);									//初期化処理関数.
	HRESULT Load(std::vector<std::string> vecFileName);		//読み込み処理関数.
	HRESULT ReleaseCalling();								//解放呼び出し処理関数.

	//=============情報取得処理関数=========//.
	T1*	GetMeshObject(T2 enObjectInfo);	
private:
	//================関数==================//.
	HRESULT Create(T2 enObjectInfo, const char* pFileName);	//作成処理関数.
	HRESULT Release(T2 enObjectInfo);						//解放処理関数.
	HRESULT Check_ObjectRange(T2 enObjectInfo);			//範囲確認処理関数.

	//================変数==================//.
	T1**	m_ppCObject;	//オブジェクト.

};

#endif	//#ifndef COBJECT_RESOURCE_H.