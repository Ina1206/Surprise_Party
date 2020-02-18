#ifndef CGHOST_ICON_H
#define CGHOST_ICON_H

#include "..\CIcon.h"

/*************************************
*		�������p�A�C�R���N���X.
*******/
class CGhostIcon
	: public CIcon
{
public:
	CGhostIcon();
	~CGhostIcon();

	//=======================�񋓑�=========================//.
	enum class enFaceType {
		Bad_Face = 0,	//�����Ƃ��̊�.
		Normal_Face,	//�ʏ펞�̊�.
		Good_Face,		//�ǂ��Ƃ��̊�.
		Great_Face,		//���C�Ȏ��̊�.

		Max,			//�ő吔.
	};

	//========================�萔==========================//.
	const D3DXVECTOR2	SELECTED_FACE		= D3DXVECTOR2(0.0f, 1.0f);			//�I�𒆂̊�.
	const D3DXVECTOR2	REST_FACE			= D3DXVECTOR2(2.0f, 1.0f);			//�x�e���̊�.
	const D3DXVECTOR2	GREAT_FACE			= D3DXVECTOR2(1.0f, 0.0f);			//���C�Ȏ��̊�.
	const D3DXVECTOR2	GOOD_FACE			= D3DXVECTOR2(0.0f, 0.0f);			//�ǂ��Ƃ��̊�.
	const D3DXVECTOR2	NORMAL_FACE			= D3DXVECTOR2(1.0f, 2.0f);			//�ʏ펞�̊�.
	const D3DXVECTOR2	BAD_FACE			= D3DXVECTOR2(0.0f, 2.0f);			//�������̊�.
	const float			STRENGTH_FACE_MAX	= static_cast<int>(enFaceType::Max);//�̗͕\��ő吔.

	//========================�֐�==========================//.
	void UpDate();		//�X�V�����֐�.

	//===================���u�������֐�===================//.
	//�̗�.
	void SetStrength(const float& fStrength) { m_fStrength = fStrength; }
	//�̗͍ő�l.
	void SetStrengthMax(const float& fStrength) { m_fStrengthMax = fStrength; }
	//�x�e�t���O.
	void SetRestFlag(const bool& bFlag) { m_RestFlag = bFlag; }

	//===================���擾�����֐�====================//.
	//�\����.
	int GetFaceType() { return m_FaceType; }

private:
	//========================�֐�==========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void ChangeFace();	//�\��ύX�����֐�.

	//========================�ϐ�==========================//.
	float			m_fStrength;		//�̗�.
	float			m_fStrengthMax;		//�̗͍ő�l.
	int				m_FaceType;			//�\����.
	bool			m_RestFlag;			//�x�e�t���O.
};

#endif	//#ifndef CGHOST_ICON_H.