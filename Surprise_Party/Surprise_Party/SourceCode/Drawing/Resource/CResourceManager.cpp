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
//		読み込み処理関数.
//==========================================.
HRESULT CResourceManager::Load(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	//スプライトファイル名設定処理関数.
	SpriteFileNameSetting();
	//スプライトUIファイル名設定処理関数.
	SpriteUIFileNameSetting();
	//スタティックメッシュのファイル名設定処理関数.
	StaticMeshFileNmaeSetting();
	//スキンメッシュのファイル名設定処理関数.
	SkinMeshFileNameSetting();

	//スプライト情報構造体設定処理関数.
	SpriteStateSetting();
	//スプライトUI情報構造体設定処理関数.
	SpriteUIStateSetting();

	//スプライトクラス.
	m_pCSprite.reset(new CSprite_Resource<CSprite, enSprite>());
	//初期値設定処理.
	m_pCSprite->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//初期化処理.
	m_pCSprite->Init(static_cast<int>(enSprite::Max));
	//スプライト情報構造体設定.
	m_pCSprite->SetSpriteState(m_pstSpriteState);
	//読み込み処理.
	m_pCSprite->Load(m_vSpriteFileName);

	//スプライトUIクラス.
	m_pCSpriteUI.reset(new CSprite_Resource<CSpriteUI, enSpriteUI>());
	//初期値設定処理.
	m_pCSpriteUI->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//初期化処理.
	m_pCSpriteUI->Init(static_cast<int>(enSpriteUI::Max));
	//スプライトUI情報構造体設定.
	m_pCSpriteUI->SetSpriteState(m_pstSpriteUIState);
	//読み込み処理.
	m_pCSpriteUI->Load(m_vSpriteUIFileNmae);

	//スタティックメッシュ.
	m_pCStaticMesh.reset(new CObjectResource<CDX9Mesh, enStaticMeshType>());
	//初期値設定.
	m_pCStaticMesh->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//初期化処理.
	m_pCStaticMesh->Init(static_cast<int>(enStaticMeshType::Max));
	//読み込み処理.
	m_pCStaticMesh->Load(m_vStaticMeshFileName);
	//当たり判定用スフィア作成処理関数.
	if (FAILED(InitSphere())) {
		_ASSERT_EXPR(false, L"当たり判定用スフィア作成失敗");
		return E_FAIL;
	}

	//スキンメッシュ.
	m_pCSkinMesh.reset(new CObjectResource<CDX9SkinMesh, enSkinMeshType>());
	//初期値設定処理.
	m_pCSkinMesh->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	//初期化処理.
	m_pCSkinMesh->Init(static_cast<int>(enSkinMeshType::Max));
	//読み込み処理.
	m_pCSkinMesh->Load(m_vSkinMeshFileName);

	//エフェクト.
	m_pCEffect.reset(new CResourceEffect());
	m_pCEffect->Init(hWnd, pDevice11, pContext11);
	m_pCEffect->LoadEffect();

	//フォント.
	m_pCFont.reset(new CFontResource());
	//初期化処理関数.
	m_pCFont->Init(pDevice11, pContext11);

	return S_OK;
}

//=======================================.
//		解放処理関数.
//=======================================.
HRESULT CResourceManager::Release()
{
	//解放呼び出し処理関数.
	m_pCSkinMesh->ReleaseCalling();		//スキンメッシュ.
	m_pCStaticMesh->ReleaseCalling();	//スタティックメッシュ.
	m_pCSpriteUI->ReleaseCalling();		//スプライトUI.
	m_pCSprite->ReleaseCalling();		//スプライト.

	SAFE_DELETE_ARRAY(m_pstSpriteUIState);
	SAFE_DELETE_ARRAY(m_pstSpriteState);

	return S_OK;
}

