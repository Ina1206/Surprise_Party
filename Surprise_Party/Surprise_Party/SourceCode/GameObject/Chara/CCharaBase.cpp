#include "CCharaBase.h"

/*************************************************
*		�L�����N�^���N���X.
******/
CCharaBase::CCharaBase()
	: m_pCFileResource	(nullptr)
{
	m_pCFileResource = CFileResource::GetResourceInstance();
}

CCharaBase::~CCharaBase()
{

}