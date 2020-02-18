#ifndef CCHARA_UI_H
#define CCHARA_UI_H

#include "..\CMapUI.h"

/**********************************
*		�L�����N�^�[UI�N���X.
*******/
class CCharaUI
	: public CMapUI
{
public:
	CCharaUI();
	virtual ~CCharaUI();

	//====================�萔=========================//.
	const float		MAP_DISTANCE_MAX = 1280.0f;							//�}�b�v�̍ő�l.

	//====================�֐�=========================//.
	virtual void UpDate() = 0;

	//===========���u�������֐�==============//.
	//�L�����N�^�̍��W�擾�����֐�.
	void SetCharaPos(const D3DXVECTOR3& vPos) { m_vCharaPos = vPos; }
	//�X�e�[�W�ő吔�擾.
	void SetStageMax(const float& fStageMax) { m_fStageMax = fStageMax; }

protected:
	//====================�֐�==========================//.
	void GameMapConversion();			//�Q�[��������}�b�v���ɍ��W�ϊ������֐�.

	//=================�ϐ�====================//.
	D3DXVECTOR3		m_vCharaPos;		//�L�����N�^�̍��W.
	float			m_fStageMax;		//�X�e�[�W�ő�l.

};

#endif	//#ifndef CCHARA_UI_H.