//==================================================.
//	スタティックメッシュのファイル名設定処理関数.
//==================================================.
void CResourceManager::StaticMeshFileNmaeSetting()
{
	m_vStaticMeshFileName = {
		"Data\\Object\\StaticMesh\\Wall\\Wall.x",				//壁.
		"Data\\Object\\StaticMesh\\Floor\\Flor.X",				//床.
		"Data\\Object\\StaticMesh\\Painting\\e.X",				//絵画.
		"Data\\Object\\StaticMesh\\BookShelf\\BookShelf.x",		//本棚.
		"Data\\Object\\StaticMesh\\UpDownFloor\\UpDownFloor.X",	//オブジェクト移動スイッチ.
		"Data\\Object\\StaticMesh\\Switch\\Switch.X",			//音が鳴るスイッチ.
		"Data\\Object\\StaticMesh\\Ghost\\gost_a.X",			//スイッチを押すお化け.
		"Data\\Object\\StaticMesh\\Phone\\phone.X",				//携帯.
		"Data\\Object\\StaticMesh\\HitSphere\\Sphere.x",		//当たり判定用スフィア.
		"Data\\Object\\StaticMesh\\Table\\Round table.X",		//机.
		"Data\\Object\\StaticMesh\\VaseFlowar\\vase_flower.X",	//花瓶.
	};
}

//=================================================.
//	スキンメッシュのファイル名設定処理関数.
//=================================================.
void CResourceManager::SkinMeshFileNameSetting()
{
	m_vSkinMeshFileName = {
		"Data\\Object\\SkinMesh\\People\\Sayaka\\Sayaka_s.X",	//女の子.
		"Data\\Object\\SkinMesh\\People\\Towa\\Towa_s.X",		//男の子.
		"Data\\Object\\SkinMesh\\Ghost\\GhostB\\GhostB_s.X",	//現れるお化け.
		"Data\\Object\\SkinMesh\\Ghost\\BigGhost\\BigGhost_s.X",//大きいお化け.
	};
}

//=================================================.
//	スプライトのファイル名設定処理関数.
//=================================================.
void CResourceManager::SpriteFileNameSetting()
{
	m_vSpriteFileName = {
		"Data\\Texture\\UI\\Game\\CursorUp.png",			//カーソル.
		"Data\\Texture\\UI\\Game\\Select.png",				//行動選択.
		"Data\\Texture\\UI\\Game\\ActMoveString.png",		//移動文字.
		"Data\\Texture\\UI\\Game\\ActRestString.png",		//休憩文字.
		"Data\\Texture\\UI\\Game\\bubble.png",				//泡.
		"Data\\Texture\\UI\\Game\\Z.png",					//睡眠のｚ.
		"Data\\Texture\\UI\\Game\\Swet.png",				//汗.
		"Data\\Texture\\UI\\Game\\TextBoxSmall.png",		//テキストボックス小.
		"Data\\Texture\\UI\\Game\\AnswerNo.png",			//「いいえ」の回答.
		"Data\\Texture\\UI\\Game\\AnswerYes.png",			//「はい」の回答.
		"Data\\Texture\\UI\\Game\\shock.png",				//驚き.
		"Data\\Texture\\UI\\Game\\HelthIcon.png",			//体力アイコン.
		"Data\\Texture\\UI\\Game\\eight_part_note.png",		//8分音符.
		"Data\\Texture\\UI\\Game\\sixteen_part_note.png",	//16分音符.
		"Data\\Texture\\UI\\Game\\flower.png",				//花.
	};
}

