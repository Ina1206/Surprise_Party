#ifndef CENDING_STAGE_BASE_H
#define CENDING_STAGE_BASE_H

#include "..\..\GameObject\Chara\Ghost\BigGhost\CBigGhost.h"
#include "..\..\GameObject\Object\StaticObject\Floor\CFloor.h"
#include "..\..\GameObject\Object\StaticObject\Light\BackstageLight\CBackstageLight.h"

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
	std::unique_ptr<CBigGhost>			m_pCBigGhost;		//�r�b�O�S�[�X�g�N���X.
	std::unique_ptr<CFloor>				m_pCFloor;			//���N���X.
	std::unique_ptr<CBackstageLight>	m_pCBackstageLight;	//���䗠���C�g�N���X.

private:
	//========================�֐�=============================//.
	void InitCommonValue();		//���ʒl�̏����������֐�.


};

#endif	//#ifndef CENDING_STAGE_BASE_H.