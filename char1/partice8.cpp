#include <iostream>
#include <Windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

int main()
{
	XMVECTOR u = XMVectorSet(-1.0f, 3.0f, 2.0f, 0.0f);
	XMVECTOR v = XMVectorSet(3.0f, -4.0f, 1.0f, 0.0f);
	XMVECTOR angleVec = XMVector3AngleBetweenVectors(u, v);
	float angleRadians = XMVectorGetX(angleVec);
	float angleDegrees = XMConvertToDegrees(angleRadians);
	cout << angleDegrees << endl;
}