//=================================================.
//	スプライトUIのファイル名設定処理関数.
//=================================================.
void CResourceManager::SpriteUIFileNameSetting()
{
	m_vSpriteUIFileNmae = {
		"Data\\Texture\\UI\\Map\\Stage.png",					//ステージ全体のマップ.
		"Data\\Texture\\UI\\Map\\Girl_Icon.png",				//女の子のアイコン.
		"Data\\Texture\\UI\\Map\\Boy_Icon.png",					//男の子のアイコン.
		"Data\\Texture\\UI\\Map\\DispButton.png",				//現れるボタンアイコン.
		"Data\\Texture\\UI\\Map\\SwitchButton.png",				//スイッチアイコン."
		"Data\\Texture\\UI\\Map\\PushButton.png",				//ボタン押したとき.
		"Data\\Texture\\UI\\Game\\TimeUpToClosed.png", 			//閉店までの文字.
		"Data\\Texture\\UI\\Game\\Bar.png",						//ゲージの下地.
		"Data\\Texture\\UI\\Game\\Blue_Bar.png",				//ゲージ.
		"Data\\Texture\\UI\\Game\\ThankYouStamp.png",			//満員御礼ハンコ.
		"Data\\Texture\\UI\\Game\\Shutter.jpg",					//シャッター.
		"Data\\Texture\\UI\\Game\\BlackCurtain.jpg",			//黒カーテン.
		"Data\\Texture\\UI\\Game\\SignBoard.png",				//看板.
		"Data\\Texture\\UI\\Game\\PreparingString.png",			//準備中文字.
		"Data\\Texture\\UI\\Game\\OpenString.png",				//Open文字.
		"Data\\Texture\\UI\\Game\\CloseString.png",				//Close文字.
		"Data\\Texture\\UI\\Game\\extended_notification.png",	//延長通知.
		"Data\\Texture\\UI\\Game\\TextBox.png",					//テキストボックス.
		"Data\\Texture\\UI\\Game\\PauseTitle.png",				//ポーズ.
		"Data\\Texture\\UI\\Game\\ToGame.png",					//続ける.
		"Data\\Texture\\UI\\Game\\ToTitle.png",					//終わる.
		"Data\\Texture\\UI\\Game\\BigGhostIcon.png",			//ビッグゴーストアイコン.
		"Data\\Texture\\UI\\Game\\DispPaintGhostComment.png",	//現れるお化けコメント.
		"Data\\Texture\\UI\\Game\\SwitchGhostComment.png",		//スイッチお化けコメント.
		"Data\\Texture\\UI\\Game\\Arrow.png",					//矢印.
		"Data\\Texture\\UI\\Map\\GhostIcon.png",				//お化けのアイコン.
		"Data\\Texture\\UI\\Game\\Time.png",					//時間.
		"Data\\Texture\\UI\\Game\\TreeBord.png",				//木の板.
		"Data\\Texture\\UI\\Game\\GhostCursor.png",				//お化けカーソル.
		"Data\\Texture\\UI\\Game\\balloon.png",					//吹き出し.
	};
}

