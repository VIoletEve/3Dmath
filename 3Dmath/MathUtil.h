#pragma once

#include <math.h>

//Բ����
const float kPi = 3.14159265f;
const float k2Pi = kPi * 2.0f;
const float kpiOver2 = kPi / 2.0f;
const float k1OverPi = 1.0f / kPi;
const float k1Over2Pi = 1.0f / k2Pi;

//���Ƕ�������-pi��pi������
extern float wrapPi(float theta);

//��ȫ�����Ǻ���
extern float safeAcos(float x);

inline void sinCos(float* returnSin, float* returnCos, float theta) {
	*returnSin = sin(theta);
	*returnCos = cos(theta);
}

