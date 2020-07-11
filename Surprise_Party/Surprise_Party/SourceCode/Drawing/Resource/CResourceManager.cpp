#include "CResourceManager.h"

CResourceManager::CResourceManager()
	: m_pCSprite			(nullptr)
	, m_pCSpriteUI			(nullptr)
	, m_pCStaticMesh		(nullptr)
	, m_pCSkinMesh			(nullptr)
	, m_pCEffect			(nullptr)
	, m_pCFont				(nullptr)
	, m_vSpriteFileName		()
	, m_vSpriteUIFileNmae	()
	, m_vStaticMeshFileName	()
	, m_vSkinMeshFileName	()
	, m_bUseSpotLightFlag	()
	, m_pstSpriteState		(nullptr)
	, m_pstSpriteUIState	(nullptr)
{
	m_pstSpriteState = new SPRITE_STATE[static_cast<int>(enSprite::Max)]();
	m_pstSpriteUIState = new SPRITE_STATE[static_cast<int>(enSpriteUI::Max)]();
}

CResourceManager::~CResourceManager()
{
}

//==========================================.
//		�ǂݍ��ݏ����֐�.
//==========================================.
HRESULT CResourceManager::Load(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	//�X�v���C�g�t�@�C�����ݒ菈���֐�.
	SpriteFileNameSetting();
	//�X�v���C�gUI�t�@�C�����ݒ菈���֐�.
	SpriteUIFileNameSetting();
	//�X�^�e�B�b�N���b�V���̃t�@�C�����ݒ菈���֐�.
	StaticMeshFileNmaeSetting();
	//�X�L�����b�V���̃t�@�C�����ݒ菈���֐�.
	SkinMeshFileNameSetting();

	//�X�v���C�g���\���̐ݒ菈���֐�.
	SpriteStateSetting();
	//�X�v���C�gUI���\���̐ݒ菈���֐�.
	SpriteUIStateSetting();

	//�X�v���C�g�N���X.
	m_pCSprite.reset(new CSprite_Resource<CSprite, enSprite>());
	//�����l�ݒ菈��.
	m_pCSprite->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//����������.
	m_pCSprite->Init(static_cast<int>(enSprite::Max));
	//�X�v���C�g���\���̐ݒ�.
	m_pCSprite->SetSpriteState(m_pstSpriteState);
	//�ǂݍ��ݏ���.
	m_pCSprite->Load(m_vSpriteFileName);

	//�X�v���C�gUI�N���X.
	m_pCSpriteUI.reset(new CSprite_Resource<CSpriteUI, enSpriteUI>());
	//�����l�ݒ菈��.
	m_pCSpriteUI->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//����������.
	m_pCSpriteUI->Init(static_cast<int>(enSpriteUI::Max));
	//�X�v���C�gUI���\���̐ݒ�.
	m_pCSpriteUI->SetSpriteState(m_pstSpriteUIState);
	//�ǂݍ��ݏ���.
	m_pCSpriteUI->Load(m_vSpriteUIFileNmae);

	//�X�^�e�B�b�N���b�V��.
	m_pCStaticMesh.reset(new CObjectResource<CDX9Mesh, enStaticMeshType>());
	//�����l�ݒ�.
	m_pCStaticMesh->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//����������.
	m_pCStaticMesh->Init(static_cast<int>(enStaticMeshType::Max));
	//�ǂݍ��ݏ���.
	m_pCStaticMesh->Load(m_tStaticMesh);
	//m_pCStaticMesh->Load(m_vStaticMeshFileName);
	//�����蔻��p�X�t�B�A�쐬�����֐�.
	if (FAILED(InitSphere())) {
		_ASSERT_EXPR(false, L"�����蔻��p�X�t�B�A�쐬���s");
		return E_FAIL;
	}

	//�X�L�����b�V��.
	m_pCSkinMesh.reset(new CObjectResource<CDX9SkinMesh, enSkinMeshType>());
	//�����l�ݒ菈��.
	m_pCSkinMesh->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//����������.
	m_pCSkinMesh->Init(static_cast<int>(enSkinMeshType::Max));
	//�ǂݍ��ݏ���.
	m_pCSkinMesh->Load(m_tSkinMesh);

	//�G�t�F�N�g.
	m_pCEffect.reset(new CResourceEffect());
	m_pCEffect->Init(hWnd, pDevice11, pContext11);
	m_pCEffect->LoadEffect();

	//�t�H���g.
	m_pCFont.reset(new CFontResource());
	//�����������֐�.
	m_pCFont->Init(pDevice11, pContext11);

	return S_OK;
}

//=======================================.
//		��������֐�.
//=======================================.
HRESULT CResourceManager::Release()
{
	//����Ăяo�������֐�.
	m_pCSkinMesh->ReleaseCalling();		//�X�L�����b�V��.
	m_pCStaticMesh->ReleaseCalling();	//�X�^�e�B�b�N���b�V��.
	m_pCSpriteUI->ReleaseCalling();		//�X�v���C�gUI.
	m_pCSprite->ReleaseCalling();		//�X�v���C�g.

	SAFE_DELETE_ARRAY(m_pstSpriteUIState);
	SAFE_DELETE_ARRAY(m_pstSpriteState);

	return S_OK;
}

//==================================================.
//	�X�^�e�B�b�N���b�V���̃t�@�C�����ݒ菈���֐�.
//==================================================.
void CResourceManager::StaticMeshFileNmaeSetting()
{
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Wall\\Wall.x",				true));	//��.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Floor\\Flor.X",				true));	//��.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Painting\\e.X",				true));	//�G��.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\BookShelf\\BookShelf.x",		true));	//�{�I.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\UpDownFloor\\UpDownFloor.X", true));	//�I�u�W�F�N�g�ړ��X�C�b�`.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Switch\\Switch.X",			true));	//������X�C�b�`.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Ghost\\gost_a.X",			true));	//�X�C�b�`������������.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Phone\\phone.X",				false));//�g��.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\HitSphere\\Sphere.x",		true));	//�����蔻��p�X�t�B�A.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\Table\\Round table.X",		true));	//��.
	m_tStaticMesh.push_back(std::make_tuple("Data\\Object\\StaticMesh\\VaseFlowar\\vase_flower.X",	true));	//�ԕr.
}