//=================================================.
//	スプライト情報構造体設定処理関数.
//=================================================.
void CResourceManager::SpriteStateSetting()
{
	//カーソル.
	int CursorNum = static_cast<int>(enSprite::Cursol);
	m_pstSpriteState[CursorNum].Base.w = 74.0f;
	m_pstSpriteState[CursorNum].Base.h = 73.0f;
	m_pstSpriteState[CursorNum].Disp.w = 1.0f;
	m_pstSpriteState[CursorNum].Disp.h = 1.0f;

	//行動選択.
	int SelectionNum = static_cast<int>(enSprite::ActSelection);
	m_pstSpriteState[SelectionNum].Base.w = 256.0f;
	m_pstSpriteState[SelectionNum].Base.h = 256.0;
	m_pstSpriteState[SelectionNum].Disp.w = 5.0f;
	m_pstSpriteState[SelectionNum].Disp.h = 5.0f;

	//文字.
	int MoveStringNum = static_cast<int>(enSprite::ActMoveString);
	for (int stringNum = MoveStringNum; stringNum <= static_cast<int>(enSprite::ActRestString); stringNum++) {
		m_pstSpriteState[stringNum].Base.w = 80.0f;
		m_pstSpriteState[stringNum].Base.h = 180.0f;
		m_pstSpriteState[stringNum].Disp.w = 1.6f;
		m_pstSpriteState[stringNum].Disp.h = 3.6f;
	}

	//泡.
	int BubbleNum = static_cast<int>(enSprite::Bubble);
	m_pstSpriteState[BubbleNum].Base.w = 350.0f;
	m_pstSpriteState[BubbleNum].Base.h = 350.0f;
	m_pstSpriteState[BubbleNum].Disp.w = 1.0f;
	m_pstSpriteState[BubbleNum].Disp.h = 1.0f;

	//睡眠のz.
	int SleepZNum = static_cast<int>(enSprite::SleepZ);
	m_pstSpriteState[SleepZNum].Base.w = 70.0f;
	m_pstSpriteState[SleepZNum].Base.h = 70.0f;
	m_pstSpriteState[SleepZNum].Disp.w = 1.0f;
	m_pstSpriteState[SleepZNum].Disp.h = 1.0f;

	//汗.
	int SwetNum = static_cast<int>(enSprite::Swet);
	m_pstSpriteState[SwetNum].Base.w = 300.0f;
	m_pstSpriteState[SwetNum].Base.h = 300.0f;
	m_pstSpriteState[SwetNum].Disp.w = 1.0f;
	m_pstSpriteState[SwetNum].Disp.h = 1.0f;

	//テキストボックス小.
	int TextBoxSmallNum = static_cast<int>(enSprite::TextBoxSmall);
	m_pstSpriteState[TextBoxSmallNum].Base.w = 209.0f;
	m_pstSpriteState[TextBoxSmallNum].Base.h = 57.0f;
	m_pstSpriteState[TextBoxSmallNum].Disp.w = 4.0f;
	m_pstSpriteState[TextBoxSmallNum].Disp.h = 1.0f;

	//「いいえ」の回答.
	int AnswerNoNum = static_cast<int>(enSprite::AnswerNo);
	m_pstSpriteState[AnswerNoNum].Base.w = 220.0f;
	m_pstSpriteState[AnswerNoNum].Base.h = 70.0f;
	m_pstSpriteState[AnswerNoNum].Disp.w = 3.0f;
	m_pstSpriteState[AnswerNoNum].Disp.h = 1.0f;

	//「はい」の回答.
	int AnswerYesNum = static_cast<int>(enSprite::AnswerYes);
	m_pstSpriteState[AnswerYesNum].Base.w = 150.0f;
	m_pstSpriteState[AnswerYesNum].Base.h = 70.0f;
	m_pstSpriteState[AnswerYesNum].Disp.w = 2.0f;
	m_pstSpriteState[AnswerYesNum].Disp.h = 1.0f;

	//驚き.
	int ShockNum = static_cast<int>(enSprite::Shock);
	m_pstSpriteState[ShockNum].Base.w = 100.0f;
	m_pstSpriteState[ShockNum].Base.h = 200.0f;
	m_pstSpriteState[ShockNum].Disp.w = 0.5f;
	m_pstSpriteState[ShockNum].Disp.h = 1.0f;

	//まとめて一コマ当たりのサイズ指定.
	for (int sprite = 0; sprite < static_cast<int>(enSprite::SingleSpriteMax); sprite++) {
		m_pstSpriteState[sprite].Stride.w = m_pstSpriteState[sprite].Base.w;
		m_pstSpriteState[sprite].Stride.h = m_pstSpriteState[sprite].Base.h;
	}

	//体力アイコン.
	int StrengthIconNum = static_cast<int>(enSprite::Strenght_Icon);
	m_pstSpriteState[StrengthIconNum].Base.w = 618.0f;
	m_pstSpriteState[StrengthIconNum].Base.h = 405.0f;
	m_pstSpriteState[StrengthIconNum].Stride.w = m_pstSpriteState[StrengthIconNum].Base.w / 6.0f;
	m_pstSpriteState[StrengthIconNum].Stride.h = m_pstSpriteState[StrengthIconNum].Base.h / 4.0f;
	m_pstSpriteState[StrengthIconNum].Disp.w = 1.0f;
	m_pstSpriteState[StrengthIconNum].Disp.h = 1.0f;

	//音符.
	int NoteNum = static_cast<int>(enSprite::eight_part_note);
	for (int note = NoteNum; note <= static_cast<int>(enSprite::sixteen_part_note); note++) {
		m_pstSpriteState[note].Base.w = 1321.0f;
		m_pstSpriteState[note].Base.h = 1321.0f;
		m_pstSpriteState[note].Stride.w = m_pstSpriteState[note].Base.w / 3.0f;
		m_pstSpriteState[note].Stride.h = m_pstSpriteState[note].Base.h / 3.0f;
		m_pstSpriteState[note].Disp.w = 1.5f;
		m_pstSpriteState[note].Disp.h = 1.5f;
	}

	//花.
	int FlowerNum = static_cast<int>(enSprite::Flower);
	m_pstSpriteState[FlowerNum].Base.w = 960.0f;
	m_pstSpriteState[FlowerNum].Base.h = 960.0f;
	m_pstSpriteState[FlowerNum].Stride.w = m_pstSpriteState[FlowerNum].Base.w / 2.0f;
	m_pstSpriteState[FlowerNum].Stride.h = m_pstSpriteState[FlowerNum].Base.h / 2.0f;
	m_pstSpriteState[FlowerNum].Disp.w = 1.5f;
	m_pstSpriteState[FlowerNum].Disp.h = 1.5f;
}

