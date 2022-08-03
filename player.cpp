#include "Player.h"

Player::Player()
{
	playerX = 400;
	playerY = 600;
	playerR = 16;

	playerSpeed = 5;
}

Player::~Player()
{
}

void Player::PlayerControl(char* key, char* oldkey)
{
	if (key[KEY_INPUT_W] == 1)
	{
		playerY += -playerSpeed;
	}
	if (key[KEY_INPUT_A] == 1)
	{
		playerX += -playerSpeed;
	}
	if (key[KEY_INPUT_S] == 1)
	{
		playerY += playerSpeed;
	}
	if (key[KEY_INPUT_D] == 1)
	{
		playerX += playerSpeed;
	}
}

void Player::Draw()
{
	/*DrawBox(playerX - playerR, playerY - playerR, playerX + playerR, playerY + playerR, GetColor(255, 255, 255), TRUE);*/
	DrawCircle(playerX, playerY, playerR, GetColor(255, 255, 255), TRUE);
}
