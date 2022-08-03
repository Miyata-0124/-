#pragma once
#include "DxLib.h"
class Player
{
public:
	Player();
	~Player();
	void PlayerControl(char* key, char* oldkey);
	void Draw();
public:
	float playerX;		//プレイヤーの座標
	float playerY;
	float playerR;

	float playerSpeed;	//速度
};
