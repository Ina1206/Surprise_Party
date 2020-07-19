#ifndef CSCENE_BASE_H
#define CSCENE_BASE_H

#include "..\..\Global.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/************************************
*		�V�[�����N���X.
*****/
class CSceneBase
{
public:
	CSceneBase();
	virtual ~CSceneBase();

	//===================�萔======================//.
	const D3DXVECTOR4	BACK_COLOR	= D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);	//�w�i�̐F.


	//===================�֐�======================//.
	void	RenderInitSetting(const D3DXMATRIX& mProj);						//�`�揉���ݒ�.

	virtual void UpDate()	= 0;											//�X�V�����֐�.
	virtual void Render()	= 0;											//�`�揈���֐�.
	void PlayBGM(const enBGMType& enBGMType);								//BGM�Đ������֐�.

	//=============���l�������֐�================//.
	D3DXVECTOR4 GetBackColor()		{ return m_vBackColor; }				//���̐F���擾�����֐�.
	bool		GetChangeSceneFlag(){ return m_bChangeScene; }				//�V�[���ύX�t���O�擾�����֐�.
	bool		GetPauseFlag() const { return m_bPauseFlag; }				//�ꎞ��~�t���O.
	int			GetEvaluation() const { return m_Evaluation; }				//�]��.
	bool		GetTitleFlag() const { return m_bTitle; }					//�^�C�g���t���O.
	bool		GetChangeVolume() const { return m_bChangeVolume; }			//�O���ŉ��ʕύX�t���O.

	//=============���u�������֐�================//.
	void SetPauseFlag(const bool& flag) { m_bPauseFlag = flag; }			//�ꎞ��~�t���O.
	void SetEvaluation(const int& Num) { m_Evaluation = Num; }				//�]��.
	void SetPlayBGM(const enBGMType& enBGM) { m_enPlayBGMType = enBGM; }	//�Đ�BGM�̎��.
	void SetBGMVolume(const int& Volume); 									//����.
	void SetTitleFlag(const bool& bFlag) { m_bTitle = bFlag; }				//�^�C�g���t���O.
protected:
	//===================�֐�======================//.
	virtual void Init()		= 0;											//�����������֐�.
	virtual void Release()	= 0;											//��������֐�.

	//===================�ϐ�======================//.
	D3DXMATRIX	m_mView;													//�r���[�s��.
	D3DXMATRIX	m_mProj;													//�v���W�F�N�V�����s��.
	bool		m_bChangeScene;												//�V�[���ύX�t���O.
	bool		m_bPauseFlag;												//�ꎞ��~�t���O.
	int			m_Evaluation;												//�]��.
	bool		m_bTitle;													//�^�C�g���փt���O.
	int			m_BGMVolume;												//BGM�̉���.
	enBGMType	m_enPlayBGMType;											//�Đ�BGM�̎��.
	bool		m_bChangeVolume;											//�O���ŉ��ʕύX�t���O.
private:
	//===================�ϐ�======================//.
	D3DXVECTOR4 m_vBackColor;												//���̐F.

};

#endif	//#ifndef CSCENE_BASE_H.