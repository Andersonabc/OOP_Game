#ifndef SASUKEFIREBALL_H
#define SASUKEFIREBALL_H
#include "Shoot.h"
namespace game_framework {
	class SasukeFireball : public Shoot
	{
	public:
		SasukeFireball(int _x, int _y, int _direction);
		void Init(int _x, int _y, int _direction);
		int GetX1();					// ���l���W�� x �y��
		int GetY1();					// ���l���W�� y �y��
		int GetX2();
		int GetY2();
		int Getdirection();
		void AddPic();				// ���J�ϧ�
		void OnShow();
		void Move();
		void SetXY(int _x, int _y);
	};

}
#endif
