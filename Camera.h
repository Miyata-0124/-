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
	float cameraX;	//�J�����{�̂̍��W
	float cameraY;
	float cameraR;

	float cameraVisionX[2];	//�J�����̎��E
	float cameraVisionY[2];

	float visionMemoryX[2];	//���E�ړ��̋L���ϐ�
	float visionMemoryY[2];

	int visionFlag = 0;

	float visionTimer;
};
