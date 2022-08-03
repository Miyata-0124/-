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

	//視界移動の記録用
	for (int i = 0; i < 2; i++)
	{
		visionMemoryX[i] = 0;
		visionMemoryY[i] = 0;
	}

	//視界が動くまでのタイマー
	visionTimer = 15.0f;
}

Camera::~Camera()
{
}

void Camera::VisionMove()
{
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
	//移動させる
	for (int i = 0; i < 2; i++)
	{
		cameraVisionX[i] = visionMemoryX[i];
		cameraVisionY[i] = visionMemoryY[i];
	}
	if (visionFlag == 0 && cameraVisionX[0] <= 113.6 && cameraVisionY[0] <= 112.6)
	{
		visionFlag = 3;
	}

	if (visionFlag == 1 && cameraVisionX[1] >= -112.7 && cameraVisionY[1] <= 113.5)
	{
		visionFlag = 4;
	}
	
	if (visionFlag == 3)
	{
		visionTimer--;
		if (visionTimer < 0)
		{
			visionFlag = 1;
			visionTimer = 15.0f;
		}
	}
}

void Camera::Draw()
{
	
	DrawPixel(cameraVisionX[0]+cameraX, cameraVisionY[0]+cameraY, GetColor(255, 255, 255));
	DrawPixel(cameraVisionX[1]+cameraX, cameraVisionY[1]+cameraY, GetColor(255, 255, 255));
	for (int i = 0; i < 2; i++)
	{
		DrawLine(cameraX, cameraY, cameraVisionX[i]+cameraX, cameraVisionY[i]+cameraY, GetColor(255, 255, 255), TRUE);
	}
	DrawLine(cameraVisionX[0] + cameraX, cameraVisionY[0] + cameraY, cameraVisionX[1] + cameraX, cameraVisionY[1] + cameraY, GetColor(255, 255, 255), TRUE);
	
	DrawBox(cameraX - cameraR, cameraY - cameraR, cameraX + cameraR, cameraY + cameraR, GetColor(255, 255, 255), FALSE);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "視界の座標[0][x=%f][y=%f]\n視界の座標[1][x=%f][y=%f]\n", cameraVisionX[0], cameraVisionY[0], cameraVisionX[1], cameraVisionY[1]);
}
