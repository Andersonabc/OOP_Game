#ifndef SASUKEFIREBALL_H
#define SASUKEFIREBALL_H
#include "Shoot.h"
namespace game_framework {
	class SasukeFireball : public Shoot
	{
	public:
		SasukeFireball(int _x, int _y, int _direction);
		void Init(int _x, int _y, int _direction);
		int GetX1();					// 擦子左上角 x 座標
		int GetY1();					// 擦子左上角 y 座標
		int GetX2();
		int GetY2();
		int Getdirection();
		void AddPic();				// 載入圖形
		void OnShow();
		void Move();
		void SetXY(int _x, int _y);
	};

}
#endif
