#include "Camera.h"

Camera::Camera()
{
	// カメラ本体
	cameraX = 400;
	cameraY = 400;
	cameraR = 16;

	//カメラの視界
	cameraVisionX[0] =  50;
	cameraVisionY[0] = 160;

	cameraVisionX[1] = -50;
	cameraVisionY[1] = 160;

	speed = 1;
	//視界移動の記録用
	for (int i = 0; i < 2; i++)
	{
		visionMemoryX[i] = 0;
		visionMemoryY[i] = 0;
	}
	//視界の移動を制御するフラグ
	visionFlag = 0;
	//視界の当たり判定用フラグ
	visionHitFlag[2] = {};
	//視界が再び動くまでのタイマー
	visionTimer = 15.0f;
}

Camera::~Camera()
{
}

void Camera::VisionMove()
{

#pragma region 回転処理
	if (visionFlag == 0)
	{
		//座標を回転させる
		for (int i = 0; i < 2; i++)
		{
			visionMemoryX[i] = cameraVisionX[i] * cos(PI / 180 * 1) - cameraVisionY[i] * sin(PI / 180 * 1);
			visionMemoryY[i] = cameraVisionX[i] * sin(PI / 180 * 1) + cameraVisionY[i] * cos(PI / 180 * 1);
		}
	}
	else if (visionFlag == 1)
	{
		//座標を回転させる
		for (int i = 0; i < 2; i++)
		{
			visionMemoryX[i] = cameraVisionX[i] * cos(PI / 180 * 1) - cameraVisionY[i] * -sin(PI / 180 * 1);
			visionMemoryY[i] = cameraVisionX[i] * -sin(PI / 180 * 1) + cameraVisionY[i] * cos(PI / 180 * 1);
		}
	}
	
#pragma endregion
	//角度決め
	if (visionFlag == 0 && cameraVisionX[0] <= 113.6 && cameraVisionY[0] <= 112.6)
	{
		visionFlag = 3;
	}

	if (visionFlag == 1 && cameraVisionX[1] >= -112.7 && cameraVisionY[1] <= 113.5)
	{
		visionFlag = 4;
	}
	//----------------------------------
#pragma region 視界が動くまでのタイマーの処理
	if (visionFlag == 3)
	{
		visionTimer--;
		if (visionTimer < 0)
		{
			visionFlag = 1;
			visionTimer = 15.0f;
		}
	}
	if (visionFlag == 4)
	{
		visionTimer--;
		if (visionTimer < 0)
		{
			visionFlag = 0;
			visionTimer = 15.0f;
		}
	}
	if (visionFlag == 5)
	{
		visionTimer--;
		if (visionTimer < 0)
		{
			cameraVisionX[0] = 50;
			cameraVisionY[0] = 160;

			cameraVisionX[1] = -50;
			cameraVisionY[1] = 160;
			visionFlag = rand() % 2;
			visionTimer = 15.0f;
		}
	}
#pragma endregion
	//----------------------------------
	//移動させる
	for (int i = 0; i < 2; i++)
	{
		cameraVisionX[i] = visionMemoryX[i];
		cameraVisionY[i] = visionMemoryY[i];
	}
}

