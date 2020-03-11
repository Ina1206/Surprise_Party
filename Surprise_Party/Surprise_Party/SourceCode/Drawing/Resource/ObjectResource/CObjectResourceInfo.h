#ifndef COBJECT_RESOURCE_INFO_H
#define COBJECT_RESOURCE_INFO_H

//スタティックメッシュの種類.
enum class enStaticMeshType {
	Wall,				//壁.
	Floor,				//床.
	Painting,			//絵画.
	BookShelf,			//本棚.
	MoveObjectSwitch,	//オブジェクト移動スイッチ.
	PlaySoundSwitch,	//音が鳴るスイッチ.
	SwitchPushGhost,	//スイッチを押すお化け.
	Phone,				//携帯.
	HitSphere,			//当たり判定用スフィア.
	Table,				//机.
	Vase_Flower,		//花瓶.

	Max,		//最大値.
	Start = Wall,
};

//スキンメッシュの種類.
enum class enSkinMeshType {
	Girl,				//女の子.
	Boy,				//男の子.
	DispGhost,			//現れるお化け.
	BigGhost,			//大きいお化け.
	Max,				//最大値.
};

//テクスチャ変更オブジェ.
enum class enSkinTexChange {
	Girl,	//女の子.
	Max
};

#endif	//#ifndef COBJECT_RESOURCE_INFO_H.