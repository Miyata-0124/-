#pragma once
#include "DxLib.h"
class Player
{
public:
	Player();
	~Player();
	void PlayerControl(char* key, char* oldkey);
	void Draw();
private:
	float playerX;		//�v���C���[�̍��W
	float playerY;
	float playerR;

	float playerSpeed;	//���x
};