//=================================================.
//	�X�L�����b�V���̃t�@�C�����ݒ菈���֐�.
//=================================================.
void CResourceManager::SkinMeshFileNameSetting()
{
	m_tSkinMesh.push_back(std::make_tuple("Data\\Object\\SkinMesh\\People\\Sayaka\\Sayaka_s.X",		true));	//���̎q.
	m_tSkinMesh.push_back(std::make_tuple("Data\\Object\\SkinMesh\\People\\Towa\\Towa_s.X",			true));	//�j�̎q.
	m_tSkinMesh.push_back(std::make_tuple("Data\\Object\\SkinMesh\\Ghost\\GhostB\\GhostB_s.X",		true));	//����邨����.
	m_tSkinMesh.push_back(std::make_tuple("Data\\Object\\SkinMesh\\Ghost\\BigGhost\\BigGhost_s.X",	true));	//�傫��������.
}

//=================================================.
//	�X�v���C�g�̃t�@�C�����ݒ菈���֐�.
//=================================================.
void CResourceManager::SpriteFileNameSetting()
{
	m_vSpriteFileName = {
		"Data\\Texture\\UI\\Game\\CursorUp.png",			//�J�[�\��.
		"Data\\Texture\\UI\\Game\\Select.png",				//�s���I��.
		"Data\\Texture\\UI\\Game\\ActMoveString.png",		//�ړ�����.
		"Data\\Texture\\UI\\Game\\ActRestString.png",		//�x�e����.
		"Data\\Texture\\UI\\Game\\bubble.png",				//�A.
		"Data\\Texture\\UI\\Game\\Z.png",					//�����̂�.
		"Data\\Texture\\UI\\Game\\Swet.png",				//��.
		"Data\\Texture\\UI\\Game\\TextBoxSmall.png",		//�e�L�X�g�{�b�N�X��.
		"Data\\Texture\\UI\\Game\\AnswerNo.png",			//�u�������v�̉�.
		"Data\\Texture\\UI\\Game\\AnswerYes.png",			//�u�͂��v�̉�.
		"Data\\Texture\\UI\\Game\\shock.png",				//����.
		"Data\\Texture\\UI\\Game\\Wave.png",				//�g��.
		"Data\\Texture\\UI\\Game\\Smoke.png",				//��.
		"Data\\Texture\\UI\\Game\\QuestionMark.png",		//�͂Ăȃ}�[�N.
		"Data\\Texture\\UI\\Game\\HelthIcon.png",			//�̗̓A�C�R��.
		"Data\\Texture\\UI\\Game\\eight_part_note.png",		//8������.
		"Data\\Texture\\UI\\Game\\sixteen_part_note.png",	//16������.
		"Data\\Texture\\UI\\Game\\flower.png",				//��.
	};
}

//=================================================.
//	�X�v���C�gUI�̃t�@�C�����ݒ菈���֐�.
//=================================================.
void CResourceManager::SpriteUIFileNameSetting()
{
	m_vSpriteUIFileNmae = {
		"Data\\Texture\\UI\\Map\\Stage.png",							//�X�e�[�W�S�̂̃}�b�v.
		"Data\\Texture\\UI\\Map\\Girl_Icon.png",						//���̎q�̃A�C�R��.
		"Data\\Texture\\UI\\Map\\Boy_Icon.png",							//�j�̎q�̃A�C�R��.
		"Data\\Texture\\UI\\Map\\DispButton.png",						//�����{�^���A�C�R��.
		"Data\\Texture\\UI\\Map\\SwitchButton.png",						//�X�C�b�`�A�C�R��."
		"Data\\Texture\\UI\\Map\\PushButton.png",						//�{�^���������Ƃ�.
		"Data\\Texture\\UI\\Game\\TimeUpToClosed.png", 					//�X�܂ł̕���.
		"Data\\Texture\\UI\\Game\\Bar.png",								//�Q�[�W�̉��n.
		"Data\\Texture\\UI\\Game\\Blue_Bar.png",						//�Q�[�W.
		"Data\\Texture\\UI\\Game\\ThankYouStamp.png",					//�������n���R.
		"Data\\Texture\\UI\\Game\\Shutter.jpg",							//�V���b�^�[.
		"Data\\Texture\\UI\\Game\\BlackCurtain.jpg",					//���J�[�e��.
		"Data\\Texture\\UI\\Game\\SignBoard.png",						//�Ŕ�.
		"Data\\Texture\\UI\\Game\\PreparingString.png",					//����������.
		"Data\\Texture\\UI\\Game\\OpenString.png",						//Open����.
		"Data\\Texture\\UI\\Game\\CloseString.png",						//Close����.
		"Data\\Texture\\UI\\Game\\extended_notification.png",			//�����ʒm.
		"Data\\Texture\\UI\\Game\\TextBox.png",							//�e�L�X�g�{�b�N�X.
		"Data\\Texture\\UI\\Game\\SpeakCursor.png",						//���̉�b���̃J�[�\��.
		"Data\\Texture\\UI\\Game\\PauseTitle.png",						//�|�[�Y.
		"Data\\Texture\\UI\\Game\\ToGame.png",							//������.
		"Data\\Texture\\UI\\Game\\ToTitle.png",							//�I���.
		"Data\\Texture\\UI\\Game\\BigGhostIcon.png",					//�r�b�O�S�[�X�g�A�C�R��.
		"Data\\Texture\\UI\\Game\\DispPaintGhostComment.png",			//����邨�����R�����g.
		"Data\\Texture\\UI\\Game\\SwitchGhostComment.png",				//�X�C�b�`�������R�����g.
		"Data\\Texture\\UI\\Game\\Arrow.png",							//���.
		"Data\\Texture\\UI\\DescriptionBlack.png",						//�����p�����.
		"Data\\Texture\\UI\\Game\\WhiteScreen.png",						//�����.
		"Data\\Texture\\UI\\Game\\SNSCursor.png",						//SNS�p�J�[�\��.
		"Data\\Texture\\UI\\Game\\SNSPictureRest.png",					//SNS�p�̎ʐ^(�x�e).
		"Data\\Texture\\UI\\Game\\SNSPictureFlower.png",				//SNS�p�̎ʐ^(��).
		"Data\\Texture\\UI\\Game\\SNSPictureSurprise.png",				//SNS�p�̎ʐ^(����).
		"Data\\Texture\\UI\\Game\\PushEnter.png",						//PushEnter����,
		"Data\\Texture\\UI\\Game\\Start.png",							//�Q�[���J�n����.
		"Data\\Texture\\UI\\Game\\End.png",								//�I������.
		"Data\\Texture\\UI\\Map\\ShockingSign.png",						//�Ռ��I����.
		"Data\\Texture\\UI\\Game\\AutoString.png",						//�����Đ�����.
		"Data\\Texture\\UI\\Game\\Shout.png",							//����.
		"Data\\Texture\\UI\\Game\\SurpriseDegree.png",					//�������x.
		"Data\\Texture\\UI\\Map\\GhostIcon.png",						//�������̃A�C�R��.
		"Data\\Texture\\UI\\Game\\Time.png",							//����.
		"Data\\Texture\\UI\\Game\\TreeBord.png",						//�؂̔�.
		"Data\\Texture\\UI\\Game\\GhostCursor.png",						//�������J�[�\��.
		"Data\\Texture\\UI\\Game\\balloon.png",							//�����o��.
		"Data\\Texture\\UI\\Game\\Title.png",							//Title.
		"Data\\Texture\\UI\\Game\\HightEvaluationString.png",			//���]�����̕���.
		"Data\\Texture\\UI\\Game\\IntermediateEvaluationString.png",	//���ԕ]�����̕���.
		"Data\\Texture\\UI\\Game\\LowEvaluationString.png",				//��]�����̕���.
	};
}

