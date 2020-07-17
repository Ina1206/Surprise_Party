#ifndef CBOY_H
#define CBOY_H

#include "..\CPeopleBase.h"

/************************************
*	�j�̎q�N���X.
**********/
class CBoy
	: public CPeopleBase
{
public:
	CBoy();
	~CBoy();
	//================�񋓑�==================//.
	//�A�j���[�V����.
	enum class enBoyAnim {
		Walk,		//���s.
		Stand,		//����.
		Surprise,	//����.
	};

	//=================�萔===================//.
	const float	DEPTH_POS = -2.0f;	//���s���̍��W.

	//=================�֐�===================//.
	void Update();		//�X�V�����֐�.
	
private:
	//=================�֐�===================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

};

#endif	//#ifndef CBOY_H.