//================================================.
//	スプライトUI情報構造体設定処理関数.
//================================================.
void CResourceManager::SpriteUIStateSetting()
{
	//ステージマップ.
	int StageMapNum = static_cast<int>(enSpriteUI::StageMap);
	m_pstSpriteUIState[StageMapNum].Base.w = 1280.0f;
	m_pstSpriteUIState[StageMapNum].Base.h = 180.0f;
	m_pstSpriteUIState[StageMapNum].Disp.w = 1280.0f;
	m_pstSpriteUIState[StageMapNum].Disp.h = 180.0f;

	//女の子.
	int GirlIconNum = static_cast<int>(enSpriteUI::Girl_Icon);
	m_pstSpriteUIState[GirlIconNum].Base.w = 256.0f;
	m_pstSpriteUIState[GirlIconNum].Base.h = 256.0f;
	m_pstSpriteUIState[GirlIconNum].Disp.w = 64.0f;
	m_pstSpriteUIState[GirlIconNum].Disp.h = 64.0f;

	//男の子.
	int BoyIconNum = static_cast<int>(enSpriteUI::Boy_Icon);
	m_pstSpriteUIState[BoyIconNum].Base.w = 256.0f;
	m_pstSpriteUIState[BoyIconNum].Base.h = 256.0f;
	m_pstSpriteUIState[BoyIconNum].Disp.w = 64.0f;
	m_pstSpriteUIState[BoyIconNum].Disp.h = 64.0f;

	//ギミック.
	int GimmickStartNum = static_cast<int>(enSpriteUI::DispGimmick_Iccon);
	for (int gimmick = GimmickStartNum; gimmick <= static_cast<int>(enSpriteUI::Switch_Icon); gimmick++) {
		m_pstSpriteUIState[gimmick].Base.w = 500.0f;
		m_pstSpriteUIState[gimmick].Base.h = 350.0f;
		m_pstSpriteUIState[gimmick].Disp.w = 70.0f;
		m_pstSpriteUIState[gimmick].Disp.h = 49.0f;
	}

	//ボタン押したとき.
	int ButtonPushNum = static_cast<int>(enSpriteUI::ButtonPush);
	m_pstSpriteUIState[ButtonPushNum].Base.w = 324.0f;
	m_pstSpriteUIState[ButtonPushNum].Base.h = 324.0f;
	m_pstSpriteUIState[ButtonPushNum].Disp.h = 40.0f;
	m_pstSpriteUIState[ButtonPushNum].Disp.h = 40.0f;

	//閉店までの文字.
	int ClosedStringNum = static_cast<int>(enSpriteUI::ClosedString);
	m_pstSpriteUIState[ClosedStringNum].Base.w = 390.0f;
	m_pstSpriteUIState[ClosedStringNum].Base.h = 120.0f;
	m_pstSpriteUIState[ClosedStringNum].Disp.w = 125.0f;
	m_pstSpriteUIState[ClosedStringNum].Disp.h = 50.0f;

	//ゲージの下地.
	int GageGroundNum = static_cast<int>(enSpriteUI::GageGround);
	m_pstSpriteUIState[GageGroundNum].Base.w = 300.0f;
	m_pstSpriteUIState[GageGroundNum].Base.h = 75.0f;
	m_pstSpriteUIState[GageGroundNum].Disp.w = m_pstSpriteUIState[GageGroundNum].Base.w;
	m_pstSpriteUIState[GageGroundNum].Disp.h = m_pstSpriteUIState[GageGroundNum].Base.h;

	//ゲージ.
	int GageNum = static_cast<int>(enSpriteUI::Gage);
	m_pstSpriteUIState[GageNum].Base.w = 242.0f;
	m_pstSpriteUIState[GageNum].Base.h = 23.0f;
	m_pstSpriteUIState[GageNum].Disp.w = m_pstSpriteUIState[GageNum].Base.w;
	m_pstSpriteUIState[GageNum].Disp.h = m_pstSpriteUIState[GageNum].Base.h;

	//満員御礼ハンコ.
	int StampNum = static_cast<int>(enSpriteUI::ThankYouStamp);
	m_pstSpriteUIState[StampNum].Base.w = 500.0f;
	m_pstSpriteUIState[StampNum].Base.h = 500.0f;
	m_pstSpriteUIState[StampNum].Disp.w = 200.0f;
	m_pstSpriteUIState[StampNum].Disp.h = 200.0f;

	//シャッター.
	int ShutterNum = static_cast<int>(enSpriteUI::Shutter);
	m_pstSpriteUIState[ShutterNum].Base.w = 1600.0f;
	m_pstSpriteUIState[ShutterNum].Base.h = 1036.0f;
	m_pstSpriteUIState[ShutterNum].Disp.w = 1600.0f;
	m_pstSpriteUIState[ShutterNum].Disp.h = 1036.0f;

	//黒カーテン.
	int BlackCurtainNum = static_cast<int>(enSpriteUI::BlackCurtain);
	m_pstSpriteUIState[BlackCurtainNum].Base.w = 645.0f;
	m_pstSpriteUIState[BlackCurtainNum].Base.h = 853.0f;
	m_pstSpriteUIState[BlackCurtainNum].Disp.w = m_pstSpriteUIState[BlackCurtainNum].Base.w;
	m_pstSpriteUIState[BlackCurtainNum].Disp.h = m_pstSpriteUIState[BlackCurtainNum].Base.h;

	//看板.
	int SignBoardNum = static_cast<int>(enSpriteUI::SignBoard);
	m_pstSpriteUIState[SignBoardNum].Base.w = 3325.0f;
	m_pstSpriteUIState[SignBoardNum].Base.h = 2433.0f;
	m_pstSpriteUIState[SignBoardNum].Disp.w = 665.0f;
	m_pstSpriteUIState[SignBoardNum].Disp.h = 486.6f;

	//文字列(準備中文字～Close文字まで).
	int StartStringNum = static_cast<int>(enSpriteUI::PreparingString);
	int FinishStringNum = static_cast<int>(enSpriteUI::CloseString);
	for (int stringNum = StartStringNum; stringNum <= FinishStringNum; stringNum++) {
		m_pstSpriteUIState[stringNum].Base.w = 290.0f;
		m_pstSpriteUIState[stringNum].Base.h = 110.0f;
		m_pstSpriteUIState[stringNum].Disp.w = m_pstSpriteUIState[stringNum].Base.w;
		m_pstSpriteUIState[stringNum].Disp.h = m_pstSpriteUIState[stringNum].Base.h;
	}

	//延長通知.
	int NotificationNum = static_cast<int>(enSpriteUI::ExtendedNotification);
	m_pstSpriteUIState[NotificationNum].Base.w = 800.0f;
	m_pstSpriteUIState[NotificationNum].Base.h = 270.0f;
	m_pstSpriteUIState[NotificationNum].Disp.w = 200.0f;
	m_pstSpriteUIState[NotificationNum].Disp.h = 82.5f;

	//テキストボックス.
	int TextBoxNum = static_cast<int>(enSpriteUI::TextBox);
	m_pstSpriteUIState[TextBoxNum].Base.w = 774.0f;
	m_pstSpriteUIState[TextBoxNum].Base.h = 187.0f;
	m_pstSpriteUIState[TextBoxNum].Disp.w = m_pstSpriteUIState[TextBoxNum].Base.w * 1.5f;
	m_pstSpriteUIState[TextBoxNum].Disp.h = m_pstSpriteUIState[TextBoxNum].Base.h * 1.5f;

	//ポーズ時の文字.
	int PauseStringNum = static_cast<int>(enSpriteUI::Pause);
	for(int pause = PauseStringNum; pause <= static_cast<int>(enSpriteUI::NextTitle); pause++){
		m_pstSpriteUIState[pause].Base.w = 500.0f;
		m_pstSpriteUIState[pause].Base.h = 218.0f;
		m_pstSpriteUIState[pause].Disp.w = m_pstSpriteUIState[pause].Base.w;
		m_pstSpriteUIState[pause].Disp.h = m_pstSpriteUIState[pause].Base.h;
	}

	//ビッグゴーストアイコン番号.
	int BigGhostIconNum = static_cast<int>(enSpriteUI::BigGhostIcon);
	m_pstSpriteUIState[BigGhostIconNum].Base.w = 311.0f;
	m_pstSpriteUIState[BigGhostIconNum].Base.h = 311.0f;
	m_pstSpriteUIState[BigGhostIconNum].Disp.w = 150;
	m_pstSpriteUIState[BigGhostIconNum].Disp.h = 150;

	//コメント.
	const int CommentNum = static_cast<int>(enSpriteUI::DispPaintGhostComment);
	for (int comment = CommentNum; comment <= static_cast<int>(enSpriteUI::SwitchGhostComment); comment++) {
		m_pstSpriteUIState[comment].Base.w = 460.0f;
		m_pstSpriteUIState[comment].Base.h = 180.0f;
		m_pstSpriteUIState[comment].Disp.w = 230.0f;
		m_pstSpriteUIState[comment].Disp.h = 90.0f;
	}

	//矢印.
	const int ArrowNum = static_cast<int>(enSpriteUI::Arrow);
	m_pstSpriteUIState[ArrowNum].Base.w = 504.0f;
	m_pstSpriteUIState[ArrowNum].Base.h = 273.0f;
	m_pstSpriteUIState[ArrowNum].Disp.w = 504.0f;
	m_pstSpriteUIState[ArrowNum].Disp.h = 273.0f;

	//お化け.
	int GhostIconNum = static_cast<int>(enSpriteUI::Ghost_Icon);
	m_pstSpriteUIState[GhostIconNum].Base.w = 3580.0f;
	m_pstSpriteUIState[GhostIconNum].Base.h = 3580.0f;
	m_pstSpriteUIState[GhostIconNum].Stride.w = m_pstSpriteUIState[GhostIconNum].Base.w / 3.0f;
	m_pstSpriteUIState[GhostIconNum].Stride.h = m_pstSpriteUIState[GhostIconNum].Base.h / 3.0f;
	m_pstSpriteUIState[GhostIconNum].Disp.w = 64.0f;
	m_pstSpriteUIState[GhostIconNum].Disp.h = 64.0f;

	//時間.
	int TimeNum = static_cast<int>(enSpriteUI::Time);
	m_pstSpriteUIState[TimeNum].Base.w = 1020.0f;
	m_pstSpriteUIState[TimeNum].Base.h = 120.0f;
	m_pstSpriteUIState[TimeNum].Stride.w = m_pstSpriteUIState[TimeNum].Base.w / 11.5f;
	m_pstSpriteUIState[TimeNum].Stride.h = m_pstSpriteUIState[TimeNum].Base.h;
	m_pstSpriteUIState[TimeNum].Disp.w = 50.0f;
	m_pstSpriteUIState[TimeNum].Disp.h = 50.0f;

	//木の板.
	int TreeBordNum = static_cast<int>(enSpriteUI::TreeBord);
	m_pstSpriteUIState[TreeBordNum].Base.w = 3318.0f;
	m_pstSpriteUIState[TreeBordNum].Base.h = 2305.0f;
	m_pstSpriteUIState[TreeBordNum].Stride.w = m_pstSpriteUIState[TreeBordNum].Base.w / 3.0f;
	m_pstSpriteUIState[TreeBordNum].Stride.h = m_pstSpriteUIState[TreeBordNum].Base.h / 3.0f;
	m_pstSpriteUIState[TreeBordNum].Disp.w = 300.0f;
	m_pstSpriteUIState[TreeBordNum].Disp.h = 150.0f;

	//お化けのカーソル.
	int GhostCursor = static_cast<int>(enSpriteUI::GhostCursor);
	m_pstSpriteUIState[GhostCursor].Base.w = 1600.0f;
	m_pstSpriteUIState[GhostCursor].Base.h = 1600.0f;
	m_pstSpriteUIState[GhostCursor].Stride.w = m_pstSpriteUIState[GhostCursor].Base.w / 2.0f;
	m_pstSpriteUIState[GhostCursor].Stride.h = m_pstSpriteUIState[GhostCursor].Base.h / 2.0f;
	m_pstSpriteUIState[GhostCursor].Disp.w =100.0f;
	m_pstSpriteUIState[GhostCursor].Disp.h =100.0f;

	//吹き出し.
	int BalloonNum = static_cast<int>(enSpriteUI::Balloon);
	m_pstSpriteUIState[BalloonNum].Base.w = 1755.0f;
	m_pstSpriteUIState[BalloonNum].Base.h = 1754.0f;
	m_pstSpriteUIState[BalloonNum].Stride.w = m_pstSpriteUIState[BalloonNum].Base.w / 2.0f;
	m_pstSpriteUIState[BalloonNum].Stride.h = m_pstSpriteUIState[BalloonNum].Base.h / 2.0f;
	m_pstSpriteUIState[BalloonNum].Disp.w = 300.0f;
	m_pstSpriteUIState[BalloonNum].Disp.h = 300.0f;

	//全てのスプライトの1コマ当たりのサイズ.
	for (int spriteui = 0; spriteui < static_cast<int>(enSpriteUI::SingleSpriteMax); spriteui++) {
		m_pstSpriteUIState[spriteui].Stride.w = m_pstSpriteUIState[spriteui].Base.w;
		m_pstSpriteUIState[spriteui].Stride.h = m_pstSpriteUIState[spriteui].Base.h;
	}
}