//=================================================.
//	�X�v���C�g���\���̐ݒ菈���֐�.
//=================================================.
void CResourceManager::SpriteStateSetting()
{
	//�J�[�\��.
	int CursorNum = static_cast<int>(enSprite::Cursol);
	m_pstSpriteState[CursorNum].Base.w = 74.0f;
	m_pstSpriteState[CursorNum].Base.h = 73.0f;
	m_pstSpriteState[CursorNum].Disp.w = 1.0f;
	m_pstSpriteState[CursorNum].Disp.h = 1.0f;

	//�s���I��.
	int SelectionNum = static_cast<int>(enSprite::ActSelection);
	m_pstSpriteState[SelectionNum].Base.w = 256.0f;
	m_pstSpriteState[SelectionNum].Base.h = 256.0;
	m_pstSpriteState[SelectionNum].Disp.w = 5.0f;
	m_pstSpriteState[SelectionNum].Disp.h = 5.0f;

	//����.
	int MoveStringNum = static_cast<int>(enSprite::ActMoveString);
	for (int stringNum = MoveStringNum; stringNum <= static_cast<int>(enSprite::ActRestString); stringNum++) {
		m_pstSpriteState[stringNum].Base.w = 80.0f;
		m_pstSpriteState[stringNum].Base.h = 180.0f;
		m_pstSpriteState[stringNum].Disp.w = 1.6f;
		m_pstSpriteState[stringNum].Disp.h = 3.6f;
	}

	//�A.
	int BubbleNum = static_cast<int>(enSprite::Bubble);
	m_pstSpriteState[BubbleNum].Base.w = 350.0f;
	m_pstSpriteState[BubbleNum].Base.h = 350.0f;
	m_pstSpriteState[BubbleNum].Disp.w = 1.0f;
	m_pstSpriteState[BubbleNum].Disp.h = 1.0f;

	//������z.
	int SleepZNum = static_cast<int>(enSprite::SleepZ);
	m_pstSpriteState[SleepZNum].Base.w = 70.0f;
	m_pstSpriteState[SleepZNum].Base.h = 70.0f;
	m_pstSpriteState[SleepZNum].Disp.w = 1.0f;
	m_pstSpriteState[SleepZNum].Disp.h = 1.0f;

	//��.
	int SwetNum = static_cast<int>(enSprite::Swet);
	m_pstSpriteState[SwetNum].Base.w = 300.0f;
	m_pstSpriteState[SwetNum].Base.h = 300.0f;
	m_pstSpriteState[SwetNum].Disp.w = 1.0f;
	m_pstSpriteState[SwetNum].Disp.h = 1.0f;

	//�e�L�X�g�{�b�N�X��.
	int TextBoxSmallNum = static_cast<int>(enSprite::TextBoxSmall);
	m_pstSpriteState[TextBoxSmallNum].Base.w = 209.0f;
	m_pstSpriteState[TextBoxSmallNum].Base.h = 57.0f;
	m_pstSpriteState[TextBoxSmallNum].Disp.w = 4.0f;
	m_pstSpriteState[TextBoxSmallNum].Disp.h = 1.0f;

	//�u�������v�̉�.
	int AnswerNoNum = static_cast<int>(enSprite::AnswerNo);
	m_pstSpriteState[AnswerNoNum].Base.w = 220.0f;
	m_pstSpriteState[AnswerNoNum].Base.h = 70.0f;
	m_pstSpriteState[AnswerNoNum].Disp.w = 3.0f;
	m_pstSpriteState[AnswerNoNum].Disp.h = 1.0f;

	//�u�͂��v�̉�.
	int AnswerYesNum = static_cast<int>(enSprite::AnswerYes);
	m_pstSpriteState[AnswerYesNum].Base.w = 150.0f;
	m_pstSpriteState[AnswerYesNum].Base.h = 70.0f;
	m_pstSpriteState[AnswerYesNum].Disp.w = 2.0f;
	m_pstSpriteState[AnswerYesNum].Disp.h = 1.0f;

	//����.
	int ShockNum = static_cast<int>(enSprite::Shock);
	m_pstSpriteState[ShockNum].Base.w = 100.0f;
	m_pstSpriteState[ShockNum].Base.h = 200.0f;
	m_pstSpriteState[ShockNum].Disp.w = 0.5f;
	m_pstSpriteState[ShockNum].Disp.h = 1.0f;

	//�g��.
	int WaveNum = static_cast<int>(enSprite::Wave);
	m_pstSpriteState[WaveNum].Base.w = 80.0f;
	m_pstSpriteState[WaveNum].Base.h = 80.0f;
	m_pstSpriteState[WaveNum].Disp.w = 1.5f;
	m_pstSpriteState[WaveNum].Disp.h = 1.5f;

	//��.
	int SmokeNum = static_cast<int>(enSprite::Smoke);
	m_pstSpriteState[SmokeNum].Base.w = 200.0f;
	m_pstSpriteState[SmokeNum].Base.h = 200.0f;
	m_pstSpriteState[SmokeNum].Disp.w = 2.0f;
	m_pstSpriteState[SmokeNum].Disp.h = 2.0f;

	//�͂Ăȃ}�[�N.
	const int QuestionMark = static_cast<int>(enSprite::QuestionMark);
	m_pstSpriteState[QuestionMark].Base.w = 625.0f;
	m_pstSpriteState[QuestionMark].Base.h = 625.0f;
	m_pstSpriteState[QuestionMark].Disp.w = 2.0f;
	m_pstSpriteState[QuestionMark].Disp.h = 2.0f;

	//�܂Ƃ߂Ĉ�R�}������̃T�C�Y�w��.
	for (int sprite = 0; sprite < static_cast<int>(enSprite::SingleSpriteMax); sprite++) {
		m_pstSpriteState[sprite].Stride.w = m_pstSpriteState[sprite].Base.w;
		m_pstSpriteState[sprite].Stride.h = m_pstSpriteState[sprite].Base.h;
		m_pstSpriteState[sprite].Frame.w = 1;
		m_pstSpriteState[sprite].Frame.h = 1;
	}

	//�̗̓A�C�R��.
	int StrengthIconNum = static_cast<int>(enSprite::Strenght_Icon);
	m_pstSpriteState[StrengthIconNum].Base.w = 618.0f;
	m_pstSpriteState[StrengthIconNum].Base.h = 405.0f;
	m_pstSpriteState[StrengthIconNum].Frame.w = 6.0f;
	m_pstSpriteState[StrengthIconNum].Frame.h = 4.0f;
	m_pstSpriteState[StrengthIconNum].Stride.w = m_pstSpriteState[StrengthIconNum].Base.w / m_pstSpriteState[StrengthIconNum].Frame.w;
	m_pstSpriteState[StrengthIconNum].Stride.h = m_pstSpriteState[StrengthIconNum].Base.h / m_pstSpriteState[StrengthIconNum].Frame.h;
	m_pstSpriteState[StrengthIconNum].Disp.w = 1.0f;
	m_pstSpriteState[StrengthIconNum].Disp.h = 1.0f;

	//����.
	int NoteNum = static_cast<int>(enSprite::eight_part_note);
	for (int note = NoteNum; note <= static_cast<int>(enSprite::sixteen_part_note); note++) {
		m_pstSpriteState[note].Base.w = 1321.0f;
		m_pstSpriteState[note].Base.h = 1321.0f;
		m_pstSpriteState[note].Frame.w = 3.0f;
		m_pstSpriteState[note].Frame.h = 3.0f;
		m_pstSpriteState[note].Stride.w = m_pstSpriteState[note].Base.w / m_pstSpriteState[note].Frame.w;
		m_pstSpriteState[note].Stride.h = m_pstSpriteState[note].Base.h / m_pstSpriteState[note].Frame.w;
		m_pstSpriteState[note].Disp.w = 2.0f;
		m_pstSpriteState[note].Disp.h = 2.0f;
	}

	//��.
	int FlowerNum = static_cast<int>(enSprite::Flower);
	m_pstSpriteState[FlowerNum].Base.w = 960.0f;
	m_pstSpriteState[FlowerNum].Base.h = 960.0f;
	m_pstSpriteState[FlowerNum].Frame.w = 2.0f;
	m_pstSpriteState[FlowerNum].Frame.h = 2.0f;
	m_pstSpriteState[FlowerNum].Stride.w = m_pstSpriteState[FlowerNum].Base.w / m_pstSpriteState[FlowerNum].Frame.w;
	m_pstSpriteState[FlowerNum].Stride.h = m_pstSpriteState[FlowerNum].Base.h / m_pstSpriteState[FlowerNum].Frame.h;
	m_pstSpriteState[FlowerNum].Disp.w = 1.5f;
	m_pstSpriteState[FlowerNum].Disp.h = 1.5f;
}

