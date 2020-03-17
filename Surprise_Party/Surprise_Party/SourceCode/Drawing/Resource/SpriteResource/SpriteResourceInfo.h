#ifndef SPRITE_RESOURCE_INFO_H
#define SPRITE_RESOURCE_INFO_H

//幅高さ構造体(float型).
struct WHSIZE_FLOAT
{
	float w;
	float h;
	float z;

	WHSIZE_FLOAT()
		: w(0.0f)
		, h(0.0f)
		, z(0.0f)
	{}
};

//スプライト毎の構造体.
struct SPRITE_STATE
{
	WHSIZE_FLOAT	Disp;	//表示幅高さ.
	WHSIZE_FLOAT	Base;	//元画像幅高さ.
	WHSIZE_FLOAT	Stride;	//1コマ当たりの幅高さ.
};

//スプライト種類の列挙体.
enum class enSprite
{
	Cursol = 0,						//カーソル.
	ActSelection,					//行動選択.
	ActMoveString,					//移動文字.
	ActRestString,					//休憩文字.
	Bubble,							//泡.
	SleepZ,							//睡眠のz
	Swet,							//汗.

	Strenght_Icon,					//体力アイコン.
	eight_part_note,				//8分音符.
	sixteen_part_note,				//16分音符.

	Max,
	Start,
	SingleSpriteMax = Strenght_Icon,//単体スプライト最大数.
};

//スプライトUI種類の列挙体.
enum class enSpriteUI
{
	StageMap = 0,					//ステージマップ.
	Girl_Icon,						//女の子のアイコン.
	Boy_Icon,						//男の子のアイコン.
	DispGimmick_Iccon,				//現れるギミックアイコン.
	Switch_Icon,					//スイッチアイコン.
	ButtonPush,						//ボタン押したとき.
	ClosedString,					//閉店までの文字.
	GageGround,						//ゲージの下地.
	Gage,							//ゲージ.
	ThankYouStamp,					//満員御礼ハンコ.
	Shutter,						//シャッター.
	BlackCurtain,					//黒カーテン.
	SignBoard,						//看板.
	PreparingString,				//準備中文字.
	OpenString,						//Open文字.
	CloseString,					//Close文字.
	ExtendedNotification,			//延長通知.

	Ghost_Icon,						//お化けアイコン.
	Time,							//時間.
	TreeBord,						//木の板.

	Max,							//最大数.
	Start,							//開始.
	SingleSpriteMax = Ghost_Icon,	//単体のスプライト最大数.
};

#endif //#ifndef SPRITE_RESOURCE_INFO_H