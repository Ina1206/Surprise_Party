#ifndef CBOY_H
#define CBOY_H

#include "..\CPeopleBase.h"

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

	//=================�֐�===================//.
	void UpDate();		//�X�V�����֐�.
	
private:
	//=================�֐�===================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

};

#endif	//#ifndef CBOY_H.