//================================================.
//	�X�v���C�gUI���\���̐ݒ菈���֐�.
//================================================.
void CResourceManager::SpriteUIStateSetting()
{
	//�X�e�[�W�}�b�v.
	int StageMapNum = static_cast<int>(enSpriteUI::StageMap);
	m_pstSpriteUIState[StageMapNum].Base.w = 1280.0f;
	m_pstSpriteUIState[StageMapNum].Base.h = 180.0f;
	m_pstSpriteUIState[StageMapNum].Disp.w = 1280.0f;
	m_pstSpriteUIState[StageMapNum].Disp.h = 180.0f;

	//���̎q.
	int GirlIconNum = static_cast<int>(enSpriteUI::Girl_Icon);
	m_pstSpriteUIState[GirlIconNum].Base.w = 256.0f;
	m_pstSpriteUIState[GirlIconNum].Base.h = 256.0f;
	m_pstSpriteUIState[GirlIconNum].Disp.w = 64.0f;
	m_pstSpriteUIState[GirlIconNum].Disp.h = 64.0f;

	//�j�̎q.
	int BoyIconNum = static_cast<int>(enSpriteUI::Boy_Icon);
	m_pstSpriteUIState[BoyIconNum].Base.w = 256.0f;
	m_pstSpriteUIState[BoyIconNum].Base.h = 256.0f;
	m_pstSpriteUIState[BoyIconNum].Disp.w = 64.0f;
	m_pstSpriteUIState[BoyIconNum].Disp.h = 64.0f;

	//�M�~�b�N.
	int GimmickStartNum = static_cast<int>(enSpriteUI::DispGimmick_Iccon);
	for (int gimmick = GimmickStartNum; gimmick <= static_cast<int>(enSpriteUI::Switch_Icon); gimmick++) {
		m_pstSpriteUIState[gimmick].Base.w = 500.0f;
		m_pstSpriteUIState[gimmick].Base.h = 350.0f;
		m_pstSpriteUIState[gimmick].Disp.w = 70.0f;
		m_pstSpriteUIState[gimmick].Disp.h = 49.0f;
	}

	//�{�^���������Ƃ�.
	int ButtonPushNum = static_cast<int>(enSpriteUI::ButtonPush);
	m_pstSpriteUIState[ButtonPushNum].Base.w = 324.0f;
	m_pstSpriteUIState[ButtonPushNum].Base.h = 324.0f;
	m_pstSpriteUIState[ButtonPushNum].Disp.h = 40.0f;
	m_pstSpriteUIState[ButtonPushNum].Disp.h = 40.0f;

	//�X�܂ł̕���.
	int ClosedStringNum = static_cast<int>(enSpriteUI::ClosedString);
	m_pstSpriteUIState[ClosedStringNum].Base.w = 390.0f;
	m_pstSpriteUIState[ClosedStringNum].Base.h = 120.0f;
	m_pstSpriteUIState[ClosedStringNum].Disp.w = 125.0f;
	m_pstSpriteUIState[ClosedStringNum].Disp.h = 50.0f;

	//�Q�[�W�̉��n.
	int GageGroundNum = static_cast<int>(enSpriteUI::GageGround);
	m_pstSpriteUIState[GageGroundNum].Base.w = 300.0f;
	m_pstSpriteUIState[GageGroundNum].Base.h = 75.0f;
	m_pstSpriteUIState[GageGroundNum].Disp.w = m_pstSpriteUIState[GageGroundNum].Base.w;
	m_pstSpriteUIState[GageGroundNum].Disp.h = m_pstSpriteUIState[GageGroundNum].Base.h;

	//�Q�[�W.
	int GageNum = static_cast<int>(enSpriteUI::Gage);
	m_pstSpriteUIState[GageNum].Base.w = 242.0f;
	m_pstSpriteUIState[GageNum].Base.h = 23.0f;
	m_pstSpriteUIState[GageNum].Disp.w = m_pstSpriteUIState[GageNum].Base.w;
	m_pstSpriteUIState[GageNum].Disp.h = m_pstSpriteUIState[GageNum].Base.h;

	//�������n���R.
	int StampNum = static_cast<int>(enSpriteUI::ThankYouStamp);
	m_pstSpriteUIState[StampNum].Base.w = 500.0f;
	m_pstSpriteUIState[StampNum].Base.h = 500.0f;
	m_pstSpriteUIState[StampNum].Disp.w = 200.0f;
	m_pstSpriteUIState[StampNum].Disp.h = 200.0f;

	//�V���b�^�[.
	int ShutterNum = static_cast<int>(enSpriteUI::Shutter);
	m_pstSpriteUIState[ShutterNum].Base.w = 1600.0f;
	m_pstSpriteUIState[ShutterNum].Base.h = 1036.0f;
	m_pstSpriteUIState[ShutterNum].Disp.w = 1600.0f;
	m_pstSpriteUIState[ShutterNum].Disp.h = 1036.0f;

	//���J�[�e��.
	int BlackCurtainNum = static_cast<int>(enSpriteUI::BlackCurtain);
	m_pstSpriteUIState[BlackCurtainNum].Base.w = 645.0f;
	m_pstSpriteUIState[BlackCurtainNum].Base.h = 853.0f;
	m_pstSpriteUIState[BlackCurtainNum].Disp.w = m_pstSpriteUIState[BlackCurtainNum].Base.w;
	m_pstSpriteUIState[BlackCurtainNum].Disp.h = m_pstSpriteUIState[BlackCurtainNum].Base.h;

	//�Ŕ�.
	int SignBoardNum = static_cast<int>(enSpriteUI::SignBoard);
	m_pstSpriteUIState[SignBoardNum].Base.w = 3325.0f;
	m_pstSpriteUIState[SignBoardNum].Base.h = 2433.0f;
	m_pstSpriteUIState[SignBoardNum].Disp.w = 665.0f;
	m_pstSpriteUIState[SignBoardNum].Disp.h = 486.6f;

	//������(�����������`Close�����܂�).
	int StartStringNum = static_cast<int>(enSpriteUI::PreparingString);
	int FinishStringNum = static_cast<int>(enSpriteUI::CloseString);
	for (int stringNum = StartStringNum; stringNum <= FinishStringNum; stringNum++) {
		m_pstSpriteUIState[stringNum].Base.w = 290.0f;
		m_pstSpriteUIState[stringNum].Base.h = 110.0f;
		m_pstSpriteUIState[stringNum].Disp.w = m_pstSpriteUIState[stringNum].Base.w;
		m_pstSpriteUIState[stringNum].Disp.h = m_pstSpriteUIState[stringNum].Base.h;
	}

	//�����ʒm.
	int NotificationNum = static_cast<int>(enSpriteUI::ExtendedNotification);
	m_pstSpriteUIState[NotificationNum].Base.w = 800.0f;
	m_pstSpriteUIState[NotificationNum].Base.h = 270.0f;
	m_pstSpriteUIState[NotificationNum].Disp.w = 200.0f;
	m_pstSpriteUIState[NotificationNum].Disp.h = 82.5f;

	//�e�L�X�g�{�b�N�X.
	int TextBoxNum = static_cast<int>(enSpriteUI::TextBox);
	m_pstSpriteUIState[TextBoxNum].Base.w = 774.0f;
	m_pstSpriteUIState[TextBoxNum].Base.h = 187.0f;
	m_pstSpriteUIState[TextBoxNum].Disp.w = m_pstSpriteUIState[TextBoxNum].Base.w * 1.5f;
	m_pstSpriteUIState[TextBoxNum].Disp.h = m_pstSpriteUIState[TextBoxNum].Base.h * 1.5f;

	//���̉�b���̃J�[�\��.
	int NextSpeakCursorNum = static_cast<int>(enSpriteUI::NextSpeakCursor);
	m_pstSpriteUIState[NextSpeakCursorNum].Base.w = 74.0f;
	m_pstSpriteUIState[NextSpeakCursorNum].Base.h = 73.0f;
	m_pstSpriteUIState[NextSpeakCursorNum].Disp.w = 50.0f;
	m_pstSpriteUIState[NextSpeakCursorNum].Disp.h = 50.0f;

	//�|�[�Y���̕���.
	int PauseStringNum = static_cast<int>(enSpriteUI::Pause);
	for(int pause = PauseStringNum; pause <= static_cast<int>(enSpriteUI::NextTitle); pause++){
		m_pstSpriteUIState[pause].Base.w = 350.0f;
		m_pstSpriteUIState[pause].Base.h = 90.0f;
		m_pstSpriteUIState[pause].Disp.w = m_pstSpriteUIState[pause].Base.w;
		m_pstSpriteUIState[pause].Disp.h = m_pstSpriteUIState[pause].Base.h;
	}

	//�r�b�O�S�[�X�g�A�C�R���ԍ�.
	int BigGhostIconNum = static_cast<int>(enSpriteUI::BigGhostIcon);
	m_pstSpriteUIState[BigGhostIconNum].Base.w = 311.0f;
	m_pstSpriteUIState[BigGhostIconNum].Base.h = 311.0f;
	m_pstSpriteUIState[BigGhostIconNum].Disp.w = 150;
	m_pstSpriteUIState[BigGhostIconNum].Disp.h = 150;

	//�R�����g.
	const int CommentNum = static_cast<int>(enSpriteUI::DispPaintGhostComment);
	for (int comment = CommentNum; comment <= static_cast<int>(enSpriteUI::SwitchGhostComment); comment++) {
		m_pstSpriteUIState[comment].Base.w = 460.0f;
		m_pstSpriteUIState[comment].Base.h = 180.0f;
		m_pstSpriteUIState[comment].Disp.w = 230.0f;
		m_pstSpriteUIState[comment].Disp.h = 90.0f;
	}

	//���.
	const int ArrowNum = static_cast<int>(enSpriteUI::Arrow);
	m_pstSpriteUIState[ArrowNum].Base.w = 450.0f;
	m_pstSpriteUIState[ArrowNum].Base.h = 300.0f;
	m_pstSpriteUIState[ArrowNum].Disp.w = 150.0f;
	m_pstSpriteUIState[ArrowNum].Disp.h = 100.0f;

	//�����p�����.
	const int DescriptionBlackNum = static_cast<int>(enSpriteUI::DescriptionBlack);
	m_pstSpriteUIState[DescriptionBlackNum].Base.w = WND_W;
	m_pstSpriteUIState[DescriptionBlackNum].Base.h = WND_H;
	m_pstSpriteUIState[DescriptionBlackNum].Disp.w = WND_W;
	m_pstSpriteUIState[DescriptionBlackNum].Disp.h = WND_H;

	//�����.
	const int WhiteScreenNum = static_cast<int>(enSpriteUI::WhiteScreen);
	m_pstSpriteUIState[WhiteScreenNum].Base.w = WND_W;
	m_pstSpriteUIState[WhiteScreenNum].Base.h = WND_H;
	m_pstSpriteUIState[WhiteScreenNum].Disp.w = WND_W;
	m_pstSpriteUIState[WhiteScreenNum].Disp.h = WND_H;

	//�J�[�\��SNS.
	const int CursorSNSNum = static_cast<int>(enSpriteUI::CursorSNS);
	m_pstSpriteUIState[CursorSNSNum].Base.w = 90.0f;
	m_pstSpriteUIState[CursorSNSNum].Base.h = 90.0f;
	m_pstSpriteUIState[CursorSNSNum].Disp.w = 90.0f;
	m_pstSpriteUIState[CursorSNSNum].Disp.h = 90.0f;

	//SNS�p�̎ʐ^(����).
	const int PictureStartNum = static_cast<int>(enSpriteUI::PictureSNSRest);
	for (int Picture = PictureStartNum; Picture <= static_cast<int>(enSpriteUI::PictureSNSSurprise); Picture++) {
		m_pstSpriteUIState[Picture].Base.w = 475.0f;
		m_pstSpriteUIState[Picture].Base.h = 270.0f;
		m_pstSpriteUIState[Picture].Disp.w = 475.0f;
		m_pstSpriteUIState[Picture].Disp.h = 270.0f;
	}

	//PushEnter����.
	const int PushEnterStringNum = static_cast<int>(enSpriteUI::PushEnterString);
	m_pstSpriteUIState[PushEnterStringNum].Base.w = 218.0f;
	m_pstSpriteUIState[PushEnterStringNum].Base.h = 48.0f;
	m_pstSpriteUIState[PushEnterStringNum].Disp.w = m_pstSpriteUIState[PushEnterStringNum].Base.w;
	m_pstSpriteUIState[PushEnterStringNum].Disp.h = m_pstSpriteUIState[PushEnterStringNum].Base.h;

	//�J�n�����ԍ�.
	const int StartNum = static_cast<int>(enSpriteUI::StartString);
	for (int StringNum = StartNum; StringNum <= static_cast<int>(enSpriteUI::FinishString); StringNum++) {
		m_pstSpriteUIState[StringNum].Base.w = 340.0f;
		m_pstSpriteUIState[StringNum].Base.h = 90.0f;
		m_pstSpriteUIState[StringNum].Disp.w = m_pstSpriteUIState[StringNum].Base.w;
		m_pstSpriteUIState[StringNum].Disp.h = m_pstSpriteUIState[StringNum].Base.h;
	}

	//�Ռ��I����.
	const int ShockingSignNum = static_cast<int>(enSpriteUI::ShockingSign);
	m_pstSpriteUIState[ShockingSignNum].Base.w = 800.0f;
	m_pstSpriteUIState[ShockingSignNum].Base.h = 800.0f;
	m_pstSpriteUIState[ShockingSignNum].Disp.w = 40.0f;
	m_pstSpriteUIState[ShockingSignNum].Disp.h = 40.0f;

	//�����Đ�����.
	const int AutoStringNum = static_cast<int>(enSpriteUI::AutoString);
	m_pstSpriteUIState[AutoStringNum].Base.w = 550.0f;
	m_pstSpriteUIState[AutoStringNum].Base.h = 90.0f;
	m_pstSpriteUIState[AutoStringNum].Disp.w = 275.0f;
	m_pstSpriteUIState[AutoStringNum].Disp.h = 45.0f;

	//����.
	const int ShoutNum = static_cast<int>(enSpriteUI::Shout);
	m_pstSpriteUIState[ShoutNum].Base.w = 375.0f;
	m_pstSpriteUIState[ShoutNum].Base.h = 294.0f;
	m_pstSpriteUIState[ShoutNum].Disp.w = m_pstSpriteUIState[ShoutNum].Base.w;
	m_pstSpriteUIState[ShoutNum].Disp.h = m_pstSpriteUIState[ShoutNum].Base.h;

	//�������x.
	const int SurprsieDegreeNum = static_cast<int>(enSpriteUI::SurpriseDegree);
	m_pstSpriteUIState[SurprsieDegreeNum].Base.w = 600.0f;
	m_pstSpriteUIState[SurprsieDegreeNum].Base.h = 140.0f;
	m_pstSpriteUIState[SurprsieDegreeNum].Disp.w = m_pstSpriteUIState[SurprsieDegreeNum].Base.w;
	m_pstSpriteUIState[SurprsieDegreeNum].Disp.h = m_pstSpriteUIState[SurprsieDegreeNum].Base.h;

	//������.
	int GhostIconNum = static_cast<int>(enSpriteUI::Ghost_Icon);
	m_pstSpriteUIState[GhostIconNum].Base.w = 3580.0f;
	m_pstSpriteUIState[GhostIconNum].Base.h = 3580.0f;
	m_pstSpriteUIState[GhostIconNum].Frame.w = 3.0f;
	m_pstSpriteUIState[GhostIconNum].Frame.h = 3.0f;
	m_pstSpriteUIState[GhostIconNum].Stride.w = m_pstSpriteUIState[GhostIconNum].Base.w / m_pstSpriteUIState[GhostIconNum].Frame.w;
	m_pstSpriteUIState[GhostIconNum].Stride.h = m_pstSpriteUIState[GhostIconNum].Base.h / m_pstSpriteUIState[GhostIconNum].Frame.h;
	m_pstSpriteUIState[GhostIconNum].Disp.w = 64.0f;
	m_pstSpriteUIState[GhostIconNum].Disp.h = 64.0f;

	//����.
	int TimeNum = static_cast<int>(enSpriteUI::Time);
	m_pstSpriteUIState[TimeNum].Base.w = 1020.0f;
	m_pstSpriteUIState[TimeNum].Base.h = 120.0f;
	m_pstSpriteUIState[TimeNum].Frame.w = 11.5f;
	m_pstSpriteUIState[TimeNum].Frame.h = 1;
	m_pstSpriteUIState[TimeNum].Stride.w = m_pstSpriteUIState[TimeNum].Base.w / m_pstSpriteUIState[TimeNum].Frame.w;
	m_pstSpriteUIState[TimeNum].Stride.h = m_pstSpriteUIState[TimeNum].Base.h;
	m_pstSpriteUIState[TimeNum].Disp.w = 50.0f;
	m_pstSpriteUIState[TimeNum].Disp.h = 50.0f;

	//�؂̔�.
	int TreeBordNum = static_cast<int>(enSpriteUI::TreeBord);
	m_pstSpriteUIState[TreeBordNum].Base.w = 3318.0f;
	m_pstSpriteUIState[TreeBordNum].Base.h = 2305.0f;
	m_pstSpriteUIState[TreeBordNum].Frame.w = 3.0f;
	m_pstSpriteUIState[TreeBordNum].Frame.h = 3.0f;
	m_pstSpriteUIState[TreeBordNum].Stride.w = m_pstSpriteUIState[TreeBordNum].Base.w / m_pstSpriteUIState[TreeBordNum].Frame.w;
	m_pstSpriteUIState[TreeBordNum].Stride.h = m_pstSpriteUIState[TreeBordNum].Base.h / m_pstSpriteUIState[TreeBordNum].Frame.h;
	m_pstSpriteUIState[TreeBordNum].Disp.w = 300.0f;
	m_pstSpriteUIState[TreeBordNum].Disp.h = 150.0f;

	//�������̃J�[�\��.
	int GhostCursor = static_cast<int>(enSpriteUI::GhostCursor);
	m_pstSpriteUIState[GhostCursor].Base.w = 1600.0f;
	m_pstSpriteUIState[GhostCursor].Base.h = 1600.0f;
	m_pstSpriteUIState[GhostCursor].Frame.w = 2.0f;
	m_pstSpriteUIState[GhostCursor].Frame.h = 2.0f;
	m_pstSpriteUIState[GhostCursor].Stride.w = m_pstSpriteUIState[GhostCursor].Base.w / m_pstSpriteUIState[GhostCursor].Frame.w;
	m_pstSpriteUIState[GhostCursor].Stride.h = m_pstSpriteUIState[GhostCursor].Base.h / m_pstSpriteUIState[GhostCursor].Frame.h;
	m_pstSpriteUIState[GhostCursor].Disp.w =100.0f;
	m_pstSpriteUIState[GhostCursor].Disp.h =100.0f;

	//�����o��.
	int BalloonNum = static_cast<int>(enSpriteUI::Balloon);
	m_pstSpriteUIState[BalloonNum].Base.w = 1755.0f;
	m_pstSpriteUIState[BalloonNum].Base.h = 1754.0f;
	m_pstSpriteUIState[BalloonNum].Frame.w = 2.0f;
	m_pstSpriteUIState[BalloonNum].Frame.h = 2.0f;
	m_pstSpriteUIState[BalloonNum].Stride.w = m_pstSpriteUIState[BalloonNum].Base.w / m_pstSpriteUIState[BalloonNum].Frame.w;
	m_pstSpriteUIState[BalloonNum].Stride.h = m_pstSpriteUIState[BalloonNum].Base.h / m_pstSpriteUIState[BalloonNum].Frame.h;
	m_pstSpriteUIState[BalloonNum].Disp.w = 300.0f;
	m_pstSpriteUIState[BalloonNum].Disp.h = 300.0f;

	//Title����.
	const int TitleNum = static_cast<int>(enSpriteUI::Title);
	m_pstSpriteUIState[TitleNum].Base.w = 680.0f;
	m_pstSpriteUIState[TitleNum].Base.h = 400.0f;
	m_pstSpriteUIState[TitleNum].Frame.w = 1.0f;
	m_pstSpriteUIState[TitleNum].Frame.h = 2.0f;
	m_pstSpriteUIState[TitleNum].Stride.w = m_pstSpriteUIState[TitleNum].Base.w;
	m_pstSpriteUIState[TitleNum].Stride.h = m_pstSpriteUIState[TitleNum].Base.h / m_pstSpriteUIState[TitleNum].Frame.h;
	m_pstSpriteUIState[TitleNum].Disp.w = m_pstSpriteUIState[TitleNum].Base.w;
	m_pstSpriteUIState[TitleNum].Disp.h = m_pstSpriteUIState[TitleNum].Stride.h;

	//���]�����̕���.
	const int HightEvaluationStringNum = static_cast<int>(enSpriteUI::HightEvaluationString);
	m_pstSpriteUIState[HightEvaluationStringNum].Base.w = 720.0f;
	m_pstSpriteUIState[HightEvaluationStringNum].Base.h = 180.0f;
	m_pstSpriteUIState[HightEvaluationStringNum].Frame.w = 4.0f;
	m_pstSpriteUIState[HightEvaluationStringNum].Frame.h = 1.0f;
	m_pstSpriteUIState[HightEvaluationStringNum].Stride.w = m_pstSpriteUIState[HightEvaluationStringNum].Base.w / m_pstSpriteUIState[HightEvaluationStringNum].Frame.w;
	m_pstSpriteUIState[HightEvaluationStringNum].Stride.h = m_pstSpriteUIState[HightEvaluationStringNum].Base.h;
	m_pstSpriteUIState[HightEvaluationStringNum].Disp.w = m_pstSpriteUIState[HightEvaluationStringNum].Stride.w;
	m_pstSpriteUIState[HightEvaluationStringNum].Disp.h = m_pstSpriteUIState[HightEvaluationStringNum].Base.h;

	//���ԕ]�����̕���.
	const int IntermediateEvaluationStringNum = static_cast<int>(enSpriteUI::IntermediateEvaluationString);
	m_pstSpriteUIState[IntermediateEvaluationStringNum].Base.w = 720.0f;
	m_pstSpriteUIState[IntermediateEvaluationStringNum].Base.h = 180.0f;
	m_pstSpriteUIState[IntermediateEvaluationStringNum].Frame.w = 4.0f;
	m_pstSpriteUIState[IntermediateEvaluationStringNum].Frame.h = 1.0f;
	m_pstSpriteUIState[IntermediateEvaluationStringNum].Stride.w = m_pstSpriteUIState[IntermediateEvaluationStringNum].Base.w / m_pstSpriteUIState[IntermediateEvaluationStringNum].Frame.w;
	m_pstSpriteUIState[IntermediateEvaluationStringNum].Stride.h = m_pstSpriteUIState[IntermediateEvaluationStringNum].Base.h;
	m_pstSpriteUIState[IntermediateEvaluationStringNum].Disp.w = m_pstSpriteUIState[IntermediateEvaluationStringNum].Stride.w;
	m_pstSpriteUIState[IntermediateEvaluationStringNum].Disp.h = m_pstSpriteUIState[IntermediateEvaluationStringNum].Base.h;

	//��]�����̕���.
	const int LowEvaluationStringNum = static_cast<int>(enSpriteUI::LowEvaluationString);
	m_pstSpriteUIState[LowEvaluationStringNum].Base.w = 360.0f;
	m_pstSpriteUIState[LowEvaluationStringNum].Base.h = 180.0f;
	m_pstSpriteUIState[LowEvaluationStringNum].Frame.w = 2.0f;
	m_pstSpriteUIState[LowEvaluationStringNum].Frame.h = 1.0f;
	m_pstSpriteUIState[LowEvaluationStringNum].Stride.w = m_pstSpriteUIState[LowEvaluationStringNum].Base.w / m_pstSpriteUIState[LowEvaluationStringNum].Stride.w;
	m_pstSpriteUIState[LowEvaluationStringNum].Stride.h = m_pstSpriteUIState[LowEvaluationStringNum].Base.h;
	m_pstSpriteUIState[LowEvaluationStringNum].Disp.w = m_pstSpriteUIState[LowEvaluationStringNum].Stride.w;
	m_pstSpriteUIState[LowEvaluationStringNum].Disp.h = m_pstSpriteUIState[LowEvaluationStringNum].Base.h;
	
	//�S�ẴX�v���C�g��1�R�}������̃T�C�Y.
	for (int spriteui = 0; spriteui < static_cast<int>(enSpriteUI::SingleSpriteMax); spriteui++) {
		m_pstSpriteUIState[spriteui].Stride.w = m_pstSpriteUIState[spriteui].Base.w;
		m_pstSpriteUIState[spriteui].Stride.h = m_pstSpriteUIState[spriteui].Base.h;
		m_pstSpriteUIState[spriteui].Frame.w = 1.0f;
		m_pstSpriteUIState[spriteui].Frame.h = 1.0f;
	}
}

