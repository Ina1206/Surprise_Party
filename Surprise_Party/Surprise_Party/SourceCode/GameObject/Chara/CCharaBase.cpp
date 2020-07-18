#include "CCharaBase.h"

/*************************************************
*		キャラクタ基底クラス.
******/
CCharaBase::CCharaBase()
	: m_pCFileResource	(nullptr)
{
	m_pCFileResource = CFileResource::GetResourceInstance();
}

CCharaBase::~CCharaBase()
{

}