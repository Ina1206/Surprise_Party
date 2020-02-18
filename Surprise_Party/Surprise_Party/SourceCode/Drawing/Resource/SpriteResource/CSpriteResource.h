#ifndef CSPRITE_RESOURCE_H
#define CSPRITE_RESOURCE_H

#include "..\..\Sprite\Sprite\CSprite.h"
#include "..\..\Sprite\SpriteUI\CSpriteUI.h"
#include "..\..\..\Global.h"
#include "..\CResourceBase.h"

/***********************************************
*		�X�v���C�g�n�N���X.
**/
template <class Sprite, class SpriteType>
class CSprite_Resource
	: public CResourceBase
{
public:
	CSprite_Resource();
	~CSprite_Resource();

	//===============�֐�==================//.
	HRESULT Init(int max);								//�����������֐�.
	HRESULT Load(std::vector<std::string> vecFileName);	//�ǂݍ��ݏ����֐�.
	HRESULT ReleaseCalling();							//����Ăяo�������֐�.

	//==========���l�������֐�============//.
	Sprite* GetSprite(SpriteType enSprite);		//�X�v���C�g�n�N���X�̃A�h���X.

	//==========���u�������֐�============//.
	void	SetSpriteState(SPRITE_STATE* stSpriteState) { m_pSpriteState = stSpriteState; }
	
private:
	//===============�֐�=================//.
	HRESULT Create(SpriteType enSprite, const char* pfileName);	//�쐬�����֐�.
	HRESULT Release(SpriteType enSprite);						//��������֐�.
	HRESULT Check_SpriteRange(SpriteType enSprite);				//�X�v���C�g�͈̔͂��m�F�����֐�.

	//===============�ϐ�=================//.
	Sprite**		m_ppSprite;			//�X�v���C�g�n�N���X.
	SPRITE_STATE*	m_pSpriteState;		//�X�v���C�g�n�̃X�e�[�^�X�\����.

};

#endif	//#ifndef CSPRITE_RESOURCE_H.