//============================================.
//		�����蔻��p�X�t�B�A�쐬�����֐�.
//============================================.
HRESULT CResourceManager::InitSphere()
{
	//���b�V���ԍ�.
	const int	MeshNo = static_cast<int>(enStaticMeshType::HitSphere);
	//�X�t�B�A���b�V��.
	CDX9Mesh*	m_pCHitSphere = m_pCStaticMesh->GetMeshObject(enStaticMeshType::HitSphere);

	LPDIRECT3DVERTEXBUFFER9 pVB			= nullptr;		//���_�o�b�t�@.
	void*					pVertices	= nullptr;		//���_.
	D3DXVECTOR3				vCenter;					//���S.
	float					fRadius;					//���a.

	//���_�o�b�t�@���擾.
	if (FAILED(m_pCHitSphere->GetMesh()->GetVertexBuffer(&pVB))){
		return E_FAIL;
	}

	//���b�V���̒��_�o�b�t�@�����b�N����.
	if (FAILED(pVB->Lock(0, 0, &pVertices, 0))) {
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}

	//���b�V���̊O�ډ~�ƒ��S�̔��a���v�Z����.
	D3DXComputeBoundingSphere(
		static_cast<D3DXVECTOR3*>(pVertices),						
		m_pCHitSphere->GetMesh()->GetNumVertices(),					//���_�̐�.
		D3DXGetFVFVertexSize(m_pCHitSphere->GetMesh()->GetFVF()),	//���_���.
		&vCenter,													//(out)���S���W.			
		&fRadius);													//(out)���a.

	//�A�����b�N.
	pVB->Unlock();
	SAFE_RELEASE(pVB);

	//���S�Ɣ��a���\���̂ɐݒ�.
	m_pCHitSphere->m_Sphere.vCenter = vCenter;
	m_pCHitSphere->m_Sphere.fRadius = fRadius;

	return S_OK;
}