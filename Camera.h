#pragma once
#include "DxLib.h"
#include <math.h>
#define PI 3.14

class Camera
{
public:
	Camera();
	~Camera();
	void VisionMove(); //視界を動かす関数
	void VisionVector(float playerX, float playerY, float playerR); //それぞれのベクトルを得る関数
	void Draw();
private:
	float cameraX;	//カメラ本体の座標
	float cameraY;
	float cameraR;

	float cameraVisionX[2];	//カメラの視界
	float cameraVisionY[2];

	float visionMemoryX[2];	//視界移動の記憶変数
	float visionMemoryY[2];

	int visionFlag; //視界の移動を制御するフラグ
	int visionHitFlag[3]; //視界の当たり判定用フラグ

	int speed;

	float visionTimer; //視界が再び動くまでのタイマー
};
