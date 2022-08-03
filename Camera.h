#pragma once
#include "DxLib.h"
#include <math.h>
#define PI 3.14

class Camera
{
public:
	Camera();
	~Camera();
	void VisionMove();
	void Draw();
private:
	float cameraX;	//カメラ本体の座標
	float cameraY;
	float cameraR;

	float cameraVisionX[2];	//カメラの視界
	float cameraVisionY[2];

	float visionMemoryX[2];	//視界移動の記憶変数
	float visionMemoryY[2];

	int visionFlag = 0;

	float visionTimer;
};
