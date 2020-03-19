#ifndef CREJICE_EFFECT_H
#define CREJICE_EFFECT_H

#include "..\CSpriteEffectBase.h"

/*********************************************
*		��уG�t�F�N�g.
*********/
class CRejoiceEffect
	: public CSpriteEffectBase
{
public:
	CRejoiceEffect();
	~CRejoiceEffect();

	//===================�񋓑�=======================//.
	//�X�v���C�g�̎��.
	enum class enRejoiceSpriteType {
		PinkEightPartNote = 0,		//�s���N8������.
		BlueEightPartNote,			//��8������.
		PinkFlower,					//�s���N�̉�.
		RedFlower,					//�̉�.

		Max,						//�ő吔.
		Start = PinkEightPartNote,	//�J�n.
	};

	//====================�萔========================//.
	const int	SPRITE_MAX		= 10;											//�X�v���C�g�ő吔.
	const int	SPRITE_TYPE_MAX = static_cast<int>(enRejoiceSpriteType::Max);	//�X�v���C�g�̎�ލő吔.


	//====================�֐�========================//.
	void Update();							//�X�V�����֐�.

private:
	//====================�֐�========================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void AppeartJudgement(const int& num);	//�\�����菈���֐�.
	void Move(const int& num);				//�ړ������֐�.
	void LinkSprite(const int& num);		//�X�v���C�g�R�Â������֐�.


};

#endif	//#ifndef CREJICE_EFFECT_H.