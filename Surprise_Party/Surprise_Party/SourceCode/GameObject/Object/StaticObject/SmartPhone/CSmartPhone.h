#ifndef CSMART_PHONE_H
#define CSMART_PHONE_H

#include "..\CStaticObjectBase.h"

/********************************************
*		�X�}�[�g�t�H���N���X
*************/
class CSmartPhone
	: public CStaticObjectBase
{
public:
	CSmartPhone();
	~CSmartPhone();

	//========================�񋓑�=============================//.
	//�s�����.
	enum class enMoveType {
		SeenGhsot,		//�������Ɍ����Ă��鎞.
		Drop,			//������
	};

	//=========================�֐�==============================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

	

private:
	//=========================�֐�==============================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//=========================�ϐ�==============================//.
	D3DXVECTOR2	m_vUV;	//UV���W.

};

#endif	//#ifndef CSMART_PHONE_H.