void Camera::VisionVector(float playerX, float playerY, float playerR)
{
	//それぞれのベクトル
	VECTOR vec[3];	//線
	VECTOR vecPlayer[4];	//Playerまでのベクトル
#pragma region 視界のベクトル
	//左右ラインベクトル
	for (int i = 0; i < 2; i++)
	{
		vec[i].x = (cameraVisionX[i] + cameraX) - cameraX;
		vec[i].y = (cameraVisionY[i] + cameraY) - cameraY;
		vec[i].z = 0;
		vec[i] = VNorm(vec[i]);
	}
	//最終点から最終点までのベクトル
	vec[2].x = (cameraVisionX[1] + cameraX) - (cameraVisionX[0] + cameraX);
	vec[2].y = (cameraVisionY[1] + cameraY) - (cameraVisionY[0] + cameraY);
	vec[2].z = 0;
	vec[2] = VNorm(vec[2]);
#pragma endregion
#pragma region 各視界の始まりからPlayerまでのベクトル
	//右ラインからPlayerのベクトル
	vecPlayer[0].x = (playerX - playerR) - cameraX;
	vecPlayer[0].y = playerY - cameraY;
	vecPlayer[0].z = 0;
	vecPlayer[0] = VNorm(vecPlayer[0]);
	//左ラインからPlayerのベクトル
	vecPlayer[1].x = (playerX + playerR) - cameraX;
	vecPlayer[1].y = playerY - cameraY;
	vecPlayer[1].z = 0;
	vecPlayer[1] = VNorm(vecPlayer[1]);
	//限界点[0]からPlayerのベクトル
	vecPlayer[2].x = playerX - (cameraVisionX[0] + cameraX);
	vecPlayer[2].y = (playerY - playerR) - (cameraVisionY[0] + cameraY);
	vecPlayer[2].z = 0;
	vecPlayer[2] = VNorm(vecPlayer[2]);
	//限界点[1]からPlayerのベクトル
	vecPlayer[3].x = playerX - (cameraVisionX[1] + cameraX);
	vecPlayer[3].y = (playerY - playerR) - (cameraVisionY[1] + cameraY);
	vecPlayer[3].z = 0;
	vecPlayer[3] = VNorm(vecPlayer[3]);
#pragma endregion
	//当たり判定
	//右ラインベクトルの判定
	if (vec[0].x * vecPlayer[0].y - vec[0].y * vecPlayer[0].x > 0)
	{
		visionHitFlag[0] = 1;
	}
	else
	{
		visionHitFlag[0] = 0;
	}
	//左ラインベクトルの判定
	if (vec[1].x * vecPlayer[1].y - vec[1].y * vecPlayer[1].x < 0)
	{
		visionHitFlag[1] = 1;
	}
	else
	{
		visionHitFlag[1] = 0;
	}
	//視界限界点の判定
	if (vec[2].x * vecPlayer[2].y - vec[2].y * vecPlayer[2].x > 0)
	{
		visionHitFlag[2] = 1;
	}
	else
	{
		visionHitFlag[2] = 0;
	}
#pragma region 視界に入った時の処理
	if (visionHitFlag[0] == 1 && visionHitFlag[1] == 1 && visionHitFlag[2] == 1)
	{
		visionFlag = 5;
		if (visionFlag == 5 && vecPlayer[2].x != vecPlayer[3].x)
		{
			if (vecPlayer[3].x-0.001 >= -vecPlayer[2].x)
			{
				//座標を回転させる
				for (int i = 0; i < 2; i++)
				{
					visionMemoryX[i] = cameraVisionX[i] * cos(PI / 180 * 1) - cameraVisionY[i] * -sin(PI / 180 * 1);
					visionMemoryY[i] = cameraVisionX[i] * -sin(PI / 180 * 1) + cameraVisionY[i] * cos(PI / 180 * 1);
				}
			}
			else if (-vecPlayer[2].x-0.001 >= vecPlayer[3].x)
			{
				//座標を回転させる
				for (int i = 0; i < 2; i++)
				{
					visionMemoryX[i] = cameraVisionX[i] * cos(PI / 180 * 1) - cameraVisionY[i] * sin(PI / 180 * 1);
					visionMemoryY[i] = cameraVisionX[i] * sin(PI / 180 * 1) + cameraVisionY[i] * cos(PI / 180 * 1);
				}
			}
		}

	}
#pragma endregion
	
	DrawFormatString(0,40, GetColor(255, 255, 255), "視界からPlayerまでの距離[%f][%f]",-vecPlayer[2].x,vecPlayer[3].x );
}

void Camera::Draw()
{
	
	DrawPixel(cameraVisionX[0]+cameraX, cameraVisionY[0]+cameraY, GetColor(255, 255, 255));
	DrawPixel(cameraVisionX[1]+cameraX, cameraVisionY[1]+cameraY, GetColor(255, 255, 255));
	if (visionHitFlag[0] == 1 && visionHitFlag[1] == 1 && visionHitFlag[2] == 1)
	{
		for (int i = 0; i < 2; i++)
		{
			DrawLine(cameraX, cameraY, cameraVisionX[i] + cameraX, cameraVisionY[i] + cameraY, GetColor(255, 0, 0), TRUE);
		}
		DrawLine(cameraVisionX[0] + cameraX, cameraVisionY[0] + cameraY, cameraVisionX[1] + cameraX, cameraVisionY[1] + cameraY, GetColor(255, 0, 0), TRUE);
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			DrawLine(cameraX, cameraY, cameraVisionX[i] + cameraX, cameraVisionY[i] + cameraY, GetColor(255, 255, 255), TRUE);
		}
		DrawLine(cameraVisionX[0] + cameraX, cameraVisionY[0] + cameraY, cameraVisionX[1] + cameraX, cameraVisionY[1] + cameraY, GetColor(255, 255, 255), TRUE);
	}

	DrawBox(cameraX - cameraR, cameraY - cameraR, cameraX + cameraR, cameraY + cameraR, GetColor(255, 255, 255), FALSE);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "視界の座標[0][x=%f][y=%f]\n視界の座標[1][x=%f][y=%f]\n", cameraVisionX[0], cameraVisionY[0], cameraVisionX[1], cameraVisionY[1]);
}
