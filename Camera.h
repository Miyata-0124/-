#pragma once
#include "DxLib.h"
#include <math.h>
#define PI 3.14

class Camera
{
public:
	Camera();
	~Camera();
	void VisionMove(); //���E�𓮂����֐�
	void VisionVector(float playerX, float playerY, float playerR); //���ꂼ��̃x�N�g���𓾂�֐�
	void Draw();
private:
	float cameraX;	//�J�����{�̂̍��W
	float cameraY;
	float cameraR;

	float cameraVisionX[2];	//�J�����̎��E
	float cameraVisionY[2];

	float visionMemoryX[2];	//���E�ړ��̋L���ϐ�
	float visionMemoryY[2];

	int visionFlag; //���E�̈ړ��𐧌䂷��t���O
	int visionHitFlag[3]; //���E�̓����蔻��p�t���O

	int speed;

	float visionTimer; //���E���Ăѓ����܂ł̃^�C�}�[
};
