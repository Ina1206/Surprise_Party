#ifndef CENDING_STAGE_BASE_H
#define CENDING_STAGE_BASE_H

#include "..\..\GameObject\Chara\Ghost\BigGhost\CBigGhost.h"

/*******************************************
*		�G���f�B���O�X�e�[�W���N���X.
*****************/
class CEndingStageBase
{
public:
	CEndingStageBase();
	virtual ~CEndingStageBase();

	//========================�֐�=============================//.
	virtual void Update() = 0;	//�X�V�����֐�.
	virtual void Render() = 0;	//�`�揈���֐�.

protected:
	//========================�֐�=============================//.
	virtual void Init() = 0;	//�����������֐�.
	virtual void Release() = 0;	//��������֐�.

	//========================�ϐ�=============================//.
	std::unique_ptr<CBigGhost>	m_pCBigGhost;	//�r�b�O�S�[�X�g�N���X.

private:


};

#endif	//#ifndef CENDING_STAGE_BASE_H.