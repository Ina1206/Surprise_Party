#ifndef CFRONTSTAGE_LIGHT_H
#define CFRONTSTAGE_LIGHT_H

#include "..\CLightBase.h"

/*********************************
*		�\����̃��C�g�N���X.
*************/
class CFrontstageLight
	: public CLightBase
{
public:
	CFrontstageLight();
	~CFrontstageLight();

	//======================�֐�========================//.
	void Update();										//�X�V�����֐�.
	void SettingAllLightPos(const float& fDistance);	//�S�Ẵ��C�g�̍��W�ݒ菈���֐�.

	//================���u�������֐�==================//.
	void SetCameraPos(const D3DXVECTOR3& vCameraPos) { m_vCameraPos = vCameraPos; }

private:
	//======================�֐�========================//.
	void Init();										//�����������֐�.
	void Release();										//��������֐�.

	//======================�ϐ�========================//.
	std::vector<D3DXVECTOR3>	m_vLightPos;			//���C�g�������W.
	D3DXVECTOR3					m_vCameraPos;			//�J�������W.
};

#endif	//#ifndef CFRONTSTAGE_LIGHT_H.