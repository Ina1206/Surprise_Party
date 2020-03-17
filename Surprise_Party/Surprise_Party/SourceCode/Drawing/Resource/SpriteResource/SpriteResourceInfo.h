#ifndef SPRITE_RESOURCE_INFO_H
#define SPRITE_RESOURCE_INFO_H

//�������\����(float�^).
struct WHSIZE_FLOAT
{
	float w;
	float h;
	float z;

	WHSIZE_FLOAT()
		: w(0.0f)
		, h(0.0f)
		, z(0.0f)
	{}
};

//�X�v���C�g���̍\����.
struct SPRITE_STATE
{
	WHSIZE_FLOAT	Disp;	//�\��������.
	WHSIZE_FLOAT	Base;	//���摜������.
	WHSIZE_FLOAT	Stride;	//1�R�}������̕�����.
};

//�X�v���C�g��ނ̗񋓑�.
enum class enSprite
{
	Cursol = 0,						//�J�[�\��.
	ActSelection,					//�s���I��.
	ActMoveString,					//�ړ�����.
	ActRestString,					//�x�e����.
	Bubble,							//�A.
	SleepZ,							//������z
	Swet,							//��.

	Strenght_Icon,					//�̗̓A�C�R��.
	eight_part_note,				//8������.
	sixteen_part_note,				//16������.

	Max,
	Start,
	SingleSpriteMax = Strenght_Icon,//�P�̃X�v���C�g�ő吔.
};

//�X�v���C�gUI��ނ̗񋓑�.
enum class enSpriteUI
{
	StageMap = 0,					//�X�e�[�W�}�b�v.
	Girl_Icon,						//���̎q�̃A�C�R��.
	Boy_Icon,						//�j�̎q�̃A�C�R��.
	DispGimmick_Iccon,				//�����M�~�b�N�A�C�R��.
	Switch_Icon,					//�X�C�b�`�A�C�R��.
	ButtonPush,						//�{�^���������Ƃ�.
	ClosedString,					//�X�܂ł̕���.
	GageGround,						//�Q�[�W�̉��n.
	Gage,							//�Q�[�W.
	ThankYouStamp,					//�������n���R.
	Shutter,						//�V���b�^�[.
	BlackCurtain,					//���J�[�e��.
	SignBoard,						//�Ŕ�.
	PreparingString,				//����������.
	OpenString,						//Open����.
	CloseString,					//Close����.
	ExtendedNotification,			//�����ʒm.

	Ghost_Icon,						//�������A�C�R��.
	Time,							//����.
	TreeBord,						//�؂̔�.

	Max,							//�ő吔.
	Start,							//�J�n.
	SingleSpriteMax = Ghost_Icon,	//�P�̂̃X�v���C�g�ő吔.
};

#endif //#ifndef SPRITE_RESOURCE_INFO_H