//============================================.
//		当たり判定用スフィア作成処理関数.
//============================================.
HRESULT CResourceManager::InitSphere()
{
	//メッシュ番号.
	const int	MeshNo = static_cast<int>(enStaticMeshType::HitSphere);
	//スフィアメッシュ.
	CDX9Mesh*	m_pCHitSphere = m_pCStaticMesh->GetMeshObject(enStaticMeshType::HitSphere);

	LPDIRECT3DVERTEXBUFFER9 pVB			= nullptr;		//頂点バッファ.
	void*					pVertices	= nullptr;		//頂点.
	D3DXVECTOR3				vCenter;					//中心.
	float					fRadius;					//半径.

	//頂点バッファを取得.
	if (FAILED(m_pCHitSphere->GetMesh()->GetVertexBuffer(&pVB))){
		return E_FAIL;
	}

	//メッシュの頂点バッファをロックする.
	if (FAILED(pVB->Lock(0, 0, &pVertices, 0))) {
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}

	//メッシュの外接円と中心の半径を計算する.
	D3DXComputeBoundingSphere(
		static_cast<D3DXVECTOR3*>(pVertices),						
		m_pCHitSphere->GetMesh()->GetNumVertices(),					//頂点の数.
		D3DXGetFVFVertexSize(m_pCHitSphere->GetMesh()->GetFVF()),	//頂点情報.
		&vCenter,													//(out)中心座標.			
		&fRadius);													//(out)半径.

	//アンロック.
	pVB->Unlock();
	SAFE_RELEASE(pVB);

	//中心と半径を構造体に設定.
	m_pCHitSphere->m_Sphere.vCenter = vCenter;
	m_pCHitSphere->m_Sphere.fRadius = fRadius;

	return S_OK;
}