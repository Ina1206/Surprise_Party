#include "CCharaBase.h"

CCharaBase::CCharaBase()
	: m_pCFileResource	(nullptr)
{
	m_pCFileResource = CFileResource::GetResourceInstance();
}

CCharaBase::~CCharaBase()
{

}