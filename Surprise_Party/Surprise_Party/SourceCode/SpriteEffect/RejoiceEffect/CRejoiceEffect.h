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
		YellowEightPartNote = 0,	//���F8������.
		BlueEightPartNote,			//��8������.
		PinkFlower,					//�s���N�̉�.
		RedFlower,					//�̉�.

		Max,						//�ő吔.
		Start = YellowEightPartNote,//�J�n.
	};

	//====================�萔========================//.
	const int	SPRITE_MAX			= 8;											//�X�v���C�g�ő吔.
	const int	SPRITE_TYPE_MAX		= static_cast<int>(enRejoiceSpriteType::Max);	//�X�v���C�g�̎�ލő吔.
	const int	POP_MAX				= SPRITE_MAX / 2;								//�o���ő吔.

	const int	DISP_TIME_DELIMITER	= 30;											//�\����؂莞��.
	const int	DISP_DELIMITER_MAX	= 2;											//�\����؂�ő吔.
	
	const float	MOVE_SPEED			= 0.04f;										//�ړ����x.
	const float	START_ANGLE			= 30.0f;										//�J�n�p�x.
	const float	ANGLE_WIDTH			= 250.0f;										//�p�x��.

	const float	ALPHA_SPEED			= 0.02f;										//���ߑ��x.
	const float	SCALING_SPEED		= 0.02f;										//�g�k���x.

	const D3DXVECTOR2	YELLOW_NOTE = D3DXVECTOR2(0.0f, 2.0f);						//���F�̉����ʒu.
	const D3DXVECTOR2	BLUE_NOTE	= D3DXVECTOR2(2.0f, 0.0f);						//�F�̉����ʒu.
	const D3DXVECTOR2	PINK_FLOWER = D3DXVECTOR2(0.0f, 0.0f);						//�s���N�F�̉Ԉʒu.
	const D3DXVECTOR2	RED_FLOWER	= D3DXVECTOR2(1.0f, 1.0f);						//�ԐF�̉Ԉʒu.

	//====================�֐�========================//.
	void Update();							//�X�V�����֐�.

private:
	//====================�֐�========================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void AppeartJudgement(const int& num);	//�\�����菈���֐�.
	void Move(const int& num);				//�ړ������֐�.
	void LinkSprite(const int& num);		//�X�v���C�g�R�Â������֐�.

	//====================�ϐ�=========================//.
	int					m_DispCnt;			//�\���J�E���g.
	int					m_PopCnt;			//�o���J�E���g.
	std::vector<float>	m_fDistance;		//����.
};

#endif	//#ifndef CREJICE_EFFECT_H.