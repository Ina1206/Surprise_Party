#ifndef CCHARA_BASE_H
#define CCHARA_BASE_H

#include "..\CGameObject.h"
#include "..\..\Drawing\Resource\CResourceManager.h"
#include "..\..\FileLoad\FileResource\CFileResource.h"

/*************************************************
*		�L�����N�^���N���X.
******/
class CCharaBase
	: public CGameObject
{
public:
	CCharaBase();
	virtual ~CCharaBase();

	//====================�񋓑�=======================//.
	//�L�����N�^���.
	enum class enCharacterType {
		Ghost = 0,		//������.
		Human,			//�l.

		Max,			//�ő�l.
		Start = Human,	//�J�n�l.
	};

protected:
	//=====================�ϐ�========================//.
	CFileResource*		m_pCFileResource;	//�t�@�C���ǂݍ��݃N���X.

private:

};

#endif	//#ifndef CCHARA_BASE_H.